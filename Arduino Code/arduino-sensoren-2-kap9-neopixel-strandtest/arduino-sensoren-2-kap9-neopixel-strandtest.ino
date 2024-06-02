// Neopixel-Streifen
// Datei: arduino-sensoren-2-kap9-neopixel-strandtest.ino

#include <Adafruit_NeoPixel.h>

// Pin Neopixel
#define PIN 6

// Parameter 1 = Anzahl der Pixel im Streifen
// Parameter 2 = Arduino-Pin
// Parameter 3 = Pixeltyp-Flag
//   NEO_KHZ800  800 KHz Bitstream (die meisten NeoPixel mit WS2812-LEDs)
//   NEO_KHZ400  400 KHz (klassische Version 'v1' (nicht v2) FLORA-Pixel, WS2811-Treiber)
//   NEO_GRB     Pixel für GRB-Bitstream (die meisten NeoPixel-Produkte)
//   NEO_RGB     Pixel für RGB-Bitstream (v1 FLORA-Pixel, nicht v2)
//   NEO_RGBW    Pixel für RGBW-Bitstream (NeoPixel-RGBW-Produkte)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, PIN, NEO_GRB + NEO_KHZ800);


void setup() 
{
  // Neopixel starten
  strip.begin();
  // Alle Pixel ausschalten
  strip.show();
  // Helligkeit (0 bis 255)
  strip.setBrightness(20);
}

void loop() 
{
  // Pixel-Farben
  colorWipe(strip.Color(255, 0, 0), 50); // Rot
  delay(500);
  colorWipe(strip.Color(0, 255, 0), 50); // Grün
  delay(500);
  colorWipe(strip.Color(0, 0, 255), 50); // Blau
  delay(500);

  
  //colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  // Send a theater pixel chase in...
  //theaterChase(strip.Color(127, 127, 127), 50); // White
  //theaterChase(strip.Color(127, 0, 0), 50); // Red
  //theaterChase(strip.Color(0, 0, 127), 50); // Blue

  //rainbow(20);
  //rainbowCycle(20);
  //theaterChaseRainbow(50);
  
}



// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
