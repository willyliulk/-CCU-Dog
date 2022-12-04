#line 1 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\myFootControllerByAngle.h"
#pragma once

#include "myPCA9685.h"
#include "myInterpolation.h"

class myFootControllerByAngle
{
private:
    myPCA9685 pwm;
    struct footConfig
    {
        float lagAngle_low, lagAngle_high;
        float offSetAngle_low, offSetAngle_high;
        char lagID_low, lagID_high;
    };
    footConfig footFL, footFR, footBL, footBR;
    float L1=6, L2=5, Ltotal=11;
    myInterpolation tempFL_Angle_Low, tempFL_Angle_High, tempFR_Angle_Low, tempFR_Angle_High, tempBL_Angle_Low, tempBL_Angle_High, tempBR_Angle_Low, tempBR_Angle_High;

public:
    myFootControllerByAngle(char FLlow, char FLhigh, char FRlow, char FRhigh, char BLlow, char BLhigh, char BRlow, char BRhigh);
    ~myFootControllerByAngle();
    void Init();
    void clacInverseKinematics(float lagAngle_low, float lagAngle_high, float &angleLow, float &angleHigh);
    void setOffset(float FL_Angle_Low, float FL_Angle_High, float FR_Angle_Low, float FR_Angle_High, float BL_Angle_Low, float BL_Angle_High, float BR_Angle_Low, float BR_Angle_High);
    void moveFootFL(float lagAngle_low, float lagAngle_high);
    void moveFootFR(float lagAngle_low, float lagAngle_high);
    void moveFootBL(float lagAngle_low, float lagAngle_high);
    void moveFootBR(float lagAngle_low, float lagAngle_high);
    void moveAllFootBlagAngle_Second(long moveMilisecond, float FL_Angle_Low, float FL_Angle_High, float FR_Angle_Low, float FR_Angle_High, float BL_Angle_Low, float BL_Angle_High, float BR_Angle_Low, float BR_Angle_High);
};  

myFootControllerByAngle::myFootControllerByAngle(char FLlow, char FLhigh, char FRlow, char FRhigh, char BLlow, char BLhigh, char BRlow, char BRhigh)
{
    footFL.lagID_low = FLlow;
    footFL.lagID_high = FLhigh;
    footFR.lagID_low = FRlow;
    footFR.lagID_high = FRhigh;
    footBL.lagID_low = BLlow;
    footBL.lagID_high = BLhigh;
    footBR.lagID_low = BRlow;
    footBR.lagID_high = BRhigh;
    tempFL_Angle_Low.go(0, 0); tempFL_Angle_High.go(8, 0);
    tempFR_Angle_Low.go(0, 0); tempFR_Angle_High.go(8, 0);
    tempBL_Angle_Low.go(0, 0); tempBL_Angle_High.go(8, 0);
    tempBR_Angle_Low.go(0, 0); tempBR_Angle_High.go(8, 0);
    Serial.println("foot controller initlize");
}

myFootControllerByAngle::~myFootControllerByAngle()
{
}

void myFootControllerByAngle::Init(){
    pwm.Init();
}

void myFootControllerByAngle::setOffset(float FL_Angle_Low, float FL_Angle_High, float FR_Angle_Low, float FR_Angle_High, float BL_Angle_Low, float BL_Angle_High, float BR_Angle_Low, float BR_Angle_High){
    footFL.offSetAngle_low=FL_Angle_Low;
    footFL.offSetAngle_high=FL_Angle_High;
    footFR.offSetAngle_low=FR_Angle_Low;
    footFR.offSetAngle_high=FR_Angle_High;
    footBL.offSetAngle_low=BL_Angle_Low;
    footBL.offSetAngle_high=BL_Angle_High;
    footBR.offSetAngle_low=BR_Angle_Low;
    footBR.offSetAngle_high=BR_Angle_High;
}

void myFootControllerByAngle::moveFootFL(float lagAngle_low, float lagAngle_high)
{
    footFL.lagAngle_low = lagAngle_low;
    footFL.lagAngle_high = lagAngle_high;


    pwm.setServoAngle(footFL.lagID_low, footFL.lagAngle_low+footFL.offSetAngle_low);
    pwm.setServoAngle(footFL.lagID_high, footFL.lagAngle_high+footFL.offSetAngle_high);
    // Serial.println(String("FL to ")+String(lagAngle_low)+" , " + String(lagAngle_high) + " , " + String(footFL.lagAngle_low) + " , " + String(footFL.lagAngle_high));
}

void myFootControllerByAngle::moveFootFR(float lagAngle_low, float lagAngle_high)
{
    footFR.lagAngle_low = lagAngle_low;
    footFR.lagAngle_high = lagAngle_high;


    pwm.setServoAngle(footFR.lagID_low, footFR.lagAngle_low+footFR.offSetAngle_low);
    pwm.setServoAngle(footFR.lagID_high, footFR.lagAngle_high+footFR.offSetAngle_high);
    // Serial.println(String("FR to ")+String(lagAngle_low)+" , " + String(lagAngle_high) + " , " + String(footFR.lagAngle_low) + " , " + String(footFR.lagAngle_high));

}

