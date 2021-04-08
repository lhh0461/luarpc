#include "lua.hpp"
#include "CRpc.h"

static int l_rpccall (lua_State *L)
{
    int session = luaL_checkinteger(L, 1);
    int funcid = luaL_checkinteger(L, 2);

    int argnum = lua_gettop(L);
    g_rpc->RpcCall(session, funcid);
    return 1;
}

static const luaL_Reg crpclib[] = 
{
  {"call", l_rpccall},
  {NULL, NULL}
};

LUAMOD_API int luaopen_crpc (lua_State *L) {
    luaL_newlib(L, crpclib);
    return 1;
}

