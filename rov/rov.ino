//Nick Sells, 2023
//ETSU Underwater Robotics ROV Controller

#include <Servo.h>

#include "defs.h"

#include "control.h"
#include "esc.h"
#include "grips.h"
#include "lights.h"

void setup(void) {
  pinMode(0, OUTPUT);

  delay(Defs::STARTUP_DELAY);
  Serial.begin(115200);
  Serial.println("Initializing... ");
  Control::Init();
  Esc::Init();
  Grips::Init();
  Lights::Init();
  Serial.println("Done!");
}

void loop(void) {

  Control::Update();
  if (Control::IsAvailable()) {
    // int lsX = map(Control::JoyL.x, Control::HAT_MIN, Control::HAT_MAX, Esc::REVERSE, Esc::FORWARD);
    // Esc::esc[0].writeMicroseconds(lsX);
    // Esc::esc[1].writeMicroseconds(lsX);
    // Esc::esc[2].writeMicroseconds(lsX);
    // Esc::esc[3].writeMicroseconds(lsX);
    // Esc::escVL.writeMicroseconds(lsX);
    // Esc::escVR.writeMicroseconds(lsX);

    Esc::UpdateInputs();
    Esc::ApplyInputs();
  } else {
    Serial.println("Couldn't detect a controller. Retrying next tick...");
  }

  delay(Defs::TICK_DELAY);
}
