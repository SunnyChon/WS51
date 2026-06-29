sfr P0     = 0x80;
sfr SP     = 0x81;
sfr SCCON  = 0x86;
sfr PCON   = 0x87;
sfr TCON   = 0x88;
sfr TMOD   = 0x89;
sfr HRCON  = 0x96;
sfr S0CON  = 0x98;
sfr S0BUF  = 0x99;
sfr IE     = 0xA8;
sfr T2CON  = 0xC8;
sfr T2MOD  = 0xC9;
sfr T2CL   = 0xCA;
sfr T2CH   = 0xCB;
sfr TL2    = 0xCC;
sfr TH2    = 0xCD;

sbit SM00  = S0CON^7;
sbit SM10  = S0CON^6;
sbit REN0  = S0CON^4;
sbit TI0   = S0CON^1;
sbit RI0   = S0CON^0;
sbit RCLK  = T2CON^5;
sbit TCLK  = T2CON^4;
sbit TR2   = T2CON^2;
sbit EA    = IE^7;

#define P07F (*(unsigned char volatile xdata *)0x8007)
#define P06F (*(unsigned char volatile xdata *)0x8006)

xdata unsigned char ram_buf[920];

void uart0_write(unsigned char c)
{
    S0BUF = c;
    while (!TI0);
    TI0 = 0;
}

void uart0_puts(const char *s)
{
    while (*s) uart0_write(*s++);
}

void delay(void)
{
    unsigned int i, j;
    for (i = 0; i < 500; i++)
        for (j = 0; j < 1000; j++);
}

void main(void)
{
    unsigned int i;
    unsigned int err_cnt;

    SCCON = 0x00;
    HRCON |= 0x80;

    P07F = 6;
    P06F = 6;

    SM00 = 0;
    SM10 = 1;
    REN0 = 1;
    RI0 = 0;
    TI0 = 0;

    TR2 = 0;
    T2MOD = 0x00;
    T2CL = 0xCC;
    T2CH = 0xFF;
    TL2 = T2CL;
    TH2 = T2CH;
    TR2 = 1;
    RCLK = 1;
    TCLK = 1;

    delay();

    uart0_puts("\r\n=============================\r\n");
    uart0_puts("  WS51F6240 RAM Test\r\n");
    uart0_puts("  xdata: 920 bytes\r\n");
    uart0_puts("=============================\r\n\r\n");

    err_cnt = 0;
    for (i = 0; i < 920; i++)
        ram_buf[i] = (unsigned char)(i & 0xFF);
    for (i = 0; i < 920; i++) {
        if (ram_buf[i] != (unsigned char)(i & 0xFF))
            err_cnt++;
    }
    if (err_cnt == 0)
        uart0_puts("Pattern 0-FF: PASS\r\n");
    else
        uart0_puts("Pattern 0-FF: FAIL\r\n");

    err_cnt = 0;
    for (i = 0; i < 920; i++)
        ram_buf[i] = (unsigned char)(~i);
    for (i = 0; i < 920; i++) {
        if (ram_buf[i] != (unsigned char)(~i))
            err_cnt++;
    }
    if (err_cnt == 0)
        uart0_puts("Pattern inv:  PASS\r\n");
    else
        uart0_puts("Pattern inv:  FAIL\r\n");

    err_cnt = 0;
    for (i = 0; i < 920; i++)
        ram_buf[i] = 0x55;
    for (i = 0; i < 920; i++) {
        if (ram_buf[i] != 0x55)
            err_cnt++;
    }
    if (err_cnt == 0)
        uart0_puts("Pattern 0x55: PASS\r\n");
    else
        uart0_puts("Pattern 0x55: FAIL\r\n");

    err_cnt = 0;
    for (i = 0; i < 920; i++)
        ram_buf[i] = 0xAA;
    for (i = 0; i < 920; i++) {
        if (ram_buf[i] != 0xAA)
            err_cnt++;
    }
    if (err_cnt == 0)
        uart0_puts("Pattern 0xAA: PASS\r\n");
    else
        uart0_puts("Pattern 0xAA: FAIL\r\n");

    uart0_puts("\r\nBurn verify OK!\r\n");
    uart0_puts("Heartbeat:\r\n");

    while (1) {
        uart0_write('.');
        delay();
        delay();
        delay();
    }
}
