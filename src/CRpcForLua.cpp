#include "lua.hpp"
#include "CRpcMeta.h"
#include "CRpcForLua.h"
#include "CNetBuff.h"

int PackForLua(lua_State *L, const stFunction *pFunc, CNetBuff *buff)
{
    int argnum = lua_gettop(L) - 2;
    if (argnum != (int)pFunc->argList.size())
    {
        return -1;
    }
    int iBeginIdx = 3;
    for (int i = 0; i < (int)pFunc->argList.size(); ++i, ++iBeginIdx)
    {
        if (PackField(L, &pFunc->argList[i], iBeginIdx, buff) == -1)
        {
            return -1;
        }
    }
    return 0;
}

int UnPackForLua(lua_State *L, const stFunction *pFunc, CNetBuff *buff)
{
    for (int i = 0; i < (int)pFunc->argList.size(); ++i)
    {
        if (UnPackField(L, &pFunc->argList[i], buff) == -1)
        {
            return -1;
        }
    }
    return 0;
}

int PackField(lua_State *L, stField const* pField, int idx, CNetBuff *buff)
{
    switch (pField->cFieldType)
    {
        case RPC_INT:
        {
	        int value = luaL_checkinteger(L, idx);
            buff->PushInt(value);
        }
        break;
        case RPC_STRING:
        {
            size_t len;
	        const char *value = luaL_checklstring(L, idx, &len);
            buff->PushString(value, len);
        }
        break;
        case RPC_FLOAT:
        {
	        float value = luaL_checknumber(L, idx);
            buff->PushFloat(value);
        }
        break;
        case RPC_BYTES:
        {
            size_t len;
	        const char *value = luaL_checklstring(L, idx, &len);
            buff->PushBytes(value, len);
        }
        break;
    }
}

int UnPackField(lua_State *L, stField const* pField, CNetBuff *buff)
{
    switch (pField->cFieldType)
    {
        case RPC_INT:
        {
            int value = buff->PopInt();
            if (buff->GetErrorNo() > 0)
            {
                return -1;
            }
            lua_pushinteger(L, value);
        }
        break;
        case RPC_STRING:
        {
            size_t size;
            const char *ptr = buff->PopString(size);
            if (buff->GetErrorNo() > 0)
            {
                return -1;
            }
            lua_pushlstring(L, ptr, size);
        }
        break;
        case RPC_FLOAT:
        {
            float value = buff->PopFloat();
            if (buff->GetErrorNo() > 0)
            {
                return -1;
            }
            lua_pushnumber(L, value);
        }
        break;
        case RPC_BYTES:
        {
            size_t size;
            const char *ptr = buff->PopBytes(size);
            if (buff->GetErrorNo() > 0)
            {
                return -1;
            }
            lua_pushlstring(L, ptr, size);
        }
        break;
        default:
        break;
    }
    return 0;
}