#include "ubee.h"
#include "eeprom.h"
#include <string.h>
#include <stdio.h>
#include <usart.h>


#define ID_ADDR           0x02
#define SOURCE_ADDR       0x03
#define DESTIN_ADDR       0x04
#define CHANNEL_ADDR      0x05

#define M_INN1 0
#define M_INN2 1
#define M_INN3 2

#define M_OUT1 3
#define M_OUT2 4
#define M_OUT3 5

#define DATA_WRITED       0x99

#define DELAY_TIME        30 

BYTE volatile destination_adress;
BYTE volatile source_adress;
BYTE volatile id;
BYTE volatile channel;
BYTE volatile saved;
char param1, param2, param3;
static char buff[10];

/*
                        Zigbee Protocol
 * +---+----+----+----+----+----+-----+---------+-----+---+
   | * | 10 | SA | DA | ID | CH | ACK | PAYLOAD | CKS | # |
 * +---+----+----+----+----+----+-----+---------+-----+---+
 */
void ConfigBee(void) {
    Serial_Flag_TX();
    putsUSART((char *) "+++\r"); //start the configuration
    __delay_ms(DELAY_TIME);
    sprintf(buff, "ATDA %03d\r", destination_adress);
    Serial_Flag_TX();
    putrsUSART(buff);
    __delay_ms(DELAY_TIME);
    putrsUSART(buff);
    __delay_ms(DELAY_TIME);
    sprintf(buff, "ATSA %03d\r", source_adress);
    putrsUSART(buff);
    __delay_ms(DELAY_TIME);
    sprintf(buff, "ATID %03d\r", id);
    putrsUSART(buff);
    __delay_ms(DELAY_TIME);
    sprintf(buff, "ATCH %02d\r", channel);
    Serial_Flag_TX();
    putrsUSART(buff);
    __delay_ms(DELAY_TIME);
    Serial_Flag_TX();
    putrsUSART(buff);
    __delay_ms(DELAY_TIME);
    Serial_Flag_TX();
    putrsUSART(buff);
    __delay_ms(DELAY_TIME);
    Serial_Flag_TX();
    putsUSART((char *) "ATWR\r"); //ends the configuration
    __delay_ms(DELAY_TIME);
    Serial_Flag_TX();
    putsUSART((char *) "ATCN\r"); //ends the configuration
    __delay_ms(DELAY_TIME);
}

//void FrameTest(void) {
//    putsUSART((char *) "*10010001001110OK!907#");
//}

char *Protocols(char rx_tx) {
    unsigned char *protocols[] = {
        "[INN1]", //0
        "[INN2]", //1
        "[INN3]", //2
        "[SENO]", //3
        "[SESI]", //4
        "[ALAM]" //5
    };
    switch (rx_tx) {
        case M_INN1:
            return protocols[0];
            break;

        case M_INN2:
            return protocols[1];
            break;

        case M_INN3:
            return protocols[2];
            break;

        case M_OUT1:
            return protocols[3];
            break;

        case M_OUT2:
            return protocols[4];
            break;

        case M_OUT3:
            return protocols[5];
            break;
    }

}

void SendMessage(unsigned char message_type) {
    char sendmessage[30];
    sprintf(sendmessage, "%c10%03d%03d%03d%02d0",
            START_FRAME, source_adress
            , destination_adress, id, channel);
    switch (message_type) {
        case 0:
            strcat(sendmessage, Protocols(0));
            strcat(sendmessage, CheckSum(sendmessage));
            break;

        case 1:
            strcat(sendmessage, Protocols(1));
            strcat(sendmessage, CheckSum(sendmessage));
            break;

        case 2:
            strcat(sendmessage, Protocols(2));
            strcat(sendmessage, CheckSum(sendmessage));
            break;

        case 3:
            strcat(sendmessage, Protocols(3));
            strcat(sendmessage, CheckSum(sendmessage));
            break;

        case 4:
            strcat(sendmessage, Protocols(4));
            strcat(sendmessage, CheckSum(sendmessage));
            break;

        case 5:
            strcat(sendmessage, Protocols(5));
            strcat(sendmessage, CheckSum(sendmessage));
            break;
    }
    putsUSART(sendmessage);
}

BYTE GetID() {
    return id;
}

BYTE GetSourceAddress() {
    return source_adress;
}

BYTE GetDestinationAddress() {
    return destination_adress;
}

BYTE GetChannel() {
    return channel;
}

void SetID(BYTE netId) {
    id = netId;
    E2promWrite(ID_ADDR, id);
    SetBeeChange(id, UBEE_ID);
}

void SetSourceAddress(BYTE source) {
    source_adress = source;
    E2promWrite(SOURCE_ADDR, source_adress);
    SetBeeChange(source, UBEE_SOURCE_ADDR);
}

void SetDestinationAddress(BYTE destination) {
    destination_adress = destination;
    E2promWrite(DESTIN_ADDR, destination_adress);
    SetBeeChange(destination, UBEE_DEST_ADDR);
}

void SetChannel(BYTE ch) {
    channel = ch;
    E2promWrite(CHANNEL_ADDR, channel);
    SetBeeChange(ch, UBEE_CHANNEL);
}

void SetFlagWritted(BYTE s) {
    saved = s;
    E2promWrite(DATASAVED_ADDR, saved);
}

void SetBeeChange(BYTE change, UBEE_PARAM param) {
    Serial_Flag_TX();
    putsUSART((char *) "+++\r"); //start the configuration
    __delay_ms(DELAY_TIME);
    switch (param) {
        case UBEE_DEST_ADDR:
            sprintf(buff, "ATDA %03d\r", change);
            break;
        case UBEE_SOURCE_ADDR:
            sprintf(buff, "ATSA %03d\r", change);
            break;
        case UBEE_CHANNEL:
            sprintf(buff, "ATCH %02d\r", change);
            break;
        case UBEE_ID:
            sprintf(buff, "ATID %03d\r", change);
            break;
    }
    Serial_Flag_TX();
    putrsUSART(buff);
    __delay_ms(DELAY_TIME);
    putsUSART((char *) "ATCN\r"); //ends the configuration
    __delay_ms(DELAY_TIME);
}

void eeprom_init(void) {
    saved = E2promRead(DATASAVED_ADDR);
    if (saved != DATA_WRITED) {
        destination_adress = 1;
        source_adress = 10;
        id = 1;
        channel = 11;
    } else {
        destination_adress = E2promRead(DESTIN_ADDR);
        source_adress = E2promRead(SOURCE_ADDR);
        id = E2promRead(ID_ADDR);
        channel = E2promRead(CHANNEL_ADDR);
    }
}

char *CheckSum(char *data) {
    char buf[4];
    char lenght = strlen(data), i;
    int sum = 0;
    /*Sum all the values in ASCII format if the result is 
    greater than 999 must be divided by 16*/
    for (i = 0; i <= (lenght - 1); i++) {
        sum += (int) data[i];
    }
    if (sum > 999)
        sum /= 16;
    //Split the result	
    Convert(sum);
    //Join result with configuration
    sprintf(buf, "%d%d%d#", param1, param2, param3);
    return buf;
}

void Convert(int convert) {
    param1 = convert / 100;
    convert %= 100;
    param2 = (convert / 10);
    convert %= 10;
    param3 = convert;
}