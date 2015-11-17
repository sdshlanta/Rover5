// Created by Mike Shlanta
// Copyright 2015 License: GNU GPL v3 http://www.gnu.org/licenses/gpl.html


/*
*Quadrature Decoder 
*/
#include "Arduino.h"
#include "../digitalWriteFast/digitalWriteFast.h"
#include "Rover5.h"                             // library for high performance reads and writes by jrraines

volatile bool _EncoderASet;
volatile bool _EncoderBSet;
volatile bool _EncoderAPrev;
volatile bool _EncoderBPrev;
volatile long _EncoderTicks = 0;

//Arduino PWM Speed Control：
int _MotorADirection = 4; 
int _MotorASpeed = 5;
int _MotorBSpeed = 6;
int _MotorBDirection = 7;

void setupEncoder() {
  pinMode(c_EncoderPinA, INPUT);      // sets pin A as input
  digitalWriteFast(c_EncoderPinA, LOW);  // turn on pullup resistors
  pinMode(c_EncoderPinB, INPUT);      // sets pin B as input
  digitalWriteFast(c_EncoderPinB, LOW);  // turn on pullup resistors
  bindEncoder();
  pinMode(_MotorADirection, OUTPUT);   
  pinMode(_MotorBDirection, OUTPUT); 
}

void bindEncoder() {
  attachInterrupt(c_EncoderInterruptA, _HandleMotorInterruptA, CHANGE);
  attachInterrupt(c_EncoderInterruptB, _HandleMotorInterruptB, CHANGE);
}

void unbindEncoder() {
  dettachInterrupt(c_EncoderInterruptA, _HandleMotorInterruptA, CHANGE);
  dettachInterrupt(c_EncoderInterruptB, _HandleMotorInterruptB, CHANGE);
}

int _ParseEncoder() {
  if(_EncoderAPrev && _EncoderBPrev){
    if(!_EncoderASet && _EncoderBSet) return 1;
    if(_EncoderASet && !_EncoderBSet) return -1;
  }else if(!_EncoderAPrev && _EncoderBPrev){
    if(!_EncoderASet && !_EncoderBSet) return 1;
    if(_EncoderASet && _EncoderBSet) return -1;
  }else if(!_EncoderAPrev && !_EncoderBPrev){
    if(_EncoderASet && !_EncoderBSet) return 1;
    if(!_EncoderASet && _EncoderBSet) return -1;
  }else if(_EncoderAPrev && !_EncoderBPrev){
    if(_EncoderASet && _EncoderBSet) return 1;
    if(!_EncoderASet && !_EncoderBSet) return -1;
  }
}

// Interrupt service routines for the  motor's quadrature encoder
void _HandleMotorInterruptA() {
  _EncoderBSet = digitalReadFast(c_EncoderPinB);
  _EncoderASet = digitalReadFast(c_EncoderPinA);
  
  _EncoderTicks+=_ParseEncoder();
  
  _EncoderAPrev = _EncoderASet;
  _EncoderBPrev = _EncoderBSet;
}

// Interrupt service routines for the right motor's quadrature encoder
void _HandleMotorInterruptB() {
  // Test transition;
  _EncoderBSet = digitalReadFast(c_EncoderPinB);
  _EncoderASet = digitalReadFast(c_EncoderPinA);
  
  _EncoderTicks+=_ParseEncoder();
  
  _EncoderAPrev = _EncoderASet;
  _EncoderBPrev = _EncoderBSet;
}

long getEncoderTicks() {
  return _EncoderTicks;
}

void goForward() {
  digitalWriteFast(_MotorADirection, HIGH);
  digitalWriteFast(_MotorBDirection, HIGH);
  digitalWriteFast(_MotorASpeed, HIGH);
  digitalWriteFast(_MotorBSpeed, HIGH);
}

void goReverse() {
  digitalWriteFast(_MotorADirection, LOW);
  digitalWriteFast(_MotorBDirection, LOW);
  digitalWriteFast(_MotorASpeed, HIGH);
  digitalWriteFast(_MotorBSpeed, HIGH);
}

void turnLeft() {
  digitalWriteFast(_MotorADirection, LOW);
  digitalWriteFast(_MotorBDirection, HIGH);
  digitalWriteFast(_MotorASpeed, HIGH);
  digitalWriteFast(_MotorBSpeed, HIGH);
}

void turnRight() {
  digitalWriteFast(_MotorADirection, HIGH);
  digitalWriteFast(_MotorBDirection, LOW);
  digitalWriteFast(_MotorASpeed, HIGH);
  digitalWriteFast(_MotorBSpeed, HIGH);
}

void roverStop() {
  digitalWriteFast(_MotorADirection, LOW);
  digitalWriteFast(_MotorBDirection, LOW);
}

void goForward(int speed) {
  digitalWriteFast(_MotorADirection, HIGH);
  digitalWriteFast(_MotorBDirection, HIGH);
  analogWrite(_MotorASpeed, speed);
  analogWrite(_MotorBSpeed, speed);
}

void goReverse(int speed) {
  digitalWriteFast(_MotorADirection, LOW);
  digitalWriteFast(_MotorBDirection, LOW);
  analogWrite(_MotorASpeed, speed);
  analogWrite(_MotorBSpeed, speed);
}

void turnLeft(int speed) {
  digitalWriteFast(_MotorADirection, LOW);
  digitalWriteFast(_MotorBDirection, HIGH);
  analogWrite(_MotorASpeed, speed);
  analogWrite(_MotorBSpeed, speed);
}

void turnRight(int speed) {
  digitalWriteFast(_MotorADirection, HIGH);
  digitalWriteFast(_MotorBDirection, LOW);
  analogWrite(_MotorASpeed, speed);
  analogWrite(_MotorBSpeed, speed);
}