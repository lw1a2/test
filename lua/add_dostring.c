//add_dostring.c

#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

//the lua interpreter
lua_State* L;

const char* s = "function add(x,y)\n" \
				"return x + y\n" \
				"end";

int luaadd(int x, int y)
{
	int sum;
	//the function name
	lua_getglobal(L, "add");
	//the first argument
	lua_pushnumber(L, x);
	//the second argument
	lua_pushnumber(L, y);
	//call the function with 2 arguments, return 1 result.
	lua_call(L, 2, 1);
	//get the result.
	sum = (int)lua_tonumber(L, -1);
	//cleanup the return
	lua_pop(L, 1);
	return sum;
}

int main(int argc, char *argv[])
{
	int sum;
	//initialize Lua
	L = luaL_newstate();
	//load Lua base libraries
	luaL_openlibs(L);
	//load the script
	luaL_dostring(L, s);
	//call the add function
	sum = luaadd(10, 15);
	//print the result
	printf("The sum is %d \n", sum);
	//cleanup Lua
	lua_close(L);
	return 0;
}
