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

char file_name[128] = "/tmp/http_header_fitler.lua";

#define LUA_CONTENT "function http_header_fitler(req)\n" \
                    "\tif %s then\n" \
                    "\t\treturn 1\n" \
                    "\telse\n" \
                    "\t\treturn 0\n" \
                    "\tend\n" \
                    "end\n"

/*
  convert operator to function, such as:
  a contains b --> string.match(a, b)
  a not-contains b --> not string.match(a, b)
*/
int convert_op2func(char **p_converted, char **p_filter, int max_len, 
    char *op, char *func_pref, size_t *i, size_t *j, int *double_quot_begin)
{
    char *converted = *p_converted;
    char *filter = *p_filter;

    // find word on left of op
    size_t word_len = 0;
    int k = strlen(converted) - 2;   // -2 stand for skip blank which is on left of op
    --(*j);
    for (; k >= 0; k--) {
        if (converted[k] == ' ')
            break;
        else {
            converted[k] = '\0';
            word_len++;
            --(*j);
        }
    }
    if (k < 0)
        k = 0;
    strcpy(converted + strlen(converted), func_pref);
    if (*j + strlen(func_pref) >= max_len)
        return 1;
    *j += strlen(func_pref);
    while (k < word_len) {
        converted[(*j)++] = filter[k++];
    }
    if (*j + 1 >= max_len)
        return 1;
    converted[(*j)++] = ',';
    if (*j + 1 >= max_len)
        return 1;
    converted[(*j)++] = ' ';

    // word on right of op
    *i += strlen(op) + 1;
    while (*i < strlen(filter)) {
        if (filter[*i] == '"') {
            if (*double_quot_begin) {
                *double_quot_begin = 0;
                if (*j + 1 >= max_len)
                    return 1;
                converted[(*j)++] = filter[(*i)++];
                break;
            }
            else
                *double_quot_begin = 1;
        }

        if (filter[*i] == ' ' && !*double_quot_begin)
            break;
        if (*j + 1 >= max_len)
            return 1;
        converted[(*j)++] = filter[(*i)++];
    }

    if (*j + 1 >= max_len)
        return 1;
    converted[(*j)++] = ')';

    return 0;
}

int convert_filter(char *converted, char *filter, int max_len)
{
    // printf("filter: %s\n", filter);

    size_t i, j;
    int double_quot_begin = 0;
    for (i = 0, j = 0; i < strlen(filter);) {
        if (filter[i] == '"') {
            if (double_quot_begin)
                double_quot_begin = 0;
            else
                double_quot_begin = 1;
        }

        // != --> ~=
        if (!double_quot_begin
            && filter[i] == '!' 
            && i + 1 < strlen(filter) && filter[i + 1] == '=') {
            if (j + 1 >= max_len)
                return 1;
            converted[j++] = '~';
            ++i;
            continue;
        }

        // a contains b --> string.match(a, b)
        if (!double_quot_begin
            && filter[i] == 'c'
            && i + strlen("contains") < strlen(filter)
            && filter[i + 1] == 'o'
            && filter[i + 2] == 'n'
            && filter[i + 3] == 't'
            && filter[i + 4] == 'a'
            && filter[i + 5] == 'i'
            && filter[i + 6] == 'n'
            && filter[i + 7] == 's') {

            if (convert_op2func(&converted, &filter, max_len, 
                "contains", "string.match(", &i, &j, &double_quot_begin))
                return 1;
            
            continue;
        }

        // a not-contains b --> not string.match(a, b)
        if (!double_quot_begin
            && filter[i] == 'n'
            && i + strlen("not-contains") < strlen(filter)
            && filter[i + 1] == 'o'
            && filter[i + 2] == 't'
            && filter[i + 3] == '-'
            && filter[i + 4] == 'c'
            && filter[i + 5] == 'o'
            && filter[i + 6] == 'n'
            && filter[i + 7] == 't'
            && filter[i + 8] == 'a'
            && filter[i + 9] == 'i'
            && filter[i + 10] == 'n'
            && filter[i + 11] == 's') {

            if (convert_op2func(&converted, &filter, max_len, 
                "not-contains", "not string.match(", &i, &j, &double_quot_begin))
                return 1;
            
            continue;
        }

        // normal character
        if (j + 1 >= max_len)
            return 1;
        converted[j++] = filter[i++];
    }

    // printf("converted: %s\n", converted);
    return 0;
}

int gen_lua_file(char *filter)
{
    char *converted = (char*)calloc(2 * strlen(filter), 1);
    if (convert_filter(converted, filter, 2 * strlen(filter))) {
        printf("failed to convert filter\n");
        return 1;
    }

    FILE *fp = fopen(file_name, "w");
    if(fp == NULL) {
        return;
    }
    char content[8192];
    bzero(content, sizeof(content));

    sprintf(content, LUA_CONTENT, converted);

    fputs(content, fp);
    fflush(fp);
    fclose(fp);
    free(converted);
    return 0;
}

