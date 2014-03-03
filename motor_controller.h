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
    motor_controller(unsigned int uiPWMPin_, unsigned int uiDirPin_, int iMaxPWM_, int iDelay_);

    void emergencyStop(void);
    void setSpeed(int iSpd_);
    int getCurrentSpeed(void);
    int getSetSpeed(void);
    void update(void);

  private:
    unsigned int uiPWMPin;
    unsigned int uiDirPin;

    int iCurrentSpd;
    int iSetSpd;
    int iDelay;

    double dSpdPWMScale;

    unsigned long ulLastUpdate;

    void changeSpeed(int iSpd_);
};

#endif // motor_controller_h
