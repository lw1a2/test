#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_stream.h>
 
 
static char *ngx_stream_hello(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf);
static void *ngx_stream_hello_create_srv_conf(ngx_conf_t *cf);

typedef struct {
    ngx_str_t                 hello;
} ngx_stream_hello_srv_conf_t;
 
static ngx_command_t ngx_stream_hello_commands[] = {
    { ngx_string("hello"),
      NGX_STREAM_SRV_CONF|NGX_CONF_TAKE1,
      ngx_stream_hello,
      NGX_STREAM_SRV_CONF_OFFSET,
      0,
      NULL },
 
    ngx_null_command
};
 
 
static ngx_stream_module_t ngx_stream_hello_module_ctx = {
    NULL,
    NULL,
 
    NULL,
    ngx_stream_hello_create_srv_conf,
 
    NULL
};
 
 
ngx_module_t ngx_stream_hello_module = {
    NGX_MODULE_V1,
    &ngx_stream_hello_module_ctx,       /* module context */
    ngx_stream_hello_commands,          /* module directives */
    NGX_STREAM_MODULE,             /* module type */
    NULL,                          /* init master */
    NULL,                          /* init module */
    NULL,                          /* init process */
    NULL,                          /* init thread */
    NULL,                          /* exit thread */
    NULL,                          /* exit process */
    NULL,                          /* exit master */
    NGX_MODULE_V1_PADDING
};
 
 
static void
ngx_stream_hello_handler(ngx_stream_session_t *s)
{
    ngx_stream_hello_srv_conf_t *hscf;

    hscf = ngx_stream_get_module_srv_conf(s, ngx_stream_hello_module);

    s->connection->send(s->connection, hscf->hello.data, hscf->hello.len);
    ngx_stream_close_connection(s->connection);
}
 
 
static char *
ngx_stream_hello(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_stream_hello_srv_conf_t *hscf;
	ngx_str_t                   *value;
    ngx_stream_core_srv_conf_t  *cscf;

    cscf = ngx_stream_conf_get_module_srv_conf(cf, ngx_stream_core_module);
    cscf->handler = ngx_stream_hello_handler;

    hscf = ngx_stream_conf_get_module_srv_conf(cf, ngx_stream_hello_module);

    value = cf->args->elts;	
    hscf->hello = value[1];

    return NGX_CONF_OK;
}

static void *
ngx_stream_hello_create_srv_conf(ngx_conf_t *cf)
{
    ngx_stream_hello_srv_conf_t  *hscf;

    hscf = ngx_pcalloc(cf->pool, sizeof(ngx_stream_hello_srv_conf_t));
    if (hscf == NULL) {
        return NULL;
    }

    return hscf;
}

