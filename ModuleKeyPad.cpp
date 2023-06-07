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

    ModuleKeyPad::currentInput[ModuleKeyPad::currentIndex] = key;
    
    if(ModuleKeyPad::BRUTEFORCE == ModuleKeyPad::currentBRUTEFORCE) {
      delay(1000*60);
      ModuleKeyPad::currentBRUTEFORCE = 0;
    }

    switch (ModuleKeyPad::promptPass()) {
      case INCOMPLET:
        ModuleKeyPad::currentIndex++;
        break;
      case WRONG:
        ModuleKeyPad::currentIndex = 0;
        Global::led(Global::WRONG);
        if(ModuleKeyPad::BRUTEFORCE != 0) {
          ModuleKeyPad::currentBRUTEFORCE++;
        }
        break;
      case GOOD:
        Global::led(Global::GOOD);
        break;
    }
    
  }
}

ModuleKeyPad::PassState ModuleKeyPad::promptPass() {
  if(strlen(Global::password) == ModuleKeyPad::currentIndex+1) {
    if(String(Global::password).equals(String(ModuleKeyPad::currentInput))) {
      return ModuleKeyPad::GOOD;
    }else {
      return ModuleKeyPad::WRONG;
    }
  }else {
    return ModuleKeyPad::INCOMPLET;
  }
}