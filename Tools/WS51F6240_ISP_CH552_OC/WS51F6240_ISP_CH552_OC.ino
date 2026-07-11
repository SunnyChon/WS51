/*

WS51F6240 ISP Programmer code for CH552G
Overclock version : ~100kHz Bit-bang I2C , 16KB/5s = ~25.6kbps

*/


/*Rewritten using Poe(ChatGPT)
  Over clock version by SunnyA.I.
  Modified some details:
  
  (Not suitable)Tested - works under 3V3 (Overclocking to 16MHz with atmega328pb) / -Should work with CH552 -
  
  Modified and Tested - works for CH552G via USB CDC

  Using wiring_digital_fast.h for high speed bit-bang I2C

  Most delay removed.

  Debugged by SunnyA.I.

  ISP works by bit-banging IIC.

  WS51 Loader - Arduino Uno rewrite (Serial + bit-banged ISP)

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
#include <wiring_digital_fast.h>

//#define PIN_SCLK 14  // ISP clock output (Arduino pin)
#define PIN_SCLK_PORT 1  // ISP clock output (Arduino pin)
#define PIN_SCLK_PIN 4   // ISP clock output (Arduino pin)
//#define PIN_DATA 15  // ISP data (must support input + output)
#define PIN_DATA_PORT 1  // ISP data (must support input + output)
#define PIN_DATA_PIN 5   // ISP data (must support input + output)

//#define PIN_RST 16   // target reset output (Not required.)
#define PIN_RST_PORT 1  // target reset output (Not required.)
#define PIN_RST_PIN 6   // target reset output (Not required.)

//#define PIN_PWR 32   // target power enable output
#define PIN_PWR_PORT 3  // target power enable output
#define PIN_PWR_PIN 2   // target power enable output
//#define PIN_LED   13  // optional onboard LED

static int cdc_getc_blocking() {
  // Wait for next byte.
  while (!USBSerial_available()) {
  }
  return USBSerial_read();
}

static uint8_t cdc_getc_u8() {
  return (uint8_t)cdc_getc_blocking();
}

static void cdc_putc(char c) {
  USBSerial_write((uint8_t)c);
}

static void cdc_puts(const char *s) {
  while (*s) cdc_putc(*s++);
}

static void cdc_puthex8(uint8_t b) {
  const char hex[] = "0123456789ABCDEF";
  cdc_putc(hex[b >> 4]);
  cdc_putc(hex[b & 0x0F]);
}

static void cdc_puthex16(uint16_t w) {
  cdc_puthex8((uint8_t)(w >> 8));
  cdc_puthex8((uint8_t)(w & 0xFF));
}

// SCLK high/low
static inline void SCLK_H() {
  digitalWriteFast(PIN_SCLK_PORT, PIN_SCLK_PIN, HIGH);
  digitalWriteFast(PIN_SCLK_PORT, PIN_SCLK_PIN, HIGH);
}
static inline void SCLK_L() {
  digitalWriteFast(PIN_SCLK_PORT, PIN_SCLK_PIN, LOW);
  digitalWriteFast(PIN_SCLK_PORT, PIN_SCLK_PIN, LOW);
}

// DATA high/low
// Important: DATA is bidirectional, so for reads we set it to INPUT.
// For writes we set it to OUTPUT and drive.
static inline void DATA_as_output() {
  pinModeFast(PIN_DATA_PORT, PIN_DATA_PIN, OUTPUT);
}
static inline void DATA_as_input() {
  pinModeFast(PIN_DATA_PORT, PIN_DATA_PIN, INPUT);
}

static inline void DATA_H() {
  digitalWriteFast(PIN_DATA_PORT, PIN_DATA_PIN, HIGH);
  digitalWriteFast(PIN_DATA_PORT, PIN_DATA_PIN, HIGH);
}  // only valid when OUTPUT
static inline void DATA_L() {
  digitalWriteFast(PIN_DATA_PORT, PIN_DATA_PIN, LOW);
  digitalWriteFast(PIN_DATA_PORT, PIN_DATA_PIN, LOW);
}  // only valid when OUTPUT

static inline uint8_t DATA_R() {
  // only meaningful when PIN_DATA is INPUT
  return (digitalReadFast(PIN_DATA_PORT, PIN_DATA_PIN) ? 1 : 0);
}

// Reset & power controls
static inline void RST_L() {
  digitalWriteFast(PIN_RST_PORT, PIN_RST_PIN, LOW);
  digitalWriteFast(PIN_RST_PORT, PIN_RST_PIN, LOW);
}
static inline void RST_H() {
  digitalWriteFast(PIN_RST_PORT, PIN_RST_PIN, HIGH);
  digitalWriteFast(PIN_RST_PORT, PIN_RST_PIN, HIGH);
}
static inline void PWR_L() {
  digitalWriteFast(PIN_PWR_PORT, PIN_PWR_PIN, LOW);
  digitalWriteFast(PIN_PWR_PORT, PIN_PWR_PIN, LOW);
}
static inline void PWR_H() {
  digitalWriteFast(PIN_PWR_PORT, PIN_PWR_PIN, HIGH);
  digitalWriteFast(PIN_PWR_PORT, PIN_PWR_PIN, HIGH);
}


static void isp_start() {
  DATA_as_output();
  DATA_H();
  SCLK_H();
  DATA_L();
  SCLK_L();
}

static void isp_stop() {
  DATA_as_output();
  SCLK_L();
  DATA_L();
  SCLK_H();
  DATA_H();
}

static void isp_send_byte(uint8_t data) {
  DATA_as_output();

  for (int i = 0; i < 8; i++) {
    if (data & 0x80) DATA_H();
    else DATA_L();

    SCLK_H();
    SCLK_L();

    data <<= 1;
  }
}

static int isp_read_ack() {
  DATA_as_output();
  DATA_H();
  SCLK_H();
  DATA_as_input();
  int ack = DATA_R();

  SCLK_L();
  DATA_as_output();
  return ack;
}

static void isp_clock_pulse() {
  SCLK_H();
  SCLK_L();
}

static uint8_t isp_read_byte() {
  uint8_t result = 0;

  DATA_as_output();
  DATA_H();
  DATA_as_input();
  for (int i = 0; i < 8; i++) {
    SCLK_H();
    delayMicroseconds(2);
    result = (uint8_t)((result << 1) | (DATA_R() ? 1 : 0));
    SCLK_L();
    delayMicroseconds(2);
  }
  DATA_as_output();
  DATA_H();
  SCLK_H();
  SCLK_L();
  return result;
}

static void isp_send_3bytes(uint8_t b1, uint8_t b2, uint8_t b3) {
  isp_start();
  isp_send_byte(b1);
  isp_read_ack();
  isp_send_byte(b2);
  isp_read_ack();
  isp_send_byte(b3);
  isp_read_ack();
  isp_stop();
}

static void isp_wr_reg(uint8_t reg_hi, uint8_t reg_lo, uint8_t data) {
  isp_start();
  isp_send_byte(data);
  isp_read_ack();
  isp_send_byte(reg_hi);
  isp_read_ack();
  isp_send_byte(reg_lo);
  isp_read_ack();
  isp_stop();
}

static void isp_wr_word(uint8_t reg_hi, uint8_t reg_lo) {
  isp_start();
  isp_send_byte(0);
  isp_read_ack();
  isp_send_byte(reg_hi);
  isp_clock_pulse();
  isp_send_byte(reg_lo);
  isp_clock_pulse();
  isp_stop();
}

static uint8_t isp_read_phase(uint8_t reg) {
  isp_start();
  isp_send_byte(0);
  isp_read_ack();
  isp_send_byte(reg);
  isp_read_ack();
  isp_stop();

  isp_start();
  isp_send_byte(1);
  isp_read_ack();
  uint8_t val = isp_read_byte();
  isp_stop();
  return val;
}

static uint8_t isp_rd_reg(uint8_t addr) {
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
  isp_wr_reg(2, addr & 0xFF, 0);
  isp_wr_reg(3, (addr >> 8) & 0xFF, 0);
  isp_wr_reg(5, data, 0);
}

static int target_power_on() {
  PWR_L();
  RST_L();
  //delay(200);
  PWR_H();
  RST_H();
  RST_L();
  RST_H();
  delay(1);

  return 0;
}

static int isp_sync() {
  for (int retry = 0; retry <= 200; retry++) {
    isp_wr_word(0x1F, 0x75);
    isp_wr_word(0x1E, 0x6F);
    isp_wr_reg(1, 0xAA, 0);

    uint8_t resp = isp_read_phase(1);
    if ((resp & 0xF0) == 0x80) {
      return 0;
    }
    delay(1);
  }
  return 1;
}

static void do_erase() {
  isp_wr_flash(0x8304, 0x78);
  isp_wr_flash(0x8307, 0x07);
  isp_wr_flash(0x8306, 0x40);
  isp_wr_flash(0x8301, 0x81);
  isp_wr_flash(0x8304, 0x78);
  isp_wr_flash(0x8307, 0x07);
  isp_wr_flash(0x8306, 0x41);
  isp_wr_flash(0x8301, 0x81);
  isp_wr_flash(0x8304, 0x12);
  isp_wr_flash(0x8301, 0x04);

  delay(120);
}

static void do_reset_run() {
  isp_wr_reg(1, 0xAA, 0);
  uint8_t isp_contr = isp_rd_reg(0x87);
  isp_wr_reg_addr(0x87, (uint8_t)(isp_contr | 0x20));
  isp_wr_reg(1, 0x55, 0);
  isp_wr_word(0x1F, 0xF6);
  isp_wr_word(0x1E, 0x57);
  delay(1);
  RST_L();
  delay(1);
  RST_H();
}

static uint8_t page_buf[512];

void setup() {
  pinModeFast(PIN_SCLK_PORT, PIN_SCLK_PIN, OUTPUT);
  pinModeFast(PIN_DATA_PORT, PIN_DATA_PIN, OUTPUT);
  pinModeFast(PIN_RST_PORT, PIN_RST_PIN, OUTPUT);
  pinModeFast(PIN_PWR_PORT, PIN_PWR_PIN, OUTPUT);
  SCLK_L();
  DATA_as_input();
  DATA_H();
  RST_L();
  PWR_L();
}

void loop() {
  if (USBSerial_available()) return;

  uint8_t cmd = (uint8_t)cdc_getc_u8();

  if (cmd == 'S') {
    USBSerial_flush();
    if (target_power_on() == 0 && isp_sync() == 0) {
      uint8_t cfg = isp_rd_reg(0xA1);
      isp_wr_reg_addr(0xA1, (uint8_t)(cfg & 0xFC));
      cdc_puts("OK\n");
    } else {
      cdc_puts("FAIL\n");
    }
  } else if (cmd == 'E') {
    do_erase();
    cdc_puts("OK\n");
  } else if (cmd == 'P') {
    uint16_t addr = ((uint16_t)cdc_getc_u8() << 8) | cdc_getc_u8();
    for (int i = 0; i < 512; i++) {
      page_buf[i] = cdc_getc_u8();
    }
    isp_wr_flash(0x8304, 0x34);
    isp_wr_flash(0x8302, 0xFF);
    isp_wr_flash(0x8307, (uint8_t)((addr >> 8) & 0xFF));
    isp_wr_flash(0x8306, (uint8_t)(addr & 0xFF));
    isp_wr_flash(0x8301, 0x06);

    for (int i = 0; i < 512; i++) {
      isp_wr_flash(0x8303, page_buf[i]);
    }

    cdc_puts("OK\n");
  } else if (cmd == 'R') {
    do_reset_run();
    cdc_puts("OK\n");
    DATA_as_input();
  } else {
  }
}