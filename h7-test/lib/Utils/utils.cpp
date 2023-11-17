#include "utils.h"

namespace utils {
    // New control parameters: param_angular * x + param_linear
    double param_angular_pos_high = 1.688; //ok
    double param_angular_pos_low = 2.072; //ok
    double param_angular_neg_high = 1.727; //ok
    double param_angular_neg_low = 2.113; //ok
    double param_linear_pos_high = -9.702;  //
    double param_linear_pos_low = -11; //ok
    double param_linear_neg_high = 7.159; //ok
    double param_linear_neg_low = 7.085; //ok

    DigitalIn SW1(PIN_SELECTOR_1, PullUp);
    DigitalIn SW2(PIN_SELECTOR_2, PullUp);
    DigitalIn SW3(PIN_SELECTOR_3, PullUp);
    DigitalIn SW4(PIN_SELECTOR_4, PullUp);
    // DigitalOut _red(PIN_LED_RED);
    // DigitalOut _green(PIN_LED_RED);
    // DigitalOut _blue(PIN_LED_RED);
    // PwmOut Buzzer(PIN_BUZZER);
    
    AnalogIn BATT(PIN_BATT);

    // AnalogIn current_M1(M1_CURR);
    // AnalogIn current_M2(M2_CURR);

    float battAverage = 0;
    
    void initRobot()
    {
        int robotId = utils::getRobotId();

        // Status::init(PIN_LED_RED);
                
        printf("Initializing robot...\n");
        printf("RobotId = %d\n", robotId);
        updateBatteryAvg();
        ThisThread::sleep_for(1000ms);

        checkBattery();

        // Status::send(WHITE, LED_1); 
        // Status::send(GREEN, LED_2);
        beep(1000);
        noBeep(0);

        ThisThread::sleep_for(1500ms);

        switch (robotId%4){
        case 0:
            blinkColor(robotId, RED);
            break;
        case 1:
            blinkColor(robotId, GREEN);
            break;
        case 2:
            blinkColor(robotId, ROSA);
            break;
        case 3:
            blinkColor(robotId, CIANO);
            break;
        }
        printf("Initialization complete!\n");
    }

    // BATTERY
    double getBattery()
    {
        float value = BATT.read();
        //linear regression
        double last_battery = SLOPE*value + INTERCEPT;

        return  last_battery;
    }

    double getBatteryAvg(){
        return battAverage;
    }

    void updateBatteryAvg(){
        if(battAverage != 0){
            battAverage = BATT_AVG_WEIGHT*getBattery() + (1.0 - BATT_AVG_WEIGHT)*battAverage;
        } else {
            battAverage = getBattery();
        }
    }

    void checkBattery()
    {
        updateBatteryAvg();
        if(battAverage < BATT_WARNING_VOLT && battAverage >= BATT_MINIMAL_VOLT){
            //Warning
            for(int i = 0; i < 10; i++){
                beep(300);
                noBeep(100);
            }
        } else if (battAverage < BATT_MINIMAL_VOLT){
            //Stops robot
            printf("Low battery!\n");
            while(1){
                beep(300);
                noBeep(100);
            }
        }
    }

    int getRobotId()
    {
        int _robotId = 0;
        // _robotId += (!SW1.read());
        _robotId += (!SW2.read() * 4);
        _robotId += (!SW3.read() * 2);
        _robotId += (!SW4.read() * 1);
        
        if(_robotId <= 15)
            return _robotId;
        else
            return 16;
    }
    
    void blinkColor(int time, int hexValue)
    {   
        // Status::send(hexValue, ALL_LEDS);

        if (time == 0) 
            ThisThread::sleep_for(500ms);
        
        for(; time > 0; time--){
            beep(500);
            noBeep(100);
        }
        // Status::clearColors();
    }

    void beep(uint32_t time)
    {
        // Buzzer.period_ms(2); 
        // Buzzer.write(0.5);
        // ThisThread::sleep_for(time);
    }

    void noBeep(uint32_t time)
    {
        // Buzzer.write(0);
        // ThisThread::sleep_for(time);
    }

    void  writeRGB(int hexValue)
    {
        int red, green, blue;

        red     = ((hexValue >> 16) & 0xFF) / 255.0;
        green   = ((hexValue >> 8) & 0xFF) / 255.0;
        blue    = ((hexValue) & 0xFF) / 255.0;
        
        // _red.write(red);
        // _green.write(green);
        // _blue.write(blue);
    }

    // double getCurrent(uint8_t motor){
    //     if(motor == 1){
    //         return current_M1.read();
    //     } else if(motor == 2){
    //         return current_M2.read();
    //     }
    // }
    // motor curve function

    bool timerMillisExpired(const Timer& timer, double time){
      return timerRead<chrono::milliseconds>(timer) > time;
    }

    double timerMillisRead(const Timer& timer){
      return timerRead<chrono::milliseconds>(timer);
    }

    double rad_s_to_pwm_pi(double rad_s)
    {
        double param_angular = param_angular_pos_high;
        double param_linear = param_linear_pos_high;
        if (rad_s < -41.0)
        {
            param_angular = param_angular_neg_high;
            param_linear = param_linear_neg_high;
        }
        else if (rad_s >= -41.0 && rad_s < 0)
        {
            param_angular = param_angular_neg_low;
            param_linear = param_linear_neg_low;
        }
        else if (rad_s >= 0 && rad_s <= 42){
            param_angular = param_angular_pos_low;
            param_linear = param_linear_pos_low;
        }
        else
        {
            param_angular = param_angular_pos_high;
            param_linear = param_linear_pos_high;
        }
        return (param_angular * rad_s) + param_linear;
    }
}
