
#include <Arduino.h>
#include <Servo.h>

#include "esc.h"
#include "control.h"
#include "defs.h"

namespace Esc {

  //pulse widths to lerp between to communicate with our ESCs
  const uint16_t HALT = 1500;
  const uint16_t REVERSE = 1100;
  const uint16_t FORWARD = 1900;

  //it takes roughly this many ms for our ESCs to initialize after being fed a halt signal
  const uint16_t INIT_DELAY = 7000;

  //coefficients for inputs to limit the speed of the thrusters so we don't draw too many amps
  const float MOVE_SPEED = 0.6f;
  const float TURN_SPEED = 0.4f;
  const float VERT_SPEED = 0.5f;
  const float invSqrt2 = 0.7071f;

  //servo objects to control each ESC
  Servo esc[6];

  int32_t moveInput[4];
  int32_t turnInput[4];

  int32_t combinedInput[4];
  int32_t oldCombinedInput[4];

  int32_t vertInput;

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

  void UpdateInputs(void) noexcept {

    //NOTE: any -1's are temporary, the wires just need to be swapped

    //check for the up/down overrides
    //if we are holding up or down on the d-pad, give them full power and prevent any other thrusters from getting power
    if (Control::GetButtonHeld(UP)) {
      vertInput = (Control::HAT_MAX) * -1;
      for(auto i = 0; i < 4; i++) {
        moveInput[i] = 0;
        turnInput[i] = 0;
      }
      return;
    }
    else if (Control::GetButtonHeld(DOWN)) {
      vertInput = (Control::HAT_MIN) * -1;
      for(auto i = 0; i < 4; i++) {
        moveInput[i] = 0;
        turnInput[i] = 0;
      }
      return;
    }

    //we use the left stick to indicate which way we want to go and how fast
    float mult = invSqrt2 * MOVE_SPEED;
    int32_t c = (int32_t)(Control::GetHat(LeftHatX) * mult);
    int32_t s = (int32_t)(Control::GetHat(LeftHatY) * mult);
    moveInput[0] = (c + s);
    moveInput[1] = (-c + s) * -1;
    moveInput[2] = (c - s) * -1;
    moveInput[3] = (-c - s) * -1; //NOTE: temporary neg one mult bc the wires need to be swapped

    //we use the horizontal axis of the right stick to indicate which direction to turn and how fast
    int32_t r = (int32_t)(Control::GetHat(RightHatX) * TURN_SPEED);
    turnInput[0] = (r);
    turnInput[1] = (-r) * -1;
    turnInput[2] = (-r) * -1;
    turnInput[3] = (r) * -1; //NOTE: temporary neg one mult bc the wires need to be swapped

    //we use the vertical axis of the right stick to dive and surface
    vertInput = (int32_t)(Control::GetHat(RightHatY) * VERT_SPEED) * -1;
  }

  void ApplyInputs(void) noexcept {

    for (auto i = 0; i < 4; i++) {
      combinedInput[i] = moveInput[i] + turnInput[i];

      uint16_t sig = map(combinedInput[i], Control::HAT_MIN, Control::HAT_MAX, REVERSE, FORWARD);
      esc[i].writeMicroseconds(sig);
    }

    int16_t vertSig = map(vertInput, Control::HAT_MIN, Control::HAT_MAX, REVERSE, FORWARD);
    for (auto i = 4; i < 6; i++)
      esc[i].writeMicroseconds(vertSig);
  }
}