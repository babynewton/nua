#include "lua5.1/lua.h"
#include "lua5.1/lauxlib.h"

static int matrix_set(lua_State* L){
	return 0;
}

static int matrix_scalar_product(lua_State* L){
	return 0;
}

static int matrix_new(lua_State* L){
	return 0;
}

static int vector_new_column(lua_State* L){
	return 0;
}

static int vector_new_row(lua_State* L){
	return 0;
}


static const luaL_Reg matrix_lib[] = {
	{"set", matrix_set},
	{"__mul", matrix_scalar_product},
	{NULL, NULL}
};

static const luaL_Reg algebralib[] = {
	{"matrix", matrix_new},
	{"column", vector_new_column},
	{"row", vector_new_row},
	{NULL, NULL}
};

extern "C" {
LUALIB_API int luaopen_nua(lua_State* L){
	luaL_register(L, "algebra", algebralib);
	return 1;
}
}
