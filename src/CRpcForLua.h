#ifndef __CRPC_FOR_LUA__
#define __CRPC_FOR_LUA__

#include "lua.hpp"
#include "CRpcMeta.h"
#include "CNetBuff.h"

int PackForLua(lua_State *L, stFunction const*pFunc, CNetBuff *buff);
int UnPackForLua(lua_State *L, const stFunction *pFunc, CNetBuff *buff);
int PackField(lua_State *L, stField const* pField, int idx, CNetBuff *buff);
int UnPackField(lua_State *L, stField const* pField, CNetBuff *buff);

#endif