#include <stdint.h>
#include <util/delay.h>

//STM32 C code Rewrittn by gemini for AVR, original ISP code from https://gitee.com/tanxiaoyao/WS51

/*
 * Pin Mapping for Arduino Uno (ATmega328P):
 *
 *      W51F6240S16U W51F6240S20U
 *                   W51F6240T20U
 *
 *      SOP16        SOP20
 * SCLK (07)         (10)             -> Digital Pin 2 (PD2)
 * DATA (15)         (19)             -> Digital Pin 3 (PD3) [Emulated Open-Drain Interface]
 * RST  (NA)         (16)             -> Digital Pin 4 (PD4)
 * PWR  (01)         (01)             -> Digital Pin 5 (PD5)
 * GND  (16)         (20)             -> GND
 * LED                                -> Digital Pin 13 (PB5 - Onboard LED)
 *
 * Note from original repo README : SDA(DATA) require a ~5K pull up resistor.
 */

#define SCLK_H (PORTD |= (1 << PD2))
#define SCLK_L (PORTD &= ~(1 << PD2))

// Open-Drain Emulation for Bidirectional DATA Line
#define DATA_H \
  do { \
    DDRD &= ~(1 << PD3); \
    PORTD |= (1 << PD3); \
  } while (0)
#define DATA_L \
  do { \
    PORTD &= ~(1 << PD3); \
    DDRD |= (1 << PD3); \
  } while (0)
#define DATA_R ((PIND >> PD3) & 1)

#define RST_H (PORTD |= (1 << PD4))
#define RST_L (PORTD &= ~(1 << PD4))

#define PWR_H (PORTD |= (1 << PD5))
#define PWR_L (PORTD &= ~(1 << PD5))

#define LED_ON (PORTB |= (1 << PB5))  // Active High on Arduino Uno
#define LED_OFF (PORTB &= ~(1 << PB5))
#define LED_TGL (PORTB ^= (1 << PB5))

// Debug logging redirection to hardware serial bridge

//Debug message output disabled since atmega328p doesn't have secondary UART.
/*
static void uart_puts(const char *s) {
  Serial.print(s);
}
*/

//Unused function
/*
static void uart_putc(char c) {
  Serial.print(c);
}
*/

static void uart_puthex8(uint8_t b) {
  if (b < 16) Serial.print('0');
  Serial.print(b, HEX);
}

static void uart_puthex16(uint16_t w) {
  uart_puthex8(w >> 8);
  uart_puthex8(w & 0xFF);
}

// Protocol communication channel mapping
static void cdc_puts(const char *s) {
  Serial.print(s);
}
static uint8_t cdc_getc(void) {
  while (Serial.available() == 0) {
    // Wait block for character arrival
  }
  return Serial.read();
}

static void isp_start(void) {
  DATA_H;
  SCLK_H;
  delayMicroseconds(2);
  DATA_L;
  delayMicroseconds(1);
  SCLK_L;
  delayMicroseconds(1);
}

static void isp_stop(void) {
  SCLK_L;
  DATA_L;
  delayMicroseconds(1);
  SCLK_H;
  delayMicroseconds(1);
  DATA_H;
  delayMicroseconds(2);
}

static void isp_send_byte(uint8_t data) {
  for (int i = 0; i < 8; i++) {
    if (data & 0x80) DATA_H;
    else DATA_L;
    delayMicroseconds(1);
    SCLK_H;
    delayMicroseconds(1);
    SCLK_L;
    data <<= 1;
  }
}

static int isp_read_ack(void) {
  DATA_H;
  delayMicroseconds(1);
  SCLK_H;
  delayMicroseconds(1);
  int ack = DATA_R;
  SCLK_L;
  delayMicroseconds(1);
  return ack;
}

static void isp_clock_pulse(void) {
  DATA_H;
  delayMicroseconds(1);
  SCLK_H;
  delayMicroseconds(1);
  SCLK_L;
  delayMicroseconds(1);
}

