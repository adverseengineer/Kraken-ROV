
#ifndef UTIL_H
#define UTIL_H

namespace Util {

  inline template <typename T> int8_t sgn(T val) noexcept {
    return (T(0) < val) - (val < T(0));
  }
}

#endif
