
#include <Arduino.h>

#include "lights.h"
#include "control.h"
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

  void Update(void) noexcept {
    if(Control::GetButtonHit(A)) {
      if(!lit) On();
      else Off();
    }
  }
}
