#include <Arduino.h>
#line 1 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino"
#include <Adafruit_PWMServoDriver.h>
#include <HUSKYLENS.h>
#include <SoftwareSerial.h>
#include <LedControl.h>

#include "myPCA9685.h"
#include "myFootControllerByAngle.h"
#include "myTesk.h"

#define MIN_PULSE_WIDTH       102
#define MAX_PULSE_WIDTH       512

myFootControllerByAngle foots(0, 1, 2, 3, 12, 13, 14, 15);
HUSKYLENS huskylens;


#line 17 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino"
void pwmAllNutral();
#line 21 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino"
void setup();
#line 73 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino"
void loop();
#line 17 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino"
void pwmAllNutral(){
    foots.moveAllFootBlagAngle_Second(0, 0, 0, 0, 0, 0, 0, 0, 0);
}

void setup()
{
    //init serial
	Serial.begin(115200);
    for(int i = 0; i <100; i++)
        Serial.println("starting test.....'");


    //inti type choose pin
    pinMode(8, INPUT);
    pinMode(9, INPUT);
    pinMode(10, INPUT);
    pinMode(11, INPUT);

    //init huskylens
    Wire.begin();
    while (!huskylens.begin(Wire))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
    huskylens.writeAlgorithm(protocolAlgorithm::ALGORITHM_OBJECT_CLASSIFICATION);
    Serial.println("huskylens ready.....'");

    //init numberDisplayer
    displayer.shutdown(0, false);
    displayer.setIntensity(0, 1);
    displayer.clearDisplay(0);
    Serial.println("displayer ready.....'");

    //inti foots
    foots.Init();
    foots.setOffset(-15,-15,-15,-10,-15,-15,-15,-15);
    foots.moveAllFootBlagAngle_Second(100, 0,0,0,0,0,0,0,0);
    foots.moveAllFootBlagAngle_Second(100, 49.48, 22.34, 49.48, 22.34, 49.48, 22.34, 49.48, 22.34);
    Serial.println("displayer ready.....'");

    //ready to go
    Serial.println("start test.....'");
    displayImage(IMAGES[10]);
    delay(2000);
    displayer.clearDisplay(0);
}
int i=0;
// int fa=-5.49, fb=40.8;
// int ma=-29.4, mb=52.92;
// int ba=-39.72, bb=40.8;
// int ua=-49.07, ub=81.89;
// int ufa=-20.79, ufb=72.84;
bool goWalk50, goUpAndDown, goRaiseFoot, goLook;
void loop()
{
	Serial.println(String("go: ") + String(i));
    i++;

        // oneFootUp(foots);
        // walk50cm(foots);
        // squatAndStand(foots);
        // detectNumber(huskylens);



    goWalk50=digitalRead(8)==HIGH;
    goUpAndDown=digitalRead(9)==HIGH;
    goRaiseFoot=digitalRead(10)==HIGH;
    goLook=digitalRead(11)==HIGH;
    if(goWalk50){
        blinkNumTimes(1, 3);
        walk50cm(foots);
    }else if(goUpAndDown){
        blinkNumTimes(2, 3);
        squatAndStand(foots);
    }else if(goRaiseFoot){
        blinkNumTimes(3, 3);
        oneFootUp(foots);
    }else if(goLook){
        blinkNumTimes(4, 3);
        detectNumber(huskylens);
    }else{
        Serial.println("put onr of the 8~11 pin to HIGH");
    }
}
