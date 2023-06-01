#ifndef MODULEMQTT_H
#define MODULEMQTT_H

#include <Arduino.h>
#include <Ethernet2.h>
#include <PubSubClient.h>

class ModuleMQTT {
  public:
    static const int SECURE_PORT = 1883;
    static const int NO_SECURE_PORT = 1883;

    ModuleMQTT();

    void setup(int port);
    void loop();
    void publish(char* topic, char* message);

    static char* SECURITY;

  private:
    static const char* HOSTNAME;
    static const char* USERNAME;
    static const char* PASSWORD;
    
    PubSubClient client;
    EthernetClient ethClient;

    static void callback(char* topic, byte* payload, unsigned int length);
    void connect();

    static void checkSecurity(char* message);
};

#endif