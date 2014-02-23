/*
  motor_controller.h - Library for running a motor controller.
  Created by Geoffrey A. Thomas, February 9, 2014.
*/

#ifndef motor_controller_h
#define motor_controller_h

#include "Arduino.h"

class motor_controller
{
  public:
    motor_controller(int iPWMPin_, int iDirPin_, int iMaxPWM_, int iDelay_);
    
    void Stop(void);
    void EStop(void);
    void IncrSpeed(void);
    void DecrSpeed(void);
    void Speed(int iSpd_);
    
  private:
    int iPWMPin;
    int iDirPin;
    int iSpd;
    int iDelay;
    
    double dSpdPWMScale;
    
    void ChangeSpeed(int iSpd_);
};

#endif // motor_controller_h
