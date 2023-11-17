#include "MotionControl.h"

MotionControl::MotionControl():
_M1(M1_PWM, M1_DIR, TIM1, 4096, 2), // sampling time 2ms +
_M2(M2_PWM, M2_DIR, TIM8, 4096, 2) // sampling time 2ms 
{
    speedSampler.start();
}

void MotionControl::init(){
    _M1.init();
    _M2.init();
} 

void MotionControl::moveRobot(double speedM1, double speedM2){
    _M1.run(-speedM1); // estava negativo
    _M2.run(speedM2);
    }

// void MotionControl::getMotorInfo(VSSRobotInfo& telemetry){
//     telemetry.m1 = _M1.get_current_speed_rad_s();
//     telemetry.m2 = _M2.get_current_speed_rad_s();
// }

Motors MotionControl::getRobotSpeed(){
    Motors speeds;
    this->getMotorsSpeed(speeds);
    return speeds;
}

void MotionControl::getMotorsSpeed(Motors &m){
    m.m1 = _M1.get_current_speed_rad_s();
    m.m2 = _M2.get_current_speed_rad_s();
}

void MotionControl::accelRobot(Motors desiredSpeed){
    
    this->moveRobotPID(desiredSpeed);

    Motors currentSpeed;
    currentSpeed = this->getRobotSpeed();

    //Controle de stall removido na larc mas ainda pode ser usado (a decidir)
    // //every millisecond
    // if(utils::timerRead<chrono::milliseconds>(speedSampler) >= 1){
    //     speedSampler.reset();
    //     //reset the counter if told to stop
    //     if(desiredSpeed.m1 == 0 && desiredSpeed.m2 == 0){
    //         this->stallCounter = 0;
    //     }else{
    //         //if trying to moving but not moving, increments
    //         if(fabs(currentSpeed.m1) <= 1 || fabs(currentSpeed.m2) <= 1)
    //             this->stallCounter++;
    //     }
    // }
    // //if its been stalling for 300ms
    // if(this->stallCounter >= 300){
    //     this->stopRobot();
    //     utils::beep(500);
    //     utils::noBeep(0);
    //     this->stallCounter = 0;
    // }
}

void MotionControl::moveRobotPID(Motors desiredSpeed){
    _M1.runPID(desiredSpeed.m1);
    _M2.runPID(desiredSpeed.m2);
}

void MotionControl::stopRobot(){
    // Sets motor PWM to 0, releasing their power
    _M1.stop();
    _M2.stop();
}

void MotionControl::brakeRobot(){
    // Controls the motors' velocities to 0, braking the robot
    this->moveRobotPID(Motors());
}