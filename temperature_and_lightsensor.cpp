#include "mbed.h"
#include "TextLCD.h"
#include "DHT11.h"
#include "SDFileSystem.h"
Timer sure;
DigitalIn btn(PC_13);
DigitalOut kartled(LED1);
AnalogIn ldr(A0);
SDFileSystem sd(PB_15, PB_14, PB_13, PB_1, "sd"); // mosi, miso, sclk, cs(scl)

TextLCD lcd(D11, D12, D7, D8, D9, D10); // rs, e, d4-d7
DHT11 t(D3);
volatile char sicaklik;
volatile float isik;
unsigned char c;
void sicaklikmetodu()
{
            sure.start();
            if(sure.read()>=2)
            {
            t.readData();
       sicaklik= t.readTemperature();
       lcd.cls();
       lcd.printf("Sicaklik: %d",sicaklik);
       //printf("Sicaklik: %d",sicaklik);
       sure.reset();
       }
       
    }
    void ldrmetodu()
    {
        isik=ldr.read();
        if(isik==1)
        {
        kartled=0;
                //printf("Led OFF\n");
        }
        else
        {
        kartled=1;
        //printf("Led ON\n");
        }
        //printf("Isik Seviyesi: %f \n",ldr.read());
        }
int main() {
          
          btn.mode(PullUp);
           mkdir("/sd", 0777);
           while(1)
           {
                   ldrmetodu();
                   if(btn==0)
                   {
                    set_time(1572432498); 
                    } 
                    time_t seconds = time(NULL);
                  
                    sicaklikmetodu();  
                FILE *fp = fopen("/sd/sicaklik.txt", "a");
                 if(fp == NULL) {
            error("Yazma icin dosya acilamadi \n");
            printf("Yazma icin dosya acilamadi \n");
        }
         else {
            //Sd karta yazar
            if(isik<1)
            fprintf(fp, "%c, %s LED ON",sicaklik,ctime(&seconds));
            else
            fprintf(fp, "%c, %s LED OFF",sicaklik,ctime(&seconds));
            fclose(fp); //Dosya kapat
//
            FILE *fpr = fopen("/sd/sicaklik.txt", "r");
            //Okunacak dosya seçildi

//file end of. Okuma işlemi bitene kadar devam et.
//Dosya sonuna kadar okumaya devam et.
            while (!feof(fpr)) {
                c=fgetc(fpr);
                printf("%c",c);
            }
            fclose(fpr);
        }
         
               }

}
