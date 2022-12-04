#line 1 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\myFootController.h"
#pragma once

#include "myPCA9685.h"
#include "myInterpolation.h"

class myFootController
{
private:
    myPCA9685 pwm;
    struct footConfig
    {
        float x, y;
        float lagAngle_low, lagAngle_high;
        char lagID_low, lagID_high;
    };
    footConfig footFL, footFR, footBL, footBR;
    float L1=6, L2=5, Ltotal=11;
    myInterpolation tempFLx, tempFLy, tempFRx, tempFRy, tempBLx, tempBLy, tempBRx, tempBRy;

public:
    myFootController(char FLlow, char FLhigh, char FRlow, char FRhigh, char BLlow, char BLhigh, char BRlow, char BRhigh);
    ~myFootController();
    void clacInverseKinematics(float x, float y, float &angleLow, float &angleHigh);
    void moveFootFL(float x, float y);
    void moveFootFR(float x, float y);
    void moveFootBL(float x, float y);
    void moveFootBR(float x, float y);
    void moveAllFootBySecond(long moveMilisecond, float FLx, float FLy, float FRx, float FRy, float BLx, float BLy, float BRx, float BRy);
};  

myFootController::myFootController(char FLlow, char FLhigh, char FRlow, char FRhigh, char BLlow, char BLhigh, char BRlow, char BRhigh)
{
    footFL.lagID_low = FLlow;
    footFL.lagID_high = FLhigh;
    footFR.lagID_low = FRlow;
    footFR.lagID_high = FRhigh;
    footBL.lagID_low = BLlow;
    footBL.lagID_high = BLhigh;
    footBR.lagID_low = BRlow;
    footBR.lagID_high = BRhigh;
    tempFLx.go(0, 0); tempFLy.go(8, 0);
    tempFRx.go(0, 0); tempFRy.go(8, 0);
    tempBLx.go(0, 0); tempBLy.go(8, 0);
    tempBRx.go(0, 0); tempBRy.go(8, 0);
    Serial.println("foot controller initlize");
}

myFootController::~myFootController()
{
}

void myFootController::moveFootFL(float x, float y)
{
    footFL.x = x;
    footFL.y = y;
    if(sqrt(sq(x) + sq(y)) > Ltotal){
        Serial.println("lag move out of range");
        return;
    }
    clacInverseKinematics(x, y, footFL.lagAngle_low, footFL.lagAngle_high);

    // footFL.lagAngle_low = footFL.lagAngle_low;

    pwm.setServoAngle(footFL.lagID_low, footFL.lagAngle_low-10);
    pwm.setServoAngle(footFL.lagID_high, footFL.lagAngle_high-10);
    // Serial.println(String("FL to ")+String(x)+" , " + String(y) + " , " + String(footFL.lagAngle_low) + " , " + String(footFL.lagAngle_high));
}

void myFootController::moveFootFR(float x, float y)
{
    footFR.x = x;
    footFR.y = y;
    if(sqrt(sq(x) + sq(y)) > Ltotal){
        Serial.println("lag move out of range");
        return;
    }
    clacInverseKinematics(x, y, footFR.lagAngle_low, footFR.lagAngle_high);

    // footFR.lagAngle_low = -footFR.lagAngle_low;

    pwm.setServoAngle(footFR.lagID_low, footFR.lagAngle_low-10);
    pwm.setServoAngle(footFR.lagID_high, footFR.lagAngle_high);
    // Serial.println(String("FR to ")+String(x)+" , " + String(y) + " , " + String(footFR.lagAngle_low) + " , " + String(footFR.lagAngle_high));

}

void myFootController::moveFootBL(float x, float y)
{
    footBL.x = x;
    footBL.y = y;
    if(sqrt(sq(x) + sq(y)) > Ltotal){
        Serial.println("lag move out of range");
        return;
    }
    clacInverseKinematics(x, y, footBL.lagAngle_low, footBL.lagAngle_high);

    // footBL.lagAngle_low = -footBL.lagAngle_low;

    pwm.setServoAngle(footBL.lagID_low, footBL.lagAngle_low);
    pwm.setServoAngle(footBL.lagID_high, footBL.lagAngle_high);
    // Serial.println(String("BL to ")+String(x)+" , " + String(y) + " , " + String(footBL.lagAngle_low) + " , " + String(footBL.lagAngle_high));

}

