//Nick Sells, 2023
//ETSU Underwater Robotics

#ifndef UTIL_H
#define UTIL_H

namespace Util {

  template <typename T> inline int8_t sgn(T val) noexcept {
    return (T(0) < val) - (val < T(0));
  }
}

#endif
