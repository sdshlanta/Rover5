// Created by Mike Shlanta
// Copyright 2015 License: GNU GPL v3 http://www.gnu.org/licenses/gpl.html


#ifndef Rover5_h
#define Rover5_h

#include "Arduino.h"


#define c_EncoderInterruptA 0
#define c_EncoderInterruptB 1
#define c_EncoderPinA 2
#define c_EncoderPinB 3
#define EncoderIsReversed


void setupEncoder();
void bindEncoder();
void unbindEncoder();
long getEncoderTicks();
void goForward();
void turnLeft();
void turnRight();
void goReverse();
void roverStop();
void goForward(int speed);
void turnLeft(int speed);
void turnRight(int speed);
void goReverse(int speed);
void _HandleMotorInterruptA();
void _HandleMotorInterruptB();
int _ParseEncoder();



#endif
