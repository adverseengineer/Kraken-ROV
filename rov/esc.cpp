
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
  const float MOVE_SPEED = 0.35f;//0.5f;
  const float TURN_SPEED = 0.15f;//0.3f;
  const float VERT_SPEED = 0.5f;//0.5f;
  const float invSqrt2 = 0.7071f;

  //servo objects to control each ESC
  Servo esc[4];
  Servo escVL;
  Servo escVR;

  int32_t moveInput[4];
  int32_t turnInput[4];

  int32_t combinedInput[4];
  int32_t oldCombinedInput[4];

  int32_t vertInput;
  int32_t oldVertInput;

  //initialize our ESCs
  //TODO: establish two-way communication with our ESCs so we can do this more elegantly
  void Init(void) noexcept {
    Serial.print("Initializing ESCs... ");

    //init the four lateral escs
    pinMode(Defs::Pins::FL, OUTPUT);
    pinMode(Defs::Pins::FR, OUTPUT);
    pinMode(Defs::Pins::BL, OUTPUT);
    pinMode(Defs::Pins::BR, OUTPUT);
    esc[0].attach(Defs::Pins::FL, REVERSE, FORWARD);
    esc[1].attach(Defs::Pins::FR, REVERSE, FORWARD);
    esc[2].attach(Defs::Pins::BL, REVERSE, FORWARD);
    esc[3].attach(Defs::Pins::BR, REVERSE, FORWARD);
    for (auto i = 0; i < 4; i++)
      esc[i].writeMicroseconds(HALT);
    
    //init the two vertical ones
    pinMode(Defs::Pins::VL, OUTPUT);
    pinMode(Defs::Pins::VR, OUTPUT);
    escVL.attach(Defs::Pins::VL, REVERSE, FORWARD);
    escVR.attach(Defs::Pins::VR, REVERSE, FORWARD);
    escVL.writeMicroseconds(HALT);
    escVR.writeMicroseconds(HALT);

    delay(INIT_DELAY);

    Serial.println("ESCs Initialized!");
  }

  void UpdateInputs(void) noexcept {
    //we use the left stick to indicate which way we want to go and how fast
    float mult = invSqrt2 * MOVE_SPEED;
    int32_t c = (int32_t)(Control::JoyL.x * mult);
    int32_t s = (int32_t)(Control::JoyL.y * mult);
    moveInput[0] = c + s;
    moveInput[1] = -c + s;
    moveInput[2] = c - s;
    moveInput[3] = -c - s;

    //we use the horizontal axis of the right stick to indicate which direction to turn and how fast
    int32_t r = (int32_t)(Control::JoyR.x * TURN_SPEED);
    turnInput[0] = r;
    turnInput[1] = -r;
    turnInput[2] = -r;
    turnInput[3] = r;

    //we use the vertical axis of the right stick to dive and surface
    vertInput = (int32_t)(Control::JoyR.y * VERT_SPEED);
  }

  void ApplyInputs(void) noexcept {

    // Serial.print("sigs: { ");

    for (auto i = 0; i < 4; i++) {
      combinedInput[i] = moveInput[i] + turnInput[i];

      uint16_t sig = map(combinedInput[i], Control::HAT_MIN, Control::HAT_MAX, REVERSE, FORWARD);
      esc[i].writeMicroseconds(sig);
      // Serial.print(i);
      // Serial.print(": ");
      // Serial.print(sig);
      // Serial.print(", ");
    }

    int16_t vertSig = map(vertInput, Control::HAT_MIN, Control::HAT_MAX, REVERSE, FORWARD);
    escVL.writeMicroseconds(vertSig);
    escVR.writeMicroseconds(vertSig);
  }
}