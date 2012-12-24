#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include "nua_matrix.h"

extern "C" {
LUALIB_API int luaopen_libnua(lua_State* L){
	createmeta(L);
	luaL_register(L, "algebra", algebralib);
	return 1;
}
}
