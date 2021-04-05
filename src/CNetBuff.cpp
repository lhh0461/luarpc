#include <cstddef>
#include <cstring>

#include "CNetBuff.h"


CNetBuff::CNetBuff()
{

}

CNetBuff::~CNetBuff()
{

}

void CNetBuff::Reset()
{
    m_iSize = 0;
    m_iOffset = 0;
    m_iErrorCode = 0;
    m_pCurPtr = m_Buff;
}

void CNetBuff::PushShort(short siValue)
{
    *((short *)m_pCurPtr) = siValue;
    m_pCurPtr += sizeof(short);
}

void CNetBuff::PushInt(int iValue)
{
    *((int *)m_pCurPtr) = iValue;
    m_pCurPtr += sizeof(int);
}

void CNetBuff::PushLong(long long llValue)
{
    *((long long *)m_pCurPtr) = llValue;
    m_pCurPtr += sizeof(long long);
}

void CNetBuff::PushString(const char* ptr, size_t len)
{
    PushInt(len);
    std::memcpy(m_pCurPtr, ptr, len);
    m_pCurPtr += len;
}

void CNetBuff::PushFloat(float fValue)
{
    *((float *)m_pCurPtr) = fValue;
    m_pCurPtr += sizeof(float);
}

void CNetBuff::PushBytes(const char* ptr, size_t len)
{
    PushInt(len);
    std::memcpy(m_pCurPtr, ptr, len);
    m_pCurPtr += len;
}


int CNetBuff::PopInt()
{
    int iValue = *((int *)m_pCurPtr);
    m_pCurPtr += sizeof(int);
    return iValue;
}

const char *CNetBuff::PopString(size_t &len)
{
    len = PopInt();
    return m_pCurPtr;
}

float CNetBuff::PopFloat()
{
    float iValue = *((float *)m_pCurPtr);
    m_pCurPtr += sizeof(float);
    return iValue;
}

const char *CNetBuff::PopBytes(size_t &len)
{
    len = PopInt();
    return m_pCurPtr;
}