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
    //Serial.println(key);

    strcat(ModuleKeyPad::currentInput, &key);
    
    switch (ModuleKeyPad::promptPass()) {
      GOOD:
        Global::led(Global::GOOD);
        break;
      WRONG:
        ModuleKeyPad::currentInput = "";
        Global::led(Global::WRONG);
        break;
    }
  }
}

ModuleKeyPad::PassState ModuleKeyPad::promptPass() {
  Serial.print("DEBUG: ");
  Serial.print(Global::password);
  Serial.println(ModuleKeyPad::currentInput);
  if(strlen(Global::password) == strlen(ModuleKeyPad::currentInput)) {
    if(String(Global::password).equals(String(ModuleKeyPad::currentInput))) {
      return ModuleKeyPad::GOOD;
    }else {
      return ModuleKeyPad::WRONG;
    }
  }else {
    return ModuleKeyPad::INCOMPLET;
  }
}