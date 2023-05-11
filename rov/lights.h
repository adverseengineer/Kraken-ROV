
#ifndef LIGHTS_H
#define LIGHTS_H

#include "defs.h"

namespace Lights {

  namespace {
    bool lit;
    void Update(void) {
      digitalWrite(Defs::Pins::LIGHTL, lit);
      digitalWrite(Defs::Pins::LIGHTR, lit);
    }
  }

  void Toggle(void) {
    lit = !lit;
    Update();
  }

  void On(void) {
    lit = true;
    Update();
  }

  void Off(void) {
    lit = false;
    Update();
  }

  void Init(void) {
    Serial.print("Initializing Lights... ");
    pinMode(Defs::Pins::LIGHTL, OUTPUT);
    pinMode(Defs::Pins::LIGHTR, OUTPUT);
    On();
    Serial.println("Lights Initialized!");
  }
}

#endif
