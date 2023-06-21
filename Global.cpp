#include "Arduino.h"
#include "HardwareSerial.h"
#include "Global.h"

String Global::SECURITY = "";
String Global::password = "";
bool Global::bruteforce = true;

void Global::checkSecurity(char* message) {
  if(String(Global::SECURITY).equals("")) {
    Serial.print("Niveau de sécurité: ");
    Serial.println(message);
    Global::SECURITY = String(message);
    Global::setBruteForce();
  }else {
    if(!Global::SECURITY.equals(String(message))) {
      Serial.println("On change de niveau de sécurité => redémarrage");
      asm volatile("jmp 0x00");
    }
  }
}

void Global::led(LEDS led, bool state) {
  pinMode(led, OUTPUT);
  Serial.print("On ");
  Serial.print(state ? "allume" : "éteint");
  Serial.print(" la led: ");
  Serial.println(led);
  analogWrite(led, state ? 150 : 0);
}

void Global::ledBlink(LEDS led) {
  Global::led(led, true);
  delay(1000);
  Global::led(led, false);
}

void Global::setBruteForce() {
  if(Global::SECURITY.equals("low")) {
    Global::bruteforce = false;
  }

  Serial.print("Brute Force: ");
  Serial.println(Global::bruteforce ? "actif" : "inactif");
}

void Global::setPassword(char* message) {
  Serial.print("Mot de passe (MQTT): ");
  Serial.println(message);

  if(Global::SECURITY.equalsIgnoreCase("medium")) {
    Serial.print("Decode base64: ");
    int inputStringLength = strlen(message);
    int decodedLength = Base64.decodedLength(message, inputStringLength);
    char decodedString[decodedLength + 1];
    Base64.decode(decodedString, message, inputStringLength);
    Serial.println(decodedString);

    Global::password = String(decodedString);

  }else if(Global::SECURITY.equalsIgnoreCase("low")) {
    Global::password = String(message);
  }else {
    randomSeed(millis());
    Global::password = String(random(1000,9999));
  }

  Serial.print("Mot de passe: ");
  Serial.println(Global::password);
  
}