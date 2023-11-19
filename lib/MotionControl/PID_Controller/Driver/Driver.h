#include "mbed.h"

#ifndef Driver_H
#define Driver_H

#define MAX_SPEED 1.0f

class Driver
{
    public: 
        Driver(PinName pwm, PinName dir);

        void    init (void);
        double  run(double speed);
        void    stop(void);
        // void    reset();

    private:
        PwmOut _IN1;
        PwmOut _IN2;
};

#endif