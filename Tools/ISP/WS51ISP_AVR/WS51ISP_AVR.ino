/*Rewritten using Poe(ChatGPT)
  Modified some details:
  Disabled STM32 UART output(Arduino UNO does not have dual UART)
  Using LED Pin for SDA(so you can see the data)

  Tested - works under 3V3 (Overclocking to 16MHz with atmega328pb)
  Debugged by SunnyA.I.

  WS51 Loader - Arduino Uno rewrite (Serial + bit-banged ISP)

  Original STM32 code used USB CDC and direct USB endpoint registers.
  Arduino Uno does NOT have that USB device peripheral, so we:
  - Replace CDC with Serial (UART) on USB-to-Serial chip.
  - Keep the same command protocol:
      'S' : sync
      'E' : erase
      'P' : program (512 bytes payload)
      'R' : reset/run

  Target ISP (bit-banged):
    - SCLK: clock line to target ISP
    - DATA: bi-directional line (we bit-bang reads/writes)
    - RST : target reset line
    - PWR : target power enable line (if used by your circuit)
*/

#include <Arduino.h>

// ------------------------------
// User-configurable pin mapping
// ------------------------------
#define PIN_SCLK  12   // ISP clock output (Arduino pin)
#define PIN_DATA  13   // ISP data (must support input + output)
#define PIN_RST   7   // target reset output (Not required.)
#define PIN_PWR   5   // target power enable output (if your target needs it)
//#define PIN_LED   13  // optional onboard LED

// ------------------------------
// Timing helpers
// ------------------------------
// The STM32 code approximated 1us delays using NOP at 72MHz.
// On Arduino Uno (16MHz), we approximate using delayMicroseconds().
//
// If you find timing issues, tell me your target ISP requirements,
// and I can calibrate (or implement a cycle-accurate busy loop).
static inline void delay_1us(uint32_t us) {
  while (us--) {
    delayMicroseconds(1);
  }
}

static void delay_ms_blocking(uint32_t ms);

// ------------------------------
// UART helpers (replacing CDC)
// ------------------------------
static int uart_getc_blocking() {
  // Wait for next byte.
  while (!Serial.available()) {
    // In STM32 code usb_poll() happened; on Uno we just wait.
    // You may add watchdog-friendly yields here if desired.
  }
  return Serial.read();
}

static uint8_t uart_getc_u8() {
  return (uint8_t)uart_getc_blocking();
}

static void uart_putc(char c) {
  Serial.write((uint8_t)c);
}

static void uart_puts(const char *s) {
  while (*s) uart_putc(*s++);
}

static void uart_puthex8(uint8_t b) {
  const char hex[] = "0123456789ABCDEF";
  uart_putc(hex[b >> 4]);
  uart_putc(hex[b & 0x0F]);
}

static void uart_puthex16(uint16_t w) {
  uart_puthex8((uint8_t)(w >> 8));
  uart_puthex8((uint8_t)(w & 0xFF));
}

// ------------------------------
// ISP GPIO line operations
// ------------------------------

// SCLK high/low
static inline void SCLK_H() { digitalWrite(PIN_SCLK, HIGH); }
static inline void SCLK_L() { digitalWrite(PIN_SCLK, LOW);  }

// DATA high/low
// Important: DATA is bidirectional, so for reads we set it to INPUT.
// For writes we set it to OUTPUT and drive.
static inline void DATA_as_output() { pinMode(PIN_DATA, OUTPUT); }
static inline void DATA_as_input()  { pinMode(PIN_DATA, INPUT);  }

static inline void DATA_H() { digitalWrite(PIN_DATA, HIGH); } // only valid when OUTPUT
static inline void DATA_L() { digitalWrite(PIN_DATA, LOW);  } // only valid when OUTPUT

static inline uint8_t DATA_R() {
  // only meaningful when PIN_DATA is INPUT
  return (digitalRead(PIN_DATA) ? 1 : 0);
}

// Reset & power controls
static inline void RST_L() { digitalWrite(PIN_RST, LOW); }
static inline void RST_H() { digitalWrite(PIN_RST, HIGH); }
static inline void PWR_L() { digitalWrite(PIN_PWR, LOW); }
static inline void PWR_H() { digitalWrite(PIN_PWR, HIGH); }

//static inline void LED_ON()  { digitalWrite(PIN_LED, HIGH); }  // depending on board
//static inline void LED_OFF() { digitalWrite(PIN_LED, LOW); }

