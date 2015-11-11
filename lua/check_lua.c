#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

#include <arpa/inet.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

typedef struct client {
    char ip[INET_ADDRSTRLEN];
} client_t;

typedef struct http_req
{
    char *host;
    char *url;
    char *user_agent;
    char *accept;
    char *accept_encoding;
    char *accept_language;
    char *connection;
    char *method;
    char *version;
    char *cache_control;
    char *content_encoding;
    char *content_language;
    char *content_length;
    char *content_location;
    char *content_md5;
    char *content_range;
    char *content_type;
    size_t hdr_len;
} http_req_t;

static char *operator[] = {"==", "!=", ">", ">=", "<", "<=", "contains", "not-contains", };

/*
  convert operator to function, such as:
  a contains b --> string.match(a, b)
  a not-contains b --> not string.match(a, b)
  return: 0--OK
          1--ERROR
*/
int convert_op2func(char **p_converted, char **p_filter, size_t max_len, 
    const char *op, const char *func_pref, size_t *i, size_t *j, int *double_quot_begin)
{
    char *converted = *p_converted;
    char *filter = *p_filter;

    // find word on left of op
    size_t word_len = 0;
    int start_left_word = 0;
    int k = strlen(converted) - 1;
    --(*j);
    for (; k >= 0; --k) {
        if (start_left_word 
            && (converted[k] == ' ' || converted[k] == '(' || converted[k] == ')')) {
            break;
        } else {
            if (converted[k] != ' ')
                start_left_word = 1;
            converted[k] = '\0';
            word_len++;
            --(*j);
        }
    }
    strcpy(converted + strlen(converted), func_pref);
    if (*j + strlen(func_pref) + 1 >= max_len)
        return 1;
    *j += strlen(func_pref) + 1;
    if (*j + word_len >= max_len)
        return 1;
    size_t m = 0;
    while (m++ < word_len) {
        converted[(*j)++] = filter[*i - word_len - 1 + m];
    }
    if (*j + 1 >= max_len)
        return 1;
    converted[(*j)++] = ',';
    if (*j + 1 >= max_len)
        return 1;
    converted[(*j)++] = ' ';

    // word on right of op
    *i += strlen(op);
    int start_right_word = 0;
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

        if (start_right_word && filter[*i] == ' ' && !*double_quot_begin)
            break;
        if (*j + 1 >= max_len)
            return 1;
        if (filter[*i] != ' ') {
            start_right_word = 1;
        }
        converted[(*j)++] = filter[(*i)++];
    }

    if (*j + 1 >= max_len)
        return 1;
    converted[(*j)++] = ')';

    return 0;
}