void myFootControllerByAngle::moveFootBL(float lagAngle_low, float lagAngle_high)
{
    footBL.lagAngle_low = lagAngle_low;
    footBL.lagAngle_high = lagAngle_high;


    pwm.setServoAngle(footBL.lagID_low, footBL.lagAngle_low+footBL.offSetAngle_low);
    pwm.setServoAngle(footBL.lagID_high, footBL.lagAngle_high+footBL.offSetAngle_high);
    // Serial.println(String("BL to ")+String(lagAngle_low)+" , " + String(lagAngle_high) + " , " + String(footBL.lagAngle_low) + " , " + String(footBL.lagAngle_high));

}

void myFootControllerByAngle::moveFootBR(float lagAngle_low, float lagAngle_high)
{
    footBR.lagAngle_low = lagAngle_low;
    footBR.lagAngle_high = lagAngle_high;


    pwm.setServoAngle(footBR.lagID_low, footBR.lagAngle_low+footBR.offSetAngle_low);
    pwm.setServoAngle(footBR.lagID_high, footBR.lagAngle_high+footBR.offSetAngle_high);
    // Serial.println(String("BR to ")+String(lagAngle_low)+" , " + String(lagAngle_high) + " , " + String(footBR.lagAngle_low) + " , " + String(footBR.lagAngle_high));

}
// void delayMicroseconds_m(uint32_t us){
//   uint32_t start = micros();
//   while(micros() - start < us){int a=0;}
// }
void myFootControllerByAngle::moveAllFootBlagAngle_Second(long moveMilisecond, float FL_Angle_Low, float FL_Angle_High, float FR_Angle_Low, float FR_Angle_High, float BL_Angle_Low, float BL_Angle_High, float BR_Angle_Low, float BR_Angle_High)
{
    tempFL_Angle_Low.go(FL_Angle_Low, moveMilisecond);
    tempFL_Angle_High.go(FL_Angle_High, moveMilisecond);
    tempFR_Angle_Low.go(FR_Angle_Low, moveMilisecond);
    tempFR_Angle_High.go(FR_Angle_High, moveMilisecond);
    tempBL_Angle_Low.go(BL_Angle_Low, moveMilisecond);
    tempBL_Angle_High.go(BL_Angle_High, moveMilisecond);
    tempBR_Angle_Low.go(BR_Angle_Low, moveMilisecond);
    tempBR_Angle_High.go(BR_Angle_High, moveMilisecond);
    Serial.println("moving");
    int i =0;
    while(!tempFL_Angle_Low.isFinished() || !tempFL_Angle_High.isFinished() || !tempFR_Angle_Low.isFinished() || !tempFR_Angle_High.isFinished() || !tempBL_Angle_Low.isFinished() || !tempBL_Angle_High.isFinished() || !tempBR_Angle_Low.isFinished() || !tempBR_Angle_High.isFinished()){
        // Serial.println(String("FL to ")+String(tempFL_Angle_Low.getValue())+" , " + String(tempFL_Angle_High.getValue()));
        // Serial.println(String("FR to ")+String(tempFR_Angle_Low.getValue())+" , " + String(tempFR_Angle_High.getValue()));
        // Serial.println(String("BL to ")+String(tempBL_Angle_Low.getValue())+" , " + String(tempBL_Angle_High.getValue()));
        // Serial.println(String("BR to ")+String(tempBR_Angle_Low.getValue())+" , " + String(tempBR_Angle_High.getValue()));
        // Serial.println(String("iter: ")+String(i++));
        moveFootFL(tempFL_Angle_Low.getThenUpdate(), tempFL_Angle_High.getThenUpdate());
        moveFootFR(tempFR_Angle_Low.getThenUpdate(), tempFR_Angle_High.getThenUpdate());
        moveFootBL(tempBL_Angle_Low.getThenUpdate(), tempBL_Angle_High.getThenUpdate());
        moveFootBR(tempBR_Angle_Low.getThenUpdate(), tempBR_Angle_High.getThenUpdate());
        delay(1);
    }
    Serial.println("move finished");
}


float toDeg(float rad) {
  return rad*4068 / 71;
}

void myFootControllerByAngle::clacInverseKinematics(float lagAngle_low, float lagAngle_high, float &angleLow, float &angleHigh)
{
    float angle1, angle2;
    lagAngle_low+=0.00001;
    lagAngle_high+=0.00001;
    float h = sqrt(sq(lagAngle_low) + sq(lagAngle_high));
    float alpha = atan2(lagAngle_high, lagAngle_low);
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
    //    String("\tlagAngle_low ")+ String(lagAngle_low)+String("\tlagAngle_high ")+ String(lagAngle_high)+
    //    String(angle2));
}
