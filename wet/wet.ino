//Nick Sells, 2023
//ETSU Underwater Robotics

#include <PS2X_lib.h>

#include "lowercomms.h"
#include "escs.h"
#include "grips.h"

const int STARTUP_DELAY = 300;
const int TICK_DELAY = 1;
const int BAUD_RATE = 9600;

void setup(void) noexcept {
  delay(STARTUP_DELAY);
  Serial.begin(BAUD_RATE);
  Serial.println("Wet/Lower Arduino");
  
  LowerComms::Init();
  ESCs::Init();
  Grips::Init();
}

void loop(void) noexcept {

  LowerComms::Update();
  ESCs::Update();
  Grips::Update();
  delay(TICK_DELAY);
}
