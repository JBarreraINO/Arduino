#ifdef _MTE_CORE_H
#ifndef _OUTPUT_CORE_H 
#define _OUTPUT_CORE_H 
#include "Arduino.h"
typedef void(*OutputCore_State_Callback)();
class OutputCore {
    protected:
    private:
        bool firstState;
        OutputCore(const OutputCore&);
        OutputCore& operator=(const OutputCore&);
        const uint8_t debounceDelay = 20;
        unsigned long lastDebounceTime;
        bool lastState=HIGH;
        uint8_t _pinIn;
        OutputCore_State_Callback _cba;
        OutputCore_State_Callback _cbna;
        OutputCore_State_Callback _cbc;
    public:
        explicit OutputCore(uint8_t pinIn);
        virtual~OutputCore();
        void onEnable(OutputCore_State_Callback cb);
        void onDisable(OutputCore_State_Callback cb);
        void onChange(OutputCore_State_Callback cb);
        bool isEnable();
        void process(unsigned long now);
        bool enable();
        bool disable();
};
OutputCore::OutputCore(uint8_t pinIn) {
    _pinIn=pinIn;
    pinMode(pinIn,OUTPUT);
    digitalWrite(pinIn,HIGH);
}

OutputCore::~OutputCore() {}

void OutputCore::onEnable(OutputCore_State_Callback cb) {
    #ifdef _OUTPUT_DEBUG
    Serial.print(PIN_TO_LABEL(_pinIn));
    Serial.println(" : Set Callback onEnable");
    #endif
    _cba=cb;
}
void OutputCore::onDisable(OutputCore_State_Callback cb ){
    #ifdef _OUTPUT_DEBUG
    Serial.print(PIN_TO_LABEL(_pinIn));
    Serial.println(" : Set Callback onDisable");
    #endif
    _cbna=cb;
}
void OutputCore::onChange(OutputCore_State_Callback cb){
    #ifdef _OUTPUT_DEBUG
    Serial.print(PIN_TO_LABEL(_pinIn));
    Serial.println(" : Set Callback onChange");
    #endif
    _cbc=cb;
}
bool OutputCore::isEnable(){
    #ifdef _OUTPUT_DEBUG
    Serial.print(PIN_TO_LABEL(_pinIn));
    Serial.println(" : Hit isEnable"); 
    #endif
    return !digitalRead(_pinIn);
}
void OutputCore::process(unsigned long now){
    int reading = digitalRead(_pinIn);
    if(!firstState){
        firstState=true;
        if(reading==LOW){
            if(_cba){
                #ifdef _OUTPUT_DEBUG
                Serial.print(PIN_TO_LABEL(_pinIn));
                Serial.print(" : Hit First State Callback onEnable TimeStamp => ");
                Serial.println(now +(now - lastDebounceTime));
                #endif
                _cba();
            }
        }else{
            if(_cbna){
                #ifdef _OUTPUT_DEBUG
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
                #ifdef _OUTPUT_DEBUG
                Serial.print(PIN_TO_LABEL(_pinIn));
                Serial.print(" : onChange TimeStamp =>"); 
                Serial.println(now);
                #endif
                    /* onChange */
                    if(_cbc){
                        #ifdef _OUTPUT_DEBUG
                        Serial.print(PIN_TO_LABEL(_pinIn));
                        Serial.print(" : Hit Callback onChange TimeStamp => "); 
                        Serial.println(now +(now - lastDebounceTime));
                        #endif
                        _cbc();
                    }
                    /* ------- */
                if(reading==LOW){
                    /* onEnable */
                    if(_cba){
                        #ifdef _OUTPUT_DEBUG
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
                        #ifdef _OUTPUT_DEBUG
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
bool OutputCore::enable(){
    #ifdef _OUTPUT_DEBUG
    Serial.print(PIN_TO_LABEL(_pinIn));
    Serial.println(" : enable"); 
    #endif
    digitalWrite(_pinIn,LOW);
    return digitalRead(_pinIn)==LOW;
}
bool OutputCore::disable(){
    #ifdef _OUTPUT_DEBUG
    Serial.print(PIN_TO_LABEL(_pinIn));
    Serial.println(" : Hit disable");
    #endif 
    digitalWrite(_pinIn,HIGH);
    return digitalRead(_pinIn)==HIGH;
}
#endif //_OUTPUT_CORE_H
#endif //_MTE_CORE_H