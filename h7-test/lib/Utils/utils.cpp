#include "utils.h"

namespace utils {
    //New control parameters: param_angular * x + param_linear
    double param_angular_pos = 0.5216;
    double param_angular_neg = 0.5188;
    double param_linear_pos = 8.973;
    double param_linear_neg =  -8.572;

    //OLD control M1, M2, M3, M4
    //26 - 80 PWM
    double param_linear_high = -0.013224680654642617;
    double param_angular_high = 0.5747438597464971;

    //16 - 25 PWM
    double param_linear_med = -0.007091802443299156;
    double param_angular_med = 0.8732608145568327;
    //11 - 15 PWM
    double param_linear_low = 0.009218162479061202;
    double param_angular_low = 1.4021732662260056;
    // 0 - 11 PWM
    double param_linear_ex_low = -0.03891500283241567;
    double param_angular_ex_low = 2.4368664502124703;

    //To control M5
    //9.4 - 22 PWM == -13.44 ~ -314.159 RAD/S
    double param_linear_r1 = 210.9059206;
    double param_angular_r1 = -23.8665873;
    //22 - 38 PWM == -314.159 ~ -688.158 RAD/S
    double param_linear_r2 = 200.089625;
    double param_angular_r2 = -23.3749375;
    //38 - 53 PWM == -688.158 ~ -1002.318 RAD/S
    double param_linear_r3 = 107.714;
    double param_angular_r3 = -20.944;
    //53 - 73 PWM == -1002.318 ~ -1436.150 RAD/S
    double param_linear_r4 = 127.3368;
    double param_angular_r4 = -20.600;
    //73 PWM == -1436.150 RAD/S
    double param_linear_r5 = 140.3368;
    double param_angular_r5 = -20.320;

    DigitalIn PBT1(PIN_PB1);
    DigitalIn PBT2(PIN_PB2);
    DigitalIn SW1(PIN_SELECTOR_1);
    DigitalIn SW2(PIN_SELECTOR_2);
    DigitalIn SW3(PIN_SELECTOR_3);
    DigitalIn SW4(PIN_SELECTOR_4);
    PwmOut Buzzer(PIN_BUZZER);

    AnalogIn BATT(PIN_BATT);

    void initRobot(){
        printf("Booting Robot....id %d\n", getRobotId());
        Buzzer.period_us(DEFAULT_BUZZER_CYCLE);
        Status::init(PIN_RGB);
        Status::send(0x0000FF, DRIBBLER_LED);
        Buzzer.write(DEFAULT_BUZZER_FREQUENCY);
        Status::sendAllColor(0x00FF00, 80);
        Buzzer.write(0);
        ThisThread::sleep_for(80ms);
        Buzzer.write(DEFAULT_BUZZER_FREQUENCY);
        Status::sendAllColor(0x00FF00, 80);
        Buzzer.write(0);
        ThisThread::sleep_for(80ms);
        Buzzer.write(DEFAULT_BUZZER_FREQUENCY);
        Status::sendAllColor(0x00FF00, 80);
        Buzzer.write(0);
        Status::clearColors();
    }

    bool timerMillisExpired(const Timer& timer, double time){
      return timerRead<chrono::milliseconds>(timer) > time;
    }

    double timerMillisRead(const Timer& timer){
      return timerRead<chrono::milliseconds>(timer);
    }

    //New line equation to control M1, M2, M3, M4
    double rad_s_to_pwm_pi(double rad_s)
    {
        double param_angular = param_angular_pos;
        double param_linear = param_linear_pos;

        if (fabs(rad_s) < MOTOR_MIN_SPEED_RAD_S) {
            return 0;
        }
        if (rad_s < 0)
        {
            param_angular = param_angular_neg;
            param_linear = param_linear_neg;
        }
        return (param_angular * rad_s) + param_linear;
    }

