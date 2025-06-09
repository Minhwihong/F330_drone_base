#include "drvRs485.h"


std::array<DrvRs485*, 6> DrvRs485::m_selfList;
u8 DrvRs485::m_listIdx;

bool DrvRs485::ReadByte(uint8_t* byte){

    bool rtn = false;

    rtn = m_port.ReadByteInQue(byte);

    return rtn;
}

bool DrvRs485::IsData_Available(){
    bool rtn = m_port.IsDataAvailable();

    return rtn;
}



uint8_t DrvRs485::CheckCommSts(){

    u8 rtn = m_port.GetPortStatus();
    
    return rtn;
}

void DrvRs485::ResetCommRx(){
    m_port.ResetRcv();
}


u8 DrvRs485::SendPacketDMA(u8 *l_ucarData, u8 l_ucDataLen){
    u8 rtn = 0;

    rtn = m_port.SendDataDMA(l_ucarData, l_ucDataLen);
    if(rtn == 0){
        m_sendSts = eRs485SendSts::WaitAck;
    }
    else {
        m_sendSts = eRs485SendSts::Idle;
    }
    return rtn;
}


u8 DrvRs485::SendPacket( u8 *l_ucarData, u8 l_ucDataLen){
    u8 rtn = 0;

    (void)l_ucarData;
    (void)l_ucDataLen;

    return rtn;
}


void DrvRs485::FlowCtl(u8 ucCtl){

    if(ucCtl == 1){
        m_flowPin.Write(true);
    }
    else {
        m_flowPin.Write(false);
    }
}



//bool DrvRs485::WaitSendDone(u32 timeout, std::function<u32(void)> funcGetTick){
bool DrvRs485::WaitSendDone(u32 timeout, u32(*funcGetTick)(void)){
    
    u32 currTick = funcGetTick();

    while(m_sendSts != eRs485SendSts::AckOk){
        if(funcGetTick() - currTick >= timeout){
            return false;
        }
    }

    return true;
}





void DrvRs485::OnISR_DMASendDone(void* args){
    DrvRs485* self = (DrvRs485*)args;

    if(self->m_sendSts != eRs485SendSts::AckOk){
        self->m_sendSts = eRs485SendSts::AckOk;
    }

    if(self->m_bEnableAutoFlow){
        self->FlowCtl(0);
    }
}

