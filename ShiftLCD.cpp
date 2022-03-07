#include "mbed.h"
#include "TextLCD.h"
#define metin " auido "

TextLCD lcd(A1, A2, PD_3, PD_4, PD_5, PD_6);
  
  int main() {
    for(;true;)//while(true)
    {
        for(uint8_t digit=0;digit<=11;digit++)
        {
            lcd.locate(digit,0);      
        lcd.printf(metin);
        wait_ms(400);
   
        }
         for(uint8_t digit=10;digit>0;digit--)
        {     
           lcd.locate(digit,0);     
        lcd.printf(metin);
        wait_ms(400);
   
        }
        
        }//for(;true;)
        return 0;
  }//main