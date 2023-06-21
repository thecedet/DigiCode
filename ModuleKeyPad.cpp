#include "Arduino.h"
#include "HardwareSerial.h"
#include "ModuleKeyPad.h"

const byte ModuleKeyPad::rowPins[ModuleKeyPad::ROWS] = {3,4,5,6};
const byte ModuleKeyPad::colPins[ModuleKeyPad::COLS] = {7,8,9};

char ModuleKeyPad::keys[ModuleKeyPad::ROWS][ModuleKeyPad::COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

ModuleKeyPad::ModuleKeyPad() : keypad(
  makeKeymap(ModuleKeyPad::keys), 
  ModuleKeyPad::rowPins, 
  ModuleKeyPad::colPins, 
  ModuleKeyPad::ROWS, 
  ModuleKeyPad::COLS
){};

void ModuleKeyPad::publishKeypadInput() {
  char key = keypad.getKey();
  if (key != NO_KEY) {

    Serial.print("[publishKeypadInput]: Appui sur ");
    Serial.println(key);

    ModuleKeyPad::currentInput[ModuleKeyPad::currentIndex] = key;
       
    switch (ModuleKeyPad::promptPass()) {
      case INCOMPLET:
        ModuleKeyPad::currentIndex++;
        break;
      case WRONG:
        ModuleKeyPad::currentIndex = 0;
        ModuleKeyPad::bruteforce++;
        Global::ledBlink(Global::WRONG);
        break;
      case GOOD:
        Global::led(Global::GOOD, true);
        ModuleKeyPad::bruteforce = 0;
        break;
    }

    if(Global::bruteforce && ModuleKeyPad::bruteforce == ModuleKeyPad::bruteforceMAX) {
      ModuleKeyPad::enableBruteForce();
    }
    
  }
}

void ModuleKeyPad::enableBruteForce() {
  ModuleKeyPad::bruteforce = 0;
  Global::led(Global::WRONG, true);
  Serial.println("[BruteForce] Bloquer pendant 5min");
  delay(1000 * 60);
  Global::led(Global::WRONG, false);
}

ModuleKeyPad::PassState ModuleKeyPad::promptPass() {
  if(Global::password.length() == ModuleKeyPad::currentIndex+1) {
    Serial.println(ModuleKeyPad::currentInput);
    if(Global::password.equals(String(ModuleKeyPad::currentInput))) {
      return ModuleKeyPad::GOOD;
    }else {
      return ModuleKeyPad::WRONG;
    }
  }else {
    return ModuleKeyPad::INCOMPLET;
  }
}