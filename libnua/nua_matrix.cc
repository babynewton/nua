#include <string>
#include <sstream>
#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include "nua/nua.h"

using namespace std;

#define LUA_NUAMATRIX "nuaMatrix*"

static int newmatrix(lua_State* L,
		const int rows,
		const int cols,
		nuaMatrix<double>* val = NULL){
	nuaMatrix<double>** matrix = (nuaMatrix<double>**)lua_newuserdata(L, sizeof(nuaMatrix<double>));
	luaL_getmetatable(L, LUA_NUAMATRIX);
	lua_setmetatable(L, -2);
	*matrix = (val) ? val : new nuaMatrix<double>(rows, cols);
	if(!*matrix){
		lua_pushnil(L);
		lua_pushstring(L, "Can't allocate a matrix with given dimension");
		return 2;
	}
	return 1;
}

static int matrix_dump(lua_State* L){
	nuaMatrix<double>** matrix = (nuaMatrix<double>**)luaL_checkudata(L, 1, LUA_NUAMATRIX);
	const int args = lua_gettop(L);
	if ((args - 1) != ((*matrix)->rows() * (*matrix)->cols())) {
		lua_pushboolean(L, false);
		lua_pushstring(L, "The number of arguments doesn't match the dimension of the matrix");
		return 2;
	}
	int index = 2;
	for(int i = 0 ; i < (*matrix)->rows() ; i++){
		for(int j = 0 ; j < (*matrix)->cols() ; j++){
			(**matrix)[i][j] = luaL_checknumber(L, index++);
		}
	}
	lua_pushboolean(L, true);
	return 1;
}

static int matrix_scalar_product(lua_State* L){
	nuaMatrix<double>** lval = (nuaMatrix<double>**)luaL_checkudata(L, 1, LUA_NUAMATRIX);
	if(!*lval) {
		lua_pushnil(L);
		lua_pushstring(L, "l-value is not a matrix");
		return 2;
	}
	nuaMatrix<double>** rval = (nuaMatrix<double>**)luaL_checkudata(L, 2, LUA_NUAMATRIX);
	if(!*rval) {
		lua_pushnil(L);
		lua_pushstring(L, "r-value is not a matrix");
		return 2;
	}
	nuaMatrix<double>* ret = new nuaMatrix<double>;
	ret->multiply(**lval, **rval);
	if (ret->rows() == 1 && ret->cols() == 1){
		lua_pushnumber(L, *ret[0][0]);
		delete ret;
		return 1;
	}
	return newmatrix(L, ret->rows(), ret->cols(), ret);
}

static int matrix_gc(lua_State* L){
	nuaMatrix<double>** matrix = (nuaMatrix<double>**)luaL_checkudata(L, 1, LUA_NUAMATRIX);
	if(*matrix) delete *matrix;
	return 0;
}

static int matrix_tostring(lua_State* L){
	nuaMatrix<double>** val = (nuaMatrix<double>**)luaL_checkudata(L, 1, LUA_NUAMATRIX);
	if(!*val) {
		lua_pushnil(L);
		lua_pushstring(L, "It is not a matrix");
		return 2;
	}
	if((*val)->cols() == 0 || (*val)->rows() == 0){
		lua_pushstring(L, "empty");
		return 1;
	}
	string str;
	stringstream ss;
//	ss << "dimension" << (*val)->rows() << ":" << (*val)->cols() << endl;
	for(int i = 0 ; i < (*val)->rows() ; i++){
		for(int j = 0 ; j < (*val)->cols() ; j++){
			if (j != 0) {
				ss <<  ", ";
			} else {
				ss << "[ ";
			}
			ss << (**val)[i][j];
			if (j == ((*val)->cols() - 1)) ss << " ]" << endl;
		}
	}
	str = ss.str();
	lua_pushstring(L, str.c_str());
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
	{"dump", matrix_dump},
	{"__mul", matrix_scalar_product},
	{"__gc", matrix_gc},
	{"__tostring", matrix_tostring},
//	{"__index", matrix_get_at},
	{"__newindex", matrix_set_at},
	{NULL, NULL}
};

static const luaL_Reg algebralib[] = {
	{"matrix", matrix_new},
	{"column", vector_new_column},
	{"row", vector_new_row},
	{NULL, NULL}
};

void matrix_init(lua_State* L){
	luaL_newmetatable(L, LUA_NUAMATRIX);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_register(L, NULL, matrix_lib);
	luaL_register(L, "algebra", algebralib);
}
