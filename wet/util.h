//Nick Sells, 2023
//ETSU Underwater Robotics

#ifndef UTIL_H
#define UTIL_H

#define likely(x) __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)

namespace Util {

  template <typename T> int Sign(T val) {
    return (T(0) < val) - (val < T(0));
  }
}

#endif
