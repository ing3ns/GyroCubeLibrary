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

    void begin(void);
    void show(void);
    void setPixel(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
    void setPixel(uint16_t n, uint32_t c);
    void setIntensity(uint8_t);
    void clear(void);
    void setPixelSide(uint8_t j, uint8_t i, uint32_t c);
    void setPixelSide(uint8_t j, uint8_t i, uint8_t r, uint8_t g, uint8_t b);
 private:

  const uint16_t
    LEDs,
    Bytes;
  uint8_t
    pin,
    Intensity,
   *pixels;
  uint32_t
    finalTime;
    uint32_t delay = 50L;
};

#endif // GyroCube_h
