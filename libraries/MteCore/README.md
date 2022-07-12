# MteCore - Library For MTE Controller #
[Muara Teknik Elektrik](https://mt-elektrik.com/)

----

## What's New? ##

Version 1.0.0

* Initial release

## Description ##

This library is intended to facilitate board programming that supports Arduino-based MTE Controllers.
This library carries the concept of multitasking, by introducing an "event" function in each class.
by using the "event" function, you no longer need to bother with code that requires you to execute the code at any given moment.

----
## Features ##

* Event Function
* Timer
* Counter
* PWM
* Smooth PWM
* Analog
* Digital Input & Output
* Debug Mode
* Disable or Enable Class to Save Memory
* Settings to switch to another class

----

## Download and Installation ##

You can use the Arduino Library Manager (Sketch -> Include Library -> Manage Libraries...) to download the library.

Alternatively, you can download the library directly, and install it yourself.

* [MteCore Library - Latest Version](https://github.com/mt-elektrik/MteCore/archive/master.zip)

Unzip the folder and rename it to `MteCore`, then move it to your `arduinosketchfolder/libraries/` folder.

----

## Usage Example ##

## Input Example ##
```
/*
    14/01/2020 Muara Teknik Elektrik
    Input Event Example
*/
#define INPUT_DEBUG //uncomment this line for debug
#include "MteCore.h"

void setup(){
    Serial.begin(9600);
    //Setup callback IN1
    IN1.onEnable(callback_IN1_onEnable);
    IN1.onDisable(callback_IN1_onDisable);
    IN1.onChange(callback_IN1_OnChange);
    //Setup callback IN2
    IN2.onEnable(callback_IN2_onEnable);
    IN2.onDisable(callback_IN2_onDisable);
    IN2.onChange(callback_IN2_OnChange);
    //Setup callback IN3
    IN3.onEnable(callback_IN3_onEnable);
    IN3.onDisable(callback_IN3_onDisable);
    IN3.onChange(callback_IN3_OnChange);
    //Setup callback IN4
    IN4.onEnable(callback_IN4_onEnable);
    IN4.onDisable(callback_IN4_onDisable);
    IN4.onChange(callback_IN4_OnChange);
    //Setup callback IN5
    IN5.onEnable(callback_IN5_onEnable);
    IN5.onDisable(callback_IN5_onDisable);
    IN5.onChange(callback_IN5_OnChange);
    //Setup callback IN6
    IN6.onEnable(callback_IN6_onEnable);
    IN6.onDisable(callback_IN6_onDisable);
    IN6.onChange(callback_IN6_OnChange);
    //Setup callback IN7
    IN7.onEnable(callback_IN7_onEnable);
    IN7.onDisable(callback_IN7_onDisable);
    IN7.onChange(callback_IN7_OnChange); 
}
void loop(){
    //process main input & output
    process();
}   
//-------------------------------------------------------------------
//callback IN1
void callback_IN1_onEnable(){
    Serial.println("IN1 => onEnable");
}
void callback_IN1_onDisable(){
    Serial.println("IN1 => onDisable");
}
void callback_IN1_OnChange(){
    Serial.println("IN1 => onChange");
}
//callback IN2
void callback_IN2_onEnable(){
    Serial.println("IN2 => onEnable");
}
void callback_IN2_onDisable(){
    Serial.println("IN2 => onDisable");
}
void callback_IN2_OnChange(){
    Serial.println("IN2 => onChange");
}
//callback IN3
void callback_IN3_onEnable(){
    Serial.println("IN3 => onEnable");
}
void callback_IN3_onDisable(){
    Serial.println("IN3 => onDisable");
}
void callback_IN3_OnChange(){
    Serial.println("IN3 => onChange");
}
//callback IN4
void callback_IN4_onEnable(){
    Serial.println("IN4 => onEnable");
}
void callback_IN4_onDisable(){
    Serial.println("IN4 => onDisable");
}
void callback_IN4_OnChange(){
    Serial.println("IN4 => onChange");
}
//callback IN5
void callback_IN5_onEnable(){
    Serial.println("IN5 => onEnable");
}
void callback_IN5_onDisable(){
    Serial.println("IN5 => onDisable");
}
void callback_IN5_OnChange(){
    Serial.println("IN5 => onChange");
}
//callback IN6
void callback_IN6_onEnable(){
    Serial.println("IN6 => onEnable");
}
void callback_IN6_onDisable(){
    Serial.println("IN6 => onDisable");
}
void callback_IN6_OnChange(){
    Serial.println("IN6 => onChange");
}
//callback IN7
void callback_IN7_onEnable(){
    Serial.println("IN7 => onEnable");
}
void callback_IN7_onDisable(){
    Serial.println("IN7 => onDisable");
}
void callback_IN7_OnChange(){
    Serial.println("IN7 => onChange");
}
```

## Analog Example ##
```
//Change the jumper to F5 on the SELECTOR PIN to activate F5,
#define _ENABLE_F5_ANALOG //Enable F5 as Analog Function
// #define _ANALOG_DEBUG //uncomment this line for debug
#include "MteCore.h"
void setup(){
    Serial.begin(9600);
    F5.onChange(
        [](uint16_t val){
             Serial.println(val);
             //or
            //  Serial.println(F5.getValue());
        }
    );
}

void loop(){
    process();
}
```

## PWM Example ##
```
#define _ENABLE_F5_ANALOG //uncomment this line for set pin F5 as Analog
#define _ENABLE_F6_PWM //uncomment this line for set pin F6 as PWM
// #define _PWM_DEBUG //uncomment this line for print pwm activity
#include "MteCore.h"
void setup(){
    Serial.begin(9600);
    F5.onChange(
        [](uint16_t v){
            byte percent = map(v,0,1023,0,100);
            F6.setValue(percent);
            Serial.print("Value ANALOG : ");
            Serial.print(v);
            Serial.print(" = ");
            Serial.print(percent);
            Serial.println("%");
        }
    );
}

void loop(){
    process();
}
```
## This is only a small part of the convenience of this library, download and install this library for more examples ##
----