// ------------------------------
// ISP protocol bit-banging
// ------------------------------
/*
  The original STM32 code uses:
    isp_start()
    isp_stop()
    isp_send_byte(data)  + isp_read_ack()
    isp_read_byte()

  We keep same logical steps but implement GPIO reads/writes
  with Arduino functions.
*/

static void isp_start(void) {
  // Equivalent to STM32:
  // DATA_H; SCLK_H;
  // delay(2us); DATA_L; delay(1us); SCLK_L;
  DATA_as_output();
  DATA_H();
  SCLK_H();
  delay_1us(2);

  DATA_L();
  delay_1us(1);

  SCLK_L();
  delay_1us(1);
}

static void isp_stop(void) {
  // Equivalent to STM32:
  // SCLK_L; DATA_L;
  // delay(1us); SCLK_H; delay(1us); DATA_H; delay(2us);
  DATA_as_output();
  SCLK_L();
  DATA_L();
  delay_1us(1);

  SCLK_H();
  delay_1us(1);

  DATA_H();
  delay_1us(2);
}

static void isp_send_byte(uint8_t data) {
  // Sends MSB first (bit 7 -> bit 0).
  // For each bit:
  //   - set DATA to 1 or 0
  //   - short delays
  //   - pulse SCLK high then low
  DATA_as_output();

  for (int i = 0; i < 8; i++) {
    if (data & 0x80) DATA_H();
    else               DATA_L();

    delay_1us(1);
    SCLK_H();
    delay_1us(1);
    SCLK_L();

    data <<= 1;
  }
}

static int isp_read_ack(void) {
  // Reads a single ACK bit from target.
  // Original logic:
  //   DATA_H; delay(1); SCLK_H; delay(1); ack = DATA_R; SCLK_L; delay(1)
  DATA_as_output();
  DATA_H();          // ensure line is released high; then clock.
  delay_1us(1);

  SCLK_H();
  delay_1us(1);

  // ACK is sampled by reading DATA pin.
  DATA_as_input();
  int ack = DATA_R();

  SCLK_L();
  delay_1us(1);

  // After reading, keep it safe:
  DATA_as_output();
  return ack;
}

static void isp_clock_pulse(void) {
  // Original:
  //   DATA_H; delay(1); SCLK_H; delay(1); SCLK_L; delay(1)
  DATA_as_output();
  DATA_H();
  delay_1us(1);

  SCLK_H();
  delay_1us(1);

  SCLK_L();
  delay_1us(1);
}

static uint8_t isp_read_byte(void) {
  // Reads 8 bits, MSB first, shifting into result.
  uint8_t result = 0;

  // Original begins with:
  //   result = 0;
  //   DATA_H; delay(2);
  //   for each bit:
  //     SCLK_H; delay(2); result = (result<<1) | (DATA_R ? 1 : 0); SCLK_L; delay(2)
  //
  // Then: DATA_H; delay(2); SCLK_H; delay(2); SCLK_L; delay(2);
  DATA_as_output();
  DATA_H();
  delay_1us(2);

  DATA_as_input();

  for (int i = 0; i < 8; i++) {
    SCLK_H();
    delay_1us(2);

    result = (uint8_t)((result << 1) | (DATA_R() ? 1 : 0));

    SCLK_L();
    delay_1us(2);
  }

  DATA_as_output();
  DATA_H();
  delay_1us(2);

  SCLK_H();
  delay_1us(2);

  SCLK_L();
  delay_1us(2);

  return result;
}

static void isp_send_3bytes(uint8_t b1, uint8_t b2, uint8_t b3) {
  isp_start();
  isp_send_byte(b1); isp_read_ack();
  isp_send_byte(b2); isp_read_ack();
  isp_send_byte(b3); isp_read_ack();
  isp_stop();
}

static void isp_wr_reg(uint8_t reg_hi, uint8_t reg_lo, uint8_t data) {
  // Write register: original uses start/send_byte/data/read_ack sequence.
  isp_start();
  isp_send_byte(data);   isp_read_ack();
  isp_send_byte(reg_hi); isp_read_ack();
  isp_send_byte(reg_lo); isp_read_ack();
  isp_stop();
}

static void isp_wr_word(uint8_t reg_hi, uint8_t reg_lo) {
  // Word write: original uses sending 0 first, then hi/lo with clock pulses.
  isp_start();
  isp_send_byte(0);      isp_read_ack();
  isp_send_byte(reg_hi); isp_clock_pulse();
  isp_send_byte(reg_lo); isp_clock_pulse();
  isp_stop();
}

