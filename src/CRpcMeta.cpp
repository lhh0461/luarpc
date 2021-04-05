#include "CRpcMeta.h"

int CRpcMeta::Init(const char *pCfg)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(pCfg, "r");
    if (fp == NULL) {
        printf("open meta.cfg fail\n");
        return 1;
    }

    int iFunctionNum;
    getline(&line, &len, fp);
    sscanf(line, "function_table_num:%d", &iFunctionNum);

    int id;
    char name[200];
    char module[200];
    char field[200];
    int arg_num;
    int res_num;
    stFunction *pFunction;
    for (int i = 0; i < iFunctionNum; i++) {
        getline(&line, &len, fp);
        sscanf(line, "function_id:%d,arg_num:%d,res_num:%d,path=%[^,]%*cfunction=%s", 
            &id, &arg_num, &res_num, module, name);
        pFunction = &m_FuncTable[id];
        pFunction->id = id;
        pFunction->strFuncName = name;
        pFunction->strFuncModule = module;

        for (int j = 0; j < arg_num; j++) {
            getline(&line, &len, fp);
            int iFieldType;
            sscanf(line, "arg_type:%d,arg_name=%s", &iFieldType, field);
            pFunction->argList.push_back({(FieldType)iFieldType, field});
        }

        for (int j = 0; j < res_num; j++) {
            getline(&line, &len, fp);
            int iFieldType;
            sscanf(line, "res_type:%d,arg_name=%s", &iFieldType, field);
            pFunction->resList.push_back({(FieldType)iFieldType, field});
        }
    }
    return 0;
}

stFunction const* CRpcMeta::FindFuncById(int iId) const
{
    return &m_FuncTable[iId];
}