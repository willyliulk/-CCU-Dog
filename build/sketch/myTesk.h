#line 1 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\myTesk.h"
#include "myPCA9685.h"
#include "myFootControllerByAngle.h"
#include <Adafruit_PWMServoDriver.h>
#include <LedControl.h>
LedControl displayer(7, 6, 5);

const uint64_t IMAGES[] = {
  0x3c66666e76663c00,
  0x7e1818181c181800,
  0x7e060c3060663c00,
  0x3c66603860663c00,
  0x30307e3234383000,
  0x3c6660603e067e00,
  0x3c66663e06663c00,
  0x1818183030667e00,
  0x3c66663c66663c00,
  0x3c66607c66663c00,
  0x3c66c399db7e1818,
  0xc3e77e3c3c7ee7c3
};
const int IMAGES_LEN = sizeof(IMAGES)/8;
void displayImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      displayer.setLed(0, i, j, bitRead(row, j));
    }
  }
}


void walk50cm(myFootControllerByAngle &foots){
    int flow = 23.57, ftop = 32.51;
    int blow = 23.57, btop = -11.11;
    int mlow = 49.48, mtop = 22.34;
    int tlow = 97.18, ttop = 38.64;
    for(int times=0; times < 9; times++){
    foots.moveAllFootBlagAngle_Second(50, blow, btop, flow, ftop, tlow, ttop, mlow, mtop);
    foots.moveAllFootBlagAngle_Second(50, mlow, mtop, tlow, ttop, flow, ftop, blow, btop);
    foots.moveAllFootBlagAngle_Second(50, flow, ftop, blow, btop, mlow, mtop, tlow, ttop);
    foots.moveAllFootBlagAngle_Second(50, tlow, ttop, mlow, mtop, blow, btop, flow, ftop);
    }
}

void squatAndStand(myFootControllerByAngle &foots){
    foots.moveAllFootBlagAngle_Second(100, 0,0,0,0,0,0,0,0);
        foots.moveAllFootBlagAngle_Second(100, 0,0,20,90,0,0,20,90);


    foots.moveAllFootBlagAngle_Second(100, 20,90,20,90,20,90,20,90);
    delay(5000);
    foots.moveAllFootBlagAngle_Second(100, 90,90,90,90,90,90,90,90);
    foots.moveAllFootBlagAngle_Second(100, 0,0,0,0,0,0,0,0);
    delay(5000);
}

void oneFootUp(myFootControllerByAngle &foots){
    foots.moveAllFootBlagAngle_Second(100, -10,90,0,0,0,0,0,0);
    delay(5000);
    foots.moveAllFootBlagAngle_Second(100, 0,0,0,0,0,0,0,0);
    delay(5000);
}

void detectNumber(HUSKYLENS &huskylens){
      while(1){
        if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
        else
        {
            Serial.println(F("###########"));
            while (huskylens.available())
            {
                HUSKYLENSResult result = huskylens.read();
                // Serial.println(String()+ "iter: " + i+ " result: " + result.ID);
                int id = result.ID-1;
                huskylens.customText(String(id), 160, 120);
                if(0<=id && id<=9){
                    displayImage(IMAGES[id]);
                }
                else{
                    displayImage(IMAGES[11]);
                }
            }    
        }
        delay(500);
}
}

void blinkNumTimes(int num, int times){
    for(int i=0; i<times; i++){
        displayImage(IMAGES[num]);
        delay(500);
        displayer.clearDisplay(0);
        delay(500);
    }
}