static uint8_t isp_read_phase(uint8_t reg) {
  // Original read phase is two-step:
  // 1) send reg (with 0 first)
  // 2) send 1, then read a byte
  isp_start();
  isp_send_byte(0);   isp_read_ack();
  isp_send_byte(reg); isp_read_ack();
  isp_stop();

  isp_start();
  isp_send_byte(1);  isp_read_ack();
  uint8_t val = isp_read_byte();
  isp_stop();

  return val;
}

static uint8_t isp_rd_reg(uint8_t addr) {
  // Mirrors STM32:
  // isp_wr_reg(2, addr, 0);
  // isp_wr_reg(3, 0, 0);
  // return isp_read_phase(4);
  isp_wr_reg(2, addr, 0);
  isp_wr_reg(3, 0, 0);
  return isp_read_phase(4);
}

static uint8_t isp_rd_reg16(uint16_t addr) {
  isp_wr_reg(2, addr & 0xFF, 0);
  isp_wr_reg(3, (addr >> 8) & 0xFF, 0);
  return isp_read_phase(4);
}

static void isp_wr_reg_addr(uint8_t addr, uint8_t val) {
  isp_wr_reg(2, addr, 0);
  isp_wr_reg(3, 0, 0);
  isp_wr_reg(4, val, 0);
}

static void isp_wr_reg16(uint16_t addr, uint8_t val) {
  isp_wr_reg(2, addr & 0xFF, 0);
  isp_wr_reg(3, (addr >> 8) & 0xFF, 0);
  isp_wr_reg(4, val, 0);
}

static void isp_wr_flash(uint16_t addr, uint8_t data) {
  // Original:
  // isp_wr_reg(2, addr & 0xFF, 0);
  // isp_wr_reg(3, addr>>8, 0);
  // isp_wr_reg(5, data, 0);
  isp_wr_reg(2, addr & 0xFF, 0);
  isp_wr_reg(3, (addr >> 8) & 0xFF, 0);
  isp_wr_reg(5, data, 0);
}

static void wait_isp_ready(void) {
  // Original loops reading status register 0x8301 until bit0 clears.
  // We keep that logic; USB polling removed, so we just delay a bit.
  for (int i = 0; i < 2000; i++) {
    uint8_t status = isp_rd_reg16(0x8301);
    if (!(status & 0x01)) return;

    if (i % 200 == 0) {
      //uart_puts("Wait Busy... Status: ");
      uart_puthex8(status);
      //uart_puts("\n");
    }

    for (int j = 0; j < 10; j++) {
      delay_1us(100);
      // No usb_poll() equivalent on Uno.
    }
  }

  //uart_puts("Wait Timeout!\n");
}

// ------------------------------
// Higher-level loader commands
// ------------------------------
static int target_power_on(void) {
  //uart_puts("Target Power ON\n");

  // Original:
  // PWR_L; RST_L; delay_ms(200);
  // PWR_H; RST_H; RST_L;
  // RST_H; delay_ms(1);
  PWR_L();
  RST_L();
  delay_ms_blocking(200);

  PWR_H();
  RST_H();
  RST_L();

  RST_H();
  delay_ms_blocking(1);

  return 0;
}

static int isp_sync(void) {
  //uart_puts("Syncing...");

  // Original tries up to 200 times:
  //   isp_wr_word(0x1F, 0x75);
  //   isp_wr_word(0x1E, 0x6F);
  //   isp_wr_reg(1, 0xAA, 0);
  //   resp = isp_read_phase(1);
  //   if (resp & 0xF0) == 0x80 => success
  for (int retry = 0; retry <= 200; retry++) {
    isp_wr_word(0x1F, 0x75);
    isp_wr_word(0x1E, 0x6F);
    isp_wr_reg(1, 0xAA, 0);

    uint8_t resp = isp_read_phase(1);

    if (resp != 0xFF) {
      //uart_puts(" Resp: ");
      uart_puthex8(resp);
      //uart_puts("\n");
    }

    if ((resp & 0xF0) == 0x80) {
      //uart_puts("Sync Success!\n");
      return 0;
    }

    delay_ms_blocking(1);
  }

  //uart_puts("Sync Timeout\n");
  return 1;
}

static void do_erase(void) {
  //uart_puts("Erase Stage 1\n");
  isp_wr_flash(0x8304, 0x78);
  isp_wr_flash(0x8307, 0x07);
  isp_wr_flash(0x8306, 0x40);
  isp_wr_flash(0x8301, 0x81);

  //uart_puts("Erase Stage 2\n");
  isp_wr_flash(0x8304, 0x78);
  isp_wr_flash(0x8307, 0x07);
  isp_wr_flash(0x8306, 0x41);
  isp_wr_flash(0x8301, 0x81);

  //uart_puts("Erase Stage 3\n");
  isp_wr_flash(0x8304, 0x12);
  isp_wr_flash(0x8301, 0x04);

  // Original waits 120ms.
  delay_ms_blocking(120);

  //uart_puts("Erase Done\n");
}

