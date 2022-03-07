#include "hcsr04.h"
#include "mbed.h"
/*
*HCSR04.cpp
*/
HCSR04::HCSR04(PinName t, PinName e) : trig(t), echo(e) {}
 int HCSR04::echo_sure() {
        
    timer.reset();  //reset timer
    trig=0;   // trigger low 
    wait_us(2); //  wait 
    trig=1;   //  trigger high
    wait_us(10);
    trig=0;  // trigger low
         while(!echo); // start pulseIN
      timer.start();
     while(echo);
      timer.stop();
     return timer.read_us(); 
 
}
 
//return distance in cm 
int HCSR04::uzaklik(){
    sure = echo_sure();
 mesafe_cm = (sure/2)/29.1  ;
        return mesafe_cm;

}