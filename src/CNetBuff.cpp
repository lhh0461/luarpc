#include <cstddef>
#include <cstring>
#include <arpa/inet.h>

#include "CNetBuff.h"


CNetBuff::CNetBuff()
{
    Reset();
}

CNetBuff::~CNetBuff()
{

}

void CNetBuff::Reset()
{
    m_iErrorCode = 0;
    m_iWritePtr = m_Buff;
    m_iReadPtr = m_Buff;
}

void CNetBuff::PushShort(short siValue)
{
    *((short *)m_iWritePtr) = siValue;
    m_iWritePtr += sizeof(short);
}

void CNetBuff::PushInt(int iValue)
{
    *((int *)m_iWritePtr) = iValue;
    m_iWritePtr += sizeof(int);
}

void CNetBuff::PushLong(long long llValue)
{
    *((long long *)m_iWritePtr) = llValue;
    m_iWritePtr += sizeof(long long);
}

void CNetBuff::PushString(const char* ptr, size_t len)
{
    PushInt(len);
    std::memcpy(m_iWritePtr, ptr, len);
    m_iWritePtr += len;
}

void CNetBuff::PushFloat(float fValue)
{
    *((float *)m_iWritePtr) = fValue;
    m_iWritePtr += sizeof(float);
}

void CNetBuff::PushBytes(const char* ptr, size_t len)
{
    PushInt(len);
    std::memcpy(m_iWritePtr, ptr, len);
    m_iWritePtr += len;
}


int CNetBuff::PopInt()
{
    int iValue = *((int *)m_iReadPtr);
    m_iReadPtr += sizeof(int);
    return iValue;
}

const char *CNetBuff::PopString(size_t &len)
{
    len = PopInt();
    char *ptr = m_iReadPtr;
    m_iReadPtr += len;
    return ptr;
}

float CNetBuff::PopFloat()
{
    float iValue = *((float *)m_iReadPtr);
    m_iReadPtr += sizeof(float);
    return iValue;
}

const char *CNetBuff::PopBytes(size_t &len)
{
    len = PopInt();
    char *ptr = m_iReadPtr;
    m_iReadPtr += len;
    return ptr;
}
