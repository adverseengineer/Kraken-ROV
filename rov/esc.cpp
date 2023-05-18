
#include <Arduino.h>
#include <Servo.h>

#include <FixedPoints.h>
#include <FixedPointsCommon.h>

#include "esc.h"
#include "control.h"
#include "util.h"
#include "defs.h"

//TODO: get an accelerometer inside the capsule to use to tell when we are tipping
//this will allow us to potentially use any of the six thrusters to right ourselves, rather than just the verticals

namespace Esc {

  //pulse widths to lerp between to communicate with our ESCs
  const uint16_t HALT = 1500;
  const uint16_t REVERSE = 1100;
  const uint16_t FORWARD = 1900;

  //it takes roughly this many ms for our ESCs to initialize after being fed a halt signal
  const uint16_t INIT_DELAY = 7000;

  //coefficients for inputs to limit the speed of the thrusters so we don't draw too many amps
  const float invSqrt2 = 0.7071068;
  const float MOVE_SPEED = 0.6 * invSqrt2;
  const float TURN_SPEED = 0.4;
  const float VERT_SPEED = 0.5;
  
  //servo objects to control each ESC
  Servo esc[6];

  int16_t input[5];
  int16_t oldInput[5];

  //initialize our ESCs
  //TODO: establish two-way communication with our ESCs so we can do this more elegantly
  void Init(void) noexcept {
    Serial.print("Initializing ESCs... ");

    for (auto i = 0; i < 6; i++) {
      pinMode(Defs::PINS[i], OUTPUT);
      esc[i].attach(Defs::PINS[i], REVERSE, FORWARD);
      esc[i].writeMicroseconds(HALT);
    }

    delay(INIT_DELAY);

    Serial.println("ESCs Initialized!");
  }

  void Update(void) noexcept {

    //we track the old and new inputs so that we can check if the sign changed
    //if it did, we write HALT to an ESC for an instant before continuing
    for(auto i = 0; i < 5; i++) {
      oldInput[i] = input[i];
      input[i] = 0;
    }

    //check for the up/down overrides
    //if we are holding up or down on the d-pad, give them full power and prevent any other thrusters from getting power
    if (Control::GetButtonHeld(UP))
      input[4] = Control::HAT_MAX;
    else if (Control::GetButtonHeld(DOWN))
      input[4] = Control::HAT_MIN;
    
    //if neither of the overrides is being used, allow for other inputs
    else {
      //we use the left stick to indicate which way we want to go and how fast
      int16_t c = (int16_t)(Control::GetHat(LeftHatX) * MOVE_SPEED);
      int16_t s = (int16_t)(Control::GetHat(LeftHatY) * MOVE_SPEED);

      //the diagonal pairs are 0,3 and 1,2
      //members of these pairs will always have the same multiplier but opposite sign
      int16_t diag03 = -c + s;
      int16_t diag12 = c + s;
      input[0] += diag03;
      input[1] += diag12;
      input[2] -= diag12;
      input[3] -= diag03;

      //we use the horizontal axis of the right stick to indicate which direction to turn and how fast 
      int16_t r = (int16_t)(Control::GetHat(RightHatX) * TURN_SPEED);
      input[0] += r;
      input[1] -= r;
      input[2] -= r;
      input[3] += r;

      //we use the vertical axis of the right stick to dive and surface
      input[4] = (int16_t)(Control::GetHat(RightHatY) * VERT_SPEED);
    }

    //NOTE: these neg ones are temporary until i can get quintin to swap the wires
    //the thrusters are 3-phase brushless motors, so swapping any two of the three wires will reverse the motor
    input[0] *= -1;
    // input[1] *= -1;
    // input[2] *= -1;
    // input[3] *= -1;
    input[4] *= -1;

    //for each of the lateral thrusters,
    for(auto i = 0; i < 4; i++) {
      
      //if the sign has changed, write a halt signal for an instant first
      if(Util::sgn(input[i]) != Util::sgn(oldInput[i]))
        esc[i].writeMicroseconds(HALT);

      uint16_t sig = map(input[i], Control::HAT_MIN, Control::HAT_MAX, REVERSE, FORWARD);
      esc[i].writeMicroseconds(sig);
    }

    //for both of the vertical thrusters
    int16_t sig = map(input[4], Control::HAT_MIN, Control::HAT_MAX, REVERSE, FORWARD);
    esc[4].writeMicroseconds(sig);
    esc[5].writeMicroseconds(sig);
  }
}
