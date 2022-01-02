#include "services/ServiceManager.h"
#include "services/BluetoothService.h"
#include "services/RoverCService.h"
#include <M5StickCPlus.h>

void loop() {
  Services::ServiceRegistery& serviceManager = Services::ServiceRegistery::GetInstance();
  M5.update();
  if (M5.BtnA.wasReleased()) {

      serviceManager["rover"]["stop"](std::string("100"));
      delay(1500); 
      
      serviceManager["rover"]["servo_angle"](std::string("1, 90"));
      delay(1000);
      
      serviceManager["rover"]["back"](std::string("50"));
      delay(2000);

      serviceManager["rover"]["left"](std::string("50"));
      delay(2000);

      serviceManager["rover"]["right"](std::string("50"));
      delay(2000);

      serviceManager["rover"]["turn_left"](std::string("30"));
      delay(2000);

      serviceManager["rover"]["turn_right"](std::string("30"));
      delay(2000);
      
      serviceManager["rover"]["forward"](std::string("50"));
      delay(2000);
      
      
      serviceManager["rover"]["stop"](std::string("100"));
      serviceManager["rover"]["servo_angle"](std::string("1, 0"));
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
    
    Services::ServiceRegistery& serviceManager = Services::ServiceRegistery::GetInstance();
    serviceManager.RegisterService<Services::RoverCService>("rover");
    //serviceManager.RegisterService<Services::BluetoothService>("bluetooth");
  
    
    Serial.begin(115200);

    int bootcount = 0;
    while(true) {
        //loop();
        Serial.printf("start ESP32 %d\n", bootcount++);
        delay(2000);
        serviceManager["rover"]["forward"](std::string("10"));
    }
}