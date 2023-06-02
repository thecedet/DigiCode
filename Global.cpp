#include "Global.h"

char* Global::SECURITY = "";
char* Global::password;

void Global::checkSecurity(char* message) {
  if(String(Global::SECURITY).equals("")) {
    Serial.print("Niveau de sécurité: ");
    Serial.println(message);
    strcpy(Global::SECURITY, message);
    Global::setPassword(); // init le mot de passe
  }else {
    if(!String(Global::SECURITY).equals(String(message))) {
      Serial.println("On change de niveau de sécurité => redémarrage");
      asm volatile("jmp 0x00");
    }
  }
}

void Global::led(LEDS led) {
  Serial.print("On allume la led: ");
  Serial.println(led);
}

void Global::setPassword() {
  Global::password="1234";
}