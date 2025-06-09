#ifndef __IF_PWM_H__
#define __IF_PWM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "portStm32_Pwm.h"

#define PWM_POLE_U_POS           (1)
#define PWM_POLE_U_NEG           (2)

#define PWM_POLE_V_POS           (3)
#define PWM_POLE_V_NEG           (4)

#define PWM_POLE_W_POS           (5)
#define PWM_POLE_W_NEG           (6)


enum eBLDC_PWM_CH{
    ePWM_POLE_U_POS = 0,
    ePWM_POLE_U_NEG,

    ePWM_POLE_V_POS,
    ePWM_POLE_V_NEG,

    ePWM_POLE_W_POS,
    ePWM_POLE_W_NEG,

    eBLDC_PWM_MAX
};

typedef struct PWM_LookupTb_tag{
    u8 ucBldcChId;
    u32 uiHwChId;
}PWM_LookupTb_t;




enum eBLDC_PWM_DUAL_CH{
    ePWM_POLE_DUAL_U = 0,
    ePWM_POLE_DUAL_V,
    ePWM_POLE_DUAL_W,

    eBLDC_PWM_DUAL_MAX
};




typedef struct PWM_Complementary_tag{
    u8 ucChP;
    u8 ucChN;
}PWM_Complementary_t;



typedef struct PWM_Context_tag{
    Pwm1Ch_HwWrapper* pxPwmSrc[eBLDC_PWM_MAX];
   
    u8 ucChId[eBLDC_PWM_MAX];
    u32 uiLookupChTb[eBLDC_PWM_MAX];
    u32 uiMaxDuty[eBLDC_PWM_MAX];

}BldcPWM_Ctx_t;


typedef struct DualPWM_Context_tag{
    PWM2Ch_HwWrapper* pxPwmSrc[eBLDC_PWM_DUAL_MAX];
    u8 ucChId[eBLDC_PWM_DUAL_MAX];

    u32 uiLookupChTb[eBLDC_PWM_DUAL_MAX];
    PWM_Complementary_t dualCh[eBLDC_PWM_DUAL_MAX];
}Bldc_DualPWM_Ctx_t;



void PWM_StartStop(BldcPWM_Ctx_t* pxCtx, u8 ucOnOff, u8 ucCh);
void PWM_ChannelMatching(BldcPWM_Ctx_t* pxBldcCtx, Pwm1Ch_HwWrapper* pxHw, u8 ucBldcCh);

void PWM_Generate(BldcPWM_Ctx_t* pxCtx, u32 uiDuty,u8 ucCh);
void PWM_Generate_Complementary(BldcPWM_Ctx_t* pxCtx, u32 uiDuty, u8 ucChP, u8 ucChN);
void PWM_GenerateMax(BldcPWM_Ctx_t* pxCtx, u8 ucCh);


void PWMDual_Init();
void PWMDual_StartStop(Bldc_DualPWM_Ctx_t* pxCtx, u8 ucOnOff, u8 ucCh);
void PWMDual_Generate(Bldc_DualPWM_Ctx_t* pxCtx, u8 ucCh, u32 uiDuty);
void PWMDual_NChannelHigh(Bldc_DualPWM_Ctx_t* pxCtx, u8 ucCh);
void PWMDual_NChannelLow(Bldc_DualPWM_Ctx_t* pxCtx, u8 ucCh);
void PWMDual_Complementary(Bldc_DualPWM_Ctx_t* pxCtx, PWM_Complementary_t* xCh, u8 ucMode);


#ifdef __cplusplus
}
#endif

#endif