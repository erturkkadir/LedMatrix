// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#define PIN        25 
#define NUMPIXELS 1024 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

int getPos(int x, int y) {
  int ledPos = 0;
  int even = 0;
  if((x%2)==0) even = 17;
  if(x<17) {
    if(y<17) { // zone 1
      ledPos = (x-1)*16 - (pow(-1, x) * y) + even;
    } else {   // zone 2
      ledPos = (x-1)*16 - (pow(-1, x) * (y-16)) + 256 + even;  
    }
  } else {
    if(y<17) {  // zone 3
      ledPos = (x-1)*16 - (pow(-1, x) * y) + 512 + even;
    } else {    // zone 4
      ledPos = (x-1)*16 - (pow(-1, x) * (y-16))+ 256 +even;
    }
  }
  return ledPos-1;
}

void loop() {
  int k=0;
  pixels.clear();
  int cx = 16;
  int cy = 16;
  int r = 10;

  float sqr = 0;
  int y = 0;
  int pos = 0;

//  pos = getPos(1, 1);
//  pixels.setPixelColor(0, pixels.Color(8, 8, 8));
//  pixels.show();
//  pixels.setPixelColor(388, pixels.Color(8, 8, 8));
//  pixels.setPixelColor(412, pixels.Color(8, 8, 8));
//  pixels.setPixelColor(422, pixels.Color(8, 8, 8));
//  pixels.setPixelColor(442, pixels.Color(8, 8, 8));
//  pixels.setPixelColor(455, pixels.Color(8, 8, 8));
//  pixels.setPixelColor(473, pixels.Color(8, 8, 8));
//  pixels.setPixelColor(488, pixels.Color(8, 8, 8));
//  pixels.setPixelColor(505, pixels.Color(8, 8, 8));
//  pixels.setPixelColor(520, pixels.Color(8, 8, 8));
//  pixels.setPixelColor(537, pixels.Color(8, 8, 8));
//  pixels.setPixelColor(551, pixels.Color(8, 8, 8));
//  pixels.setPixelColor(570, pixels.Color(8, 8, 8));
//  pixels.setPixelColor(582, pixels.Color(8, 8, 8));
//  pixels.setPixelColor(604, pixels.Color(8, 8, 8));
//  pixels.setPixelColor(612, pixels.Color(8, 8, 8));
//  pixels.setPixelColor(881, pixels.Color(8, 8, 8));
// pixels.show();
    
  for(int x=-r; x<=r; x++) {
    y = round(sqrt(r*r-(x*x)));
    pos = getPos(x+cx, y+cy);
    pixels.setPixelColor(pos, pixels.Color(8, 8, 8));    
    pos = getPos(x+cx, -y+cy);
    pixels.setPixelColor(pos, pixels.Color(8, 8, 8));
  }
  pixels.show();
  delay(5000);

}
