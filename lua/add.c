//add.c

#include        <stdio.h>
#include        "lua.h"
#include        "lualib.h"
#include        "lauxlib.h"

typedef struct ss
{
    char *name;
    int value;
} ss_t;

/*the lua interpreter*/
lua_State* L;
int
luaadd(int x, int y)
{
    int sum;
/*the function name*/
    lua_getglobal(L, "add");
/*the first argument*/
    lua_pushnumber(L, x);
/*the second argument*/
    lua_pushnumber(L, y);
/*call the function with 2 arguments, return 1 result.*/
    lua_call(L, 2, 1);
/*get the result.*/
    sum = (int)lua_tonumber(L, -1);
/*cleanup the return*/
    lua_pop(L, 1);
    return sum;
}

int
luaadd2(ss_t x, ss_t y)
{
    int sum;
/*the function name*/
    lua_getglobal(L, "add2");
    lua_newtable(L);
    lua_pushinteger(L, x.value);
    lua_setfield(L, -2, "value");
    lua_newtable(L);
    lua_pushinteger(L, y.value);
    lua_setfield(L, -2, "value");
/*call the function with 2 arguments, return 1 result.*/
    lua_call(L, 2, 1);
/*get the result.*/
    sum = (int)lua_tonumber(L, -1);
/*cleanup the return*/
    lua_pop(L, 1);
    return sum;
}

int
main(int argc, char *argv[])
{
    int sum;
/*initialize Lua*/
    L = luaL_newstate();
/*load Lua base libraries*/
    luaL_openlibs(L);
/*load the script*/
    luaL_dofile(L, "add.lua");
/*call the add function*/
    sum = luaadd(10, 15);
/*print the result*/
    printf("The sum is %d \n", sum);

    ss_t x = {.value = 20};
    ss_t y = {.value = 15};
    sum = luaadd2(x, y);
    printf("The sum is %d \n", sum);
/*cleanup Lua*/
    lua_close(L);
    return 0;
}
