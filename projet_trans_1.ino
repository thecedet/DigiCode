#include "ModuleMQTT.h"
#include "ModuleKeyPad.h"

ModuleMQTT moduleMQTT;
ModuleKeyPad moduleKeyPad;

void setup() {
  Serial.begin(9600);
  moduleMQTT.setup(ModuleMQTT::SECURE_PORT);
}

void loop() {
  moduleKeyPad.publishKeypadInput();
  moduleMQTT.loop();
}
