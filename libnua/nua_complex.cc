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

#include <complex>
#include <string.h>
#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>

#define LUA_NUACOMPLEX "nuaComplex*"

using namespace std;

static int newcomplex(lua_State* L, const double real, const double imag){
	complex<double>** cmplx = (complex<double>**)lua_newuserdata(L, sizeof(complex<double>));
	luaL_getmetatable(L, LUA_NUACOMPLEX);
	lua_setmetatable(L, -2);
	*cmplx = new complex<double>(real, imag);
	if(!*cmplx){
		lua_pushnil(L);
		lua_pushstring(L, "Can't allocate a complex");
		return 2;
	}
	(**cmplx) = complex<double>(real, imag);
	return 1;
}

static int complex_add(lua_State* L){
	complex<double>** lval = (complex<double>**)luaL_checkudata(L, 1, LUA_NUACOMPLEX);
	if(!*lval) {
		lua_pushnil(L);
		lua_pushstring(L, "It is not a complex");
		return 2;
	}
	complex<double>** rval = (complex<double>**)luaL_checkudata(L, 2, LUA_NUACOMPLEX);
	if(*rval) {
		return newcomplex(L, (*lval)->real() + (*rval)->real(), (*lval)->imag() + (*rval)->imag());
	} else if(!strcmp(lua_typename(L, lua_type(L, 2)), "number")){
		double rv = luaL_checknumber(L, 2);
		return newcomplex(L, (*lval)->real() + rv, (*lval)->imag());
	}
	lua_pushnil(L);
	lua_pushstring(L, "It is neither a complex nor a number");
	return 2;
}

static int complex_sub(lua_State* L){
	complex<double>** lval = (complex<double>**)luaL_checkudata(L, 1, LUA_NUACOMPLEX);
	if(!*lval) {
		lua_pushnil(L);
		lua_pushstring(L, "It is not a complex");
		return 2;
	}
	complex<double>** rval = (complex<double>**)luaL_checkudata(L, 2, LUA_NUACOMPLEX);
	if(*rval) {
		return newcomplex(L, (*lval)->real() - (*rval)->real(), (*lval)->imag() - (*rval)->imag());
	} else if(!strcmp(lua_typename(L, lua_type(L, 2)), "number")){
		double rv = luaL_checknumber(L, 2);
		return newcomplex(L, (*lval)->real() - rv, (*lval)->imag());
	}
	lua_pushnil(L);
	lua_pushstring(L, "It is neither a complex nor a number");
	return 2;
}

static int complex_mul(lua_State* L){
	complex<double>** lval = (complex<double>**)luaL_checkudata(L, 1, LUA_NUACOMPLEX);
	if(!*lval) {
		lua_pushnil(L);
		lua_pushstring(L, "It is not a complex");
		return 2;
	}
	complex<double>** rval = (complex<double>**)luaL_checkudata(L, 2, LUA_NUACOMPLEX);
	if(*rval) {
		complex<double> prod = (**lval) * (**rval);
		return newcomplex(L, prod.real(), prod.imag());
	} else if(!strcmp(lua_typename(L, lua_type(L, 2)), "number")){
		double rv = luaL_checknumber(L, 2);
		complex<double> prod = (**lval) * rv;
		return newcomplex(L, prod.real(), prod.imag());
	}
	lua_pushnil(L);
	lua_pushstring(L, "It is neither a complex nor a number");
	return 2;
}

static int complex_div(lua_State* L){
	complex<double>** lval = (complex<double>**)luaL_checkudata(L, 1, LUA_NUACOMPLEX);
	if(!*lval) {
		lua_pushnil(L);
		lua_pushstring(L, "It is not a complex");
		return 2;
	}
	complex<double>** rval = (complex<double>**)luaL_checkudata(L, 2, LUA_NUACOMPLEX);
	if(*rval) {
		complex<double> prod = (**lval) / (**rval);
		return newcomplex(L, prod.real(), prod.imag());
	} else if(!strcmp(lua_typename(L, lua_type(L, 2)), "number")){
		double rv = luaL_checknumber(L, 2);
		complex<double> prod = (**lval) / rv;
		return newcomplex(L, prod.real(), prod.imag());
	}
	lua_pushnil(L);
	lua_pushstring(L, "It is neither a complex nor a number");
	return 2;
}

