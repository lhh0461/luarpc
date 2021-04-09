
#include "lua.hpp"
#include "CRpc.h"

static int l_rpccall (lua_State *L)
{
    int session = luaL_checkinteger(L, 1);
    int funcid = luaL_checkinteger(L, 2);

    int argnum = lua_gettop(L);
    g_pRpc->RpcCall(session, funcid);
    return 1;
}

static const luaL_Reg rpclib[] = 
{
  {"call", l_rpccall},
  {NULL, NULL}
};

LUAMOD_API "C" int luaopen_librpc (lua_State *L) {
    luaL_newlib(L, rpclib);
    return 1;
}

