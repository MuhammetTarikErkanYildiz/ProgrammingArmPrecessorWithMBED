#include "mbed.h"
#include "TextLCD.h"
DigitalOut myled(LED1);
TextLCD lcd(A1, A2, PD_3, PD_4, PD_5, PD_6); 
Timer timer1;
int saniye=0,dakika=0,saat=0;

int main() {
   timer1.start();
   
   while(1){
    saniye=timer1.read();
    if(saniye>59&&saniye<=60){
        dakika++;
        timer1.reset();
        }
    if(dakika>59&&dakika<=60){
        saat++;
        dakika=0;
        }
  if(saat==24){
        saat=0;
        dakika=0;
        timer1.reset();
        }
    lcd.printf("%d.%d.%d",saat,dakika,saniye);
    wait_us(5);
    lcd.cls();
    
    
    
    
    }
    
}
