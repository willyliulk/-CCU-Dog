#pragma once
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

class myPCA9685
{
private:
  Adafruit_PWMServoDriver pwm;
  uint16_t micorMin=500, micorMid=1500, micorMax=2500;
public:
  myPCA9685(){
  };
  ~myPCA9685(){
  };

  void Init(){
    pwm=Adafruit_PWMServoDriver();
    pwm.begin();
    // pwm.wakeup();
    pwm.setPWMFreq(50);
  }

  /*set angle between -90 ~ 90 to ServoID*/
  void setServoAngle(int ServoID,int angle){
    pwm.writeMicroseconds(ServoID, map(angle, -90, 90, micorMax, micorMin));
    // Serial.println(String(ServoID) + ": " + String(map(angle, -90, 90, micorMax, micorMin)));
  };
};
