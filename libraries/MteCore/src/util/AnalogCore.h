// #ifdef _MTE_CORE_H
    #ifndef _ANALOG_CORE_H 
    #define _ANALOG_CORE_H 
    #include "Arduino.h"
    typedef void(*analog_core_callback)(uint16_t value); 
    class AnalogCore
    {
    private:
        uint8_t _pinIn;
        analog_core_callback _cb_onChange;
        uint16_t tmpVal;
        uint16_t countVal;
        uint8_t indexVal;
        unsigned long _timeStamp;
    public:
        AnalogCore(uint8_t pinIn);
        ~AnalogCore();
        void onChange(analog_core_callback cb);
        void process(unsigned long now);
        uint16_t getValue();
    };
    
    AnalogCore::AnalogCore(uint8_t pinIn)
    {
        _pinIn = pinIn;
        pinMode(pinIn,INPUT);
    }
    
    AnalogCore::~AnalogCore()
    {
    }
    void AnalogCore::onChange(analog_core_callback cb){
        #ifdef _ANALOG_DEBUG
            Serial.print(PIN_TO_LABEL(_pinIn));
            Serial.println(" : Set Callback onChange");
        #endif
        _cb_onChange = cb;
    }
    void AnalogCore::process(unsigned long now){
        if((now - _timeStamp) > 10){
            uint16_t val = analogRead(A6);
            if(indexVal>50){
                countVal=0;
                indexVal=0;
            }
            indexVal++;
            countVal=countVal+val;
            val = countVal/indexVal;
            if(val!=tmpVal){
                // if(abs(val-tmpVal)>1){
                tmpVal=val;
                #ifdef _ANALOG_DEBUG
                    Serial.print(PIN_TO_LABEL(_pinIn));
                    Serial.print(" : Value = ");
                    Serial.println(val);
                #endif
                if(_cb_onChange){
                    #ifdef _ANALOG_DEBUG
                        Serial.print(PIN_TO_LABEL(_pinIn));
                        Serial.println(" : Hit Callback onChange");
                    #endif
                    _cb_onChange(val);
                }

                // }
            }
            _timeStamp = now;
        }
    }
    uint16_t AnalogCore::getValue(){
        return countVal/indexVal;
        #ifdef _ANALOG_DEBUG
            Serial.print(PIN_TO_LABEL(_pinIn));
            Serial.print(" : Hit getValue = ");
            Serial.println(countVal/indexVal);
        #endif
    }
    #endif //_ANALOG_CORE_H
// #endif // _MTE_CORE_H