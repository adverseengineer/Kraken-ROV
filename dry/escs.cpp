#include "PS2X_lib.h"
//Nick Sells, 2023
//ETSU Underwater Robotics

#include <Arduino.h>
#include <Servo.h>

#include "escs.h"
#include "controls.h"
#include "util.h"

//TODO: get an accelerometer inside the capsule to use to tell when we are tipping
//this will allow us to potentially use any of the six thrusters to right ourselves, rather than just the verticals

const static uint8_t PINS[6] = {2, 3, 4, 5, 6, 7};

//pulse widths to lerp between to communicate with our ESCs
const static uint16_t HALT = 1500;
const static uint16_t REVERSE = 1100;
const static uint16_t FORWARD = 1900;

//it takes roughly this many ms for our ESCs to initialize after being fed a halt signal
const static uint16_t INIT_DELAY = 7000;

//coefficients for inputs to limit the speed of the thrusters so we don't draw too many amps
const static float invSqrt2 = 0.7071068;
const static float MOVE_SPEED = 0.6 * invSqrt2;
const static float TURN_SPEED = 0.4;
const static float VERT_SPEED = 0.5;

static Servo esc[6];
static uint8_t input[6];
static uint8_t oldInput[6];

//initialize our ESCs
void ESCs::Init(void) noexcept {
  Serial.print(F("Initializing ESCs... "));

  for(size_t i = 0; i < 6; i++) {
    pinMode(PINS[i], OUTPUT);
    esc[i].attach(PINS[i], REVERSE, FORWARD);
    esc[i].writeMicroseconds(HALT);
  }

  delay(INIT_DELAY);

  Serial.println(F("ESCs Initialized!"));
}

//update the state of our ESCs
void ESCs::Update(void) noexcept {

  //we track the old and new inputs so that we can check if the sign changed
  //if it did, we write HALT to an ESC for an instant before continuing
  for(size_t i = 0; i < 6; i++) {
    oldInput[i] = input[i];
    input[i] = 0;
  }

  //check for the up/down overrides
  //if we are holding up or down on the d-pad, give them full power and prevent any other thrusters from getting power
  if(Controls::ButtonHeld(PSB_PAD_UP))
    input[4] = input[5] = Controls::ANALOG_MAX;
  else if(Controls::ButtonHeld(PSB_PAD_DOWN))
    input[4] = input[5] = Controls::ANALOG_MIN;
  
  //if neither of the overrides is being used, allow for other inputs
  else {
    //we use the left stick to indicate which way we want to go and how fast
    int8_t c = (int8_t)(Controls::Analog(PSS_LX) * MOVE_SPEED);
    int8_t s = (int8_t)(Controls::Analog(PSS_LY) * MOVE_SPEED);

    //the diagonal pairs are 0,3 and 1,2
    //members of these pairs will always have the same multiplier but opposite sign
    int16_t diag03 = -c + s;
    int16_t diag12 = c + s;
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
  input[0] *= -1;
  // input[1] *= -1;
  // input[2] *= -1;
  // input[3] *= -1;
  input[4] *= -1;
  input[5] *= -1;

  for(size_t i = 0; i < 6; i++) {
    
    //if the sign has changed, write a halt signal for an instant first
    if(Util::Sign(input[i]) != Util::Sign(oldInput[i]))
      esc[i].writeMicroseconds(HALT);

    uint8_t sig = map(input[i], Controls::ANALOG_MIN, Controls::ANALOG_MAX, REVERSE, FORWARD);
    esc[i].writeMicroseconds(sig);
  }
}

//PSB_PAD_UP
//PSB_PAD_DOWN
//PSB_PAD_LEFT
//PSB_PAD_RIGHT

//PSB_L1
//PSB_L2
//PSB_L3

//PSB_R1
//PSB_R2
//PSB_R3

//PSB_CROSS
//PSB_CIRCLE
//PSB_TRIANGLE
//PSB_SQUARE

//for any of the PSB_* constants, there is also PSAB_*, meant for use with ps2x.Analog

//PSS_LX
//PSS_LY
//PSS_RX
//PSS_RY

//You can read any button as analog with ps2x.Analog
//analog returns an 8-bit unsigned integer

//ps2x.Analog(axis) gets analog values from sticks
//ps2x.Button(button): true if button is currently pressed
//ps2x.ButtonPressed(button): true if button was just pressed
//ps2x.ButtonReleased(button): true if button was just released
//ps2x.NewButtonState(button): true if button was just pressed OR released
//ps2x.NewButtonState(void): true if ANY button was just pressed OR released
//ps2x.ButtonDataByte(void): returns the entire button flags integer
  //NOTE: this is supposedly the state of the buttons