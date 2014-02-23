/*
  motor_controller.h - Library for running a motor controller.
  Created by Geoffrey A. Thomas, February 9, 2014.
*/

#include "Arduino.h"
#include "motor_controller.h"

motor_controller::motor_controller(int iPWMPin_, int iDirPin_, int iMaxPWM_, int iDelay_)
{
  iSpd = 0;
  iPWMPin = iPWMPin_;
  iDirPin = iDirPin_;
  iDelay = iDelay_;
  
  dSpdPWMScale = iMaxPWM_ / 255.0;
  
  pinMode(iPWMPin_, OUTPUT);
  pinMode(iDirPin_, OUTPUT);
}

void motor_controller::IncrSpeed(void)
{
  iSpd++;
  
  if(iSpd > 100)
  {
    // Not allowed to exceed 100%
    iSpd = 100;
  }
  else
  {
    ChangeSpeed(iSpd);
  }
}

void motor_controller::DecrSpeed(void)
{
  iSpd--;
  
  if(iSpd < -100)
  {
    // Not allowed to exceed -100%
    iSpd = -100;
  }
  else
  {
    ChangeSpeed(iSpd);
  }
}

void motor_controller::Speed(int iSpd_)
{
  int iSpdDelta = iSpd_ - iSpd;
  
  if(iSpd_ > 100)
  {
    iSpd_ = 100;
  }
  else if(iSpd_ < -100)
  {
    iSpd_  = -100;
  }
  else
  {
    // Intentional do-nothing
  }
  
  do
  {
    iSpdDelta = iSpd_ - iSpd;
    
    if(iSpdDelta > 0)
    {
      IncrSpeed();
    }
    else if(iSpdDelta < 0)
    {
      DecrSpeed();
    }
    else
    {
      // Intentional do-nothing
    }
  } while(iSpdDelta != 0);
}

void motor_controller::Stop(void)
{
  Speed(0);
}

void motor_controller::EStop(void)
{
  ChangeSpeed(0);
}

void motor_controller::ChangeSpeed(int iSpd_)
{
  int iPWMVal = iSpd_ * dSpdPWMScale;
  
  // we only allow delays greater than 0, this will make it look like the motor has momentum
  if(iDelay > 0)
  {
    delay(iDelay);
  }
  
  // Check the current speed and see if we need to adjust the direction pins
  if(iSpd_ > 0)
  {
    // Write direction pins so the motor is going forward
    digitalWrite(iDirPin, HIGH);
  }
  else if(iSpd < 0)
  {
    // Write direction pin so the motor is going backward
    digitalWrite(iDirPin, LOW);
  }
  else
  {
    // Motor should be stopped at this point direction pin doesn't have to change
  }
  
  // output the current pwm
  analogWrite(iPWMPin, iPWMVal);
}
