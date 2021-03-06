#include "menu.h"
#include "configuration.h"
#include "lcd.h"
#include "io.h"
#include <stdio.h>
#include "ubee.h"
#include "delay.h"



extern BYTE destination_adress;
extern BYTE source_adress;
extern BYTE id;
extern BYTE channel;
extern BYTE saved;

BYTE *msg[] = {
    "DEST ADDRESS",
    "SOURCE ADDRESS",
    "CHANNEL",
    "ID",
    "APPLY"
};

BYTE buffer[4];

/*
 MENU +--->Set_DestinationAddress --> 
      | 
 *    +--->Set_SourceAddress -->
 *    |
 *    +--->Set_Channel -->
 *    |
      +--->Set_ID -->      
 */

enum CHOOSE {
    DESTINATION_ADDRESS = 0,
    SOURCE_ADDRESS,
    CHANNEL,
    ID,
    APPLY
};

/********************************** MAIN MENU *********************************/
void Menu(void) {

    BYTE lcd_write = 1, selection = 0;

    while (1) {
        if (!KBD_DOWN) {
            __delay_ms(50);
            if (!KBD_DOWN) {
                __delay_ms(80);
                if (selection >= APPLY) {
                    selection = APPLY;
                } else {
                    selection++;
                    lcd_write = 1;
                }
            }
        }

        if (!KBD_UP) {
            __delay_ms(50);
            if (!KBD_UP) {
                __delay_ms(80);
                if (selection <= DESTINATION_ADDRESS) {
                    selection = DESTINATION_ADDRESS;
                } else {
                    selection--;
                    lcd_write = 1;
                }
            }
        }

        if (!KBD_ENTER) {
            __delay_ms(50);
            if (!KBD_ENTER) {
                __delay_ms(80);
                switch (selection) {
                    case DESTINATION_ADDRESS:
                        Set_DestinationAddress();
                        break;

                    case SOURCE_ADDRESS:
                        Set_SourceAddress();
                        break;

                    case CHANNEL:
                        Set_Channel();
                        break;

                    case ID:
                        Set_ID();
                        break;

                    case APPLY:
                        Lcd_Printf("Updating...", LCD_LINE_2);
                        ConfigBee(); //ver
                        Lcd_Printf("Updating...OK", LCD_LINE_2);
                        break;
                }
            }

        }

        if (!KBD_BACK) {
            __delay_ms(50);
            if (!KBD_BACK) {
                __delay_ms(80);
                Lcd_Clear();
                Lcd_Printf("   HOUSE.V004", LCD_LINE_1);
                break;
            }
        }

        lcd_write = ShowMenu(lcd_write, selection);

    }
}
/******************************* END MAIN MENU ********************************/
/*----------------------------------------------------------------------------*/

/************************** MENU DESTINATION ADDRESS **************************/
void Set_DestinationAddress(void) {
    BYTE lcd_write_flag = 0;
    Lcd_Clear();
    Lcd_Printf(msg[0], LCD_LINE_1);
    destination_adress = GetDestinationAddress();
    sprintf(buffer, "%03d", destination_adress);
    Lcd_Printf(buffer, LCD_LINE_2);
    while (1) {
        if (!KBD_ENTER) {
            __delay_ms(50);
            while (!KBD_ENTER);
            __delay_ms(50);
            SetDestinationAddress(destination_adress);
            SetFlagWritted(0x99);
            Lcd_Message_Saved();
            delay_ms(1000);
            Lcd_Printf(LCD_CLEAR_LINE, LCD_LINE_2);
            Lcd_Printf(buffer, LCD_LINE_2);
        }

        if (!KBD_UP) {
            __delay_ms(50);
            if (!KBD_UP) {
                __delay_ms(80);
                if (destination_adress > 253) {
                    destination_adress = 254;
                } else {
                    destination_adress++;
                }
                lcd_write_flag = 1;
            }
        }

        if (!KBD_DOWN) {
            __delay_ms(50);
            if (!KBD_DOWN) {
                __delay_ms(80);
                if ((destination_adress--) <= 0) {
                    destination_adress = 0;
                }
                lcd_write_flag = 1;
            }
        }

        if (!KBD_BACK) {
            __delay_ms(50);
            if (!KBD_BACK) {
                __delay_ms(80);
                (void) ShowMenu(1, 0);
                break;
            }
        }

        if (lcd_write_flag) {
            sprintf(buffer, "%03d", destination_adress);
            Lcd_Printf(buffer, LCD_LINE_2);
            lcd_write_flag = 0;
        }
    }
}
/************************ END MENU DESTINATION ADDRESS ************************/
/*----------------------------------------------------------------------------*/

