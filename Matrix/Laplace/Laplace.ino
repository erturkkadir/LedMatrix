#include <Adafruit_NeoPixel.h>
#include "arduinoFFT.h"

#define PIN         25 
#define NUMPIXELS 1024

const int16_t n  =  32;
const int16_t n2 = n/2;
 
double frq = 100;

double vReal[n];
double vImag[n];

int cx = 15;
int cy = 15;

int r, g, b;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

arduinoFFT FFT = arduinoFFT(); /* Create FFT object */

void setup() {
  Serial.begin(9600);
//  Serial.clear();
  pixels.setBrightness(20);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void setData() {
  for(int i=0; i<n; i++) {
    vReal[i] = sin(2.0*3.14*i*frq/n);
    vImag[i] = 0;
  }
}

void draw_axis() {
  int pos;
  for(int x=-16; x<16; x++) {    
    pos = getPos(x, 0);
    pixels.setPixelColor(pos, pixels.Color(16, 0, 0));    
  }
  for(int y=-15; y<=16; y++) {
    pos = getPos(0, y);
    pixels.setPixelColor(pos, pixels.Color(0, 0, 16));    
  } 
  pixels.show();
}

void draw_corners() {
  /* Draw four corners */
  int pos = 0;
  
  pos = getPos(-16, 16); pixels.setPixelColor(pos, pixels.Color(32,   0, 32));
  pos = getPos( -1, 16); pixels.setPixelColor(pos, pixels.Color( 0,  32,  0));
  pos = getPos(-16,  1); pixels.setPixelColor(pos, pixels.Color( 0,   0, 32));
  pos = getPos( -1,  1); pixels.setPixelColor(pos, pixels.Color(32,  32, 32));
  
  pos = getPos( 0,16); pixels.setPixelColor(pos, pixels.Color( 32,  0,  0));
  pos = getPos(15,16); pixels.setPixelColor(pos, pixels.Color(  0, 32,  0));
  pos = getPos( 0, 1); pixels.setPixelColor(pos, pixels.Color(  0,  0,  32));
  pos = getPos(15, 1); pixels.setPixelColor(pos, pixels.Color( 32, 32,  32));
  
  pos = getPos(-1, 0); pixels.setPixelColor(pos, pixels.Color( 0,  0, 32));
  pos = getPos(-16,0); pixels.setPixelColor(pos, pixels.Color( 0,  0, 32));
  pos = getPos(-16,-15); pixels.setPixelColor(pos, pixels.Color( 0,  0, 32));
  pos = getPos( -1,-15); pixels.setPixelColor(pos, pixels.Color( 0,  0, 32));

  pos = getPos(  0,  0); pixels.setPixelColor(pos, pixels.Color(32, 32, 32));
  pos = getPos(  0,-15); pixels.setPixelColor(pos, pixels.Color(32, 32, 32));
  pos = getPos( 15,  0); pixels.setPixelColor(pos, pixels.Color(32, 32, 32));
  pos = getPos( 15,-15); pixels.setPixelColor(pos, pixels.Color(32, 32, 32));  
  pixels.show();
}

int getPos(int x, int y) {  
  String zone = "";
  int ledPos = 0;  
  bool even;
  even = (x%2==0);
  
  if(x<0) {
    if(y>0) { // zone 1
      zone = "Zone 1";
      if(even) 
        ledPos = (16+x)*16 - (y+x) + (16+x); 
      else
        ledPos = (16+x)*16 - 16*pow(-1,x)+y-17;      
    } else {   // zone 3
      zone = "Zone 3";
      if(even)
        ledPos = (x+16)*16 + 16*pow(-1,x) - y + 256 - 16;
      else
        ledPos = (x+16)*16 + y + 255 + 16;
    }
  } else {
    if(y>0) {  
      zone = "zone 2";      
      if(even)
        ledPos = (16+x)*16 - (y-x) + (16+x) + 512; 
      else
        ledPos = (16+x)*16 - 16*pow(-1,x)+y-17 + 512;
    } else {   
      zone = "zone 4";      
      if(even)
        ledPos = (16+x)*16 +16*pow(-1,x)-y+256-16;
      else
        ledPos = (16+x)*16 + y +255 +16;
    }
  }
  return ledPos;
}

void colorScale(double mag) {
  double sMax = 0.04;
  Serial.print("mag : ");
  Serial.print(mag); 
  r = 1;
  g = 1;
  b = 1;
  if(mag >0        && mag<sMax*1/4) {r =   0, g=   0; b = 255;}
  if(mag >sMax*1/4 && mag<sMax*2/4) {r =   0, g= 255; b = 255;}
  if(mag >sMax*2/4 && mag<sMax*3/4) {r = 255, g= 255; b =   0;}
  if(mag >sMax*3/4 && mag<sMax*4/4) {r = 255, g=   0; b =   0;}  
  if(mag >sMax) {r = 255, g= 0; b = 0;}    
}

void getSignal(int j) {
}  

void loop() {  
  int pos = 0;
 
  //draw_axis();
  
  setData();  
//  
//  // for(int j=-16; j<16; j++) 
  int i = 0;
//  {
// 
    getSignal(0);
    
    FFT.Compute(vReal, vImag, n, FFT_FORWARD);

    Serial.println("+ frq");
    for(int j=0; j<n2; j++) {
      double real = vReal[j]*vReal[j];
      double imag = vImag[j]*vImag[j];
      double mag = sqrt(real*real+imag*imag)/n;
      colorScale(mag);
      pos = getPos(0, j);
      pixels.setPixelColor(pos, pixels.Color(r, g, b));      
      Serial.print(" j : ");Serial.print(j);
      Serial.print(" mag : ");Serial.println(mag);
    }
    Serial.println("- frq");

    for(int j=n2; j<n; j++) {
      double real = vReal[j]*vReal[j];
      double imag = vImag[j]*vImag[j];
      double mag = sqrt(real*real+imag*imag)/n;
      colorScale(mag);
      pos = getPos(0, j);
      pixels.setPixelColor(pos, pixels.Color(r, g, b));
      Serial.print(" j : ");Serial.print(j);
      Serial.print(" mag : ");Serial.println(mag);
    }
    pixels.show();
  
  delay(10000);
}
