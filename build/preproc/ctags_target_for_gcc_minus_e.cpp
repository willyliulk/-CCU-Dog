# 1 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino"
# 2 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino" 2
# 3 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino" 2
# 4 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino" 2
# 5 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino" 2

# 7 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino" 2
# 8 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino" 2
# 9 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino" 2




myFootControllerByAngle foots(0, 1, 2, 3, 12, 13, 14, 15);
HUSKYLENS huskylens;


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
    pinMode(8, 0x0);
    pinMode(9, 0x0);
    pinMode(10, 0x0);
    pinMode(11, 0x0);

    //init huskylens
    Wire.begin();
    while (!huskylens.begin(Wire))
    {
        Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 39 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 39 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino"
                      "Begin failed!"
# 39 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino" 3
                      ); &__c[0];}))
# 39 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino"
                      )));
        Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 40 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 40 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino"
                      "1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"
# 40 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino" 3
                      ); &__c[0];}))
# 40 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino"
                      )));
        Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 41 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 41 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino"
                      "2.Please recheck the connection."
# 41 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino" 3
                      ); &__c[0];}))
# 41 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\type1_main_ver2.ino"
                      )));
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



    goWalk50=digitalRead(8)==0x1;
    goUpAndDown=digitalRead(9)==0x1;
    goRaiseFoot=digitalRead(10)==0x1;
    goLook=digitalRead(11)==0x1;
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
