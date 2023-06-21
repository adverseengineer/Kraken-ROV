#include "PS2X_lib.h"
//Nick Sells, 2023
//ETSU Underwater Robotics

#include <Arduino.h>
#include <Servo.h>

#include "controls.h"
#include "motors.h"
#include "uppercomms.h"

//positions for the grip servos
const static uint16_t GRIP_OPEN = 1900;
const static uint16_t GRIP_CLOSED = 1200;

//amounts to increment the grip servo positions by
const static uint16_t GRIP_OPEN_SPEED = 14;
const static uint16_t GRIP_CLOSE_SPEED = 14;

//pulse widths to lerp between to communicate with our ESCs
const static uint16_t ESC_HALT = 1500;
const static uint16_t ESC_REVERSE = 1100;
const static uint16_t ESC_FORWARD = 1900;

//it takes roughly this many ms for our ESCs to initialize after being fed a halt signal
const static uint16_t INIT_DELAY = 7000;

//coefficients for inputs to limit the speed of the thrusters so we don't draw too many amps
const static float MOVE_SPEED = 0.6;
const static float TURN_SPEED = 0.4;
const static float VERT_SPEED = 0.5;

static uint8_t input[6];
static uint16_t sigs[8];

namespace ESCs {

  void Update(void) noexcept {
    //for each motor
    for(size_t i = 0; i < 6; i++)
      input[i] = 0;

    //check for the up/down overrides
    //if we are holding up or down on the d-pad, give them full power and prevent any other thrusters from getting power
    if(Controls::ButtonHeld(PSB_PAD_UP))
      input[4] = input[5] = Controls::ANALOG_MAX;
    else if(Controls::ButtonHeld(PSB_PAD_DOWN))
      input[4] = input[5] = Controls::ANALOG_MIN;
    
    //if neither of the overrides is being used, allow for other inputs
    else {

      //we use the left stick to indicate which way we want to go and how fast
      //8 bits is still enough for these because the multipliers will always be <=1
      uint8_t x = Controls::Analog(PSS_LX);
      uint8_t y = Controls::Analog(PSS_LY);
      float mult = MOVE_SPEED / sqrt(2*(x*x+y*y));
      uint8_t horz = (uint8_t)(x * mult);
      uint8_t vert = (uint8_t)(y * mult);

      //the diagonal pairs that share a multiplier are 0,3 and 1,2. they do however have opposite signs
      uint8_t diag03 = -horz + vert;
      uint8_t diag12 = horz + vert;
      input[0] += diag03;
      input[1] += diag12;
      input[2] -= diag12;
      input[3] -= diag03;

      //we use the horizontal axis of the right stick to indicate which direction to turn and how fast 
      int8_t r = (int8_t)(Controls::Analog(PSS_RX) * TURN_SPEED);
      input[0] += r;
      input[1] -= r;
      input[2] -= r;
      input[3] += r;

      //we use the vertical axis of the right stick to dive and surface
      input[4] = input[5] = (int8_t)(Controls::Analog(PSS_RY) * VERT_SPEED);
    }

    //NOTE: these neg ones are temporary until i can get quintin to swap the wires
    //the thrusters are 3-phase brushless motors, so swapping any two of the three wires will reverse the motor
    // input[0] *= -1;
    // input[1] *= -1;
    // input[2] *= -1;
    // input[3] *= -1;
    // input[4] *= -1;
    // input[5] *= -1;

    for(size_t i = 0; i < 6; i++)
      sigs[i] = map(input[i], Controls::ANALOG_MIN, Controls::ANALOG_MAX, ESC_REVERSE, ESC_FORWARD);
  }
}

namespace Servos {
  void Update(void) noexcept {
    //if the left trigger is held, but the grip is not yet fully closed
    if(Controls::ButtonHeld(PSB_L2) > 0) {
      if(sigs[6] > GRIP_CLOSED)
        sigs[6] -= GRIP_CLOSE_SPEED;
    }
    //if the left bumper is held, but the grip is not yet fully open
    else if(Controls::ButtonHeld(PSB_L1)) {
      if(sigs[6] < GRIP_OPEN)
        sigs[6] += GRIP_OPEN_SPEED;
    }

    //do all the same again but for right
    if(Controls::ButtonHeld(PSB_R2) > 0) {
      if(sigs[7] > GRIP_CLOSED)
        sigs[7] -= GRIP_CLOSE_SPEED;
    }
    else if(Controls::ButtonHeld(PSB_R1)) {
      if(sigs[7] < GRIP_OPEN)
        sigs[7] += GRIP_OPEN_SPEED;
    }
  }
}

//update the virtual state of all motors
void Motors::Update(void) noexcept {

  ESCs::Update();
  Servos::Update();

  UpperComms::GetSignals(sigs); //pass the signals off to our comms code
}
