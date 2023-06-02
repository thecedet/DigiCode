#include "ModuleMQTT.h"
#include "ModuleKeyPad.h"
#include "Global.h"

ModuleMQTT moduleMQTT;
ModuleKeyPad moduleKeyPad;

void setup() {
  Serial.begin(9600);
  moduleMQTT.setup(ModuleMQTT::SECURE_PORT);
}

void loop() {
  if(!Global::SECURITY.equals("")) {
    moduleKeyPad.publishKeypadInput();
  }
  moduleMQTT.loop();
}
