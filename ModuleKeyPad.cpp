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

char ModuleKeyPad::publishKeypadInput() {
  return keypad.getKey();
}