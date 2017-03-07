#include "ubee.h"
#include "eeprom.h"
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <usart.h>

#define DATASAVED_ADDR    0x10
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

#define DELAY_TIME        0x0A //10d

BYTE destination_adress;
BYTE source_adress;
BYTE id;
BYTE channel;
char param1, param2, param3;

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
    Serial_Flag_TX();
    putsUSART((char *) "ATMSE 0\r"); //Turn off report mode
    __delay_ms(DELAY_TIME);
    Serial_Flag_TX();
    putsUSART((char *) "ATNR 0\r"); //Retransmission time = 0
    __delay_ms(DELAY_TIME);
    Serial_Flag_TX();
    putsUSART((char *) "ATAE 0\r"); //Acknowledge off
    __delay_ms(DELAY_TIME);
    Serial_Flag_TX();
    putsUSART((char *) "ATRO 100\r"); //Time out to send the package
    __delay_ms(DELAY_TIME);
    Serial_Flag_TX();
    putsUSART((char *) "ATSA 10\r"); //Source address "who sends the message"
    __delay_ms(DELAY_TIME);
    Serial_Flag_TX();
    putsUSART((char *) "ATDA 1\r"); //Destination address "who will receive the message"
    __delay_ms(DELAY_TIME);
    Serial_Flag_TX();
    putsUSART("ATID 1\r"); // Network ID
    __delay_ms(DELAY_TIME);
    Serial_Flag_TX();
    putsUSART("ATCH 11\r"); //Channel where the place what will occurs the connection
    __delay_ms(DELAY_TIME);
    Serial_Flag_TX();
    putsUSART((char *) "ATAPI 1\r"); //Mode API and Protocol 10 active    
    __delay_ms(DELAY_TIME);
    Serial_Flag_TX();
    putsUSART((char *) "ATCN\r"); //ends the configuration
    __delay_ms(DELAY_TIME);
    Serial_Flag_TX();

}

void FrameTest(void) {
    putsUSART((char *) "*10010001001110OK!907#");
}

char *Protocols(char rx_tx) {
    unsigned char *protocols[] = {
        "[INN1]", //0
        "[INN2]", //1
        "[INN3]", //2
        "[OUT1]", //3
        "[OUT2]", //4
        "[OUT3]" //5
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
            strcat(sendmessage,Protocols(0));
            strcat(sendmessage, CheckSum(sendmessage));             
            break;

        case 1:
            strcat(sendmessage,Protocols(1));
            strcat(sendmessage, CheckSum(sendmessage));
            break;

        case 2:
            strcat(sendmessage,Protocols(2));
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
}

void SetSourceAddress(BYTE source) {
    source_adress = source;
    E2promWrite(SOURCE_ADDR, source_adress);
}

void SetDestinationAddress(BYTE destination) {
    destination_adress = destination;
    E2promWrite(DESTIN_ADDR, destination_adress);
}

void SetChannel(BYTE ch) {
    channel = ch;
    E2promWrite(CHANNEL_ADDR, channel);
}

void eeprom_init(void) {
    if (E2promRead(DATASAVED_ADDR) != 0x99) {
        destination_adress = 150;
        source_adress = 100;
        id = 8;
        channel = 18;
    } else {
        destination_adress = E2promRead(DESTIN_ADDR);
        source_adress = E2promRead(SOURCE_ADDR);
        id = E2promRead(ID_ADDR);
        channel = E2promRead(CHANNEL_ADDR);
    }
}

void SetFlagWritted() {
    E2promWrite(DATASAVED_ADDR, DATA_WRITED);
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
    param2 = convert / 10;
    convert %= 10;
    param3 = convert;
}