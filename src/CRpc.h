#ifndef __CRPC__
#define __CRPC__

#include "lua.hpp"
#include "CRpcMeta.h"
#include "CNetBuff.h"

class CRpc
{
public:
    CRpc();
    ~CRpc();
public:
    int Init(lua_State *L, const char *pCfg);
    int RpcCall(int iSessionId, int iFuncId);
    int RpcDisptach(CNetBuff *pBuff);
    CRpcMeta const* GetMetaInfo();
private:
    lua_State *m_luaState;
    CRpcMeta m_MetaInfo;
    CNetBuff m_Buff;
};

#endif