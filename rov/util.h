//Nick Sells, 2023
//ETSU Underwater Robotics

#ifndef UTIL_H
#define UTIL_H

#include <WString.h> //for __FlashStringHelper

namespace Util {

  template <typename T> extern void Assert(T cond, const __FlashStringHelper* msg) noexcept;  
  template <typename T> extern int8_t sgn(T val) noexcept;

}

#endif
