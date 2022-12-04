#line 1 "d:\\Code\\Arduino\\機電下程式\\type1_main_ver2\\myInterpolation.h"
#pragma once

class myInterpolation
{
private:
    float terget;
    float now;
    float duration;
    float start;
    float step;
public:
    myInterpolation(/* args */);
    ~myInterpolation();
    void go(int terget, int duration);
    void update();
    bool isFinished();
    float getValue();
    float getThenUpdate();
};

myInterpolation::myInterpolation()
{
}

myInterpolation::~myInterpolation()
{
}

void myInterpolation::go(int terget, int duration)
{
    this->terget = terget;
    this->duration = duration;
    this->start = now;
    if(duration != 0){
        this->step = (terget - start) / duration;
    }
    else{
        step=0;
    }
}

void myInterpolation::update()
{
    if (duration == 0)
    {
        now = terget;
        return;
    }
    int delta = terget - start;
    if (delta > 0)
    {
        if (now < terget)
        {
            now += step;
        }
        else
        {
            now = terget;
            duration = 0;
        }
    }
    else
    {
        if (now > terget)
        {
            now += step;
        }
        else
        {
            now = terget;
            duration = 0;
        }
    }
}

bool myInterpolation::isFinished()
{
    return duration == 0;
}

float myInterpolation::getValue()
{
    return now;
}

float myInterpolation::getThenUpdate()
{
    float temp = now;
    update();
    return temp;
}