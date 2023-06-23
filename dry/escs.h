//Nick Sells, 2023
//ETSU Underwater Robotics

#ifndef ESCS_H
#define ESCS_H

#define NUM_ESCS 6

#include <Servo.h>
#include "controls.h"
#include "uppercomms.h"

namespace ESCs {

  //pulse widths to lerp between to communicate with our ESCs
  static constexpr uint16_t HALT = 1500;
  static constexpr uint16_t REVERSE = 1100;
  static constexpr uint16_t FORWARD = 1900;

  //it takes roughly this many ms for our ESCs to initialize after being fed a halt signal
  static constexpr uint16_t INIT_DELAY = 7000;

  //coefficients for inputs to limit the speed of the thrusters so we don't draw too many amps
  static constexpr float MOVE_SPEED = 0.6;
  static constexpr float TURN_SPEED = 0.4;
  static constexpr float VERT_SPEED = 0.5;

  static int8_t input[6];

  //if any of our multipliers are ever greater than one, our math breaks and we overload our thrusters
  static_assert(MOVE_SPEED <= 1);
  static_assert(TURN_SPEED <= 1);
  static_assert(VERT_SPEED <= 1);

  //use the controller input to update the state of our controller
  void Update(void) noexcept {

    //reset all inputs back to zero
    for(size_t i = 0; i < NUM_ESCS; i++)
      input[i] = 0;

    //check for the up/down overrides
    //if we are holding up or down on the d-pad, give them full power and prevent any other thrusters from getting power
    // if(Controls::ButtonHeld(PSB_PAD_UP))
    //   input[4] = input[5] = Controls::ANALOG_MAX;
    // else if(Controls::ButtonHeld(PSB_PAD_DOWN))
    //   input[4] = input[5] = Controls::ANALOG_MIN;
    if(false) (void)0;
    
    //if neither of the overrides is being used, allow for other inputs
    else {

      //get our input axes in the range -127(inclusive) to 127(inclusive)
      // int8_t lx = Controls::Analog(PSS_LX);
      // int8_t ly = Controls::Analog(PSS_LY);
      int8_t rx = Controls::Analog(PSS_RX);
      int8_t ry = Controls::Analog(PSS_RY);

      int8_t val = MOVE_SPEED * 127;
      if(Controls::ButtonHeld(PSB_PAD_UP)) {
        input[0] = val * -1;
        input[1] = val * -1;
        input[2] = -val;
        input[3] = -val;
      }
      else if(Controls::ButtonHeld(PSB_PAD_DOWN)) {
        input[0] = -val * -1;
        input[1] = -val * -1;
        input[2] = val;
        input[3] = val;
      }
      else if(Controls::ButtonHeld(PSB_PAD_LEFT)) {
        input[0] = val * -1;
        input[1] = -val * -1;
        input[2] = val * -1;
        input[3] = -val * -1;
      }
      else if(Controls::ButtonHeld(PSB_PAD_RIGHT)) {
        input[0] = -val * -1;
        input[1] = val * -1;
        input[2] = -val * -1;
        input[3] = val * -1;
      }

      //we use the left stick to indicate which way we want to go and how fast
      //this multiplier will always be less than or equal to one
      //NOTE: we need to cast all the joystick readings to 32-bit here for sqrt to not produce NaN from a negative input caused by integer overflow
      // float mult = MOVE_SPEED / sqrt(2*(((float)lx*(float)lx)+((float)ly*(float)ly))/127);
      // int8_t horz = (int8_t)(lx * mult);
      // int8_t vert = (int8_t)(ly * mult);

      //the diagonal pairs that share a multiplier are 0,3 and 1,2. they do however have opposite signs
      // int8_t diag14 = horz + vert;
      // int8_t diag23 = -horz + vert;
      // input[0] += diag14;
      // input[1] += diag23;
      // input[2] -= diag23;
      // input[3] -= diag14;

      //we use the horizontal axis of the right stick to indicate which direction to turn and how fast 
      int8_t rot = (int8_t)(rx * TURN_SPEED);
      input[0] += rot;
      input[1] -= rot;
      input[2] -= rot;
      input[3] += rot;

      //we use the vertical axis of the right stick to dive and surface
      input[4] = input[5] = (int8_t)(ry * VERT_SPEED);
    }

    //NOTE: these neg ones are temporary until i can get quintin to swap the wires
    //the thrusters are 3-phase brushless motors, so swapping any two of the three wires will reverse the motor
    // input[0] *= -1;
    // input[1] *= -1;
    // input[2] *= -1;
    input[3] *= -1;
    input[4] *= -1;
    input[5] *= -1;

    //use the final net input values to calculate the PWM signals
    for(size_t i = 0; i < NUM_ESCS; i++)
      UpperComms::signals[i] = map(input[i], Controls::ANALOG_MIN, Controls::ANALOG_MAX, REVERSE, FORWARD);
  }

}

#endif
