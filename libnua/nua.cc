#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include "nua_matrix.h"
#include "nua_vector.h"

extern "C" {
LUALIB_API int luaopen_libnua(lua_State* L){
	matrix_init(L);
	vector_init(L);
	return 1;
}
}
