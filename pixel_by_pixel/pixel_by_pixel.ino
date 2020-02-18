#define PxMATRIX_COLOR_DEPTH 1
#define PxMATRIX_MAX_HEIGHT 32
#define PxMATRIX_MAX_WIDTH 32

#include <PxMatrix.h>
#include <pgmspace.h>
// Pins for LED MATRIX
#define P_A 19
#define P_B 23
#define P_C 18
#define P_D 5
#define P_E 15
#define P_LAT 22
#define P_OE 2
#define CLK 14
#define R0 13

//PxMATRIX display(32,16,P_LAT, P_OE,P_A,P_B,P_C);
PxMATRIX display(32,32,P_LAT, P_OE,P_A,P_B,P_C,P_D);

// Some standard colors
uint16_t myRED = display.color565(255, 0, 0);
uint16_t myGREEN = display.color565(0, 255, 0);
uint16_t myBLUE = display.color565(0, 0, 255);
uint16_t myWHITE = display.color565(255, 255, 255);
uint16_t myYELLOW = display.color565(255, 255, 0);
uint16_t myCYAN = display.color565(128, 128, 255);
uint16_t myMAGENTA = display.color565(255, 0, 255);
uint16_t myBLACK = display.color565(0, 0, 0);


uint16_t myCOLORS[8]={myRED,myGREEN,myBLUE,myWHITE,myYELLOW,myCYAN,myMAGENTA,myBLACK};

unsigned long start_time=0;

void setup() {

 Serial.begin(9600);
  // Define your display layout here, e.g. 1/8 step, and optional SPI pins begin(row_pattern, CLK, MOSI, MISO, SS)
  display.begin(8);

  display.setMuxDelay(1,1,1,1,1);
  
  //display.begin(16, 14, 13, 12, 4);

  // Define multiplex implemention here {BINARY, STRAIGHT} (default is BINARY)
  //display.setMuxPattern(BINARY);

  // Set the multiplex pattern {LINE, ZIGZAG,ZZAGG, ZAGGIZ, WZAGZIG, VZAG, ZAGZIG} (default is LINE)
  //display.setScanPattern(LINE);

  // Rotate display
  //display.setRotate(true);

  // Flip display
  //display.setFlip(true);

  // Helps to reduce display update latency on larger displays
  display.setFastUpdate(true);

  // Control the minimum color values that result in an active pixel
  //display.setColorOffset(5, 5,5);

  // Set the multiplex implemention {BINARY, STRAIGHT} (default is BINARY)
  //display.setMuxPattern(BINARY);

  // Set the time in microseconds that we pause after selecting each mux channel
  // (May help if some rows are missing / the mux chip is too slow)
  //display.setMuxDelay(1,1,1,1,1);

  // Set the number of panels that make up the display area width (default is 1)
  //display.setPanelsWidth(2);

  // Set the brightness of the panels (default is 255)
  //display.setBrightness(50);

  // Set driver chip type
  //display.setDriverChip(FM6124);


  display.setFastUpdate(true);
  display.clearDisplay();
  display.setTextColor(myCYAN);
  display.setCursor(2,2);
  display.print("Kadir Erturk");
  display.setTextColor(myMAGENTA);
  display.setCursor(2,8);
  display.print("Time");
  start_time = millis();
  while((millis()-start_time)<3000)
    display.display(2000);
}

union single_double{
  uint8_t two[2];
  uint16_t one;
} this_single_double;


void draw_pixel(int x1, int y1, uint16_t color) {
  int x2 = x1+1;
  int y2 = y1+1; 
  display.drawLine(x1, y1, x2, y2, color);
}

void scroll_text()
{
    display.setTextWrap(false);  // we don't wrap text so it scrolls nicely
    display.setTextSize(1);
    display.setRotation(0);

    for (int xpos=64; xpos>-140; xpos--)
    {
      display.setTextColor(myWHITE);
      display.clearDisplay();
      display.setCursor(xpos,0);
      display.println("Welcome to My World!");
      start_time = millis();
      while((millis()-start_time)<15)
           display.display(50);
    }
}


void loop() {
  display.clearDisplay();
 
  for (int xx=0; xx<32;xx++) {
    display.drawLine(xx,0, xx, 32, myBLUE);
  }
 
  start_time = millis();
  while((millis()-start_time)<3000)
   display.display(200);
}
