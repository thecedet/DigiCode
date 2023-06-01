#ifndef MODULEKEYPAD_H
#define MODULEKEYPAD_H

#include "ModuleMQTT.h"
#include <Arduino.h>
#include <Keypad.h>

class ModuleKeyPad {
  public:
    ModuleKeyPad();
    char publishKeypadInput();

  private:
    ModuleMQTT moduleMQTT;

    static const int ROWS = 4;
    static const int COLS = 3;
    static char keys[ROWS][COLS];
    static const byte rowPins[ROWS];
    static const byte colPins[COLS];

    Keypad keypad;
};

#endif