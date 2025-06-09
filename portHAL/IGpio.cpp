#include "IGpio.h"



UserTimer IGpio::m_tmSigFilter;
//std::vector<IGpio*> IGpio::list;
std::array<IGpio*, 32> IGpio::list;
bool IGpio::m_IsVectorReserved = false;
u32 IGpio::m_uiCntOfPinForSigFilt;
