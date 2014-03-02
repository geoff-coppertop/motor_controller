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

    void stop(void);
    void emergencyStop(void);
    void increaseSpeed(void);
    void decreaseSpeed(void);
    void setSpeed(int iSpd_);
    int getSpeed(void);
    void updateThrottle(void);

  private:
    int iPWMPin;
    int iDirPin;
    int iCurrentSpd;
    int iSetSpd;
    int iDelay;

    double dSpdPWMScale;

    unsigned long ulLastUpdate;

    void changeSpeed(int iSpd_);
};

#endif // motor_controller_h
