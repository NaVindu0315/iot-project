#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN D3
#define SS_PIN D4

MFRC522 mfrc522(SS_PIN, RST_PIN);  

// Create MFRC522 instance

int myArray[5];
int arraySize =5;
int currentindex =0;

void setup() {
  Serial.begin(9600);
    myArray[0] = 3572814;
  myArray[1] = 555959;
  myArray[2] = 12345;
  myArray[3] = 67890;
  myArray[4] = 98765;
  SPI.begin();      // Initialize SPI bus
  mfrc522.PCD_Init();   // Initialize MFRC522

  Serial.println("Ready to read RFID cards...");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Read the UID of the card
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uid += String(mfrc522.uid.uidByte[i]);
    }

    // Extract the desired 6-7 digit code from the UID
    String code = uid.substring(0, 7);

    // Print the code
    
    int newcode =code.toInt();
    Serial.println("Code: " + code);
 /*   if(newcode==3572814|| newcode==1152124)
    {
Serial.print("yes");      
    }
    else
    {
Serial.print("no");
    }*/
    for(int i=0;i<arraySize;i++)
{
if  (myArray[i]==newcode)
{
  Serial.println("yes");
}
}    

    mfrc522.PICC_HaltA();   // Halt PICC
    mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
  }
}

