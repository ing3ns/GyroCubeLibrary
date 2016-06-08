
#include "GyroCube.h"

STM32_Pin_Info* PIN_MAP2 = HAL_Pin_Map(); // Pointer required for highest access speed
#define pinLO(_pin) (PIN_MAP2[_pin].gpio_peripheral->BSRRH = PIN_MAP2[_pin].gpio_pin)
#define pinHI(_pin) (PIN_MAP2[_pin].gpio_peripheral->BSRRL = PIN_MAP2[_pin].gpio_pin)
#define pinSet(_pin, _hilo) (_hilo ? pinHI(_pin) : pinLO(_pin))


GyroCube::GyroCube():LEDs(320), Bytes(320*3), pin(2), Intensity(0), pixels(NULL), finalTime(0)
{
  if((pixels = (uint8_t *)malloc(Bytes))) {
    memset(pixels, 0, Bytes);
  }
}

GyroCube::~GyroCube() {
  if(pixels) free(pixels);
  pinMode(pin, INPUT);
}

void GyroCube::begin(void) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void GyroCube::show(void) {
  if(!pixels) return;

  while((micros() - finalTime) < delay);

  __disable_irq();

  volatile uint32_t c,mask;
  
  volatile uint16_t i = Bytes;
  volatile uint8_t j,*ptr = pixels,g,r,b;

    while(i) {
      mask = 0x800000;
      i = i-3;
      g = *ptr++;
      r = *ptr++;
      b = *ptr++;
      c = ((uint32_t)g << 16) | ((uint32_t)r <<  8) | b; // Pack the next 3 bytes to keep timing tight
      j = 0;        // reset the 24-bit counter
      do {
        pinSet(pin, HIGH); // HIGH
        if (c & mask) { // if masked bit is high
          
          //800 uS ==> 77 NOPs
          asm volatile(
            "mov r0, r0" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t"

            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"

            ::: "r0", "cc", "memory");
            
          //450 uS ==> 27 NOPs
          pinSet(pin, LOW); // LOW
          asm volatile(
            "mov r0, r0" "\n\t"

            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t"

            ::: "r0", "cc", "memory");
        }
        else { // else masked bit is low
          //400 uS ==> 24 NOPs
          asm volatile(
            "mov r0, r0" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"

            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t"
            
            ::: "r0", "cc", "memory");
          //850 uS ==> 82 NOPs
          pinSet(pin, LOW); // LOW
          asm volatile(
            "mov r0, r0" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t" "nop" "\n\t"
            "nop" "\n\t" "nop" "\n\t"
            
            ::: "r0", "cc", "memory");
        }
        mask >>= 1;
      } while ( ++j < 24 ); // ... pixel done
    } // end while(i) ... no more pixels
    
  __enable_irq();
  finalTime = micros(); // Save EOD time for latch on next call
}

// Set pixel color from separate R,G,B components:
void GyroCube::setPixel(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
  if(n < LEDs) {
    if(Intensity) { // See notes in setBrightness()
      r = (r * Intensity) >> 8;
      g = (g * Intensity) >> 8;
      b = (b * Intensity) >> 8;
    }
    uint8_t *p = &pixels[n * 3];
    *p++ = g;
    *p++ = r;
    *p = b;
  }
}

void GyroCube::setIntensity(uint8_t b) {

  uint8_t newIntensity = b + 1;
  if(newIntensity != Intensity) { // Compare against prior value
    // Brightness has changed -- re-scale existing data in RAM
    uint8_t  c,
            *ptr           = pixels,
             oldIntensity = Intensity - 1; // De-wrap old brightness value
    uint16_t scale;
    if(oldIntensity == 0) scale = 0; // Avoid /0
    else if(b == 255) scale = 65535 / oldIntensity;
    else scale = (((uint16_t)newIntensity << 8) - 1) / oldIntensity;
    for(uint16_t i=0; i<numBytes; i++) {
      c      = *ptr;
      *ptr++ = (c * scale) >> 8;
    }
    Intensity = newIntensity;
  }
}

void Adafruit_NeoPixel::clear(void) {
  memset(pixels, 0, numBytes);
}
