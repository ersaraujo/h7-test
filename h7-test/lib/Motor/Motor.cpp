#include "Motor.h"

// PWM - DIR
double map(double x, double in_min, double in_max, double out_min, double out_max)
{   
    if (x < in_min){
        return out_min;
    }
    else if (x > in_max){
        return out_max;
    }
    else{
        double out = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
        return out;
    }
}

Motor::Motor(PinName in1, PinName in2) :
    _in1(in1), _in2(in2)
{  
    _in1.period(PWM_PULSE_WIDTH);
    _in2.period(PWM_PULSE_WIDTH);
}

void Motor::init(){
    _in1.write(0);
    _in2.write(0);
}

void Motor::run(double input_1, double input_2) {
    _in1.write(input_1);
    _in2.write(input_2);
}

void Motor::stop() {
    run(0, 0);
}