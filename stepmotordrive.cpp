#include "mbed.h"
#define hiz 2
BusOut motor(D9,D10,D11,D12);
uint16_t sayac=0;//uint16_t 2byte 0...65bin..
int main() {
motor=0x0;
while(1) {

while(sayac<1000)//ileri
{
sayac++;
motor=0x8;wait_ms(hiz);
motor=0x4;wait_ms(hiz);
motor=0x2;wait_ms(hiz);
motor=0x1;wait_ms(hiz);
}
sayac=0;
while(sayac<500)//geri
{
sayac++;
motor=0x1;wait_ms(hiz);
motor=0x2;wait_ms(hiz);
motor=0x4;wait_ms(hiz);
motor=0x8;wait_ms(hiz);
}
sayac=0;
}
}