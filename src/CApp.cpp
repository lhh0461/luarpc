#include "CApp.h"
#include "CLog.h"
#include "lua.hpp"

int CApp::Start()
{
    int iRetCode = InitLua();
    if (iRetCode)
    {

    }

    //TODO 初始化线程
    //TODO 初始化网络

    SetLogFileName("./log");

    m_Rpc.Init(L, "./gen_code/meta.cfg");

    iRetCode = OnInit();
    if (iRetCode)
    {

    }
}

int CApp::Run()
{
    int ret = luaL_dofile(L, "script/test.lua");
    if (ret != LUA_OK){
        LOG_ERROR("%s", lua_tostring(L,-1));
        return -1;
    }
    m_Rpc.RpcDisptach(m_Rpc.GetNetBuff());
}

int CApp::InitLua()
{
    L = luaL_newstate();
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
    return 0;
}
