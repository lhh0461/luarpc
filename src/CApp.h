#include "lua.hpp"
#include "CRpc.h"

class CApp
{
public:
    int Start();
    int Run();
    virtual int OnInit() = 0; //业务初始化
    virtual void OnDestroy() = 0; //业务析构
protected:
    int InitLua();
private:
    lua_State *L;
    CRpc m_Rpc;
    CConnectionMgr m_ConnMgr;
    CEventLoop m_EventLoop;
};