/******************************* MENU SOURCE ADDRESS **************************/
void Set_SourceAddress(void) {
    BYTE lcd_write_flag = 0;
    Lcd_Clear();
    Lcd_Printf(msg[1], LCD_LINE_1);
    source_adress = GetSourceAddress();
    sprintf(buffer, "%03d", source_adress);
    Lcd_Printf(buffer, LCD_LINE_2);
    while (1) {
        if (!KBD_ENTER) {
            __delay_ms(50);
            while (!KBD_ENTER);
            __delay_ms(50);
            SetSourceAddress(source_adress);
            SetFlagWritted(0x99);
            Lcd_Message_Saved();
            delay_ms(1000);
            Lcd_Printf(LCD_CLEAR_LINE, LCD_LINE_2);
            Lcd_Printf(buffer, LCD_LINE_2);

        }

        if (!KBD_UP) {
            __delay_ms(50);
            if (!KBD_UP) {
                __delay_ms(80);
                if (source_adress > 253) {
                    source_adress = 254;
                } else {
                    source_adress++;
                }
                lcd_write_flag = 1;
            }
        }

        if (!KBD_DOWN) {
            __delay_ms(50);
            if (!KBD_DOWN) {
                __delay_ms(80);
                if ((source_adress--) <= 0) {
                    source_adress = 0;
                }
                lcd_write_flag = 1;
            }
        }

        if (!KBD_BACK) {
            __delay_ms(50);
            if (!KBD_BACK) {
                __delay_ms(50);
                (void) ShowMenu(1, 1);
                break;
            }
        }
        if (lcd_write_flag) {
            sprintf(buffer, "%03d", source_adress);
            Lcd_Printf(buffer, LCD_LINE_2);
            lcd_write_flag = 0;
        }
    }
}
/*************************** END MENU SOURCE ADDRESS **************************/
/*----------------------------------------------------------------------------*/

/********************************* MENU CHANNEL *******************************/
void Set_Channel(void) {
    BYTE lcd_write_flag = 0;
    Lcd_Clear();
    Lcd_Printf(msg[2], LCD_LINE_1);
    channel = GetChannel();
    sprintf(buffer, "%03d", channel);
    Lcd_Printf(buffer, LCD_LINE_2);
    while (1) {
        if (!KBD_ENTER) {
            __delay_ms(50);
            while (!KBD_ENTER);
            __delay_ms(50);
            SetChannel(channel);
            SetFlagWritted(0x99);
            Lcd_Message_Saved();
            delay_ms(1000);
            Lcd_Printf(LCD_CLEAR_LINE, LCD_LINE_2);
            Lcd_Printf(buffer, LCD_LINE_2);
        }

        if (!KBD_UP) {
            __delay_ms(50);
            if (!KBD_UP) {
                __delay_ms(80);
                if (channel > 25) {
                    channel = 26;
                } else {
                    channel++;
                }
                lcd_write_flag = 1;
            }
        }

        if (!KBD_DOWN) {
            __delay_ms(50);
            if (!KBD_DOWN) {
                __delay_ms(80);
                if ((channel--) <= 11) {
                    channel = 11;
                }
                lcd_write_flag = 1;
            }
        }

        if (!KBD_BACK) {
            __delay_ms(50);
            if (!KBD_BACK) {
                __delay_ms(50);
                (void) ShowMenu(1, 2);
                break;
            }
        }
        if (lcd_write_flag) {
            sprintf(buffer, "%03d", channel);
            Lcd_Printf(buffer, LCD_LINE_2);
            lcd_write_flag = 0;
        }
    }

}
/***************************** END MENU CHANNEL *******************************/
/*----------------------------------------------------------------------------*/

/*********************************** MENU ID **********************************/
void Set_ID(void) {
    BYTE lcd_write_flag = 0;
    Lcd_Clear();
    Lcd_Printf(msg[3], LCD_LINE_1);
    id = GetID();
    sprintf(buffer, "%03d", id);
    Lcd_Printf(buffer, LCD_LINE_2);
    while (1) {
        if (!KBD_ENTER) {
            __delay_ms(50);
            while (!KBD_ENTER);
            __delay_ms(50);
            SetID(id);
            SetFlagWritted(0x99);
            Lcd_Message_Saved();
            delay_ms(1000);
            Lcd_Printf(LCD_CLEAR_LINE, LCD_LINE_2);
            Lcd_Printf(buffer, LCD_LINE_2);
        }

        if (!KBD_UP) {
            __delay_ms(50);
            if (!KBD_UP) {
                __delay_ms(80);
                if (id > 254) {
                    id = 255;
                } else {
                    id++;
                }
                lcd_write_flag = 1;
            }
        }

        if (!KBD_DOWN) {
            __delay_ms(50);
            if (!KBD_DOWN) {
                __delay_ms(80);
                if ((id--) <= 0) {
                    id = 0;
                }
                lcd_write_flag = 1;
            }
        }

        if (!KBD_BACK) {
            __delay_ms(50);
            if (!KBD_BACK) {
                __delay_ms(50);
                (void) ShowMenu(1, 3);
                break;
            }
        }
        if (lcd_write_flag) {
            sprintf(buffer, "%03d", id);
            Lcd_Printf(buffer, LCD_LINE_2);
            lcd_write_flag = 0;
        }
    }
}
/******************************* END MENU ID **********************************/

/*----------------------------------------------------------------------------*/

BYTE ShowMenu(BYTE menu_show, BYTE index) {
    if (menu_show) {
        Lcd_Clear();
        Lcd_Send(0, LCD_MESSAGE_MODE, LCD_WRITE_MODE);
        Lcd_Printf(msg[index], LCD_LINE_1 + 1);

        if (index < 4) {
            Lcd_Printf(msg[index + 1], LCD_LINE_2);
        }
        return 0;
    }
}


