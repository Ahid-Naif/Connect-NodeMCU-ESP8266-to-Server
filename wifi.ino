/*
 * HTTP Client GET Request
 * Copyright (c) 2018, circuits4you.com
 * All rights reserved.
 * https://circuits4you.com 
 * Connects to WiFi HotSpot. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

static const uint8_t D5   = 14;
static const uint8_t D6   = 12;

SoftwareSerial mySerial(D6, D5); // RX, TX

/* Set these to your desired credentials. */
const char *ssid = "HUAWEI-0794";  //ENTER YOUR WIFI SETTINGS
const char *password = "9MQB50J8HY4";

//Web/Server address to read/write from 
const char *host = "http://charm-sa.com";   //https://circuits4you.com website or IP address of server

String read_string;

//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  mySerial.begin(9600);
 //Serial1.begin(9600);
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  HTTPClient http;    //Declare object of class HTTPClient

  while (mySerial.available())
  {
    delay(2);  //delay to allow byte to arrive in input buffer
    char c = mySerial.read();
     read_string += c;
  }

   if (read_string.length() >0) {
      read_string.remove(read_string.length() - 1, 1);
 
      http.begin(read_string);     //Specify request destination
      int httpCode = http.GET();            //Send the request
      String payload = http.getString();    //Get the response payload

      Serial.println(httpCode);   //Print HTTP return code
      Serial.println(payload);    //Print request response payload
    
      http.end();  //Close connection
  
     read_string = "";
   }
}
