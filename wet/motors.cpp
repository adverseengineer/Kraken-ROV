#include "Arduino.h"
//Nick Sells, 2023
//ETSU Underwater Robotics

#include <Servo.h>
#include "motors.h"
#include "lowercomms.h"
#include "util.h"

static constexpr uint8_t PINS[8] = {2, 3, 4, 5, 6, 7, 8, 9};

//pulse widths to lerp between to communicate with our ESCs
static constexpr uint16_t ESC_HALT = 1500;
static constexpr uint16_t ESC_REVERSE = 1100;
static constexpr uint16_t ESC_FORWARD = 1900;

//it takes roughly this many ms for our ESCs to initialize after being fed a halt signal
static constexpr uint16_t ESC_INIT_DELAY = 7000;

static Servo motors[8];

static uint16_t signals[8] = {0};
static uint16_t oldSignals[6] = {0};

void Motors::Init(void) noexcept {
  Serial.print(F("Initializing Motors... "));

  for(size_t i = 0; i < 8; i++) {
    pinMode(PINS[i], OUTPUT);
    motors[i].attach(PINS[i], ESC_REVERSE, ESC_FORWARD);
    motors[i].writeMicroseconds(ESC_HALT);
  }

  delay(ESC_INIT_DELAY);

  Serial.println(F("Motors Initialized!"));
}

void Motors::Update(void) noexcept {
  for(size_t i = 0; i < 6; i++) {
    oldSignals[i] = signals[i];
  }
  LowerComms::GiveSignals(signals); //gets the signals from lowercomms

  
  //zero-pass implementation for each thruster
  for(size_t i = 0; i < 6; i++)
    if(Util::Sign((int)oldSignals[i] - 1500) != Util::Sign((int)signals[i] - 1500))
      motors[i].writeMicroseconds(1500);
  
  //write the escs and the grips
  for(size_t i = 0; i < 8; i++) {
    motors[i].writeMicroseconds(signals[i]);
  }
}

