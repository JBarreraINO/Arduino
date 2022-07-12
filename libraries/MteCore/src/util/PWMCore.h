// #ifdef _MTE_CORE_H
    #ifndef _PWM_CORE_H 
    #define _PWM_CORE_H 
    #include "Arduino.h"
    typedef void(*pwm_core_callback)(uint8_t valuePercent); 
    class PWMCore
    {
    private:
        uint8_t _pinIn;
        #ifdef _ENABLE_SMOOTH_PWM
            #ifndef _DELAY_SMOOTH_PWM
                #define _DELAY_SMOOTH_PWM 1000
            #endif
            unsigned long _timeStamp;
            uint8_t _valDestination;
            uint8_t _tmpValNow;
            uint16_t _delayTick;
            pwm_core_callback _cb_onProcess;
        #endif
        uint8_t _valNow;
        pwm_core_callback _cb_onChange;
    public:
        PWMCore(uint8_t pin);
        ~PWMCore();
        void setValue(uint8_t valuePercent);
        uint8_t getValue();
        #ifdef _ENABLE_SMOOTH_PWM
            void process(unsigned long now);
            void onProcess(pwm_core_callback cb);
        #endif
        void onChange(pwm_core_callback cb);
    };
    
    PWMCore::PWMCore(uint8_t pin)
    {
        _pinIn = pin;
    }
    
    PWMCore::~PWMCore()
    {
    }
    uint8_t PWMCore::getValue(){
        #ifdef _PWM_DEBUG
            Serial.print(PIN_TO_LABEL(_pinIn));
            Serial.print(" : Hit getValue = ");
            Serial.println(map(_valNow,0,255,0,100));
        #endif
        return map(_valNow,0,255,0,100);
    }
    void PWMCore::setValue(uint8_t valuePercent){
        if(valuePercent>100)valuePercent=100;
        #ifdef _PWM_DEBUG
            Serial.print(PIN_TO_LABEL(_pinIn));
            Serial.print(" : Hit setValue = ");
            Serial.print(valuePercent);
            Serial.println("%");
        #endif
        #ifdef _ENABLE_SMOOTH_PWM
            _valDestination = map(valuePercent,0,100,0,255);
            if(_valNow != _valDestination){
                _tmpValNow = _valNow;
                analogWrite(_pinIn,_valNow);
                _delayTick=0;
                if(_cb_onChange){
                    _cb_onChange(getValue());
                }
            }
        #else
            if(_valNow != valuePercent){
                _valNow=map(valuePercent,0,100,0,255);
                analogWrite(_pinIn,_valNow);
                if(_cb_onChange){
                    _cb_onChange(getValue());
                }
            }
        #endif
    }
    #ifdef _ENABLE_SMOOTH_PWM
        void PWMCore::process(unsigned long now){
            if(now - _timeStamp > 30){
                if(_delayTick > _DELAY_SMOOTH_PWM){
                    _delayTick=_DELAY_SMOOTH_PWM;
                    _valNow = _valDestination;
                    analogWrite(_pinIn,_valNow);
                    if(_cb_onProcess){
                        #ifdef _PWM_DEBUG
                            Serial.print(PIN_TO_LABEL(_pinIn));
                            Serial.println(" : Hit Callback onProcess");
                        #endif
                        _cb_onProcess(getValue());
                    }
                }else if(_delayTick < _DELAY_SMOOTH_PWM){
                    if(_valNow < _valDestination){ //PWM UP
                        _valNow = map(_delayTick,0,_DELAY_SMOOTH_PWM,_tmpValNow,_valDestination);
                        analogWrite(_pinIn,_valNow);
                    }else if( _valNow > _valDestination){ //PWM DOWN
                        _valNow=map(_delayTick,_DELAY_SMOOTH_PWM,0,_valDestination,_tmpValNow);
                        analogWrite(_pinIn,_valNow);
                    }
                    _delayTick=_delayTick+30;
                    if(_cb_onProcess){
                        #ifdef _PWM_DEBUG
                            Serial.print(PIN_TO_LABEL(_pinIn));
                            Serial.println(" : Hit Callback onProcess");
                        #endif
                        _cb_onProcess(getValue());
                    }
                }
            _timeStamp=now;
            }
        }
        void PWMCore::onProcess(pwm_core_callback cb){
            #ifdef _PWM_DEBUG
            Serial.print(PIN_TO_LABEL(_pinIn));
            Serial.println(" : Set Callback onProcess");
            #endif
            _cb_onProcess = cb;
        }
    #endif
    void PWMCore::onChange(pwm_core_callback cb){
        #ifdef _PWM_DEBUG
            Serial.print(PIN_TO_LABEL(_pinIn));
            Serial.println(" : Set Callback onChange");
        #endif
        _cb_onChange = cb;
    }
    #endif //_PWM_CORE_H
// #endif // _MTE_CORE_H