int LED = 2; // Assign LED pin i.e: D1 on NodeMCU

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "NaVindu "   //SSID
#define APPSK  "Navindu99" //Password
#endif

const char *ssid = APSSID;
const char *password = APPSK;



ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}




void setup() {

// initialize GPIO 5 as an output
 
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");

  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");


pinMode(LED, OUTPUT);

}

// the loop function runs over and over again forever

void loop() {

  server.handleClient();
digitalWrite(LED, HIGH); // turn the LED on
delay(1000); // wait for a second
digitalWrite(LED, LOW); // turn the LED off
delay(1000); // wait for a second

}
