#include "mbed.h"

#define PWM_FREQUENCY 50000.0
#define PWM_PULSE_WIDTH (1.0 / PWM_FREQUENCY)
#define PWM_PULSE_WIDTH_US (PWM_PULSE_WIDTH * 1000000)

class Motor
{
public:
    Motor(PinName pwm, PinName dir, PinName rst, PinName mode, PinName coast, PinName brk);
    void init();
    double run(double speed);
    void stop();

private:
    PwmOut _m;
    DigitalOut _dir;
    DigitalOut _rst;
    DigitalOut _mode;
    DigitalOut _coast;
    DigitalOut _break;
};