//Nick Sells, 2023
//ETSU Underwater Robotics

#include <Servo.h>

#include "defs.h"

#include "control.h"
#include "esc.h"
#include "grips.h"
#include "lights.h"

void setup(void) {
  delay(Defs::STARTUP_DELAY);
  Serial.begin(4800);
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

    Esc::Update();
    Grips::Update();
    Lights::Update();

  } else {
    Serial.print("."); //"Couldn't detect a controller, retrying next tick.."
  }

  delay(Defs::TICK_DELAY);
}
 