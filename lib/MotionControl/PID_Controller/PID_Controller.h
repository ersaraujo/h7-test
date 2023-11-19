#ifndef PID_CONTROLLER
#define PID_CONTROLLER

#include "mbed.h"
#include "Encoder/Encoder.h"
#include "Encoder/QEI/QEI.h"
// #include "Encoder/QEInterruption/QEInterruption.h"
#include "Driver/Driver.h"
#include "utils.h"

// #define MAX_ERROR_SIZE 2 // Number of PID errors accumulation.
#define MOTOR_MIN_SPEED_RAD_S 4 //Minimun motor speed

class PID_Controller{
    public:

        PID_Controller(PinName pwm, PinName dir, TIM_TypeDef *timer, int pulsesPerRev, int tsample);
        
        void init();
        void stop();
        void run(double speed);
        // void runPWM(double desired_pwm);
      
        double runPID(double desired_rad_s);
        // double runPID_PWM(double desired_pwm);

        double adjust_rad_s_to_pwm_pi(double desired_rad_s);    // Speed in PWM (from PI controller)

        double get_frequency();
        double get_current_speed_rad_s();
        int get_pulses();
        
      private:

        double pi(double desired, double measured);  // With desired and measured outputs control signal
        
        Encoder* enc;
        Driver motor;
        
        PinName pin_pwm;

        double speed_rad_s;
        bool tim8;

        double P = 0;
        double ErrSum = 0;
        double I = 0;
        const double max_I = 3430.35;

        double Kp = 0.107;
        double Ki = 0.0181;

};

#endif /* PID_CONTROLLER */
