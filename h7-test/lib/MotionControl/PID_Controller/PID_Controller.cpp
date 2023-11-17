
#include "PID_Controller.h"

PID_Controller::PID_Controller(PinName pwm, PinName dir, TIM_TypeDef *timer, int pulsesPerRev, int tsample)
    : motor(pwm, dir)
{
    enc = new QEI(pulsesPerRev, tsample, timer);
    pin_pwm = pwm;
}

void PID_Controller::init()
{
    motor.init();
    enc->init();
    //printf("Encoder Init: %lf - CNT: %d\n", enc->getFrequency(), enc->getPulses());
}

void PID_Controller::run(double speed)
{
    motor.run(speed);
    //ThisThread::sleep_for(10ms);
}

double PID_Controller::get_frequency()
{
    return enc->getFrequency();
}

double PID_Controller::get_current_speed_rad_s(){
    return enc->getSpeed();
}

int PID_Controller::get_pulses()
{
    return enc->getPulses();
}

double PID_Controller::runPID(double desired_rad_s)
{
    if(fabs(desired_rad_s) < MOTOR_MIN_SPEED_RAD_S)
        desired_rad_s = 0;
    // Updates de Encoder
    double pwm;
    pwm = adjust_rad_s_to_pwm_pi(desired_rad_s); // Comment to use OLD PID
        // pwm = adjust_rad_s_to_pwm(desired_rad_s); // Uncomment to use OLD PID
    motor.run(pwm);
    return pwm;
}

void PID_Controller::stop(){
    motor.stop();
    //motor_timer.reset();
}

 double PID_Controller::pi(double desired, double measured)
 {
     double error = desired - measured; // erro em rad/s
     P = Kp * error;
     ErrSum += error;
     ErrSum = std::max(std::min(ErrSum, max_I),-max_I);
     I = Ki * ErrSum;

     return P + I;
}

double PID_Controller::adjust_rad_s_to_pwm_pi(double desired_rad_s)
{
    speed_rad_s = enc->getSpeed();
    double adjust_rad_s = pi(desired_rad_s, speed_rad_s);
    adjust_rad_s = std::min(adjust_rad_s, 165.0);
    adjust_rad_s = std::max(adjust_rad_s, -165.0);
    double adjust_pwm = utils::rad_s_to_pwm_pi(adjust_rad_s);
    return adjust_pwm;
}
