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
static constexpr uint16_t GRIP_OPEN_SPEED = 14;
static constexpr uint16_t GRIP_CLOSE_SPEED = 14;

//pulse widths to lerp between to communicate with our ESCs
static constexpr uint16_t ESC_HALT = 1500;
static constexpr uint16_t ESC_REVERSE = 1100;
static constexpr uint16_t ESC_FORWARD = 1900;

//it takes roughly this many ms for our ESCs to initialize after being fed a halt signal
static constexpr uint16_t INIT_DELAY = 7000;

//coefficients for inputs to limit the speed of the thrusters so we don't draw too many amps
static constexpr float MOVE_SPEED = 0.6;
static constexpr float TURN_SPEED = 0.4;
static constexpr float VERT_SPEED = 0.5;

static int8_t input[6];
static uint16_t sigs[8] = {ESC_HALT, ESC_HALT, ESC_HALT, ESC_HALT, ESC_HALT, ESC_HALT, GRIP_OPEN, GRIP_OPEN};

static constexpr float mountAngles[4] = {
  2.35619449019,
  0.785398163397,
  -2.35619449019,
  -0.785398163397
};

static_assert(MOVE_SPEED <= 1);
static_assert(TURN_SPEED <= 1);
static_assert(VERT_SPEED <= 1);

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

      //get our input axes in the range -127(inclusive) to 127(inclusive)
      // int8_t lx = Controls::Analog(PSS_LX);
      // int8_t ly = Controls::Analog(PSS_LY);
      int8_t rx = Controls::Analog(PSS_RX);
      int8_t ry = Controls::Analog(PSS_RY);

      int8_t val = MOVE_SPEED * 127;
      if(Controls::ButtonHeld(PSB_PAD_UP)) {
        input[0] = val;
        input[1] = val;
        input[2] = -val;
        input[3] = -val;
      }
      else if(Controls::ButtonHeld(PSB_PAD_DOWN)) {
        input[0] = -val;
        input[1] = -val;
        input[2] = val;
        input[3] = val;
      }
      else if(Controls::ButtonHeld(PSB_PAD_LEFT)) {
        input[0] = val;
        input[1] = -val;
        input[2] = val;
        input[3] = -val;
      }
      else if(Controls::ButtonHeld(PSB_PAD_RIGHT)) {
        input[0] = -val;
        input[1] = val;
        input[2] = -val;
        input[3] = val;
      }

      // float lsAngle = atan2(-ly,lx);

      // Serial.print('(');
      // Serial.print(lx);
      // Serial.print(", ");
      // Serial.print(ly);
      // Serial.print(") (");
      // Serial.print(rx);
      // Serial.print(", ");
      // Serial.print(ry);
      // Serial.println(')');

      //we use the left stick to indicate which way we want to go and how fast
      //this multiplier will always be less than or equal to one

      // Serial.print("lx: ");
      // Serial.print(lx);
      // Serial.print(" | ly: ");
      // Serial.print(ly);
      // float a = 2*(((float)lx*(float)lx)+((float)ly*(float)ly))/127;
      // Serial.print(" | a: ");
      // Serial.print(a);
      // float m = sqrt(a);
      // Serial.print(" | m: ");
      // Serial.print(m);
      //NOTE: we need to cast all the joystick readings to 32-bit here for sqrt to not produce NaN from a negative input caused by integer overflow
      // float mult = MOVE_SPEED / sqrt(a);
      // int8_t horz = (int8_t)(lx * mult);
      // int8_t vert = (int8_t)(ly * mult);
      // Serial.print(" | 0.6*m: ");
      // Serial.print(mult);
      // Serial.print(" | lx*mult: ");
      // Serial.print(lx*mult);
      // Serial.print(" | ly*mult: ");
      // Serial.print(ly*mult);
      // Serial.print(" | horz: ");
      // Serial.print(horz);
      // Serial.print(" | vert: ");
      // Serial.println(vert);

      // for(size_t i = 0; i < 4; i++) {
      //   float c = cos(lsAngle - mountAngles[i]);
      //   Serial.println(c);
      //   input[i] += MOVE_SPEED * c;
      // }

      

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
    // input[3] *= -1;
    // input[4] *= -1;
    // input[5] *= -1;

    for(size_t i = 0; i < 6; i++)
      sigs[i] = map(input[i], Controls::ANALOG_MIN, Controls::ANALOG_MAX, ESC_REVERSE, ESC_FORWARD);
      
      Serial.print("{ ");
      for(size_t i = 0; i < 8; i++) {
        Serial.print(sigs[i]);
        Serial.print(' ');
      }
      Serial.println('}');
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
