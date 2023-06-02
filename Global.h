#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>

class Global {
  public:

    enum LEDS {
      WRONG, GOOD
    };

    static void checkSecurity(char* message);
    static void led(LEDS led); 

    static String SECURITY;
    static char* password;

  private:
    static void setPassword();
};

#endif