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

#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include "nua_matrix.h"
#include "nua_vector.h"
#include "nua_complex.h"
#include "nua_math.h"

extern "C" {
LUALIB_API int luaopen_libnua(lua_State* L){
	matrix_init(L);
	vector_init(L);
	complex_init(L);
	math_init(L);
	return 1;
}
}
