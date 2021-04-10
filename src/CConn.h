#include "CNetBuff.h"

class CConnection
{
private:
    int iConnState;
    int iVfd;
    int iFd;
    CNetBuff m_RecvBuff;
    std::list<CNetBuff *> m_RecvBuffList;
    std::list<CNetBuff *> m_SendBuffList;
};
