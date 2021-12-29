#include <M5StickCPlus.h>
#include "RoverC.h"

void loop() {
  M5.update();
   if (M5.BtnA.wasReleased()) {
      delay(1500); 
      Servo_angle(1, 90);
      delay(1000);
      Move_back(50);
      delay(2000);

      Move_left(50);
      delay(2000);

      Move_right(50);
      delay(2000);

      Move_turnleft(30);
      delay(2000);
      Move_turnright(30);
      delay(2000);
      Move_forward(50);
      delay(2000);
      Move_stop(100);
      Servo_angle(1, 0);
      delay(1000); 
  }
}

extern "C" void app_main()
{
    initArduino();
    M5.begin();
  
    M5.Lcd.setRotation(3);
    M5.Lcd.setTextColor(BLUE);
    M5.Lcd.setCursor(80, 60, 4);
    M5.Lcd.printf("RoverC");

    RoverC_Init();
    Move_stop(100);

    while(true) {
        loop();
    }
}