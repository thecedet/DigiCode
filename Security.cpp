#include "ModuleMQTT.h"

char* ModuleMQTT::SECURITY = "";

void ModuleMQTT::checkSecurity(char* message) {
  if(String(ModuleMQTT::SECURITY).equals("")) {
    strcpy(ModuleMQTT::SECURITY, message);
  }else {
    if(!String(ModuleMQTT::SECURITY).equals(String(message))) {
      Serial.println("on vient de changer de sécu");
      asm volatile("jmp 0x00");
    }
  }
}