#include "mbed.h"

#include "TextLCD.h"
#include <iostream>//cin ve cout 
#include "beep.h"
#include "Keypad.h"
char x;
TextLCD lcd(D7, D6, D5, D4, D3, D2); // rs, e, d4-d7
// Define your own keypad values
char key_table[] = { '1', '2', '3', 'A',
                     '4', '5', '6', 'B',
                     '7', '8', '9', 'C',
                     '*', '0', '#', 'D'
                   };


Beep buzzer(A0);

BusOut step(D8,D9,D10,D11);
DigitalOut servo(D12);
Serial pc(USBTX,USBRX);
DigitalOut led(LED1);
void servometot();
void stepmetot();
void lcdmetot();
Thread servomotor,stepmotor,lcdekran;


int main()
{
    Keypad key(PC_4, PB_13, PB_14, PB_15, PB_1, PB_2, PB_12, PA_11);
    //satır 4321 sutun 4321
    uint32_t key_num;
    servomotor.start(servometot);
    stepmotor.start(stepmetot);
    lcdekran.start(lcdmetot);
    while(true) {
        while ((key_num = key.read()) != 0) {
            lcd.locate(0,1);
            lcd.printf("%c", *(key_table + key_num-1));
            printf("%c\n", *(key_table + key_num-1));
        }
        wait(0.1);
    }
}
void servometot()
{
    while(1) {
        for(uint8_t x=0; x<5; x++) {
            servo=1;
            wait_ms(1.5);
            servo=0;
            wait_ms(18.5);
        }
        wait(1);
        for(uint8_t x=0; x<5; x++) {
            servo=1;
            wait_ms(1);
            servo=0;
            wait_ms(19);
        }
        wait(1);
        for(uint8_t x=0; x<10; x++) {
            servo=1;
            wait_ms(2);
            servo=0;
            wait_ms(18);
        }
        wait(1);
    }

}


void stepmetot()
{
    step=0x0;
    while(1) {

        step=0x8;
        wait_ms(1);
        step=0x4;
        wait_ms(1);
        step=0x2;
        wait_ms(1);
        step=0x1;
        wait_ms(1);
    }
}
void lcdmetot()
{
    // bool y=0;
    while(1) {

        for(uint8_t x=0; x<11; x++) {

          lcd.locate(x-1,0);
            lcd.printf(" ");
            lcd.locate(x,0);
            lcd.printf("mehmet");
            wait_ms(200);
        }
          for(uint8_t x=0; x<16; x++) {

          lcd.locate(x,0);
            lcd.printf(" ");
        }
        // y=!y;

    }
}