#include "CRpc.h"
#include "CRpcMeta.h"
#include "CNetBuff.h"
#include "CRpcForLua.h"
#include "CLog.h"

CRpc::CRpc()
{
    
}

CRpc::~CRpc()
{
    
}

int CRpc::Init(lua_State *L, const char *pCfg)
{
    m_MetaInfo.Init(pCfg);
    m_luaState = L;
    return 0;
}

int CRpc::RpcCall(int iSessionID, int iFuncID)
{
    const stFunction *pFunc = GetMetaInfo()->FindFuncById(iFuncID);
    if (!pFunc)
    {
        LOG_ERROR("error func id, id=%d", iFuncID);
        return -1;
    }

    GetNetBuff()->Reset();
    GetNetBuff()->PushInt(iFuncID);
    if (pFunc->bIsCFunc)
    {
        //TODO C函数打包
        return 0;
    }
    
    if (PackForLua(m_luaState, pFunc, GetNetBuff()) == -1)
    {
        return -1;
    }

    //TODO 发送出去
    //SendMessageToSession(iSessionID);
    return 0;
}

int CRpc::RpcDisptach(CNetBuff *pBuff)
{
    int iFuncID = pBuff->PopInt();

    const stFunction *pFunc = GetMetaInfo()->FindFuncById(iFuncID);
    if (!pFunc)
    {
        LOG_ERROR("error func id, id=%d", iFuncID);
        return -1;
    }

    if (pFunc->bIsCFunc)
    {
        //TODO C函数分发
        return 0;
    }

    int top = lua_gettop(m_luaState);
    LOG_DEBUG("on dispatch id=%d, top=%d", iFuncID, top);
    std::string cmd = "require (\"" + pFunc->strFuncModule + "\")";
    LOG_DEBUG("cmd=%s", cmd.c_str());
    //TODO 清理栈大小
    const int ret= luaL_dostring(m_luaState, cmd.c_str());
    if (ret != LUA_OK) {
        LOG_ERROR("require module fail. Error:%s", lua_tostring(m_luaState, -1));
        lua_pop(m_luaState, 1); // pop error message
        return -1;
    }
    //把_LOADED表放到栈顶
    lua_getfield(m_luaState, LUA_REGISTRYINDEX, LUA_LOADED_TABLE);
    //把函数放到栈顶，协议是模块必须要返回一个表格
    lua_getfield(m_luaState, -1, pFunc->strFuncName.c_str());  /* LOADED[name] */
    int top2 = lua_gettop(m_luaState);
    LOG_DEBUG("top2=%d", top2);
    
    if (UnPackForLua(m_luaState, pFunc, pBuff) == -1)
    {
        LOG_ERROR("unpack error");
        return -1;
    }
    lua_pcall(m_luaState, pFunc->argList.size(), 0, 0);

    //此时参数已经在栈上
    //TODO 调用模块函数
    return 0;
}

CRpcMeta const* CRpc::GetMetaInfo()
{
    return &m_MetaInfo;
}

CNetBuff * CRpc::GetNetBuff()
{
    return &m_Buff;
}
