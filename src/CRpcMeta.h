#ifndef __RPC_META__
#define __RPC_META__

#include <string>
#include <vector>

enum
{
    MAX_FUNC_NUM = 500,
};

enum FieldType {
    RPC_INT = 1,
    RPC_STRING = 2,
    RPC_FLOAT = 3,
    RPC_BYTES = 4,
};

struct stField
{
    FieldType cFieldType;
    std::string strFieldName;
};

struct stFunction
{
    short int id;
    std::string strFuncName;
    std::string strFuncModule;
    bool bIsCFunc;
    std::vector<stField> argList;
    std::vector<stField> resList;
};

class CRpcMeta
{
public:
    int Init(const char *pCfg);
    stFunction const* FindFuncById(int iId) const;
private:
    stFunction m_FuncTable[MAX_FUNC_NUM];
};

#endif