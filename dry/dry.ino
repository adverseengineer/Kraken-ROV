//Nick Sells, 2023
//ETSU Underwater Robotics

#include <Servo.h>

#include "escs.h"
#include "grips.h"
#include "controls.h"
#include "uppercomms.h"


//how many ms to wait before setup to avoid the glitch where setup is called twice 
const int STARTUP_DELAY = 300;
//how many ms to wait between each tick
const int TICK_DELAY = 1;
//the rate at which we want to transmit serial data
const int BAUD_RATE = 9600;

void setup(void) {
  delay(STARTUP_DELAY);
  Serial.begin(BAUD_RATE);
  Serial.println("Dry/Upper Arduino");

  UpperComms::Init();
  Controls::Init();
}

void loop(void) {

  Controls::Update();
  ESCs::Update();
  Grips::Update();
  UpperComms::Update();
  delay(TICK_DELAY);
}
 