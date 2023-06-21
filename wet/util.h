//Nick Sells, 2023
//ETSU Underwater Robotics

#ifndef UTIL_H
#define UTIL_H

#include <WString.h> //for __FlashStringHelper and F()

#define likely(x) __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)

namespace Util {

  extern void Assert(bool cond, const __FlashStringHelper* msg) noexcept;  
  extern int8_t Sign(int val) noexcept;
}

#endif
