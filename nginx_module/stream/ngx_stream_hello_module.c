#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_stream.h>
 
 
static char *ngx_stream_hello(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf);
 
static ngx_command_t ngx_stream_hello_commands[] = {
    { ngx_string("hello"),
      NGX_STREAM_SRV_CONF|NGX_CONF_TAKE1,
      ngx_stream_hello,
      NGX_STREAM_SRV_CONF_OFFSET,
      0,
      NULL },
 
    ngx_null_command
};
 
 
static ngx_str_t ngx_hello_string;
 
 
static ngx_stream_module_t ngx_stream_hello_module_ctx = {
    NULL,
    NULL,
 
    NULL,
    NULL,
 
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
 
 
static ngx_int_t
ngx_stream_hello_handler(ngx_stream_session_t *s)
{
    ngx_int_t    rc;
    ngx_buf_t   *b;
    ngx_chain_t  out;
 
    return NGX_OK;
}
 
 
static char *
ngx_stream_hello(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_stream_core_srv_conf_t  *cscf;
	ngx_str_t                *value;

    cscf = ngx_stream_conf_get_module_srv_conf(cf, ngx_stream_core_module);
    cscf->handler = ngx_stream_hello_handler;

    value = cf->args->elts;	
    ngx_hello_string = value[1];

    return NGX_CONF_OK;
}
