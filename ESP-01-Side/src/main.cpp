#include <Arduino.h>
#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* ssid = "BISA"; 
const char* password = "bayu1234"; 
const char* websockets_server = "ws://192.168.0.115:3001"; 

using namespace websockets;

void onMessageCallback(WebsocketsMessage message);
void onEventsCallback(WebsocketsEvent event, String data);

WebsocketsClient client;

String namaAktuator = "lampu_teras";

#define RELAY_PIN 0

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    pinMode(RELAY_PIN, OUTPUT);

    for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
        Serial.print(".");
        delay(1000);
    }

    if(WiFi.status() == WL_CONNECTED){
      Serial.println("WiFi Connected");
      Serial.println(WiFi.localIP());
    }

    client.onMessage(onMessageCallback);
    client.onEvent(onEventsCallback);
    
    client.connect(websockets_server);

    client.send("Hi Server!");
    client.ping();
}

void loop() {
    client.poll();
}

void onMessageCallback(WebsocketsMessage message) {
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, message.data());

    const char* actuatorAction = doc[namaAktuator];
    String actuatorActionS = actuatorAction;

    Serial.println(actuatorAction);

    if(actuatorActionS == "ON"){
      digitalWrite(RELAY_PIN, HIGH);

      Serial.print("Menyalakan ");
      Serial.println(namaAktuator);
    }
    else{
      digitalWrite(RELAY_PIN, LOW);

      Serial.print("Mematikan ");
      Serial.println(namaAktuator);
    }
}

void onEventsCallback(WebsocketsEvent event, String data) {
    if(event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connnection Opened");
    } else if(event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("Connnection Closed");
    } else if(event == WebsocketsEvent::GotPing) {
        Serial.println("Got a Ping!");
    } else if(event == WebsocketsEvent::GotPong) {
        Serial.println("Got a Pong!");
    }
}