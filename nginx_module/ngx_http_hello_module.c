/*
 * Copyright (C) Joshua Zhu, http://www.zhuzhaoyuan.com
 */
 
 
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
 
 
static char *ngx_http_hello(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf);
 
static ngx_command_t ngx_http_hello_commands[] = {
    { ngx_string("hello"),
      NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1,
      ngx_http_hello,
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL },
 
    ngx_null_command
};
 
 
static ngx_str_t ngx_hello_string;
 
 
static ngx_http_module_t ngx_http_hello_module_ctx = {
    NULL,                          /* preconfiguration */
    NULL,                          /* postconfiguration */
 
    NULL,                          /* create main configuration */
    NULL,                          /* init main configuration */
 
    NULL,                          /* create server configuration */
    NULL,                          /* merge server configuration */
 
    NULL,                          /* create location configuration */
    NULL                           /* merge location configuration */
};
 
 
ngx_module_t ngx_http_hello_module = {
    NGX_MODULE_V1,
    &ngx_http_hello_module_ctx,    /* module context */
    ngx_http_hello_commands,       /* module directives */
    NGX_HTTP_MODULE,               /* module type */
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
ngx_http_hello_handler(ngx_http_request_t *r)
{
    ngx_int_t    rc;
    ngx_buf_t   *b;
    ngx_chain_t  out;
 
    /* we response to 'GET' and 'HEAD' requests only */
    if (!(r->method & (NGX_HTTP_GET|NGX_HTTP_HEAD))) {
        return NGX_HTTP_NOT_ALLOWED;
    }
 
    /* discard request body, since we don't need it here */
    rc = ngx_http_discard_request_body(r);
 
    if (rc != NGX_OK) {
        return rc;
    }
 
    /* set the 'Content-type' header */
    r->headers_out.content_type_len = sizeof("text/html") - 1;
    r->headers_out.content_type.len = sizeof("text/html") - 1;
    r->headers_out.content_type.data = (u_char *) "text/html";
 
    /* send the header only, if the request type is http 'HEAD' */
    if (r->method == NGX_HTTP_HEAD) {
        r->headers_out.status = NGX_HTTP_OK;
        r->headers_out.content_length_n = ngx_hello_string.len;
 
        return ngx_http_send_header(r);
    }
 
    /* allocate a buffer for your response body */
    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    if (b == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
 
    /* attach this buffer to the buffer chain */
    out.buf = b;
    out.next = NULL;
 
    /* adjust the pointers of the buffer */
    b->pos = ngx_hello_string.data;
    b->last = ngx_hello_string.data + ngx_hello_string.len;
    b->memory = 1;    /* this buffer is in memory */
    b->last_buf = 1;  /* this is the last buffer in the buffer chain */
 
    /* set the status line */
    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = ngx_hello_string.len;
 
    /* send the headers of your response */
    rc = ngx_http_send_header(r);
 
    if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {
        return rc;
    }
 
    /* send the buffer chain of your response */
    return ngx_http_output_filter(r, &out);
}
 
 
static char *
ngx_http_hello(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t *clcf;
	ngx_str_t                *value;
 
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_hello_handler; /* handler to process the 'hello' directive */

    value = cf->args->elts;	
    ngx_hello_string = value[1];

    a();

    return NGX_CONF_OK;
}
