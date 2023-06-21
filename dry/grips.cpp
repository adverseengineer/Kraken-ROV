//Nick Sells, 2023
//ETSU Underwater Robotics

#include <Arduino.h>
#include <Servo.h>

#include "grips.h"
#include "control.h"
#include "util.h"

const static uint8_t PINS[2] = {8, 9};

const static uint16_t OPEN = 1900;
const static uint16_t CLOSED = 1200; //

const static uint16_t OPEN_SPEED = 12;
const static uint16_t CLOSE_SPEED = 12;

static Servo grip[2];
static uint16_t gripPos[2];

//initialize the grippers
void Grips::Init(void) noexcept {
  Serial.print("Initializing Grippers... ");

  for(auto i = 0; i < 2; i++) {
    pinMode(PINS[i], OUTPUT);
    gripPos[i] = OPEN;
    grip[i].attach(PINS[i], CLOSED, OPEN);
    grip[i].writeMicroseconds(gripPos[i]);
  }
  
  Serial.println("Grippers Initialized!");
}

//update the state of the grippers
void Grips::Update(void) noexcept {

  //if the left trigger is held, but the grip is not yet fully closed
  if(unlikely(Control::GetButtonHeld(LT) > 0)) {
    if(gripPos[0] > CLOSED) {
      gripPos[0] -= CLOSE_SPEED;
      grip[0].writeMicroseconds(gripPos[0]);
    }
  }
  //if the left bumper is held, but the grip is not yet fully open
  else if(unlikely(Control::GetButtonHeld(LB))) {
    if(gripPos[0] < OPEN) {
      gripPos[0] += OPEN_SPEED;
      grip[0].writeMicroseconds(gripPos[0]);
    }
  }

  //do all the same again but for right
  if(unlikely(Control::GetButtonHeld(RT) > 0)) {
    if(gripPos[1] > CLOSED) {
      gripPos[1] -= CLOSE_SPEED;
      grip[1].writeMicroseconds(gripPos[1]);
    }
  }
  else if(unlikely(Control::GetButtonHeld(RB))) {
    if(gripPos[1] < OPEN) {
      gripPos[1] += OPEN_SPEED;
      grip[1].writeMicroseconds(gripPos[1]);
    }
  }
}
