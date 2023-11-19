#ifndef MOTION_CONTROL_H
#define MOTION_CONTROL_H

#include "mbed.h"
#include <utils.h>
#include <PID_Controller.h>
//#include <navigation.h>

#define HALT_SPEED 8

class MotionControl{
  public:
    MotionControl();

    void init();

    void moveRobot(double speedM1, double speedM2);
    // void getMotorInfo(VSSRobotInfo& telemetry);
    Motors getRobotSpeed();

    void moveRobotPID(Motors desiredSpeed);
    void accelRobot(Motors desiredSpeed);

    void stopRobot();
    void brakeRobot();
    void getMotorsSpeed(Motors &m);
    void printMotorSpeed();
    
  private:
    PID_Controller _M1;
    PID_Controller _M2;
    Timer speedSampler;
    int stallCounter;
};

#endif /* MOTION_CONTROL_H */