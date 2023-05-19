//rfid
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN D3
#define SS_PIN D4

MFRC522 mfrc522(SS_PIN, RST_PIN); 
//rfid end
#include <Servo.h>
 Servo s1;  


///firebase
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "NaVindu"
#define WIFI_PASSWORD "NaVindu69"

// Insert Firebase project API Key
#define API_KEY "AIzaSyB40dq_o174HaTIMshq7xuVQRXo1wbw9Vo"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "park-here-ba636-default-rtdb.firebaseio.com/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int intValue;
int uid1;
//declaring string variables
int key1;
int key3;
int key2;
float floatValue;
bool signupOK = false;

///firebase end

//setup
void setup(){
s1.attach(D2);  
Serial.begin(115200);
//firebaase
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
//firebase end
//rfid
 SPI.begin();      // Initialize SPI bus
  mfrc522.PCD_Init();   // Initialize MFRC522

  Serial.println("Ready to read RFID cards...");
//rifid end
//setup end
}
//loop
void loop()
{
//firebase
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getInt(&fbdo, "/test/key2")) {
      if (fbdo.dataType() == "int") {
        key2 = fbdo.intData();
        //Serial.println(key2);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
    ///for key1 string
  if (Firebase.RTDB.getInt(&fbdo, "/test/key1")) {
      if (fbdo.dataType() == "int") {
        key1 = fbdo.intData();
        //Serial.println(key1);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }    
    ///for key1 string end


    ///for key3 string
      if (Firebase.RTDB.getInt(&fbdo, "/test/key3")) {
      if (fbdo.dataType() == "int") {
        key3 = fbdo.intData();
        //Serial.println(key3);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  
        

  }
//firevase end
//rfid 

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
    if(newcode==key2|| newcode==key1)
    {
Serial.print("yes");
s1.write(90); // Set the servo angle to 90 degrees
  delay(1000);       // Wait for 1 second

  s1.write(180); // Set the servo angle to 180 degrees
  delay(1000);       // Wait for 1 second

  s1.write(0);   // Set the servo angle to 0 degrees
  delay(1000);      
    }
    else
    {
Serial.print("no");
    }

    mfrc522.PICC_HaltA();   // Halt PICC
    mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
  }
//rfid end

//loop end
}