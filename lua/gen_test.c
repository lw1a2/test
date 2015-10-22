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
} req_t;

lua_State* L;

void http_header_fitler(req_t *req)
{
    int ret;
    int created_table = 0;
    lua_getglobal(L, "http_header_fitler");
    if (req->host && strlen(req->host)) {
        if (!created_table) {
            lua_newtable(L);
            created_table = 1;
        }
        lua_pushstring(L, req->host);
        lua_setfield(L, -2, "host");
    }
    if (req->url && strlen(req->url)) {
        if (!created_table) {
            lua_newtable(L);
            created_table = 1;
        }
        lua_pushstring(L, req->url);
        lua_setfield(L, -2, "url");
    }
    if (req->user_agent && strlen(req->user_agent)) {
        if (!created_table) {
            lua_newtable(L);
            created_table = 1;
        }
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

char file_name[128] = "/tmp/http_header_fitler.lua";

#define LUA_CONTENT "function http_header_fitler(req)\n" \
                    "\tif %s then\n" \
                    "\t\treturn 1\n" \
                    "\telse\n" \
                    "\t\treturn 0\n" \
                    "\tend\n" \
                    "end\n"

void gen_lua_file(char *filter)
{
    FILE *fp = fopen(file_name, "w");
    if(fp == NULL) {
        return;
    }
    char content[8192];
    bzero(content, sizeof(content));

    sprintf(content, LUA_CONTENT, filter);

    fputs(content, fp);
    fflush(fp);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    int ret;
    L = luaL_newstate();
    luaL_openlibs(L);

    char *filter = "req.user_agent == \"Wget/1.15 (linux-gnu)\" and req.host == \"1.1.1.2\"";
    gen_lua_file(filter);
    luaL_dofile(L, file_name);

    req_t req;
    bzero(&req, sizeof(req));
    strcpy(req.host, "1.1.1.2");
    strcpy(req.user_agent, "Wget/1.15 (linux-gnu)");
    http_header_fitler(&req);

    lua_close(L);
    return 0;
}
