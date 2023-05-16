
#ifndef DEFS_H
#define DEFS_H

namespace Defs {

  //how many ms to wait before setup to avoid the glitch where setup is called twice
  const uint8_t STARTUP_DELAY = 90;
  //how many ms to wait between each tick
  const uint8_t TICK_DELAY = 17;

  //TODO: edit these as the rov is wired
  const uint8_t PINS[] = {2, 3, 4, 5, 6, 7, 8, 9, 0, 0};

  namespace Pins {
    const uint8_t FL = PINS[0];
    const uint8_t FR = PINS[1];
    const uint8_t BL = PINS[2];
    const uint8_t BR = PINS[3];
    const uint8_t VL = PINS[4];
    const uint8_t VR = PINS[5];
    const uint8_t GRIPL = PINS[6];
    const uint8_t GRIPR = PINS[7];
    const uint8_t LIGHTL = PINS[8];
    const uint8_t LIGHTR = PINS[9];
  }
}

#endif
