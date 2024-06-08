#include "Motor.h"

// PWM - DIR  - RST - MODE - COAST - BRK
double map(double x, double in_min, double in_max, double out_min, double out_max)
{
    double out = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    return out;
}

Motor::Motor(PinName pwm,
             PinName dir,
             PinName rst,
             PinName mode,
             PinName coast,
             PinName brk) : _m(pwm),
                            _dir(dir),
                            _rst(rst),
                            _mode(mode),
                            _coast(coast),
                            _break(brk)
{
    _rst.write(0);   // Reset Motor
    _mode.write(1);  // Low Decay (Tiggers we trust)
    _coast.write(0); // Coast
    _break.write(1); // ! Break
    _m.period_us(PWM_PULSE_WIDTH_US);
}

void Motor::init()
{
    _coast.write(0);
    _rst.write(1);
    _m.write(0);
}

double Motor::run(double speed)
{
    _coast.write(1);
    double send_pwm;
    if (_mode == 0)
    {
        _dir.write(0);
        send_pwm = map(speed, -100, 100, 0, 1.0);
        printf("Speed: %f\n", send_pwm);
    }
    else
    {
        if(speed < 0){
            _dir.write(1);
            speed *= -1;

        } else {
            _dir.write(0);
        }

        send_pwm = map(speed, 0, 100, 0, 1.0);
        // printf("Speed: %f\n", send_pwm);
    }

    _m.write(send_pwm);
    return send_pwm;
}