#ifndef MODULEKEYPAD_H
#define MODULEKEYPAD_H

#include "ModuleMQTT.h"
#include <Arduino.h>
#include <Keypad.h>

class ModuleKeyPad {
  public:

    enum PassState {
      INCOMPLET, WRONG, GOOD 
    };

    ModuleKeyPad();
    void publishKeypadInput();
    PassState promptPass();

  private:
    ModuleMQTT moduleMQTT;

    // mot de passe taille 4 + \0
    char currentInput[5] = "";
    int currentIndex = 0;

    int bruteforce = 0;
    int bruteforceMAX = 2;

    static const int ROWS = 4;
    static const int COLS = 3;
    static char keys[ROWS][COLS];
    static const byte rowPins[ROWS];
    static const byte colPins[COLS];

    void enableBruteForce();

    Keypad keypad;
};

#endif