/*
  return: 0--OK
          1--ERROR
*/
static int convert_check_filter(char *converted, char *filter, size_t max_len)
{
    size_t i, j;
    int double_quot_begin = 0;
    for (i = 0, j = 0; i < strlen(filter);) {
        if (filter[i] == '"') {
            if (double_quot_begin)
                double_quot_begin = 0;
            else
                double_quot_begin = 1;
        }

        // == --> string.match
        if (!double_quot_begin
            && filter[i] == '=' 
            && i + 1 < strlen(filter) && filter[i + 1] == '=') {
            if (j + 1 >= max_len)
                return 1;

            if (convert_op2func(&converted, &filter, max_len, 
                "==", "string.match(", &i, &j, &double_quot_begin))
                return 1;

            continue;
        }

        // != --> not string.match
        if (!double_quot_begin
            && filter[i] == '!' 
            && i + 1 < strlen(filter) && filter[i + 1] == '=') {
            if (j + 1 >= max_len)
                return 1;

            if (convert_op2func(&converted, &filter, max_len, 
                "!=", "not string.match(", &i, &j, &double_quot_begin))
                return 1;

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

    // convert \n to or
    char *tmp = NULL;
    tmp = (char*)calloc(max_len, 1);
    if (!tmp) {
        return 1;
    }
    j = 0;
    for (i = 0; i < strlen(converted); ++i) {
        if (converted[i] == '\n') {
            strcpy(tmp + strlen(tmp), "(");
            strncpy(tmp + strlen(tmp), converted + j, i - j);
            strcpy(tmp + strlen(tmp), ") or ");
            j = i + 1;
        }
    }
    strcpy(tmp + strlen(tmp), "(");
    strcpy(tmp + strlen(tmp), converted + j);
    strcpy(tmp + strlen(tmp), ")");
    strcpy(converted, tmp);
    free(tmp);

    return 0;
}

/*
return: -1--ERROR
*/
int invoke_lua_script(lua_State* L, client_t *client, http_req_t *req)
{
    lua_getglobal(L, "f");
    if (strlen(client->ip)) {
        lua_newtable(L);
        lua_pushstring(L, client->ip);
        lua_setfield(L, -2, "ip");
    }
    lua_newtable(L);
    lua_pushinteger(L, req->hdr_len);
    lua_setfield(L, -2, "hdr_len");
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
    if (req->accept && strlen(req->accept)) {
        lua_pushstring(L, req->accept);
        lua_setfield(L, -2, "accept");
    }
    if (req->accept_encoding && strlen(req->accept_encoding)) {
        lua_pushstring(L, req->accept_encoding);
        lua_setfield(L, -2, "accept_encoding");
    }
    if (req->accept_language && strlen(req->accept_language)) {
        lua_pushstring(L, req->accept_language);
        lua_setfield(L, -2, "accept_language");
    }
    if (req->connection && strlen(req->connection)) {
        lua_pushstring(L, req->connection);
        lua_setfield(L, -2, "connection");
    }
    if (req->method && strlen(req->method)) {
        lua_pushstring(L, req->method);
        lua_setfield(L, -2, "method");
    }
    if (req->version && strlen(req->version)) {
        lua_pushstring(L, req->version);
        lua_setfield(L, -2, "version");
    }
    if (req->cache_control && strlen(req->cache_control)) {
        lua_pushstring(L, req->cache_control);
        lua_setfield(L, -2, "cache_control");
    }
    if (req->content_encoding && strlen(req->content_encoding)) {
        lua_pushstring(L, req->content_encoding);
        lua_setfield(L, -2, "content_encoding");
    }
    if (req->content_language && strlen(req->content_language)) {
        lua_pushstring(L, req->content_language);
        lua_setfield(L, -2, "content_language");
    }
    if (req->content_length && strlen(req->content_length)) {
        lua_pushinteger(L, atoi(req->content_length));
        lua_setfield(L, -2, "content_length");
    }
    if (req->content_location && strlen(req->content_location)) {
        lua_pushstring(L, req->content_location);
        lua_setfield(L, -2, "content_location");
    }
    if (req->content_md5 && strlen(req->content_md5)) {
        lua_pushstring(L, req->content_md5);
        lua_setfield(L, -2, "content_md5");
    }
    if (req->content_range && strlen(req->content_range)) {
        lua_pushstring(L, req->content_range);
        lua_setfield(L, -2, "content_range");
    }
    if (req->content_type && strlen(req->content_type)) {
        lua_pushstring(L, req->content_type);
        lua_setfield(L, -2, "content_type");
    }

    int ret = lua_pcall(L, 2, 1, 0);
    if (ret == 0) {
        ret = (int)lua_tonumber(L, -1);
    } else {
        ret = -1;
    }
    lua_pop(L, 1);

    return ret;
}

/*
  return: 0--OK
          1--ERROR
*/
static int check_operator(char *filter)
{
    int i = 0;
    for (; i < sizeof(operator) / sizeof(operator[0]); ++i) {
        if (strstr(filter, operator[i])) {
            return 0;
        }
    }

    return 1;
}

/*
  return: 0--OK
          1--ERROR
*/
#define LUA_FUNC "function f(client, http)\n" \
                "\tif %s then\n" \
                "\t\treturn 0\n" \
                "\tend\n" \
                "\treturn 0\n" \
                "end\n"
static int gen_check_lua_script(char *filter, char **content)
{
    int ret = 0;
    char *converted = NULL;

    *content = (char*)calloc(512 + 256, 1);
    if (*content == NULL) {
        ret = 1;
        goto out;
    }

    if (check_operator(filter)) {
        ret = 1;
        goto out;
    }

    // generate file
    converted = (char*)calloc(4 * strlen(filter), 1);
    if (converted == NULL) {
        ret = 1;
        goto out;
    }
    if (convert_check_filter(converted, filter, 4 * strlen(filter))) {
        ret = 1;
        goto out;
    }

    sprintf(*content, LUA_FUNC, converted);

out:
    free(converted);
    return ret;
}

static void init_dummy_req(client_t *client, http_req_t *req)
{
    strcpy(client->ip, " ");
    req->host = (char*)calloc(2, 1);
    strcpy(req->host, " ");
    req->url = (char*)calloc(2, 1);
    strcpy(req->url, " ");
    req->user_agent = (char*)calloc(2, 1);
    strcpy(req->user_agent, " ");
    req->accept = (char*)calloc(2, 1);
    strcpy(req->accept, " ");
    req->accept_encoding = (char*)calloc(2, 1);
    strcpy(req->accept_encoding, " ");
    req->accept_language = (char*)calloc(2, 1);
    strcpy(req->accept_language, " ");
    req->connection = (char*)calloc(2, 1);
    strcpy(req->connection, " ");
    req->method = (char*)calloc(2, 1);
    strcpy(req->method, " ");
    req->version = (char*)calloc(2, 1);
    strcpy(req->version, " ");
    req->cache_control = (char*)calloc(2, 1);
    strcpy(req->cache_control, " ");
    req->content_encoding = (char*)calloc(2, 1);
    strcpy(req->content_encoding, " ");
    req->content_language = (char*)calloc(2, 1);
    strcpy(req->content_language, " ");
    req->content_length = (char*)calloc(2, 1);
    strcpy(req->content_length, " ");
    req->content_location = (char*)calloc(2, 1);
    strcpy(req->content_location, " ");
    req->content_md5 = (char*)calloc(2, 1);
    strcpy(req->content_md5, " ");
    req->content_range = (char*)calloc(2, 1);
    strcpy(req->content_range, " ");
    req->content_type = (char*)calloc(2, 1);
    strcpy(req->content_type, " ");
    req->hdr_len = 0;
}

static void fini_dummy_req(http_req_t *req)
{
    free(req->host);
    free(req->url);
    free(req->user_agent);
    free(req->accept);
    free(req->accept_encoding);
    free(req->accept_language);
    free(req->connection);
    free(req->method);
    free(req->version);
    free(req->cache_control);
    free(req->content_encoding);
    free(req->content_language);
    free(req->content_length);
    free(req->content_location);
    free(req->content_md5);
    free(req->content_range);
    free(req->content_type);
}

/*
  return: 0--OK
          1--ERROR
*/
int check_filter(char *filter)
{
    int ret = 0;
    lua_State* L;
    L = luaL_newstate();
    luaL_openlibs(L);
    client_t client;
    http_req_t req;
    init_dummy_req(&client, &req);

    char *content = NULL;
    if (gen_check_lua_script(filter, &content)) {
        ret = 1;
        goto out;
    }
    printf("%s\n", content);
    (void)luaL_dostring(L, content);
    if (invoke_lua_script(L, &client, &req) == -1) {
        ret = 1;
        goto out;
    }

out:
    free(content);
    fini_dummy_req(&req);
    lua_close(L);
    return ret;
}

int main(void)
{
    assert(0 == check_filter("http.url==\"/\""));
    assert(1 == check_filter("http.aaa==\"/\""));
    assert(0 == check_filter("http.url== \"/\""));
    assert(1 == check_filter("http.aaa== \"/\""));
    assert(0 == check_filter("http.url==  \"/\""));
    assert(1 == check_filter("http.aaa==  \"/\""));
    assert(0 == check_filter("http.url ==\"/\""));
    assert(1 == check_filter("http.aaa ==\"/\""));
    assert(0 == check_filter("http.url == \"/\""));
    assert(1 == check_filter("http.aaa == \"/\""));
    assert(0 == check_filter("http.url ==  \"/\""));
    assert(1 == check_filter("http.aaa ==  \"/\""));
    assert(0 == check_filter("http.url  ==\"/\""));
    assert(1 == check_filter("http.aaa  ==\"/\""));
    assert(0 == check_filter("http.url  == \"/\""));
    assert(1 == check_filter("http.aaa  == \"/\""));
    assert(0 == check_filter("http.url  ==  \"/\""));
    assert(1 == check_filter("http.aaa  ==  \"/\""));
    return 0;
}
