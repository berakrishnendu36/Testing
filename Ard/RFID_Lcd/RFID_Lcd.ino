//Read From the RFID and Print in the LCD

#include <LiquidCrystal.h>
#include <SPI.h>      
#include <MFRC522.h> 

#define SS_PIN 53  
#define RST_PIN 5  

MFRC522 mfrc522(SS_PIN, RST_PIN);  
MFRC522::MIFARE_Key key;          
int block=2;   
byte readbackblock[3][18];
const int rs = 12, en = 10, d4 = 43, d5 = 41, d6 = 39, d7 = 37;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int countTags=0;
int ambush[3];

void setup(){
  Serial.begin(9600);       
   SPI.begin();               
   mfrc522.PCD_Init();       
   Serial.println("Scan a MIFARE Classic card");
   for (byte i = 0; i < 6; i++) {
      key.keyByte[i] = 0xFF;  
    }
  lcd.begin(16, 2);
  lcd.clear();
  
}


void loop(){
    if( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

   readBlock(block, readbackblock[countTags]);
   Serial.print("read block: ");
   lcd.setCursor(0, 0);
   Serial.write(readbackblock[countTags][0]);
   ambush[countTags]=readbackblock[countTags][0]-'0';
   countTags++;
   if(countTags==2){
    for(int i=0; i<countTags; i++){
      lcd.print(ambush[i]);
      lcd.print(" ");
    }
   }

}

int readBlock(int blockNumber, byte arrayAddress[]) 
{
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;//determine trailer block for the sector

  //authentication of the desired block for access
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK) {
         Serial.print("PCD_Authenticate() failed (read): ");
         Serial.println(mfrc522.GetStatusCodeName(status));
         return 3;//return "3" as error message
  }

//reading a block
byte buffersize = 18;//we need to define a variable with the read buffer size, since the MIFARE_Read method below needs a pointer to the variable that contains the size... 
status = mfrc522.MIFARE_Read(blockNumber, arrayAddress, &buffersize);//&buffersize is a pointer to the buffersize variable; MIFARE_Read requires a pointer instead of just a number
  if (status != MFRC522::STATUS_OK) {
          Serial.print("MIFARE_read() failed: ");
          Serial.println(mfrc522.GetStatusCodeName(status));
          return 4;//return "4" as error message
  }
  Serial.println("block was read");
}
