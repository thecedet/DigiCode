#include "ModuleMQTT.h"

const char* ModuleMQTT::HOSTNAME = "ArduinoDigitCode";
const char* ModuleMQTT::USERNAME = "admin";
const char* ModuleMQTT::PASSWORD = "password";

byte mac[] = { 0xC1, 0xE8, 0xBA, 0XFE, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 111);
IPAddress MQTT_server(192, 168, 1, 4);


ModuleMQTT::ModuleMQTT() : client(ethClient){}


void ModuleMQTT::setup(int port) {
  client.setServer(MQTT_server, port);
  client.setCallback(ModuleMQTT::callback);

  Ethernet.begin(mac, ip);
  Serial.print("Ethernet started on IP: ");
  Serial.println(Ethernet.localIP());

  ModuleMQTT::connect();
}

void ModuleMQTT::callback(char* topic, byte* payload, unsigned int length) {
  String strTopic = String(topic);
  char payloadString[length + 1];
  memcpy(payloadString, (char*) payload, length);
  payloadString[length] = '\0';
  char* message = payloadString;

  if(strTopic.equals("global_security_level")) {
    Global::checkSecurity(message);
  }

  //Serial.println(strTopic);
  //Serial.println(message);
}

void ModuleMQTT::connect() {
  while(!client.connected()) {
    Serial.println("En attente de la connexion MQTT...");
    if(client.connect(ModuleMQTT::HOSTNAME, ModuleMQTT::USERNAME, ModuleMQTT::PASSWORD)) {
      Serial.println("connected");
      ModuleMQTT::publish("global_security_level", "init");
    }
  }
}

void ModuleMQTT::publish(char *topic, char *message) {
  client.publish(topic, message);
  client.subscribe(topic);
}

void ModuleMQTT::loop() {
  if(!client.connected()) {
    ModuleMQTT::connect();
  }
  client.loop();
}