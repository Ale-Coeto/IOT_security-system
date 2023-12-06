#ifndef Utilities_h
#define Utilities_h
    #include <ESP8266WiFi.h>


    class Utilities {
        public: 
            static void connectWifi();
            static const char* ssid = "wifi";
            static const char* pass = "password"; 
            static const char* userID = "clp01vc84000098nfj1dxjho1";
            static const char *websockets_connection_string = "wss://vczqzgtci9.execute-api.us-east-1.amazonaws.com/test/";

    };

    // Connect to wifi
    void Utilities::connectWifi() {
        WiFi.begin(ssid, pass);
        while(WiFi.status() != WL_CONNECTED) {
          Serial.print('.');
          delay(1000);
        }
    
        Serial.println("Wifi connected");
        Serial.print("IP adress: ");
        Serial.println(WiFi.localIP());
    }



#endif