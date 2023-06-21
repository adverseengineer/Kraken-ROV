//Nick Sells, 2023
//ETSU Underwater Robotics

#ifndef LOWERCOMMS_H
#define LOWERCOMMS_H

#include <PS2X_lib.h>

namespace LowerComms {

  extern void Init(void) noexcept;
  extern void Update(void) noexcept;
}

struct DataChunk {
  uint16_t sigs[8];
  bool LL, LR;
  inline DataChunk(void) noexcept {}
  inline void Print(void) noexcept {
    Serial.print("{ ");
    for(size_t i = 0; i < 8; i++) {
      Serial.print(sigs[i]);
      Serial.print(' ');
    }
    Serial.print(LL);
    Serial.print(' ');
    Serial.print(LR);
    Serial.println(" }");
  }
};

#endif
