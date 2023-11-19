#include "mbed.h"

#define PWM_FREQUENCY 20000.0
#define PWM_PULSE_WIDTH (1.0 / PWM_FREQUENCY)
#define PWM_PULSE_WIDTH_US  (PWM_PULSE_WIDTH * 1000000)

class Motor {
public:
    Motor(PinName in1, PinName in2);
    void init();
    void run(double in1, double in2);
    void stop();
        
private:
    PwmOut _in1;
    PwmOut _in2;
};