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
#include <DHT.h>

// Insert your networcredentials
#define WIFI_SSID "NaVindu"
#define WIFI_PASSWORD "NaVindu69"

// Insert Firebase project API Key
#define API_KEY "AIzaSyB40dq_o174HaTIMshq7xuVQRXo1wbw9Vo"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "park-here-ba636-default-rtdb.firebaseio.com/"
#define DHTPIN D1       // Pin connected to the DHT sensor
#define DHTTYPE DHT11
   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);   

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
int key4;
int key5;
float floatValue;
bool signupOK = false;

///firebase end
///array
int myArray[5];
int arraySize =5;
int currentindex =0;


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
pinMode(DHTPIN, INPUT);
  dht.begin();
//setup end
}
//loop
void loop()
{

  
  float h = dht.readHumidity();

  float t = dht.readTemperature();
  
  
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getInt(&fbdo, "/test/key2")) {
      if (fbdo.dataType() == "int") {
        key2 = fbdo.intData();
        myArray[1]=key2;
       // Serial.print(myArray[1]);
        
            
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
        myArray[0]=key1;
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
        myArray[2]=key3;
        //Serial.println(key3);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  
        ///key4
         if (Firebase.RTDB.getInt(&fbdo, "/test/key4")) {
      if (fbdo.dataType() == "int") {
        key4 = fbdo.intData();
        myArray[3]=key4;
        //Serial.println(key3);
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    ///key5
     if (Firebase.RTDB.getInt(&fbdo, "/test/key5")) {
      if (fbdo.dataType() == "int") {
        key5 = fbdo.intData();
        //Serial.println(key3);
        myArray[4]=key5;
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
        

  }
//firevase end
Firebase.RTDB.setFloat(&fbdo, "DHT/humidity",h);
Firebase.RTDB.setFloat(&fbdo, "DHT/temperature", t);
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
    //if(newcode==key2|| newcode==key1)
       for(int i=0;i<arraySize;i++)
{
if  (myArray[i]==newcode)
{
  Serial.println("yes");

       Serial.println(t);
s1.write(0);   
  
  s1.write(150); // Set the servo angle to 90 degrees
  delay(4000);       // Wait for 1 second

       // Wait for 1 second

  s1.write(0);   // Set the servo angle to 0 degrees
 // delay(1000);   
  
}
}  


    mfrc522.PICC_HaltA();   // Halt PICC
    mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
  }
//rfid end

//loop end
}