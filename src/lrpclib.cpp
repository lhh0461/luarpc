#include "lua.h"
#include "lauxlib.h"



static const luaL_Reg rpclib[] = {
  {"abs",   math_abs},
  {"acos",  math_acos},
  {"asin",  math_asin},
  {"atan",  math_atan},
  {"ceil",  math_ceil},
  {"cos",   math_cos},
  {"deg",   math_deg},
  {"exp",   math_exp},
  {"tointeger", math_toint},
  {NULL, NULL}
};


/*
** Open math library
*/
LUAMOD_API int luaopen_rpc (lua_State *L) {
  luaL_newlib(L, rpclib);
  return 1;
}

