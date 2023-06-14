#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>

class Global {
  public:

    enum LEDS {
      WRONG = A1, GOOD = A0
    };

    static void checkSecurity(char* message);
    static void ledBlink(LEDS led); 
    static void led(LEDS led, bool state);
    static void setPassword(char* message);
    
    static String SECURITY;
    static String password;
    static bool bruteforce;

};

#endif