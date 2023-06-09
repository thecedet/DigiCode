#include "ModuleMQTT.h"
#include "ModuleKeyPad.h"
#include "Global.h"

ModuleMQTT moduleMQTT;
ModuleKeyPad moduleKeyPad;

const int pinLed = A0;

void setup() {
  Serial.begin(9600);
  moduleMQTT.setup(ModuleMQTT::SECURE_PORT);
  pinMode(pinLed, OUTPUT);
}

void loop() {
  if(!Global::password.equals("")) {
    moduleKeyPad.publishKeypadInput();
    delay(50);
  }
  moduleMQTT.loop();
}
