
#include <Arduino.h>

#include "lights.h"
#include "defs.h"

namespace Lights {

  static bool lit;

  void Init(void) noexcept {
    Serial.print("Initializing Lights... ");
    pinMode(Defs::Pins::LIGHTL, OUTPUT);
    pinMode(Defs::Pins::LIGHTR, OUTPUT);
    lit = true;
    digitalWrite(Defs::Pins::LIGHTL, lit);
    digitalWrite(Defs::Pins::LIGHTR, lit);
    Serial.println("Lights Initialized!");
  }

  void Toggle(void) noexcept {
    lit = !lit;
    digitalWrite(Defs::Pins::LIGHTL, lit);
    digitalWrite(Defs::Pins::LIGHTR, lit);
  }

  void On(void) noexcept {
    lit = true;
    digitalWrite(Defs::Pins::LIGHTL, lit);
    digitalWrite(Defs::Pins::LIGHTR, lit);
  }

  void Off(void) noexcept {
    lit = false;
    digitalWrite(Defs::Pins::LIGHTL, lit);
    digitalWrite(Defs::Pins::LIGHTR, lit);
  }
}
