#ifndef __IGPIO_H__
#define __IGPIO_H__

#include "typeSimple.h"
#include "portSTM32_timer.h"
#include <vector>

#define GPI_FILTER_ON       (1)
#define GPI_FILTER_OFF      (0)

enum class eGpioMode{
    Input = 0,
    Output,
    Interrupt,
};

class IGpio{
public:

    IGpio(u8 _ucFilter, eGpioMode _useMode) : m_ucFilter(_ucFilter), m_useMode(_useMode){
        //m_ucFilter = 0;
    }

    virtual void Toggle() = 0;
    virtual void Write(bool sig) = 0;
    virtual u8 Read() = 0;


    void Init(eGpioMode _mode, u8 _ucUseFilter){
        IGpio::InitVector();
        //IGpio::list.push_back(this);
        
        m_useMode = _mode;
        m_ucUseFilter = _ucUseFilter;
    }

    void Init(){
        IGpio::InitVector();
        //IGpio::list.push_back(this);
        IGpio::list[IGpio::m_uiCntOfPinForSigFilt++] = this;
    }

    u8 GetValue(){return m_mcFilterVal;}

    

    

    static void InitFilterConfig(ITimer* _tmSrc){
        m_tmSigFilter.OnOffCtl(1);
        m_tmSigFilter.SetTimerInterface(_tmSrc);
        m_tmSigFilter.RegisterCallback(SigFilterCallback, nullptr, 1, true);

    }

    

protected:
    bool m_ucUseFilter;
    u8 m_ucFilter = 0;
    eGpioMode m_useMode;
    u8 m_mcFilterVal;
    

    static UserTimer m_tmSigFilter;
    //static std::vector<IGpio*> list;
    static std::array<IGpio*, 32> list;
    static bool m_IsVectorReserved;
    static u32 m_uiCntOfPinForSigFilt;


    static void InitVector(){
        if(IGpio::m_IsVectorReserved == false){
            //IGpio::list.reserve(32);
            m_IsVectorReserved = true;
        }    
    }

    static void SigFilterCallback(void* args){

        u8 l_ucDiTemp;

        (void)args;

        for(u8 idx=0; idx< m_uiCntOfPinForSigFilt; ++idx){
            IGpio* pin = list[idx];

            if(pin->m_useMode == eGpioMode::Input){
                l_ucDiTemp = pin->Read();

                if(pin->m_ucUseFilter == true){
                    pin->m_ucFilter <<= 1;
                    pin->m_ucFilter= pin->m_ucFilter | l_ucDiTemp;

                    if(pin->m_ucFilter == 0x00 )
                    {
                        pin->m_mcFilterVal = 0;
                    }
                    else if(pin->m_ucFilter == 0xFF)
                    {
                        pin->m_mcFilterVal = 1;
                    }
                }
                else {
                    pin->m_mcFilterVal = l_ucDiTemp;
                }
            }
        }

        // for(auto pin : list){

        //     if(pin->m_useMode == eGpioMode::Input){
        //         l_ucDiTemp = pin->Read();

        //         if(pin->m_ucUseFilter == true){
        //             pin->m_ucFilter <<= 1;
        //             pin->m_ucFilter= pin->m_ucFilter | l_ucDiTemp;

        //             if(pin->m_ucFilter == 0x00 )
        //             {
        //                 pin->m_mcFilterVal = 0;
        //             }
        //             else if(pin->m_ucFilter == 0xFF)
        //             {
        //                 pin->m_mcFilterVal = 1;
        //             }
        //         }
        //         else {
        //             pin->m_mcFilterVal = l_ucDiTemp;
        //         }
        //     }
        // }
    }

};







#endif
