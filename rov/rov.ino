//Nick Sells, 2023
//ETSU Underwater Robotics ROV Controller

#include <Servo.h>

#include "defs.h"

#include "control.h"
#include "esc.h"
#include "grips.h"
#include "lights.h"

void setup(void) {
  delay(Defs::STARTUP_DELAY);
  Serial.begin(115200);
  Serial.println("Initializing... ");
  Control::Init();
  ESC::Init();
  Grips::Init();
  Lights::Init();
  Serial.println("Done!");
}

void loop(void) {

  Control::Update();
  if(Control::xb.Xbox360Connected) {
    int lsX = map(Control::JoyL.x, Control::HAT_MIN, Control::HAT_MAX, ESC::REVERSE, ESC::FORWARD);
    ESC::escFL.writeMicroseconds(lsX);
    ESC::escFR.writeMicroseconds(lsX);
    ESC::escBL.writeMicroseconds(lsX);
    ESC::escBR.writeMicroseconds(lsX);
    ESC::escVL.writeMicroseconds(lsX);
    ESC::escVR.writeMicroseconds(lsX);
  }
  else {
    Serial.println("Couldn't detect a controller. Retrying next tick...");
  }

  delay(Defs::TICK_DELAY);
}
