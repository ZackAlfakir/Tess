#ifndef DRIVETRAIN
#define DRIVETRAIN

//#include "servo.h"
#include "Ports.h"
#include "fdserial.h"

void driveForward(int);
void driving(int, int);
void driveBackward(float);
void drive(void *x);
int getLeftTicks();
int getRightTicks();
float getLeftDistance();
float getRightDistance();
void turn(); //default 90 degrees
void stop();
void stopLeftSide();
void stopRightSide();

#endif