static uint8_t isp_read_byte(void) {
  uint8_t result = 0;
  DATA_H;
  delayMicroseconds(2);
  for (int i = 0; i < 8; i++) {
    SCLK_H;
    delayMicroseconds(2);
    result = (result << 1) | (DATA_R ? 1 : 0);
    SCLK_L;
    delayMicroseconds(2);
  }
  DATA_H;
  delayMicroseconds(2);
  SCLK_H;
  delayMicroseconds(2);
  SCLK_L;
  delayMicroseconds(2);
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

static void wait_isp_ready(void) {
  for (int i = 0; i < 2000; i++) {
    uint8_t status = isp_rd_reg16(0x8301);
    if (!(status & 0x01)) return;

    if (i % 200 == 0) {
      //uart_puts("Wait Busy... Status: ");
      uart_puthex8(status);
      //uart_puts("\n");
    }
    delay(1);
  }
  //uart_puts("Wait Timeout!\n");
}

static int target_power_on(void) {
  //uart_puts("Target Power ON\n");
  PWR_L;
  RST_L;
  delay(200);
  PWR_H;
  RST_H;
  RST_L;
  RST_H;
  delay(1);
  return 0;
}

static int isp_sync(void) {
  //uart_puts("Syncing...");
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
    delay(1);
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

  delay(120);
  //uart_puts("Erase Done\n");
}

static void do_reset_run(void) {
  isp_wr_reg(1, 0xAA, 0);

  uint8_t isp_contr = isp_rd_reg(0x87);
  isp_wr_reg_addr(0x87, isp_contr | 0x20);

  isp_wr_reg(1, 0x55, 0);
  isp_wr_word(0x1F, 0xF6);
  isp_wr_word(0x1E, 0x57);

  delay(1);
  RST_L;
  delay(1);
  RST_H;
}

static void gpio_init(void) {
  // Configure SCLK (PD2), RST (PD4), PWR (PD5) as outputs
  DDRD |= (1 << PD2) | (1 << PD4) | (1 << PD5);

  // Configure LED pin (PB5) as output
  DDRB |= (1 << PB5);

  // Default Startup States
  SCLK_L;
  DATA_H;  // Configures pin as floating input/pullup state
  RST_L;
  PWR_L;
  LED_OFF;
}

static uint8_t page_buf[512];

void setup(void) {
  // Standard baud rate calculation matching STM32 (115200 bps)
  Serial.begin(115200);
  gpio_init();
  //uart_puts("\n\n--- WS51 Loader Start (Arduino Uno) ---\n");
  delay(100);
}

void loop(void) {
  if (Serial.available() > 0) {
    uint8_t cmd = cdc_getc();

    if (cmd == 'S') {
      //uart_puts("CMD: Sync\n");
      if (target_power_on() == 0 && isp_sync() == 0) {
        uint8_t cfg = isp_rd_reg(0xA1);
        isp_wr_reg_addr(0xA1, cfg & 0xFC);
        cdc_puts("OK\n");
      } else {
        cdc_puts("FAIL\n");
      }
    } else if (cmd == 'E') {
      //uart_puts("CMD: Erase\n");
      do_erase(); 
      cdc_puts("OK\n");
    } else if (cmd == 'P') {
      uint16_t addr = (cdc_getc() << 8) | cdc_getc();
      //uart_puts("CMD: Program @ ");
      uart_puthex16(addr);
      //uart_puts("\n");

      for (int i = 0; i < 512; i++) {
        page_buf[i] = cdc_getc();
      }

      isp_wr_flash(0x8304, 0x34);
      isp_wr_flash(0x8302, 0xFF);
      isp_wr_flash(0x8307, (addr >> 8) & 0xFF);
      isp_wr_flash(0x8306, addr & 0xFF);
      isp_wr_flash(0x8301, 0x06);

      for (int i = 0; i < 512; i++) {
        isp_wr_flash(0x8303, page_buf[i]);
        if ((i & 0x3F) == 0x3F) delay(1);
      }
      delay(200);
      cdc_puts("OK\n");
    } else if (cmd == 'R') {
      //uart_puts("CMD: Reset\n");
      do_reset_run();
      cdc_puts("OK\n");
    }
  }
}