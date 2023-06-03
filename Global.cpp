#include "Global.h"

String Global::SECURITY = "";
String Global::password = "";

void Global::checkSecurity(char* message) {
  if(String(Global::SECURITY).equals("")) {
    Serial.print("Niveau de sécurité: ");
    Serial.println(message);
    Global::SECURITY = String(message);
    //Global::setPassword(); // init le mot de passe
  }else {
    if(!Global::SECURITY.equals(String(message))) {
      Serial.println("On change de niveau de sécurité => redémarrage");
      asm volatile("jmp 0x00");
    }
  }
}

void Global::led(LEDS led) {
  Serial.print("On allume la led: ");
  Serial.println(led);
}

void Global::setPassword(char* message) {
  Serial.print("Mot de passe: ");
  Serial.println(message);
  Global::password = String(message);
}