void myFootController::moveFootBR(float x, float y)
{
    footBR.x = x;
    footBR.y = y;
    if(sqrt(sq(x) + sq(y)) > Ltotal){
        Serial.println("lag move out of range");
        return;
    }
    clacInverseKinematics(x, y, footBR.lagAngle_low, footBR.lagAngle_high);

    // footBR.lagAngle_low = -footBR.lagAngle_low;

    pwm.setServoAngle(footBR.lagID_low, footBR.lagAngle_low);
    pwm.setServoAngle(footBR.lagID_high, footBR.lagAngle_high);
    // Serial.println(String("BR to ")+String(x)+" , " + String(y) + " , " + String(footBR.lagAngle_low) + " , " + String(footBR.lagAngle_high));

}

void myFootController::moveAllFootBySecond(long moveMilisecond, float FLx, float FLy, float FRx, float FRy, float BLx, float BLy, float BRx, float BRy)
{
    tempFLx.go(FLx, moveMilisecond);
    tempFLy.go(FLy, moveMilisecond);
    tempFRx.go(FRx, moveMilisecond);
    tempFRy.go(FRy, moveMilisecond);
    tempBLx.go(BLx, moveMilisecond);
    tempBLy.go(BLy, moveMilisecond);
    tempBRx.go(BRx, moveMilisecond);
    tempBRy.go(BRy, moveMilisecond);
    Serial.println("moving");
    while(!tempFLx.isFinished() || !tempFLy.isFinished() || !tempFRx.isFinished() || !tempFRy.isFinished() || !tempBLx.isFinished() || !tempBLy.isFinished() || !tempBRx.isFinished() || !tempBRy.isFinished()){
        Serial.println(String("FL to ")+String(tempFLx.getValue())+" , " + String(tempFLy.getValue()));
        Serial.println(String("FR to ")+String(tempFRx.getValue())+" , " + String(tempFRy.getValue()));
        Serial.println(String("BL to ")+String(tempBLx.getValue())+" , " + String(tempBLy.getValue()));
        Serial.println(String("BR to ")+String(tempBRx.getValue())+" , " + String(tempBRy.getValue()));
        
        moveFootFL(tempFLx.getThenUpdate(), tempFLy.getThenUpdate());
        moveFootFR(tempFRx.getThenUpdate(), tempFRy.getThenUpdate());
        moveFootBL(tempBLx.getThenUpdate(), tempBLy.getThenUpdate());
        moveFootBR(tempBRx.getThenUpdate(), tempBRy.getThenUpdate());
        delay(1);
    }
    Serial.println("move finished");
}


float toDeg(float rad) {
  return rad*4068 / 71;
}

void myFootController::clacInverseKinematics(float x, float y, float &angleLow, float &angleHigh)
{
    float angle1, angle2;
    x+=0.00001;
    y+=0.00001;
    float h = sqrt(sq(x) + sq(y));
    float alpha = atan2(y, x);
    float beta = acos((sq(L2)-sq(L1)-sq(h))/(-2*L1*h));
    float gama = asin(L1*sin(beta)/L2);
    angle1 = alpha - beta;
    angle2 = beta + gama;

    angle1 = -(angle1-(PI/2));

    angle1=toDeg(angle1);
    angle2=toDeg(angle2);



    angleLow = angle2;
    angleHigh = angle1;

    // Serial.println(String("h ")+ String(h)+String("\t alpha ")+
    //  String(alpha)+String("\t beta ")+ String(beta)+String("\t gama ")+
    //   String(gama)+String("\t angle1 ")+ String(angle1)+String("\t angle2 ")+ String(angle2)+
    //    String("\tx ")+ String(x)+String("\ty ")+ String(y)+
    //    String(angle2));
}
