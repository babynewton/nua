#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include "nua/nua.h"

#define LUA_NUAMATRIX "nuaMatrix*"

static int newmatrix(lua_State* L,
		const int rows,
		const int cols,
		nuaMatrix<double>* val = NULL){
	nuaMatrix<double>** matrix = (nuaMatrix<double>**)lua_newuserdata(L, sizeof(nuaMatrix<double>));
	luaL_getmetatable(L, LUA_NUAMATRIX);
	lua_setmetatable(L, -2);
	*matrix = (val) ? val : nuaMatrixFactory<double>::create(rows, cols);
	if(!*matrix){
		lua_pushnil(L);
		lua_pushstring(L, "Can't allocate a matrix with given dimension o");
		return 2;
	}
	return 1;
}

static int matrix_set(lua_State* L){
	return 0;
}

static int matrix_scalar_product(lua_State* L){
	nuaMatrix<double>** lval = (nuaMatrix<double>**)luaL_checkudata(L, 1, LUA_NUAMATRIX);
	if(!*lval) {
		lua_pushnil(L);
		lua_pushstring(L, "l-value is not a matrix");
		return 2;
	}
	nuaMatrix<double>** rval = (nuaMatrix<double>**)luaL_checkudata(L, 1, LUA_NUAMATRIX);
	if(!*rval) {
		lua_pushnil(L);
		lua_pushstring(L, "r-value is not a matrix");
		return 2;
	}
	nuaMatrix<double>* ret = nuaMatrixFactory<double>::multiplicate(*lval, *rval);
	return newmatrix(L, ret->rows(), ret->cols(), ret);
}

static int matrix_gc(lua_State* L){
	nuaMatrix<double>** matrix = (nuaMatrix<double>**)luaL_checkudata(L, 1, LUA_NUAMATRIX);
	if(*matrix) delete *matrix;
	return 0;
}

static int matrix_tostring(lua_State* L){
	lua_pushstring(L, "matrix");
	return 1;
}

static int matrix_get_at(lua_State* L){
	return 0;
}

static int matrix_set_at(lua_State* L){
	return 0;
}

static int matrix_new(lua_State* L){
	const int rows = luaL_checkint(L, 1);
	const int cols = luaL_checkint(L, 2);
	return newmatrix(L, rows, cols);
}

static int vector_new_column(lua_State* L){
	const int rows = luaL_checkint(L, 1);
	const int cols = 1;
	return newmatrix(L, rows, cols);
}

static int vector_new_row(lua_State* L){
	const int rows = 1;
	const int cols = luaL_checkint(L, 1);
	return newmatrix(L, rows, cols);
}

static const luaL_Reg matrix_lib[] = {
	{"set", matrix_set},
	{"__mul", matrix_scalar_product},
	{"__gc", matrix_gc},
	{"__tostring", matrix_tostring},
//	{"__index", matrix_get_at},
//	{"__newindex", matrix_set_at},
	{NULL, NULL}
};

static const luaL_Reg algebralib[] = {
	{"matrix", matrix_new},
	{"column", vector_new_column},
	{"row", vector_new_row},
	{NULL, NULL}
};

static void createmeta(lua_State* L){
	luaL_newmetatable(L, LUA_NUAMATRIX);
	lua_pushvalue(L, -1);
	lua_setfield(L, -1, "__index");
	luaL_register(L, NULL, matrix_lib);
}

void matrix_init(lua_State* L){
	createmeta(L);
	luaL_register(L, "algebra", algebralib);
}
