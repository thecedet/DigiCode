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
  if(!Global::password.equals("")) {
    moduleKeyPad.publishKeypadInput();
    delay(1000);
  }
  moduleMQTT.loop();
}
