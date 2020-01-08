#include <SPI.h>      
#include <MFRC522.h> 

#define SS_PIN 53  
#define RST_PIN 5  

MFRC522 mfrc522(SS_PIN, RST_PIN);  
MFRC522::MIFARE_Key key;          
int block=2;  
//byte blockcontent[16] = {"Last-Minute-Engg"};  
byte blockcontent[16] = {"2"};  
byte readbackblock[18];
void setup() 
{
    Serial.begin(9600);       
    SPI.begin();               
    mfrc522.PCD_Init();       
    Serial.println("Scan a MIFARE Classic card");
    for (byte i = 0; i < 6; i++) {
      key.keyByte[i] = 0xFF;  
  }
}

void loop()
{  
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
   Serial.println("card selected");
   writeBlock(block, blockcontent);
   readBlock(block, readbackblock);
   Serial.print("read block: ");
   for (int j=0 ; j<16 ; j++)
   {
     Serial.write (readbackblock[j]);
   }
   Serial.println("");
}



//Write specific block    
int writeBlock(int blockNumber, byte arrayAddress[]) 
{
  //this makes sure that we only write into data blocks. Every 4th block is a trailer block for the access/security info.
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;//determine trailer block for the sector
  if (blockNumber > 2 && (blockNumber+1)%4 == 0){Serial.print(blockNumber);Serial.println(" is a trailer block:");return 2;}
  Serial.print(blockNumber);
  Serial.println(" is a data block:");
  
  //authentication of the desired block for access
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
         Serial.print("PCD_Authenticate() failed: ");
         Serial.println(mfrc522.GetStatusCodeName(status));
         return 3;//return "3" as error message
  }
  
  //writing the block 
  status = mfrc522.MIFARE_Write(blockNumber, arrayAddress, 16);
  //status = mfrc522.MIFARE_Write(9, value1Block, 16);
  if (status != MFRC522::STATUS_OK) {
           Serial.print("MIFARE_Write() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return 4;//return "4" as error message
  }
  Serial.println("block was written");
}



//Read specific block
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
