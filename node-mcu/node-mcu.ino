// Client code for AWS IoT Websockets

//Libraries
#include <ArduinoWebsockets.h>
#include <ArduinoJson.h>
#include <Servo.h>
#include "Utilities.h"

// Constants
#define PERIOD 2*60*1000L 
#define D2  4 //trigPind d2
#define D3  0 // echoPin d3
#define D1 5

// Variables
double distance = 0;
int pos = 0;
bool opened = false;
bool nowOpened = false;
int id = 0;
bool socketConnected = false;

using namespace websockets;
WebsocketsClient client;
Servo servo1;

// Send an image
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

// Send chunks
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
    doc["userId"] = Utilities::userID;

    size_t jsonSize = measureJson(doc);
    char jsonBuffer[jsonSize+2];
    serializeJson(doc, jsonBuffer, sizeof(jsonBuffer));

    // Send the serialized JSON data
    client.send(jsonBuffer);
    delay(100);
}

// Execute when recieving a message
void onMessageCallback(WebsocketsMessage message) {
    Serial.print("Got Message: ");
    Serial.println(message.data());

    DynamicJsonDocument doc(1024);
    DeserializationError err = deserializeJson(doc, message.data());

    if (err) {
        // Error
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(err.c_str());
    }
    else {
        // Imprimir
        serializeJson(doc, Serial);
        Serial.println();
    }

    String action = doc["action"].as<String>();

    if (action == "abrir") {
    
      pos = 0;
      servo1.write(pos);
    } 

    if (action == "cerrar") {
        pos = 180;
        servo1.write(pos);
    }

}


// Listen for events and print to debug status
void onEventsCallback(WebsocketsEvent event, String data) {
    if (event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connnection Opened");
    }
    else if (event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("Connnection Closed");
    }
    else if (event == WebsocketsEvent::GotPing) {
        Serial.println("Got a Ping!");
    }
    else if (event == WebsocketsEvent::GotPong) {
        Serial.println("Got a Pong!");
    }
}

//Set up
void setup() {
    Serial.begin(115200);
    servo1.attach(D1);
    

    //Connect to wifi
    Utilities::connectWifi();

    Serial.println("Wifi has been connected");

    // run callback when messages are received
    client.onMessage(onMessageCallback);

    // run callback when events are occuring
    client.onEvent(onEventsCallback);

    // Connect to server
    socketConnected = client.connect(Utilities::websockets_connection_string);

    // Send a ping
    client.ping();
    
}

//Loop
void loop() {

    // If not connected, try to connect
    if (!socketConnected) {
    socketConnected = client.connect(Utilities::websockets_connection_string);
    unsigned long ms3 = micros();

      while ((micros() - ms3) < 30) {
  
      }
    }

    // Check serial input
    if (Serial.available()) {

        // If input is recieved, send image through websockets
        String input = Serial.readStringUntil('\n');
        sendImage(input, 420);
        Serial.println("sent");
    } 

    // Listen for events
    client.poll();
}
