
#ifndef DEFS_H
#define DEFS_H

namespace Defs {

  //how many ms to wait before setup to avoid the glitch where setup is called twice
  const uint8_t STARTUP_DELAY = 90;
  //how many ms to wait between each tick
  const uint8_t TICK_DELAY = 1;

  //TODO: edit these as the rov is wired
  namespace Pins {
    const uint8_t FL = 2;
    const uint8_t FR = 3;
    const uint8_t BL = 4;
    const uint8_t BR = 5;
    const uint8_t VL = 6;
    const uint8_t VR = 7;
    const uint8_t GRIPL = 0;
    const uint8_t GRIPR = 0;
    const uint8_t LIGHTL = 0;
    const uint8_t LIGHTR = 0;
  }
}

#endif