void test_convert_filter()
{
    char filter[4096];
    char converted[8192];

    bzero(filter, sizeof(filter));
    bzero(converted, sizeof(converted));
    strcpy(filter, "req.user_agent == \"Wget/1.15 (linux-gnu)\" and req.host == \"1.1.1.2\"");
    convert_filter(converted, filter, sizeof(converted));
    assert(!strcmp(converted, filter));

    bzero(filter, sizeof(filter));
    bzero(converted, sizeof(converted));
    strcpy(filter, "req.user_agent == \"Wget/1.15 (linux-gnu)\" and req.host != \"1.1.1.2\"");
    convert_filter(converted, filter, sizeof(converted));
    assert(!strcmp(converted, "req.user_agent == \"Wget/1.15 (linux-gnu)\" and req.host ~= \"1.1.1.2\""));

    bzero(filter, sizeof(filter));
    bzero(converted, sizeof(converted));
    strcpy(filter, "req.user_agent == \"!=\"");
    convert_filter(converted, filter, sizeof(converted));
    assert(!strcmp(converted, "req.user_agent == \"!=\""));

    bzero(filter, sizeof(filter));
    bzero(converted, sizeof(converted));
    strcpy(filter, "req.user_agent contains \"Wget/1.15 (linux-gnu)\"");
    convert_filter(converted, filter, sizeof(converted));
    assert(!strcmp(converted, "string.match(req.user_agent, \"Wget/1.15 (linux-gnu)\")"));

    bzero(filter, sizeof(filter));
    bzero(converted, sizeof(converted));
    strcpy(filter, "req.user_agent contains \"abc\"");
    convert_filter(converted, filter, sizeof(converted));
    assert(!strcmp(converted, "string.match(req.user_agent, \"abc\")"));

    bzero(filter, sizeof(filter));
    bzero(converted, sizeof(converted));
    strcpy(filter, "req.user_agent contains abc");
    convert_filter(converted, filter, sizeof(converted));
    assert(!strcmp(converted, "string.match(req.user_agent, abc)"));

    bzero(filter, sizeof(filter));
    bzero(converted, sizeof(converted));
    strcpy(filter, "req.user_agent contains \"contains\"");
    convert_filter(converted, filter, sizeof(converted));
    assert(!strcmp(converted, "string.match(req.user_agent, \"contains\")"));

    bzero(filter, sizeof(filter));
    bzero(converted, sizeof(converted));
    strcpy(filter, "req.user_agent not-contains \"Wget/1.15 (linux-gnu)\"");
    convert_filter(converted, filter, sizeof(converted));
    assert(!strcmp(converted, "not string.match(req.user_agent, \"Wget/1.15 (linux-gnu)\")"));

    bzero(filter, sizeof(filter));
    bzero(converted, sizeof(converted));
    strcpy(filter, "req.user_agent not-contains \"abc\"");
    convert_filter(converted, filter, sizeof(converted));
    assert(!strcmp(converted, "not string.match(req.user_agent, \"abc\")"));

    bzero(filter, sizeof(filter));
    bzero(converted, sizeof(converted));
    strcpy(filter, "req.user_agent not-contains abc");
    convert_filter(converted, filter, sizeof(converted));
    assert(!strcmp(converted, "not string.match(req.user_agent, abc)"));

    bzero(filter, sizeof(filter));
    bzero(converted, sizeof(converted));
    strcpy(filter, "req.user_agent not-contains \"not-contains\"");
    convert_filter(converted, filter, sizeof(converted));
    assert(!strcmp(converted, "not string.match(req.user_agent, \"not-contains\")"));
}

void test()
{
    L = luaL_newstate();
    luaL_openlibs(L);

    char *filter = "req.user_agent == \"Wget/1.15 (linux-gnu)\" and req.host == \"1.1.1.2\"";
    gen_lua_file(filter);
    luaL_dofile(L, file_name);

    req_t req;
    bzero(&req, sizeof(req));
    req.req_len = 1000;
    strcpy(req.host, "1.1.1.2");
    strcpy(req.user_agent, "Wget/1.15 (linux-gnu)");
    http_header_fitler(&req);

    lua_close(L);
}

void test2()
{
    L = luaL_newstate();
    luaL_openlibs(L);

    char *filter = "req.user_agent contains \"Wget\"";
    gen_lua_file(filter);
    luaL_dofile(L, file_name);

    req_t req;
    bzero(&req, sizeof(req));
    req.req_len = 1000;
    strcpy(req.host, "1.1.1.2");
    strcpy(req.user_agent, "Wget/1.15 (linux-gnu)");
    http_header_fitler(&req);

    lua_close(L);
}

void test3()
{
    L = luaL_newstate();
    luaL_openlibs(L);

    char *filter = "req.user_agent contains \"Wget\"";
    gen_lua_file(filter);
    luaL_dofile(L, file_name);

    req_t req;
    bzero(&req, sizeof(req));
    req.req_len = 1000;
    strcpy(req.host, "1.1.1.2");
    strcpy(req.user_agent, "curl");
    http_header_fitler(&req);

    lua_close(L);
}

void test4()
{
    L = luaL_newstate();
    luaL_openlibs(L);

    char *filter = "req.user_agent contains \"Wget\" and req.host == \"1.1.1.2\"";
    gen_lua_file(filter);
    luaL_dofile(L, file_name);

    req_t req;
    bzero(&req, sizeof(req));
    req.req_len = 1000;
    strcpy(req.host, "1.1.1.2");
    strcpy(req.user_agent, "Wget/1.15 (linux-gnu)");
    http_header_fitler(&req);

    lua_close(L);
}

void test_req_len()
{
    L = luaL_newstate();
    luaL_openlibs(L);

    char *filter = "req.req_len <= 1000";
    gen_lua_file(filter);
    luaL_dofile(L, file_name);

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
    test2();
    test3();
    test4();
    test_req_len();
    return 0;
}
