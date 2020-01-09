//Read From the RFID and Print in the LCD

#include <LiquidCrystal.h>
#include <SPI.h>      
#include <MFRC522.h> 

#define SS_PIN 53  
#define RST_PIN 5  

MFRC522 mfrc522(SS_PIN, RST_PIN);  
MFRC522::MIFARE_Key key;          
int block=2;   
byte readbackblock[18];
const int rs = 12, en = 10, d4 = 43, d5 = 41, d6 = 39, d7 = 37;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int countTags=0;
int ambush[3];

void setup(){
  Serial.begin(9600);       
   SPI.begin();               
   mfrc522.PCD_Init();       
   
   for (byte i = 0; i < 6; i++) {
      key.keyByte[i] = 0xFF;  
    }
  lcd.begin(16, 2);
  lcd.clear();
  
}

bool flag=true;
void loop(){
   while(getID() && flag){
      mfrc522.PCD_Init();
      Serial.println("Reading Card:- ");
      Serial.write(readbackblock[0]);
      Serial.println(" ");
      int value = (char)readbackblock[0];
      ambush[countTags]=value-'0';
      countTags++;
      if(countTags>=2){
        Serial.println("All Cards read");
        Serial.println("Read values:- ");
        lcd.clear();
        lcd.setCursor(0, 0);
        flag=false;
        for(int i=0; i<countTags; i++){
          Serial.println(ambush[i]);
          lcd.print(ambush[i]);
          lcd.print(" ");
        }
      }
      mfrc522.PICC_HaltA();
      delay(1000);
   }
}


boolean getID() 
{
  
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) {
      key.keyByte[i] = 0xFF;  
  }
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
  return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
  return false;
  }
  int blockNumber =2;
  byte buffersize=18;
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;//determine trailer block for the sector

  //authentication of the desired block for access
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  mfrc522.MIFARE_Read(blockNumber, readbackblock, &buffersize);
  
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
}
