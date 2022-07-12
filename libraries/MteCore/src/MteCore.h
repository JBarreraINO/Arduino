/*
  MteCore - Library For MTE Controller

  Muara Teknik Elektrik
  https://github.com/mt-elektrik/MteCore


  Copyright 2020 Muara Teknik Elektrik

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef _MTE_CORE_H
#define _MTE_CORE_H
#include "Arduino.h"
#if defined(_INPUT_DEBUG) ||  defined(_OUTPUT_DEBUG) || defined(_ANALOG_DEBUG) || defined(_ANALOG_DEBUG) || defined(_PWM_DEBUG)
  //pin mapping for MTE-miniController V.2.0
  String PIN_TO_LABEL(uint8_t pin){
    switch (pin)
    {
    case 0:
      return "F1";
      break;
    case 1:
      return "F2";
      break;
    case 2:
      return "IN1";
      break;
    case 3:
      return "IN2";
      break;
    case 4:
      return "IN3";
      break;
    case 5:
      return "IN4";
      break;
    case 11:
      return "IN5";
      break;
    case 12:
      return "IN6";
      break;
    case 13:
      return "IN7";
      break;
    case 10:
      #if defined(_ENABLE_F8_PWM) || defined(_ENABLE_F8_UART)
        return "F8";
      #else
        return "IN8";
      #endif
      break;
    case A7:
      #ifdef _ENABLE_F7_ANALOG
        return "F7"
      #else
        return "IN9";
      #endif
      break;
    case 9:
      #if defined(_ENABLE_F6_PWM) || defined(_ENABLE_F6_UART)
        return "F6";
      #else
        return "IN10";
      #endif
      break;
    case A6:
      #ifdef _ENABLE_F5_ANALOG
        return "F5";
      #else
        return "IN11";
      #endif
      break;
    case A4:
      #if defined(_ENABLE_F3_ANALOG) || defined(_ENABLE_F3_I2C)
        return "F3"
      #else
        return "IN12";
      #endif
      break;
    case A5:
      return "F4";
      break;
      //output
    case A3:
      return "OUT1";
      break;
    case A2:
      return "OUT2";
      break;
    case A1:
      return "OUT3";
      break;
    case A0:
      return "OUT4";
      break;
    case 6:
      return "OUT5";
      break;
    case 7:
      return "OUT6";
      break;
    case 8:
      return "OUT7";
      break;
    
    default:
      break;
    }
  }
#endif

#include "util/InputCore.h"
#include "util/OutputCore.h"
#include "util/TimerCore.h"
#include "util/CounterCore.h"
#if defined(_ENABLE_F3_ANALOG) || defined(_ENABLE_F4_ANALOG) || defined(_ENABLE_F5_ANALOG) || defined(_ENABLE_F7_ANALOG)
  #include "util/AnalogCore.h"
#endif
#if defined(_ENABLE_F6_PWM) || defined(_ENABLE_F8_PWM)
  #include "util/PWMCore.h"
#endif
#ifndef _DISABLE_IN1
  InputCore IN1(2);
#endif
#ifndef _DISABLE_IN2
  InputCore IN2(3);
#endif
#ifndef _DISABLE_IN3
  InputCore IN3(4);
#endif
#ifndef _DISABLE_IN4
  InputCore IN4(5);
#endif
#ifndef _DISABLE_IN5
  InputCore IN5(11);
#endif
#ifndef _DISABLE_IN6
  InputCore IN6(12);
#endif
#ifndef _DISABLE_IN7
  InputCore IN7(13);
#endif
//Settings IN8
#ifdef _ENABLE_F8_PWM
  PWMCore F8(10);
#elif defined(_ENABLE_F8_UART)
  #ifdef _ENABLE_F6_UART
    #error "Cannot enable F8 as UART when F6 as UART is disable!"
  #else
    #define F8 10;
  #endif
#else
  #ifndef _DISABLE_IN8
    InputCore IN8(10);
  #endif
#endif
//end Settings
//Settings IN9
#ifdef _ENABLE_F7_ANALOG
  AnalogCore F7(A7); //enable F7 as Analog
#else 
  #ifndef _DISABLE_IN9
    InputCore IN9(A7);
  #endif
#endif
//end Settings
//Settings IN10
#ifdef _ENABLE_F6_PWM
  PWMCore F6(9);
#elif defined(_ENABLE_F6_UART)
  #ifdef _ENABLE_F8_UART
    #error "Cannot enable F6 as UART when F8 as UART is disable!"
  #else
    #define F6 9
  #endif
#else
  #ifndef _DISABLE_IN10
    InputCore IN10(9);
  #endif
#endif
//end Settings
//Settings IN11
#ifdef _ENABLE_F5_ANALOG
  AnalogCore F5(A6); //enable F5 as Analog
#else
  #ifndef _DISABLE_IN11
    InputCore IN11(A6);
  #endif
#endif
//end Settings

#ifdef _ENABLE_F4_ANALOG
    AnalogCore F4(A5); //enable F4 as Analog
#elif defined(_ENABLE_F4_I2C)
  #ifndef _ENABLE_F3_I2C
    #error "Cannot enable F4 as I2C when F3 as I2C is disable!"
  #else
    //enable i2c F4
  #endif
#endif

//Settings IN12
#ifdef _ENABLE_F3_ANALOG
        AnalogCore F3(A4); //enable F3 as Analog
#elif defined(_ENABLE_F3_I2C)
  #ifndef _ENABLE_F4_I2C
    #error "Cannot enable F3 as I2C when F4 as I2C is disable!"
  #else
    //enable i2c F3
  #endif
#else
  #ifndef _DISABLE_IN12
    InputCore IN12(A4); //enable IN12
  #endif
#endif
//end Settings IN12

//OUTPUT
#ifndef _DISABLE_OUT1
  OutputCore OUT1(A3);
#endif
#ifndef _DISABLE_OUT2
  OutputCore OUT2(A2);
#endif
#ifndef _DISABLE_OUT3
  OutputCore OUT3(A1);
#endif
#ifndef _DISABLE_OUT4
  OutputCore OUT4(A0);
#endif
#ifndef _DISABLE_OUT5
  OutputCore OUT5(6);
#endif
#ifndef _DISABLE_OUT6
  OutputCore OUT6(7);
#endif
#ifndef _DISABLE_OUT7
  OutputCore OUT7(8);
#endif

void process(){
  unsigned long now = millis();
  #ifndef _DISABLE_IN1
    IN1.process(now);
  #endif
  #ifndef _DISABLE_IN2
    IN2.process(now);
  #endif
  #ifndef _DISABLE_IN3
    IN3.process(now);
  #endif
  #ifndef _DISABLE_IN4
    IN4.process(now);
  #endif
  #ifndef _DISABLE_IN5
    IN5.process(now);
  #endif
  #ifndef _DISABLE_IN6
    IN6.process(now);
  #endif
  #ifndef _DISABLE_IN7
    IN7.process(now);
  #endif
//-------F8-----------------------------
  #if defined(_ENABLE_F8_PWM)
    #ifdef _ENABLE_SMOOTH_PWM
      F8.process(now);
    #endif
  #elif defined(_ENABLE_F8_UART)
  #else
    #ifndef _DISABLE_IN8
      IN8.process(now);
    #endif
  #endif
//-------F7-----------------------------
  #ifdef _ENABLE_F7_ANALOG
    F7.process(now); //F7 analog process
  #else
    #ifndef _DISABLE_IN9
      IN9.process(now);
    #endif
  #endif
//-------F6-----------------------------
  #if defined(_ENABLE_F6_PWM)
    #ifdef _ENABLE_SMOOTH_PWM
      F6.process(now);
    #endif
  #elif defined(_ENABLE_F6_UART)
  #else
      #ifndef _DISABLE_IN10
        IN10.process(now);
      #endif
  #endif
//-------F5-----------------------------
  #ifdef _ENABLE_F5_ANALOG
    F5.process(now); //F5 analog process
  #else
    #ifndef _DISABLE_IN11
      IN11.process(now);
    #endif
  #endif
//-------F4-----------------------------
  #ifdef _ENABLE_F4_I2C

  #elif _ENABLE_F4_ANALOG
    F4.process(now); //F4 analog process
  #endif
//-------F3-----------------------------
  #ifdef _ENABLE_F3_ANALOG
    F3.process(now); //F3 Analog process
  #elif defined(_ENABLE_F3_I2C)
  #else
    #ifndef _DISABLE_IN10
      IN12.process(now);
    #endif
  #endif

  //-----------OUTPUT process
  #ifndef _DISABLE_OUT1
    OUT1.process(now);
  #endif
  #ifndef _DISABLE_OUT2
    OUT2.process(now);
  #endif
  #ifndef _DISABLE_OUT3
    OUT3.process(now);
  #endif
  #ifndef _DISABLE_OUT4
    OUT4.process(now);
  #endif
  #ifndef _DISABLE_OUT5
    OUT5.process(now);
  #endif
  #ifndef _DISABLE_OUT6
    OUT6.process(now);
  #endif
  #ifndef _DISABLE_OUT7
    OUT7.process(now);
  #endif
}
#endif