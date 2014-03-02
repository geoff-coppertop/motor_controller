/*
  motor_controller.h - Library for running a motor controller.
  Created by Geoffrey A. Thomas, February 9, 2014.
*/

#include "Arduino.h"
#include "motor_controller.h"

motor_controller::motor_controller(int iPWMPin_, int iDirPin_, int iMaxPWM_, int iDelay_)
{
  iCurrentSpd = 0;
  iSetSpd = 0;

  iPWMPin = iPWMPin_;
  iDirPin = iDirPin_;

  iDelay = iDelay_;

  ulLastUpdate = millis();

  dSpdPWMScale = iMaxPWM_ / 255.0;

  pinMode(iPWMPin_, OUTPUT);
  pinMode(iDirPin_, OUTPUT);
}

void motor_controller::increaseSpeed(void)
{
   setSpeed(iCurrentSpd + 1);
}

void motor_controller::decreaseSpeed(void)
{
   setSpeed(iCurrentSpd - 1);
}

void motor_controller::setSpeed(int iSpd_)
{
  if(iSpd_ > 100)
  {
    iSetSpd = 100;
  }
  else if(iSpd_ < -100)
  {
     iSetSpd  = -100;
  }
  else
  {
     iSetSpd = iSpd_;
  }
}

void motor_controller::stop(void)
{
  setSpeed(0);
}

void motor_controller::emergencyStop(void)
{
   changeSpeed(0);
}

void motor_controller::changeSpeed(int iSpd_)
{
  int iPWMVal = iSpd_ * dSpdPWMScale;

  iCurrentSpd = iSpd_;

  // Check the current speed and see if we need to adjust the direction pins
  if(iCurrentSpd > 0)
  {
    // Write direction pins so the motor is going forward
    digitalWrite(iDirPin, HIGH);
  }
  else if(iCurrentSpd < 0)
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

int motor_controller::getSpeed(void)
{
	// return current speed
	return iCurrentSpd;
}

void motor_controller::updateThrottle(void)
{
   if((millis() - ulLastUpdate) > iDelay)
   {
      int iSpdDelta = iSetSpd - iCurrentSpd;

      if(iSpdDelta > 0)
      {
         changeSpeed(iCurrentSpd + 1);

         Serial.print("Throttle speed: ");
         Serial.println(iCurrentSpd, DEC);
      }
      else if(iSpdDelta < 0)
      {
         changeSpeed(iCurrentSpd - 1);

         Serial.print("Throttle speed: ");
         Serial.println(iCurrentSpd, DEC);
      }
      else
      {
         // Motor is stopped do nothing
      }

      ulLastUpdate = millis();
   }
}
