#ifndef UTILS_H
#define UTILS_H

#include <mbed.h>
#include "ports_v2.0.h"
// #include <commConfig.h>
// #include <commTypes.h>
// #include <status.h>

#define RED                 0xFF0000
#define GREEN               0x00FF00
#define BLUE                0x0000FF
#define YELLOW              0xFFFF00
#define CIANO               0x00FFFF
#define ROSA                0xFF00FF
#define CLEAR               0x000000
#define WHITE               0xFFFFFF

#define ID_QNT              8

#define R1_VALUE            1.0
#define R2_VALUE            0.68
#define VCC_VALUE           3.3

#define NO_MSG_TIME         200
#define NO_MSG_BEEP_TIME    60000
#define HALT_TIME           1000
#define TELEMETRY_TIME      300

#define BATT_AVG_WEIGHT 0.2f
#define BATT_WARNING_VOLT 7.4
#define BATT_MINIMAL_VOLT 7.0

#define SLOPE 7.668561995
#define INTERCEPT 0.7348076923

#define RED                 0xFF0000
#define GREEN               0x00FF00
#define BLUE                0x0000FF
#define YELLOW              0xFFFF00
#define CIANO               0x00FFFF
#define ROSA                0xFF00FF
#define CLEAR               0x000000

#define ID_QNT              8

#define R1_VALUE            1.43
#define R2_VALUE            1.0
#define VCC_VALUE           3.3

#define NO_MSG_TIME         200
#define HALT_TIME           1000
#define TELEMETRY_TIME      300

#define M_PI                3.14159265358979323846
#define MOTOR_GEAR          1.0
#define WHEEL_GEAR          5.0
#define PULSES_PER_REV      2048        
#define SAMPLE_TIME         2           // 2 ms
#define PULSES_RESET        32767

typedef struct Motors {
  double m1 = 0;
  double m2 = 0;
  double m3 = 0;
  double m4 = 0;

  Motors() {
    m1 = 0;
    m2 = 0;
    m3 = 0;
    m4 = 0;
  }

  inline Motors operator+(Motors a) {
    Motors b;
    b.m1 = m1 + a.m1;
    b.m2 = m2 + a.m2;
    b.m3 = m3 + a.m3;
    b.m4 = m4 + a.m4;
    return b;
  }
} Motors;

namespace utils{

    extern double last_battery;
    void initRobot();
    double getBattery();
    int getRobotId();
    void checkBattery();
    void updateBatteryAvg();
    double getBatteryAvg();
    void beep(uint32_t time);
    void noBeep(uint32_t time);
    void writeRGB(int hexValue);
    void blinkColor(int time, int hexValue);
    double getCurrent(uint8_t motor);
    double rad_s_to_pwm_pi(double rad_s);

    /** Note: Use this function to make the code more readable 
    * and prioritize the milliseconds unit for time conditionals
    * @param ToDuration Reading time unit, based on the chrono namespace types
    * @param T Type of variable returned, when omitted the default is to return in float
    * @param timer Timer for reading
    */
    template <class ToDuration, class T = float>
    T timerRead(const Timer& timer) {
      return chrono::duration_cast<chrono::duration<T, typename ToDuration::period>>(timer.elapsed_time()).count();
    }
    bool timerMillisExpired(const Timer &timer, double time);
    double timerMillisRead(const Timer &timer);

    extern DigitalIn SW1;
    extern DigitalIn SW2;
    extern DigitalIn SW3;
    extern DigitalIn SW4;
    // extern PwmOut Buzzer;
    extern AnalogIn BATT;
    extern AnalogIn current_M1;
    extern AnalogIn current_M2;

    extern float battAverage;
}

#endif
