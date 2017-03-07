#include "outputs.h"

void Rele_Action(BYTE rele, BYTE state) {
    switch (rele) {
        case 0:
            if (state == ON) {
                RELE_R1 = HIGH;
            }
            if (state == OFF) {
                RELE_R1 = LOW;
            }
            break;

        case 1:
            if (state == ON) {
                RELE_R2 = HIGH;
            }
            if (state == OFF) {
                RELE_R2 = LOW;
            }
            break;
    }
}
