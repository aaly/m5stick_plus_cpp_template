#include "RoverCService.h"
#include <M5StickCPlus.h>

namespace Services {

  Result<std::string> RoverCService::Init() {    //sda  0     scl  26
      Result<std::string> result;
      //Wire.begin(static_cast<int>(0), static_cast<int>(26), static_cast<uint32_t>(100));
      Wire.begin(0, 26, 100);

      AddCallback(std::string("forward"), [&](const std::string& data) { 
        Move_stop(100);
        return Move_forward(10); });

      result.SetStatus(StatusType::SUCCESS);
      return result;
  }

  Result<std::string> RoverCService::Send_iic(uint8_t Register, uint8_t Speed) {
    Result<std::string> result;
    Wire.beginTransmission(ROVER_ADDRESS);
    Wire.write(Register);
    Wire.write(Speed);
    Wire.endTransmission();
    return result;
  }

  Result<std::string> RoverCService::Move_forward(int8_t Speed) {
    Result<std::string> result;
    Send_iic(0x00, Speed );
    Send_iic(0x01, Speed );
    Send_iic(0x02, Speed );
    Send_iic(0x03, Speed );
    return result;
  }

  Result<std::string> RoverCService::Move_back(int8_t Speed) {
    Result<std::string> result;
    Send_iic(0x00, (-1) * Speed );
    Send_iic(0x01, (-1) * Speed );
    Send_iic(0x02, (-1) * Speed );
    Send_iic(0x03, (-1) * Speed );
    return result;
  }

  Result<std::string> RoverCService::Move_turnleft(int8_t Speed) {
    Result<std::string> result;
    Send_iic(0x00, Speed );
    Send_iic(0x01, (-1) * Speed );
    Send_iic(0x02, Speed );
    Send_iic(0x03, (-1) * Speed );
    return result;
  }

  Result<std::string> RoverCService::Move_turnright(int8_t Speed) {
    Result<std::string> result;
    Send_iic(0x00, (-1) * Speed );
    Send_iic(0x01, Speed );
    Send_iic(0x02, (-1) * Speed );
    Send_iic(0x03, Speed );
    return result;
  }

  Result<std::string> RoverCService::Move_left(int8_t Speed) {
    Result<std::string> result;
    Send_iic(0x00, (-1) * Speed );
    Send_iic(0x01, Speed );
    Send_iic(0x02, Speed );
    Send_iic(0x03, (-1) * Speed );
    return result;
  }

  Result<std::string> RoverCService::Move_right(int8_t Speed) {
    Result<std::string> result;
    Send_iic(0x00, Speed );
    Send_iic(0x01, (-1) * Speed );
    Send_iic(0x02, (-1) * Speed );
    Send_iic(0x03, Speed );
    return result;
  }

  Result<std::string> RoverCService::Move_stop(int8_t Speed) {
    Result<std::string> result;
    Send_iic(0x00, 0 );
    Send_iic(0x01, 0 );
    Send_iic(0x02, 0 );
    Send_iic(0x03, 0 );
    return result;
  }

  Result<std::string> RoverCService::Servo_angle(uint8_t Servo_ch, uint8_t degree) {
    Result<std::string> result;
    degree = min(90, int(degree));
    degree = max(0, int(degree));
    Send_iic((Servo_ch - 1) | 0x10 ,int(degree));
    return result;
  }

  Result<std::string> RoverCService::Servo_pulse(uint8_t Servo_ch, uint16_t width) {
    Result<std::string> result;
    width = min(2500, int(width));
    width = max(500, int(width));
    Send_iic((Servo_ch - 1) | 0x20, width);
    return result;
  }
  
} //namespace Services