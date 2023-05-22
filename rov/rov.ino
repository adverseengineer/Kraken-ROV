//Nick Sells, 2023
//ETSU Underwater Robotics

#include <Servo.h>

#include "control.h"
#include "escs.h"
#include "grips.h"
#include "lights.h"
#include "util.h"

//how many ms to wait before setup to avoid the glitch where setup is called twice
const uint8_t STARTUP_DELAY = 90;
//how many ms to wait between each tick
const uint8_t TICK_DELAY = 1;

void setup(void) {
  delay(STARTUP_DELAY);
  Serial.begin(4800);
  Serial.println(F("Initializing... "));
  Control::Init();
  ESCs::Init();
  Grips::Init();
  Lights::Init();
  Serial.println(F("Done!"));
}

void loop(void) {

  Control::Update();
  if(likely(Control::IsAvailable())) {

    ESCs::Update();
    Grips::Update();
    Lights::Update();

  } else {
    Serial.print(F(".")); //"Couldn't detect a controller, retrying next tick.."
  }

  delay(TICK_DELAY);
}
 