static void do_reset_run(void) {
  // Mirrors STM32 reset/run sequence.
  isp_wr_reg(1, 0xAA, 0);

  uint8_t isp_contr = isp_rd_reg(0x87);
  isp_wr_reg_addr(0x87, (uint8_t)(isp_contr | 0x20));

  isp_wr_reg(1, 0x55, 0);
  isp_wr_word(0x1F, 0xF6);
  isp_wr_word(0x1E, 0x57);

  delay_ms_blocking(1);

  RST_L();
  delay_ms_blocking(1);
  RST_H();
}

static void cdc_puts_like(const char *s) {
  // Since we already use Serial, just reuse //uart_puts.
  uart_puts(s);
}

static void delay_ms_blocking(uint32_t ms) {
  // Wrapper for clarity; could also call ::delay(ms) directly.
  while (ms--) {
    delay(1);

    // The STM32 usb_poll() kept USB alive.
    // On Uno, we don't have USB device tasks; if you need streaming,
    // you can check Serial availability here.
  }
}

// ------------------------------
// Setup / loop
// ------------------------------
static uint8_t page_buf[512];

void setup() {
  pinMode(PIN_SCLK, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_RST, OUTPUT);
  pinMode(PIN_PWR, OUTPUT);
 // pinMode(PIN_LED, OUTPUT);

  // Initial idle levels (matching STM32 intent):
  SCLK_L();
  DATA_as_output();
  DATA_H();

  RST_L();
  PWR_L();
  //LED_OFF();

  // Serial baud must match your PC-side tool.
  // STM32 code used UART1 on STM32 with BRR=0x271 at 72MHz -> not directly mapped.
  // Common choices: 115200.
  Serial.begin(115200);

  //uart_puts("\n\n--- WS51 Loader Start (Arduino Uno Serial ISP) ---\n");
}

void loop() {
  // Wait for command byte from host.
  // (STM32 version did usb_poll() and consumed received CDC bytes.)
  if (Serial.available() <= 0) return;

  uint8_t cmd = (uint8_t)uart_getc_u8();

  if (cmd == 'S') {
    //uart_puts("CMD: Sync\n");

    if (target_power_on() == 0 && isp_sync() == 0) {
      // STM32 did:
      // cfg = isp_rd_reg(0xA1);
      // isp_wr_reg_addr(0xA1, cfg & 0xFC);
      uint8_t cfg = isp_rd_reg(0xA1);
      isp_wr_reg_addr(0xA1, (uint8_t)(cfg & 0xFC));

      cdc_puts_like("OK\n");
    } else {
      cdc_puts_like("FAIL\n");
    }
  }
  else if (cmd == 'E') {
    //uart_puts("CMD: Erase\n");
    do_erase();
    cdc_puts_like("OK\n");
  }
  else if (cmd == 'P') {
    // 'P' then 2 bytes: addr high, addr low
    uint16_t addr = ((uint16_t)uart_getc_u8() << 8) | uart_getc_u8();

    //uart_puts("CMD: Program @ ");
    //uart_puthex16(addr);
    //uart_puts("\n");

    // Read exactly 512 bytes into page_buf
    for (int i = 0; i < 512; i++) {
      page_buf[i] = uart_getc_u8();
    }

    // STM32 wrote setup registers:
    isp_wr_flash(0x8304, 0x34);
    isp_wr_flash(0x8302, 0xFF);
    isp_wr_flash(0x8307, (uint8_t)((addr >> 8) & 0xFF));
    isp_wr_flash(0x8306, (uint8_t)(addr & 0xFF));
    isp_wr_flash(0x8301, 0x06);

    // Then streamed each byte into flash data register
    for (int i = 0; i < 512; i++) {
      isp_wr_flash(0x8303, page_buf[i]);

      // STM32 inserted delay every 64 bytes:
      if ((i & 0x3F) == 0x3F) {
        delay_ms_blocking(1);
      }
    }

    // Final wait
    delay_ms_blocking(200);

    cdc_puts_like("OK\n");
  }
  else if (cmd == 'R') {
    //uart_puts("CMD: Reset\n");
    do_reset_run();
    cdc_puts_like("OK\n");
  }
  else {
    // Unknown command: ignore or send error.
    //uart_puts("Unknown CMD\n");
  }
}