    // OLD line equation to control M1, M2, M3, M4 to avoid conflicts with new pid
    double rad_s_to_pwm(double rad_s)
    {
        double param_linear = param_linear_high;
        double param_angular = param_angular_high;
        if(rad_s <= 30 && rad_s >= -30){
            if(rad_s <= 12 && rad_s >= -12){
                if(rad_s <= 5 && rad_s >= -5){
                        param_linear = param_linear_ex_low;
                        param_angular = param_angular_ex_low;
                    } else {
                        param_linear = param_linear_low;
                        param_angular = param_angular_low;
                    }
            } else {
                param_linear = param_linear_med;
                param_angular = param_angular_med;
            }

        }
        return (rad_s * param_angular) + param_linear;
    }
    double pwm_to_rad_s(double pwm)
    {
        double param_linear = param_linear_high;
        double param_angular = param_angular_high;
        if(pwm <= 25 && pwm >= -25){
            if(pwm <= 15 && pwm >= -15){
                if(pwm <= 11 && pwm >= -11){
                    param_linear = param_linear_ex_low;
                    param_angular = param_angular_ex_low;
                } else {
                    param_linear = param_linear_low;
                    param_angular = param_angular_low;
                }

            } else {
                param_linear = param_linear_med;
                param_angular = param_angular_med;
            }
        }
        return (pwm - param_linear) / param_angular;
    }
    //To control M5
    double M5_pwm_to_rad_s(double pwm){

        double param_lin = 0.0;
        double param_ang = 0.0;
        double mod_pwm = fabs(pwm);

        if(mod_pwm >= 9.4 && mod_pwm <= 22.0){
            param_ang = param_angular_r1;
            param_lin = param_linear_r1;
        }
        else if(mod_pwm > 22.0 && mod_pwm <= 38.0){
            param_ang = param_angular_r2;
            param_lin = param_linear_r2;
        }
        else if(mod_pwm > 38.0 && mod_pwm <= 53.0){
            param_ang = param_angular_r3;
            param_lin = param_linear_r3;
        }
        else if(mod_pwm > 53.0 && mod_pwm <= 73.0){
            param_ang = param_angular_r4;
            param_lin = param_linear_r4;
        }
        else if(mod_pwm > 73.0){
            param_ang = param_angular_r5;
            param_lin = param_linear_r5;
        }

        return ((param_ang*pwm) +param_lin);
    }

    double M5_rad_s_to_pwm(double rad_s){

        double param_lin = 0.0;
        double param_ang = 0.0;
        double mod_rad_s = fabs(rad_s);
        double signal_rad_s = -(rad_s/mod_rad_s);
        if(mod_rad_s >= 13.44 && mod_rad_s <= 314.159){
            param_ang = param_angular_r1;
            param_lin = param_linear_r1;
        }
        else if(mod_rad_s > 314.159 && mod_rad_s <= 688.158){
            param_ang = param_angular_r2;
            param_lin = param_linear_r2;
        }
        else if(mod_rad_s > 688.158 && mod_rad_s <= 1002.318){
            param_ang = param_angular_r3;
            param_lin = param_linear_r3;
        }
        else if(mod_rad_s > 1002.318 && mod_rad_s <= 1436.150){
            param_ang = param_angular_r4;
            param_lin = param_linear_r4;
        }
        else if(mod_rad_s > 1436.150){
            param_ang = param_angular_r5;
            param_lin = param_linear_r5;
        }


        return ((rad_s - signal_rad_s * param_lin)/param_ang);
    }

    double last_battery = ((BATT.read()*3.3)*54)/10.0;
    double getBattery(){
        last_battery = (last_battery + (((BATT.read() * 3.3) * 54) / 10.0)) / 2.0;
        return last_battery;
    }
    void checkBattery(){
        while(utils::getBattery() < 15.5){
            Buzzer.write(DEFAULT_BUZZER_FREQUENCY);
            Status::sendRoundColor(0xFF0000, 100);
            Buzzer.write(0);
            ThisThread::sleep_for(500ms);
        }
    }
    int getRobotId()
    {
        unsigned int _robotId = 0;
        _robotId += (SW1.read());
        _robotId += (SW2.read() * 2);
        _robotId += (SW3.read() * 4);
        _robotId += (SW4.read() * 8);
        if(_robotId <= 15)
            return _robotId;
        else
            return 16;

    }
    void beep(int time, int cycleUs, double frequency){
        bool cycleUpdated = false;
        if(cycleUs != DEFAULT_BUZZER_CYCLE){
           Buzzer.period_us(cycleUs);
           cycleUpdated = true;
        }
        
        Buzzer.write(frequency);
        ThisThread::sleep_for(chrono::milliseconds(time));
        Buzzer.write(0);

        if(cycleUpdated){
            Buzzer.period_us(DEFAULT_BUZZER_CYCLE);
        }
    }
}
