#ifdef _MTE_CORE_H
    #ifndef _COUNTER_CORE_H 
    #define _COUNTER_CORE_H 
    #include "Arduino.h"
    typedef void(*counter_core_callback)(); 
    class Counter
    {
    private:
        unsigned long _counterValue;
        unsigned long _valueMax;
        int _increaseValue;
        counter_core_callback _cb_onChange;
        counter_core_callback _cb_onReset;
        counter_core_callback _cb_onTriggered;
    public:
        Counter(/* args */);
        ~Counter();
        unsigned long getCounterValue();
        void setValueMax(unsigned long value);
        void setIncreaseValue(int value = 1);
        void reset();
        void trigger();
        void onChange(counter_core_callback cb);
        void onReset(counter_core_callback cb);
        void onTriggered(counter_core_callback cb);
    };
    
    Counter::Counter(/* args */)
    {
        _counterValue=0;
        _increaseValue=1;
        _valueMax=0;
    }
    
    Counter::~Counter()
    {
    }
    unsigned long Counter::getCounterValue(){
        #ifdef _COUNTER_DEBUG
        Serial.prinln("Counter : Hit getCounterValue");
        #endif
        return _counterValue;
    }
    void Counter::setValueMax(unsigned long value){
        #ifdef _COUNTER_DEBUG
        Serial.print("Counter : setValueMax to ");
        Serial.prinln(value);
        #endif
        _valueMax = value;
    }
    void Counter::setIncreaseValue(int value=1){
        #ifdef _COUNTER_DEBUG
        Serial.print("Counter : setIncreaseValue to ");
        Serial.prinln(value);
        #endif
        _increaseValue = value;
    }
    void Counter::reset(){
        #ifdef _COUNTER_DEBUG
        Serial.prinln("Counter : Hit reset");
        #endif
        _counterValue=0;
        if(_cb_onChange){
            #ifdef _COUNTER_DEBUG
            Serial.prinln("Counter : Hit Callback onChange");
            #endif
            _cb_onChange();
        }
        if(_cb_onReset){
            #ifdef _COUNTER_DEBUG
            Serial.prinln("Counter : Hit Callback onReset");
            #endif
            _cb_onReset();
        }
    }
    void Counter::trigger(){
        #ifdef _COUNTER_DEBUG
        Serial.prinln("Counter : Hit trigger");
        #endif
        _counterValue = _counterValue + _increaseValue;
        if(_cb_onTriggered){
            #ifdef _COUNTER_DEBUG
            Serial.prinln("Counter : Hit Callback onTriggered");
            #endif
            _cb_onTriggered();
        }
        if(_counterValue >= _valueMax){
            reset();
        }else{
            if(_cb_onChange){
            #ifdef _COUNTER_DEBUG
            Serial.prinln("Counter : Hit Callback onChange");
            #endif
            _cb_onChange();
            }
        }
    }
    void Counter::onChange(counter_core_callback cb){
        #ifdef _COUNTER_DEBUG
        Serial.prinln("Counter : Hit Set Callback onChange");
        #endif
        _cb_onChange = cb;
    }
    void Counter::onReset(counter_core_callback cb){
        #ifdef _COUNTER_DEBUG
        Serial.prinln("Counter : Hit Set Callback onReset");
        #endif
        _cb_onReset = cb;
    }
    void Counter::onTriggered(counter_core_callback cb){
        #ifdef _COUNTER_DEBUG
        Serial.prinln("Counter : Hit Set Callback onTriggered");
        #endif
        _cb_onTriggered = cb;
    }
    #endif // _COUNTER_CORE_H
#endif _MTE_CORE_H