#include "mbed.h"
#include "MFRC522.h"
#include "TextLCD.h"
#include "Keypad.h"
#include "rtos.h"
#include <string.h>
#include <iostream>
#include "SDFileSystem.h"
#include "DHT11.h"
#include "wave_player.h"
//Thread sicaklik;
//https://audio.online-convert.com/convert-to-wav
Timer isizaman;
 volatile char deger;//değişken bütün bloklarda kullanılabilecek şekle geldi. Public yapıldı
 DHT11 isi(D9);

AnalogOut DACout(PA_4);
wave_player waver(&DACout);

SDFileSystem sd(PB_5, PB_4, PB_3, D7, "sd"); // mosi, miso, sclk, cs(scl)
DigitalOut lamba(PA_13);//sinyal pini pa_13
DigitalOut klima(PA_14);
AnalogIn ldr(A5);
float ldroku;
unsigned char c;    

Serial pc(USBTX,USBRX);
Serial bt(A0,A1);
char gelen[10]={0}; ;//10 adet kapasiteli değişken tanımlandı
char metinbt[10];
string veri;
uint8_t  sayacbt=0;
uint8_t abt,pckontrol=0;
TextLCD lcd(A1, A2, PD_3, PD_4, PD_5, PD_6); // rs, e, d4-d7
DigitalOut led(LED1);
void girismetot();


char x,sifre[4];
uint8_t sayac=0;
char key_table[] = { '1', '2', '3', 'A',
                     '4', '5', '6', 'B',
                     '7', '8', '9', 'C',
                     '*', '0', '#', 'D'
                   };

//KL25Z Pins for MFRC522 SPI interface
#define SPI_MOSI PC_12    
#define SPI_MISO PC_11
#define SPI_SCLK PC_10
#define SPI_CS D10//sda
// KL25Z Pin for MFRC522 reset
#define MF_RESET D8//rsT
// KL25Z Pins for Debug UART port

DigitalOut bzr(PC_8);
MFRC522    RfChip   (SPI_MOSI, SPI_MISO, SPI_SCLK, SPI_CS, MF_RESET);

void girismetot()
{
         FILE *wave_file;   
    wave_file=fopen("/sd/hosgeldiniz.wav","r");
    waver.play(wave_file);
    fclose(wave_file);
       time_t seconds = time(NULL);
    lamba=0;
    lcd.cls();
    printf("\n Giris basarili");
    lcd.printf("Giris basarili");
    for (int i = 0; i < 1000; i++ ) { //frekans oluşturuldu
        // 1 / 2000 = 500uS, 250us + 250us - olacak. 50% duty cycle
        bzr=1;
        wait_us(200);
        bzr=0;
        wait_us(200);
    }
    sayac=0;
    for(uint8_t x=0; x<4; x++) {
        sifre[x]=0;
    }
    wait(2);
    lcd.cls();
        ldroku=ldr.read();
  if(ldroku<0.50)
  lamba=1;
  else
  lamba=0;
  if(deger>30)
  klima=1;
  else
  klima=0;
  //sd karta yazma
  FILE *fp = fopen("/sd/ornek.txt", "a");
    if(fp == NULL) {
        error("Yazma icin dosya acilamadi \n");
    }
     else
    {
    
             fprintf(fp, "%s,\n Giris yapan: %X,%X,%X,%X",ctime(&seconds),RfChip.uid.uidByte[0],RfChip.uid.uidByte[1],RfChip.uid.uidByte[2],RfChip.uid.uidByte[3]);
        
  
    fclose(fp); //Dosya kapat
 
    pc.printf("Yazma islemi bitti! \n");
    
           pc.printf("Okuma islemi basladi! \n");          
      FILE *fpr = fopen("/sd/ornek.txt", "r");
      //Okunacak dosya seçildi  
 
 //file end of. Okuma işlemi bitene kadar devam et. 
 //Dosya sonuna kadar okumaya devam et.
      while (!feof(fpr)){                    
           c=fgetc(fpr);                        
           printf("%c",c);
      }
      fclose(fpr);   
      }  
}
/*
void sicaklikmetodu()
{
    while(1)
    {
         deger = isi.readData();
          pc.printf("T:%d, H:%d\r\n", isi.readTemperature(), isi.readHumidity());
           wait(2);
        }
    }*/
int main(void)
{ //set_time(1558438679); 
  isizaman.start();
      pc.baud(38400);
 
    bt.baud(38400);
    wait(1);
        //sicaklik.start(sicaklikmetodu);
 mkdir("/sd", 0777);
    Keypad key(PC_4, PB_13, PB_14, PB_15, PB_1, PB_2, PB_12, PA_11);
    uint32_t key_num;
    // Init. RC522 Chip
    RfChip.PCD_Init();

    while (true) {
       
        while ((key_num = key.read()) != 0) {
            sifre[sayac]=*(key_table + key_num-1);
            
            lcd.locate(sayac,1);
            lcd.printf("*");
            sayac++;
            if(sayac==3)
            if(sifre[0]=='1' && sifre[1]=='2' && sifre[2]=='3' && sifre[3]=='A') {
                girismetot();

            } else if(sifre[0]!='1' && sifre[1]!='2' && sifre[2]!='3' && sifre[3]!='A')
                lcd.printf("Giris basarisiz");

            printf("%c\n", *(key_table + key_num-1));
            // sayi[0]=*(key_table + key_num-1); printf("%f",sayi[0]);
        }
        // Look for new cards
        if ( ! RfChip.PICC_IsNewCardPresent()) {
                  time_t seconds = time(NULL);
               if(pc.readable()>0 ){//seri portta veri varmı?
  veri=pc.getc();
    pc.printf("%c",veri); 
            /*pc.scanf("%s",gelen);
           pc.printf("%s \n",gelen);*/

        }
     
      if(isizaman.read()>2)
      {
          
           lcd.locate(0,0);
           deger = isi.readData();
          lcd.printf("ISI:%d, NEM:%d", isi.readTemperature(), isi.readHumidity());
          lcd.printf("  ");
           isizaman.reset();
          }
    
            continue;
        }

        // Select one of the cards
        if ( ! RfChip.PICC_ReadCardSerial()) {
            wait_ms(500);
            continue;
        }


        // Print Card UID
        printf("Card UID: ");
        for (uint8_t i = 0; i < RfChip.uid.size; i++) {
            printf(" %X", RfChip.uid.uidByte[i]);
        }
        if(RfChip.uid.uidByte[0]==0x93 && RfChip.uid.uidByte[1]==0x84 && RfChip.uid.uidByte[2]==0xB7 && RfChip.uid.uidByte[3]==0x2E)

        {
            girismetot();
        } else
            printf("\n Giris basarisiz!!!");
        printf("\n\r");

        // Print Card type
        uint8_t piccType = RfChip.PICC_GetType(RfChip.uid.sak);
        printf("PICC Type: %s \n\r", RfChip.PICC_GetTypeName(piccType));
       
    }
}