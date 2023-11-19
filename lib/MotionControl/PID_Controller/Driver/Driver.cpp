#include "Driver.h"
#include "utils.h"

// PWM - DIR - RST - MODE - COAST - BRK
double map(double x, double in_min, double in_max, double out_min, double out_max)
{
    double out = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    return  out > out_max ? out_max : out;
}

Driver::Driver(PinName IN1, PinName IN2) : _IN1(IN1), _IN2(IN2)
{
    _IN1.period(1.0/20000.0);
    _IN2.period(1.0/20000.0);

}

void Driver::init(){
    run(0);
}

double Driver::run(double speed){

    speed = speed / 100.0;

    speed = min(speed, 1.0);
    speed = max(speed, -1.0);

    if(speed < 0){
        _IN1.write(1);
        _IN2.write(1 - std::abs(speed));
    }else{
        _IN1.write(1 - std::abs(speed));
        _IN2.write(1);
    }

    return speed;
}

void Driver::stop(){
    _IN1.write(0);
    _IN2.write(0);  
}

// void Driver::reset(){
//     run(0);
// }
