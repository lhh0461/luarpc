
#include "lua.hpp"
#include "CRpc.h"
#include "CLog.h"
#include <iostream>

int main()
{
    lua_State *L = luaL_newstate();  /* create state */
    luaL_openlibs(L);

    SetLogFileName("./log");

    CRpc *pRpc = new CRpc();
    pRpc->Init(L, "./tools/meta.cfg");

    pRpc->RpcCall(0, 1);
    pRpc->RpcCall(0, 1);
    std::cout << "rpc call finish." <<std::endl;
}