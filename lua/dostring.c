#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

typedef struct req
{
    char host[1024];
    char url[1024];
    char user_agent[1024];
    int req_len;
} req_t;

lua_State* L;

void http_header_fitler(req_t *req)
{
    int ret;
    lua_getglobal(L, "http_header_fitler");
    lua_newtable(L);
    lua_pushinteger(L, req->req_len);
    lua_setfield(L, -2, "req_len");
    if (req->host && strlen(req->host)) {
        lua_pushstring(L, req->host);
        lua_setfield(L, -2, "host");
    }
    if (req->url && strlen(req->url)) {
        lua_pushstring(L, req->url);
        lua_setfield(L, -2, "url");
    }
    if (req->user_agent && strlen(req->user_agent)) {
        lua_pushstring(L, req->user_agent);
        lua_setfield(L, -2, "user_agent");
    }

    ret = lua_pcall(L, 1, 1, 0);
    if (ret == 0) {
        int match = (int)lua_tonumber(L, -1);
        if (match) {
            printf("matched\n");
        } else {
            printf("don't match\n");
        }
    } else {
        printf("filter is bad\n");
    }
    lua_pop(L, 1);
}

#define LUA_CONTENT "function http_header_fitler(req)\n" \
                    "\tif %s then\n" \
                    "\t\treturn 1\n" \
                    "\telse\n" \
                    "\t\treturn 0\n" \
                    "\tend\n" \
                    "end\n"

void test()
{
    L = luaL_newstate();
    luaL_openlibs(L);

    char *filter = "req.user_agent == \"Wget/1.15 (linux-gnu)\" and req.host == \"1.1.1.2\"";
    char s[1024];
    bzero(s, sizeof(s));
    sprintf(s, LUA_CONTENT, filter);
    luaL_dostring(L, s);

    req_t req;
    bzero(&req, sizeof(req));
    req.req_len = 1000;
    strcpy(req.host, "1.1.1.2");
    strcpy(req.user_agent, "Wget/1.15 (linux-gnu)");
    http_header_fitler(&req);

    lua_close(L);
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
