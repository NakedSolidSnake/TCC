#include "eeprom.h"

void E2promWrite(int address, UCHAR data) {
    EEADR = address; // wite the required address
    EEDATA = data; // write the data
    EECON1 &= 0x3F; // EEPGD = 0, CFGS = 0, all other bits are kept unchanged
    EECON1 |= 0x04; // WREN = 1, all other bits are kept unchanged
    INTCONbits.GIE = 0; // disable all interrupt
    EECON2 = 0x55; // should write this value before initializing write
    EECON2 = 0xAA; // should write this value before initializing write
    EECON1 |= 0x02; // WR = 1, all other bits are kept unchanged
    INTCONbits.GIE = 1; // enable interrupts
    while (EECON1 & 0x20); // wait till WR becomes 0
    EECON1 &= 0xFB; // WREN = 0, all other bits are kept unchanged
}

unsigned char E2promRead(int address) {
    unsigned char data;

    EEADR = address; // wite the required address
    EECON1 &= 0x3F; // EEPGD = 0, CFGS = 0, all other bits are kept unchanged
    EECON1 |= 0x01; // RD = 1, all other bits are kept unchanged
    while (EECON1 & 0x01); // wait till RD becomes 0
    data = EEDATA; // read the data from the data register

    return data;
}
