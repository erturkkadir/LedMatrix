#include <PxMatrix.h>

#define P_LAT 22
#define P_A 19
#define P_B 23
#define P_C 18
#define P_D 5
#define P_OE 2


hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;


//PxMATRIX display(32,32,P_LAT, P_OE,P_A,P_B,P_C);
PxMATRIX display(32,32,P_LAT, P_OE,P_A,P_B,P_C,P_D);
//PxMATRIX display(64,64,P_LAT, P_OE,P_A,P_B,P_C,P_D,P_E);

void IRAM_ATTR display_updater(){
  // Increment the counter and set the time of ISR
  portENTER_CRITICAL_ISR(&timerMux);
  display.display(70);
  display.displayTestPattern(70);
  portEXIT_CRITICAL_ISR(&timerMux);
}


uint16_t myCYAN = display.color565(0, 255, 255);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  display.begin(16);
 
  display.flushDisplay();
  display.setTextColor(myCYAN);
  display.setCursor(2,0);
  display.print("Pixel");
  Serial.println("hello");
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &display_updater, true);
    timerAlarmWrite(timer, 2000, true);
    timerAlarmEnable(timer);
  delay(100);
}


void loop() {

 delay(10);

}
