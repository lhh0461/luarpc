
#include "CApp.h"
/*
#include "lua.hpp"
#include "CRpc.h"
#include "CLog.h"
#include <iostream>

int main()
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    int ret = luaL_dostring(L, "package.path = package.path .. \";script/?.lua;gen_code/?.lua\"");
    if (ret != LUA_OK){
        LOG_ERROR("Error: %s", lua_tostring(L,-1));
        return -1;
    }
    ret = luaL_dostring(L, "package.cpath = package.cpath .. \";./?.so\"");
    if (ret != LUA_OK){
        LOG_ERROR("Error: %s", lua_tostring(L,-1));
        return -1;
    }

    SetLogFileName("./log");
    g_pRpc = new CRpc();
    g_pRpc->Init(L, "./gen_code/meta.cfg");

    ret = luaL_dofile(L, "script/test.lua");
    if (ret != LUA_OK){
        LOG_ERROR("%s", lua_tostring(L,-1));
        return -1;
    }
    std::cout << "rpc call finish1." <<std::endl;
    g_pRpc->RpcDisptach(g_pRpc->GetNetBuff());
    std::cout << "rpc call finish." <<std::endl;
    return 0;
}
*/

class CSimpleServer : public CApp
{
public:
    CSimpleServer() {}
    ~CSimpleServer() {}

    // 业务初始化
    // 返回为0，初始化成功
    // 返回非0，初始化失败，框架会直接exit
    virtual int OnInit()
    {

        //ret = luaL_dofile(L, "script/test.lua");
        //if (ret != LUA_OK){
        //    LOG_ERROR("%s", lua_tostring(L,-1));
        //    return -1;
        //}
        //m_Rpc.RpcDisptach(m_Rpc->GetNetBuff());
        //LOG_DEBUG("dispatch finish");
        return 0;
    }

    // 业务析构
    virtual void OnDestroy() {}
};

CSimpleServer MyServer;

int main()
{
    MyServer.Start();
    MyServer.Run();
}
