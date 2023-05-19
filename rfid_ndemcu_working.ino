/* Read RFID Tag with RC522 RFID Reader
 *  Made by miliohm.com
 */
 /*
#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = D3;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D4;     // Configurable, see typical pin layout above

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

String tag;

void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}*/

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN D3
#define SS_PIN D4

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);
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
    Serial.println("Code: " + code);

    mfrc522.PICC_HaltA();   // Halt PICC
    mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
  }
}

