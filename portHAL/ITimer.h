#ifndef __I_TIMER_H__
#define __I_TIMER_H__

#include "typeSimple.h"
#include <functional>

#define MAX_NR_OF_HARDTIMER 16

typedef void (*tmCallback)(void*);


enum class eTimerStatus{
    Stopped = 0,
    Started = 1,
    Undef = 0xFF,
};

class UserTimer;


class ITimer {
public:
    virtual void StartHWTimer() = 0;
    virtual void StopHWTimer() = 0;
    virtual void HWTimerCallback() = 0;
    virtual uint8_t RegisterTimer(UserTimer* _timer) = 0;
    virtual uint8_t GetTimerOccupy() = 0;

    eTimerStatus GetState(){return m_usTmState;} 

protected:

    eTimerStatus m_usTmState = eTimerStatus::Undef;
	uint8_t m_ucRegisterCount;
    UserTimer *m_pTimer[MAX_NR_OF_HARDTIMER];
};


class UserTimer{

public:
    UserTimer() : src(nullptr) {}

    void SetTimerInterface(ITimer* _src){

        src = _src;

        if(src->GetTimerOccupy() >= MAX_NR_OF_HARDTIMER){
            src = NULL;
        }
    }
    

    void TimerMain(){

        if(src == nullptr ){
            return;
        }
        
        m_uiCount++;

        if(m_ucTimerStatus == 1 && m_uiCount >= m_uiPeriod){
            
            m_cb(args);
            m_uiCount = 0;
        }
    }

    void OnOffCtl(uint8_t onOff){
        m_ucTimerStatus = onOff;
    }

    
    //uint8_t RegisterCallback(std::function<void(void*)> _cb, void* _args, uint32_t _uiPeriod, bool _directStart){
    uint8_t RegisterCallback(void(*_cb)(void*), void* _args, uint32_t _uiPeriod, bool _directStart){

        if(src == nullptr){
            return 1;
        }

        m_cb = _cb;
        m_uiPeriod = _uiPeriod;
        m_uiCount = 0;
        args = _args;

        m_usId = src->RegisterTimer(this);

        if(_directStart == true){
            m_ucTimerStatus = 1;
        }

        return 0;
    }

private:
    ITimer* src;
    void* args;
    
    //tmCallback m_cb;
    //std::function<void(void*)> m_cb;
    void(*m_cb)(void*);
    
    uint8_t m_usId;

    uint8_t m_ucTimerStatus;
	uint32_t m_uiCount;
	uint32_t m_uiPeriod;

    
};



#endif
