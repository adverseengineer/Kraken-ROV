//Nick Sells, 2023
//ETSU Underwater Robotics

#include "util.h"

namespace Util {

  //soft-resets the board
  //NOTE: we are just declaring the function and telling the compiler that it lives at address 0x00
  //the function body doesn't matter. the reset is caused by jumping to 0x00 when called
  void(* resetFunc) (void) = 0;

  //asserts that a given condition is true. if it isn't, soft reset the whole board
  template <typename T> void Assert(T cond, const __FlashStringHelper* msg) noexcept {
    if(cond != T(0)) {
      Serial.print("Assertion failed: ");
      Serial.println(msg);
      Serial.println("Resetting...");
      resetFunc();
    }
  }

  //returns -1 if val is negative, 1 if positive
  template <typename T> int8_t sgn(T val) noexcept {
    return (T(0) < val) - (val < T(0));
  }

}
