//Nick Sells, 2023
//ETSU Underwater Robotics

#ifndef ESCS_H
#define ESCS_H

#define NUM_ESCS 6

#include <Servo.h>
#include "lowercomms.h"
#include "util.h"

namespace ESCs {

  static constexpr uint8_t PINS[NUM_ESCS] = {2, 3, 4, 5, 6, 7};

  //pulse widths to lerp between to communicate with our ESCs
  static constexpr uint16_t HALT = 1500;
  static constexpr uint16_t REVERSE = 1100;
  static constexpr uint16_t FORWARD = 1900;

  //it takes roughly this many ms for our ESCs to initialize after being fed a halt signal
  static constexpr uint16_t INIT_DELAY = 7000;

  static Servo escs[NUM_ESCS];
  
  static uint16_t pwm[8] = {HALT};
  static uint16_t oldPwm[6] = {HALT};

  //initialize our ESCs
  static inline void Init(void) noexcept {
    Serial.print(F("Initializing Motors... "));

    for(size_t i = 0; i < NUM_ESCS; i++) {
      pinMode(PINS[i], OUTPUT);
      escs[i].attach(PINS[i], REVERSE, FORWARD);
      escs[i].writeMicroseconds(HALT);
    }

    delay(INIT_DELAY);

    Serial.println(F("Motors Initialized!"));
  }

  static inline void Update(void) noexcept {

    for(size_t i = 0; i < NUM_ESCS; i++) {
      //track the old pwm values and fetch the new ones
      oldPwm[i] = pwm[i];
      pwm[i] = LowerComms::signals[i];

      //zero-pass
      if(Util::Sign(oldPwm[i] - 1500) != Util::Sign(pwm[i] - 1500))
        escs[i].writeMicroseconds(1500);

      escs[i].writeMicroseconds(pwm[i]);
    }
  }

}

#endif