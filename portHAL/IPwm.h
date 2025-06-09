#ifndef __I_PWM_H__
#define __I_PWM_H__

#include "typeSimple.h"


class IPwm {
public:
    virtual void StartStopPwm(bool) = 0;
    virtual void PwmControl(u16, u32) = 0;
    virtual void PwmOnOff(bool onOff, u32 _uiCh) = 0;

    // ----------------- Input Capture Mode -------------------
    virtual void InputCaptureOnOff(bool, u32) = 0;
    virtual u32 GetInputCaptureVal(bool*, u32) = 0;
    virtual bool IsOverFlowDetected() = 0;

    // ---------------- Encoder Mode --------------------
    virtual void EncoderModeOnOff(bool onOff) = 0;
    virtual u32 GetEncoderCount() = 0;
private:
};



#endif