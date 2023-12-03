// Client code for AWS IoT Websockets

#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Servo.h>
//#include "Ultrasonic.h"
#define PERIOD 2*60*1000L 
//unsigned long target_time = 0L ;
#define D2  4 //trigPind d2
#define D3  0 // echoPin d3
#define D1 5

double distance = 0;
int pos = 0;
bool opened = false;
bool nowOpened = false;
const char* ssid = "ale";// "Decored20";//"ale";////"RoBorregos2";
const char* pass = "tobytoby"; //"mexico01#";//"tobytoby";//"mexico01#";//"RoBorregos2023";
int id = 0;
const char* userID = "clp01vc84000098nfj1dxjho1";
bool socketConnected = false;
// Enter server adress
const char *websockets_connection_string = "wss://vczqzgtci9.execute-api.us-east-1.amazonaws.com/test/";

using namespace websockets;

WebsocketsClient client;
//Ultrasonic ultrasonico(D2,D3);
Servo servo1;

// Connect to wifi
void connectWifi() {
    WiFi.begin(ssid, pass);
    while(WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(1000);
    }

    Serial.println("Wifi connected");
    Serial.print("IP adress: ");
    Serial.println(WiFi.localIP());
}

void sendImage(const String& img, size_t chunkSize) {
    // Calculate the number of chunks needed
    size_t totalChunks = (img.length() + chunkSize - 1) / chunkSize;
    
    // Loop through each chunk and send it
    for (size_t i = 0; i < totalChunks; ++i) {
        size_t start = i * chunkSize;
        size_t end = min((i + 1) * chunkSize, img.length());
        String chunk = img.substring(start, end);
        sendImageChunk(chunk.c_str(), i, totalChunks);
    }
    
    id++;
    if (id > 100)
      id = 0;
}

void sendImageChunk(const char* chunk, int chunkNum, size_t totalChunks) {
    if (!socketConnected) {
    socketConnected = client.connect(websockets_connection_string);
    unsigned long ms3 = micros();

      while ((micros() - ms3) < 30) {
  
      }

  }
  
    DynamicJsonDocument doc(JSON_OBJECT_SIZE(2)+1024);
    doc["action"] = "receiveData";
    doc["data"] = chunk;
    doc["id"] = id;
    doc["chunk"] = chunkNum;
    doc["chunkSize"] = totalChunks-1;
    doc["userId"] = userID;

    size_t jsonSize = measureJson(doc);
    char jsonBuffer[jsonSize+2];
    serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));

    // Print or send the serialized JSON data as needed
    Serial.println("block sent");
    client.send(jsonBuffer);
    delay(100);
}


//void sendOpened(const char* openedS) {
//  DynamicJsonDocument doc2(JSON_OBJECT_SIZE(2)+100);
//    doc2["action"] = "receiveOpened";
//    doc2["data"] = openedS;
//    doc2["userId"] = userID;
//
//    size_t jsonSize2 = measureJson(doc2);
//    char jsonBuffer2[jsonSize2];
//    serializeJson(doc2, jsonBuffer2, sizeof(jsonBuffer2));
//
//    // Print or send the serialized JSON data as needed
////    Serial.println(jsonBuffer2);
//    client.send(jsonBuffer2);
//}
//
//void sendDistancia() {
//  if (distance > 15) {
//    nowOpened = false;
//  } else {
//    nowOpened = true;
//  }
//
//  if (nowOpened != opened) {
//    sendOpened(nowOpened ? "opened" : "closed");
//  }
//
//  opened = nowOpened;
//  
////  Serial.print(distance);
////  Serial.println(nowOpened);
//  
//}

//// Execute when recieving a message
void onMessageCallback(WebsocketsMessage message)
{
    Serial.print("Got Message: ");
    Serial.println(message.data());

    DynamicJsonDocument doc(1024);
    DeserializationError err = deserializeJson(doc, message.data());

    // Checar si hubo un error
    if (err)
    {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(err.c_str());
    }
    else
    {
        // Imprimir el mensaje
        serializeJson(doc, Serial);
        Serial.println();
    }

    String action = doc["action"].as<String>();

    if (action == "abrir")
  {
    
      pos = 0;
      servo1.write(pos);
     
  } 

  if (action == "cerrar") {
      pos = 180;
      servo1.write(pos);
  }
  


}


// Listen for events and print to debug status
void onEventsCallback(WebsocketsEvent event, String data)
{
    if (event == WebsocketsEvent::ConnectionOpened)
    {
        Serial.println("Connnection Opened");
    }
    else if (event == WebsocketsEvent::ConnectionClosed)
    {
        Serial.println("Connnection Closed");
    }
    else if (event == WebsocketsEvent::GotPing)
    {
        Serial.println("Got a Ping!");
    }
    else if (event == WebsocketsEvent::GotPong)
    {
        Serial.println("Got a Pong!");
    }
}


void setup()
{
    Serial.begin(115200);

    servo1.attach(D1);
    

    //Connect to wifi
    connectWifi();

    Serial.println("Wifi has been connected");

    // run callback when messages are received
    client.onMessage(onMessageCallback);

    // run callback when events are occuring
    client.onEvent(onEventsCallback);

    // Connect to server
    socketConnected = client.connect(websockets_connection_string);

    // Set up with the server
//    setClientType();

    // Send a ping
    client.ping();
    
//    ultrasonico.iniciar();
}

void loop() {

    if (!socketConnected) {
    socketConnected = client.connect(websockets_connection_string);
    unsigned long ms3 = micros();

      while ((micros() - ms3) < 30) {
  
      }

  }
//  
  if (Serial.available()) {
      String input = Serial.readStringUntil('\n');
      sendImage(input, 420);
      Serial.println("sent");
  } 

//  distance = ultrasonico.getDistancia();
//  sendDistancia();
//  

  
//  Serial.println(ultrasonico.getDistancia());

//    if (millis () - target_time >= PERIOD) {
//        target_time += PERIOD ;   // change scheduled time exactly, no slippage will happen
//        Serial.println(ultrasonico.getDistancia());
//    /// do stuff
//  }


    // Listen for events
    client.poll();
}