static int complex_gc(lua_State* L){
	complex<double>** cmplx = (complex<double>**)luaL_checkudata(L, 1, LUA_NUACOMPLEX);
	if(*cmplx) {
		delete *cmplx;
		*cmplx = NULL;
	}
	return 0;
}

static int complex_tostring(lua_State* L){
	complex<double>** cmplx = (complex<double>**)luaL_checkudata(L, 1, LUA_NUACOMPLEX);
	if(!*cmplx) {
		lua_pushnil(L);
		lua_pushstring(L, "It is not a complex");
		return 2;
	}
	lua_pushfstring(L, "%f%s%fj", (*cmplx)->real(), (((*cmplx)->imag() >= 0) ? "+" : ""), (*cmplx)->imag());
	return 1;
}

static int complex_new_polar(lua_State* L){
	const double mag = luaL_checknumber(L, 1);
	const double phase = luaL_checknumber(L, 2);
	return newcomplex(L, mag * cos(phase), mag * sin(phase));
}

static int complex_new_cartesian(lua_State* L){
	const double real = luaL_checknumber(L, 1);
	const double imag = luaL_checknumber(L, 2);
	return newcomplex(L, real, imag);
}

static int complex_mag(lua_State* L){
	complex<double>** cmplx = (complex<double>**)luaL_checkudata(L, 1, LUA_NUACOMPLEX);
	if(!*cmplx) {
		lua_pushnil(L);
		lua_pushstring(L, "It is not a complex");
		return 2;
	}
	lua_pushnumber(L, abs(**cmplx));
	return 1;
}

static int complex_phase(lua_State* L){
	complex<double>** cmplx = (complex<double>**)luaL_checkudata(L, 1, LUA_NUACOMPLEX);
	if(!*cmplx) {
		lua_pushnil(L);
		lua_pushstring(L, "It is not a complex");
		return 2;
	}
	lua_pushnumber(L, arg(**cmplx));
	return 1;
}

static int complex_real(lua_State* L){
	complex<double>** cmplx = (complex<double>**)luaL_checkudata(L, 1, LUA_NUACOMPLEX);
	if(!*cmplx) {
		lua_pushnil(L);
		lua_pushstring(L, "It is not a complex");
		return 2;
	}
	lua_pushnumber(L, (*cmplx)->real());
	return 1;
}

static int complex_imag(lua_State* L){
	complex<double>** cmplx = (complex<double>**)luaL_checkudata(L, 1, LUA_NUACOMPLEX);
	if(!*cmplx) {
		lua_pushnil(L);
		lua_pushstring(L, "It is not a complex");
		return 2;
	}
	lua_pushnumber(L, (*cmplx)->imag());
	return 1;
}

static int complex_conj(lua_State* L){
	complex<double>** cmplx = (complex<double>**)luaL_checkudata(L, 1, LUA_NUACOMPLEX);
	if(!*cmplx) {
		lua_pushnil(L);
		lua_pushstring(L, "It is not a complex");
		return 2;
	}
	return newcomplex(L, (*cmplx)->real(), -(*cmplx)->imag());
}

static const luaL_Reg complex_lib[] = {
	{"__add", complex_add},
	{"__sub", complex_sub},
	{"__mul", complex_mul},
	{"__div", complex_div},
	{"__gc", complex_gc},
	{"__tostring", complex_tostring},
	{NULL, NULL}
};

static const luaL_Reg complex_api[] = {
	{"polar", complex_new_polar},
	{"cartesian", complex_new_cartesian},
	{"magnitude", complex_mag},
	{"phase", complex_phase},
	{"real", complex_real},
	{"image", complex_imag},
	{"conjugate", complex_conj},
	{NULL, NULL}
};

void complex_init(lua_State* L){
	luaL_newmetatable(L, LUA_NUACOMPLEX);
	luaL_register(L, NULL, complex_lib);
	luaL_register(L, "complex", complex_api);
}
