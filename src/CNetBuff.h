#ifndef __CNET_BUFF__
#define __CNET_BUFF__

enum
{
    MAX_NETBUF_SIZE = 1024*1024, //最大的网络缓冲区==1M
};

class CNetBuff
{
public:
    CNetBuff();
    ~CNetBuff();
public:
    void Reset();
    void PushShort(short sValue);
    void PushInt(int iValue);
    void PushLong(long long llValue);
    void PushString(const char* ptr, size_t len);
    void PushFloat(float fValue);
    void PushBytes(const char* ptr, size_t len);
public:
    long long PopLong();
    short PopShort();
    int PopInt();
    const char *PopString(size_t &len);
    float PopFloat();
    const char *PopBytes(size_t &len);
public:
    int GetErrorNo() { return m_iErrorCode; }
    int GetRemainSize() { return m_iWritePtr < m_iReadPtr ? m_iWritePtr + MAX_NETBUF_SIZE - m_iReadPtr : m_iWritePtr - m_iReadPtr; }
private:
    char *m_iWritePtr;
    char *m_iReadPtr;
    int m_iErrorCode;
    char m_Buff[MAX_NETBUF_SIZE];
};

#endif
