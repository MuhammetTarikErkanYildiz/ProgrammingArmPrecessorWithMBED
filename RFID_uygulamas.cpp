#include "mbed.h"
#include "TextLCD.h"
#include <iostream>//cin ve cout
#include "mbed.h"
#include "MFRC522.h"
TextLCD lcd(A1, A2, PD_3, PD_4, PD_5, PD_6); // rs, e, d4-d7
DigitalOut buzz(A0);
//KL25Z Pins for MFRC522 SPI interface
#define SPI_MOSI PC_12    
#define SPI_MISO PC_11
#define SPI_SCLK PC_10
#define SPI_CS D10//sda
// KL25Z Pin for MFRC522 reset
#define MF_RESET D8//rsT
// KL25Z Pins for Debug UART port


MFRC522 RfChip (SPI_MOSI, SPI_MISO, SPI_SCLK, SPI_CS, MF_RESET);

int main(void) {
printf("asdasdasdasdasd");

// Init. RC522 Chip
RfChip.PCD_Init();

while (true) {

// Look for new cards
if ( ! RfChip.PICC_IsNewCardPresent())
{
wait_ms(500);
continue;
}

// Select one of the cards
if ( ! RfChip.PICC_ReadCardSerial())
{
wait_ms(500);
continue;
}


// Print Card UID
printf("Card UID: ");
for (uint8_t i = 0; i < RfChip.uid.size; i++)
{
printf(" %X", RfChip.uid.uidByte[i]);
}
printf("\n\r");

// Print Card type
uint8_t piccType = RfChip.PICC_GetType(RfChip.uid.sak);
printf("PICC Type: %s \n\r", RfChip.PICC_GetTypeName(piccType));
wait_ms(1000);
}
}