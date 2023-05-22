//Nick Sells, 2023
//ETSU Underwater Robotics

#include <HardwareSerial.h> //for Serial.print
#include "util.h"

//soft-resets the board
//NOTE: we initialize this function pointer to 0x00. calling it makes the instruction pointer
//jump to that address, effectively restarting the board
void(* resetFunc) (void) = 0x00;

//asserts that a given condition is true. if it isn't, soft reset the whole board
void Util::Assert(bool cond, const __FlashStringHelper* msg) noexcept {
  if(unlikely(cond == false)) {
    Serial.print(F("Assertion failed: "));
    Serial.println(msg);
    Serial.println(F("Resetting..."));
    resetFunc();
  }
}

//returns -1 if val is negative, 1 if positive
int8_t Util::Sign(int val) noexcept {
  return (0 < val) - (val < 0);
}
