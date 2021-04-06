
#include "lua.hpp"
#include "CRpc.h"
#include "CLog.h"
#include <iostream>

CRpc *g_pRpc = NULL;

int main()
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dostring(L, "package.path = package.path .. \";script/?.lua;gen_code/?.lua\"");

    SetLogFileName("./log");
    g_pRpc = new CRpc()
    pRpc->Init(L, "./tools/meta.cfg");

    luaL_dofile(L, "test.lua");
    pRpc->RpcDisptach(pRpc->GetNetBuff());
    std::cout << "rpc call finish." <<std::endl;
    return 0;
}
