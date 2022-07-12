#ifdef _MTE_CORE_H
#ifndef _INPUT_CORE_H 
#define _INPUT_CORE_H 
#include "Arduino.h"
typedef void(*inputCore_State_Callback)();

class InputCore {
    protected:
    private:
        bool firstState;
        InputCore(const InputCore&);
        InputCore& operator=(const InputCore&);
        uint32_t debounceDelay=50;
        unsigned long lastDebounceTime;
        bool lastState=HIGH;

        unsigned long lastDebounceTimeOnChange;
        bool lastStateOnChange;

        uint8_t _pinIn;
        inputCore_State_Callback _cba;
        inputCore_State_Callback _cbna;
        inputCore_State_Callback _cbc;

    public:
        explicit InputCore(uint8_t pinIn);
        virtual~InputCore();
        void onEnable(inputCore_State_Callback cb);
        void onDisable(inputCore_State_Callback cb);
        void onChange(inputCore_State_Callback cb);
        bool isEnable();
        void process(unsigned long now);
        void setDebounceDelay(uint32_t delayms);
};
InputCore::InputCore(uint8_t pinIn)
 {
    _pinIn=pinIn;
    if(_pinIn == A6 || _pinIn == A7){
        pinMode(pinIn,INPUT);
        lastStateOnChange= analogRead(_pinIn)>1000 ? 0:1;
        
    }else{
        pinMode(pinIn,INPUT_PULLUP);
        lastStateOnChange= digitalRead(pinIn);
    }
}

InputCore::~InputCore() {}

void InputCore::onEnable(inputCore_State_Callback cb) {
    #ifdef _INPUT_DEBUG
        Serial.print(PIN_TO_LABEL(_pinIn));
        Serial.println(" : Set Callback onEnable");
    #endif
    _cba=cb;
}
void InputCore::onDisable(inputCore_State_Callback cb ){
    #ifdef _INPUT_DEBUG
        Serial.print(PIN_TO_LABEL(_pinIn));
        Serial.println(" : Set Callback onDisable");
    #endif
    _cbna=cb;
}
void InputCore::onChange(inputCore_State_Callback cb){
    #ifdef _INPUT_DEBUG
        Serial.print(PIN_TO_LABEL(_pinIn));
        Serial.println(" : Set Callback onChange");
    #endif
    _cbc=cb;
}
bool InputCore::isEnable(){
    #ifdef _INPUT_DEBUG
        Serial.print(PIN_TO_LABEL(_pinIn));
        Serial.println(" : Hit isEnable"); 
    #endif
    if(_pinIn == A6 || _pinIn == A7){
         return analogRead(_pinIn)>1000 ? 0:1;
    }else{
         return !digitalRead(_pinIn);
    }
}
void InputCore::process(unsigned long now){
    int reading;
    if(_pinIn == A6 || _pinIn == A7){
         reading = analogRead(_pinIn)>1000 ? 1:0;
    }else{
         reading = digitalRead(_pinIn);
    }
    if (now - lastDebounceTimeOnChange > 20) {
        if(reading!=lastStateOnChange){
            #ifdef _INPUT_DEBUG
            Serial.print(PIN_TO_LABEL(_pinIn));
            Serial.print(" : onChange TimeStamp =>"); 
            Serial.println(now);
            #endif
        /* onChange */
        if(_cbc){
            #ifdef _INPUT_DEBUG
            Serial.print(PIN_TO_LABEL(_pinIn));
            Serial.print(" : Hit Callback onChange TimeStamp => "); 
            Serial.println(now +(now - lastDebounceTimeOnChange));
            #endif
            _cbc();
        }
        /* ------- */
      }
    lastStateOnChange = reading;
    lastDebounceTimeOnChange = now;  
    }
    if(!firstState){
        firstState=true;
        if(reading==LOW){
            if(_cba){
                #ifdef _INPUT_DEBUG
                Serial.print(PIN_TO_LABEL(_pinIn));
                Serial.print(" : Hit First State Callback onEnable TimeStamp => ");
                Serial.println(now +(now - lastDebounceTime));
                #endif
                _cba();
            }
        }else{
            if(_cbna){
                #ifdef _INPUT_DEBUG
                Serial.print(PIN_TO_LABEL(_pinIn));
                Serial.print(" : Hit First State Callback onDisable TimeStamp => ");
                Serial.println(now +(now - lastDebounceTime));
                #endif
                _cbna();
            }
        }
    }else{
        if (now - lastDebounceTime > debounceDelay) {
            if(reading!=lastState){
                if(reading==LOW){
                    /* onEnable */
                    if(_cba){
                        #ifdef _INPUT_DEBUG
                        Serial.print(PIN_TO_LABEL(_pinIn));
                        Serial.print(" : Hit Callback onEnable TimeStamp => "); 
                        Serial.println(now +(now - lastDebounceTime));
                        #endif
                        _cba();
                    }
                    /* ------- */
                }else{
                    /* onDisable */
                    if(_cbna){
                        #ifdef _INPUT_DEBUG
                        Serial.print(PIN_TO_LABEL(_pinIn));
                        Serial.print(" : Hit Callback onDisable TimeStamp => ");
                        Serial.println(now +(now - lastDebounceTime));
                        #endif
                        _cbna();
                    }
                    /* --------- */
                }
            }
        lastState = reading;
        lastDebounceTime = now;  
    }
    }
}
void InputCore::setDebounceDelay(uint32_t delayms){
    #ifdef _INPUT_DEBUG
    Serial.print(PIN_TO_LABEL(_pinIn));
    Serial.print(" : setDebounceDelay to ");
    Serial.print(delayms);
    Serial.println("ms.");
    #endif
    debounceDelay = delayms;
}

#endif //_INPUT_CORE_H
#endif //_MTE_CORE_H