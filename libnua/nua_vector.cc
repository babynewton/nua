/*
opyright (c) 2012 Newton Kim (babynewton73@gmail.com)

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
*/

#include <string>
#include <sstream>
#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include "nuac/nuac.h"

#define LUA_NUAVECTOR "nuaVector"

using namespace std;

static int vector_get_at(lua_State* L){
	nuaVector<double>** vector = (nuaVector<double>**)luaL_checkudata(L, 1, LUA_NUAVECTOR);
	if(!*vector) {
		lua_pushnil(L);
		lua_pushstring(L, "It is not a vector");
		return 2;
	}
	const int index = luaL_checkinteger(L, 2);
	if(index < 1 || index > (*vector)->len()){
		lua_pushnil(L);
		lua_pushstring(L, "out of boundary");
		return 2;
	}
	lua_pushnumber(L, (**vector)[index - 1]);
	return 1;
}

static int vector_set_at(lua_State* L){
	nuaVector<double>** vector = (nuaVector<double>**)luaL_checkudata(L, 1, LUA_NUAVECTOR);
	if(!*vector) {
		lua_pushnil(L);
		lua_pushstring(L, "It is not a vector");
		return 2;
	}
	const int index = luaL_checkinteger(L, 2);
	if(index < 1 || index > (*vector)->len()){
		lua_pushnil(L);
		lua_pushstring(L, "out of boundary");
		return 2;
	}
	const double value = luaL_checknumber(L, 3);
	(**vector)[index - 1] = value;
	return 0;
}

static int vector_gc(lua_State* L){
	nuaVector<double>** vector = (nuaVector<double>**)luaL_checkudata(L, 1, LUA_NUAVECTOR);
	if(*vector) {
		delete *vector;
		*vector = NULL;
	}
	return 0;
}

static int vector_tostring(lua_State* L){
	nuaVector<double>** val = (nuaVector<double>**)luaL_checkudata(L, 1, LUA_NUAVECTOR);
	if(!*val) {
		lua_pushnil(L);
		lua_pushstring(L, "It is not a vector");
		return 2;
	}
	string str;
	stringstream ss;
	for(int j = 0 ; j < (*val)->len() ; j++){
		if (j != 0) {
			ss <<  ", ";
		} else {
			ss << "[ ";
		}
		ss << (**val)[j];
		if (j == ((*val)->len() - 1)) ss << " ]" << endl;
	}
	str = ss.str();
	lua_pushstring(L, str.c_str());
	return 1;
}

static const luaL_Reg vector_lib[] = {
	{"__index", vector_get_at},
	{"__newindex", vector_set_at},
	{"__gc", vector_gc},
	{"__tostring", vector_tostring},
	{NULL, NULL}
};

int vector_new(lua_State* L, const double* line, const int len){
	nuaVector<double>** vector = (nuaVector<double>**)lua_newuserdata(L, sizeof(nuaVector<double>));
	luaL_getmetatable(L, LUA_NUAVECTOR);
	lua_setmetatable(L, -2);
	*vector = new nuaVector<double>((double*)line, len);
	if(!*vector){
		lua_pushnil(L);
		lua_pushstring(L, "Can't allocate a vector with given dimension");
		return 2;
	}
	return 1;
}

void vector_init(lua_State* L){
	luaL_newmetatable(L, LUA_NUAVECTOR);
	luaL_register(L, NULL, vector_lib);
}
