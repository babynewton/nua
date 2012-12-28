#ifndef __NUA_VECTOR_H__
#define __NUA_VECTOR_H__

void vector_init(lua_State* L);
int vector_new(lua_State* L, const double* line, const int len);
#endif //__NUA_VECTOR_H__
