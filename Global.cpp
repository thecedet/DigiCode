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

    Serial.print("Brute Force: ");
    Serial.println(Global::bruteforce ? "actif" : "inactif");

    //Global::setPassword(); // init le mot de passe
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

void Global::setPassword(char* message) {
  Serial.print("Mot de passe: ");
  Serial.println(message);
  Global::password = String(message);
}