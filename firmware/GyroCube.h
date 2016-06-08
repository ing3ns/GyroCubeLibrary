/*-------------------------------------------------------------------------
  
  Photon library to control GyroCube based in displays LED RGB 8x8 with chip WS2812B.
  
  --------------------------------------------------------------------*/

/* ======================= GyroCube.h ======================= */
/*--------------------------------------------------------------------
  This file is part of the GyroCube library.

  GyroCube is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation.

  Project:       GyroCube
                 
  Version:       1.0

  Compiler:      Particle Photon

  Author:        Ing3ns
                 
  Date:          5/2016
  --------------------------------------------------------------------*/

#ifndef GyroCube_h
#define GyroCube_h

#include "application.h" 

class GyroCube{

 public:

  // Constructor
   GyroCube();
  ~GyroCube();

  
    begin(void),
    show(void),
    setPixel(uint16_t n, uint8_t r, uint8_t g, uint8_t b),
    setPixel(uint16_t n, uint32_t c),
    setIntensity(uint8_t),
    clear(void);

 private:

  const uint16_t
    LEDs,       // Number of RGB LEDs in strip
    Bytes;      // Size of 'pixels' buffer below
  uint8_t
    pin,           // Output pin number
    Intensity,
   *pixels;        // Holds LED color values (3 bytes each)
  uint32_t
    finalTime;       // Latch timing reference
    uint32_t delay = 50L;
};

#endif // GyroCube_h
