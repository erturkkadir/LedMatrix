// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        25 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1024 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

int pos = 0;

void setup() {
  Serial.begin(9600);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

int getPos(int x, int y) {
  int shift = 0;
  if ( (y % 2) == 0) shift = 17; 
  int pos = y*16 + pow(-1, y)*x - shift;  
  return pos;
}

void loop() {
  int k=0;
  pixels.clear();
  delay(1000);
  for(int i=0;i<32;i++) {
    for(int j=0; j<32; j++) {
      pixels.setPixelColor(k++, pixels.Color(0, 0, 16));
      Serial.println(i+j);
      pixels.show();
      delay(100);
    }
  }
   delay(10000); 
}
