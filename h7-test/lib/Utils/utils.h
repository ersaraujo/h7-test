
#ifndef UTILS_H
#define UTILS_H
#define DIRECT_TRANSMISSION

#include "mathematics.h"
#include <commConfig.h>
#include <commTypes.h>
#include <mbed.h>
#include <ports_v1.2.h>
#include <status.h>

#define DEBUG false
#define ODOMETRY_PCKT

#define NAVIGATION_MAX_LINEAR_ACCEL 2.4
#define NAVIGATION_BREAK_DECAY 2.11
#define NAVIGATION_DECAY 0.09
#define NAVIGATION_CYCLE_STEP 0.16

#define DEFAULT_TOLERANCE_TO_TARGET 0.035
#define SMALL_TOLERANCE_TO_TARGET 0.01

#define NRF_NO_MSG_TIME 300
#define NRF_HALT_TIME 1000
#define DEFAULT_FEEDBACK_TIME 100
#define ODOMETRY_TIME 5

#define GYRO_TOLERANCE 0.1

#define DRIBLER_BAR_GEAR 50
#define DRIBLER_GEAR 26
#define MIN_DRIBBLER_SPEED 0
#define MAX_DRIBBLER_SPEED 720
#define DEFAULT_DRIBLER_SPEED (-50)
#define MOTOR_MIN_SPEED_RAD_S 1

#define ROBOT_ACCEL 1

#if defined(DIRECT_TRANSMISSION)
  #define MOTOR_GEAR 1  // Direct transmission
  #define WHEEL_GEAR 1  // Direct transmission
#else
  #define MOTOR_GEAR 18.0
  #define WHEEL_GEAR 60.0
#endif

#define DEFAULT_BUZZER_CYCLE 370
#define DEFAULT_BUZZER_FREQUENCY 0.5
#define MAX_CHARGE 0.75
#define MAX_CHARGE_MARGIN 0.05
#define MIN_CHARGE 0.45
#define MAX_CAP_V_LOAD 2.8
#define IR_THRESHOLD 0.15
#define KICKER_TIMEOUT 100

#define ANGLE_KP 2.0
#define DEFAULT_FEEDBACK_TIME 100
#define NRF_HALT_TIME 1000
#define NRF_NO_MSG_TIME 300

enum class ExecMode {
  GAME_ON,
  VISION_BLACKOUT,
  TEST_BASICS,
  TEST_PWM,
  TEST_PID,
  TEST_KICK,
  TEST_DRIBBLER,
  TEST_ODOMETRY,
  TEST_MPU,
  TEST_IR,
  TEST_RECEIVER_BALL,
  TEST_RANGING_SENSOR
  };

namespace utils {

extern double last_battery;
void initRobot();
double rad_s_to_pwm(double rad_s);
double rad_s_to_pwm_pi(double rad_s);
double pwm_to_rad_s(double pwm);
double M5_rad_s_to_pwm(double rad_s);
double M5_pwm_to_rad_s(double pwm);
double getBattery();
int getRobotId();
void checkBattery();
void beep(int time, int cycleUs = DEFAULT_BUZZER_CYCLE,
          double frequency = DEFAULT_BUZZER_FREQUENCY);
bool shouldStop(double motorSpeed, double haltSpeed);

/** Note: Use this function to make the code more readable
 * and prioritize the milliseconds unit for time conditionals
 * @param ToDuration Reading time unit, based on the chrono namespace types
 * @param T Type of variable returned, when omitted the default is to return in
 * float
 * @param timer Timer for reading
 */
template <class ToDuration, class T = float> T timerRead(const Timer &timer) {
  return chrono::duration_cast<
             chrono::duration<T, typename ToDuration::period>>(
             timer.elapsed_time())
      .count();
}
bool timerMillisExpired(const Timer &timer, double time);
double timerMillisRead(const Timer &timer);

extern DigitalIn PBT1;
extern DigitalIn PBT2;
extern DigitalIn SW1;
extern DigitalIn SW2;
extern DigitalIn SW3;
extern DigitalIn SW4;
extern PwmOut Buzzer;
extern AnalogIn BATT;
} // namespace utils

#endif
