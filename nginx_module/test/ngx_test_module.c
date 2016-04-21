#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_stream.h>
 

static char *ngx_test(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf);
 
static ngx_command_t ngx_test_commands[] = {
    { ngx_string("test"),
      NGX_MAIN_CONF|NGX_CONF_BLOCK|NGX_CONF_NOARGS,
      ngx_test,
      0,
      0,
      NULL },
 
    ngx_null_command
};

static ngx_core_module_t  ngx_test_module_ctx = {
    ngx_string("test"),
    NULL,
    NULL
};

ngx_module_t ngx_test_module = {
    NGX_MODULE_V1,
    &ngx_test_module_ctx,
    ngx_test_commands,             /* module directives */
    NGX_CORE_MODULE,               /* module type */
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
ngx_test_handler(ngx_stream_session_t *s)
{
    return NGX_OK;
}
 
 
static char *
ngx_test(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
	ngx_str_t                *value;

    value = cf->args->elts;	

    return NGX_CONF_OK;
}
