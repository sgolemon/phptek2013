#include "php_fcall.h"

/* {{{ proto void fcall_callback(callback $cb) */
ZEND_BEGIN_ARG_INFO(fcall_callback_arginfo, 0)
  ZEND_ARG_INFO(0, cb)
ZEND_END_ARG_INFO()
static PHP_FUNCTION(fcall_callback) {
  zend_fcall_info finfo;
  zend_fcall_info_cache fcache;
  zval **params[1];
  zval *arg, *retval = NULL;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "f", &finfo, &fcache) == FAILURE) {
    return;
  }

  MAKE_STD_ZVAL(arg);
  ZVAL_STRING(arg, "Hello World", 1);
  params[0] = &arg;

  finfo.param_count = 1;
  finfo.params = params;
  finfo.retval_ptr_ptr = &retval;
  if (zend_call_function(&finfo, &fcache TSRMLS_CC) == FAILURE) {
    php_error_docref(NULL TSRMLS_CC, E_WARNING, "Failed calling callback");
  }

  if (retval) {
    zval_ptr_dtor(&retval);
  }
  zval_ptr_dtor(&arg);
}
/* }}} */

/* {{{ proto void fcall_byname() */
static PHP_FUNCTION(fcall_byname) {
  zend_fcall_info finfo;
  zend_fcall_info_cache fcache;
  zval fname, *arg, **params[1], *retval = NULL;
  char *name = NULL;

  ZVAL_STRING(&fname, "strtolower", 0);
  if (zend_fcall_info_init(&fname, IS_CALLABLE_STRICT, &finfo, &fcache, &name, NULL TSRMLS_CC) == FAILURE) {
    php_error_docref(NULL TSRMLS_CC, E_WARNING, "WTF??? Can't find the strtolower() function!");
    return;
  }

  MAKE_STD_ZVAL(arg);
  ZVAL_STRING(arg, "Hello World", 1);
  params[0] = &arg;

  finfo.param_count = 1;
  finfo.params = params;
  finfo.retval_ptr_ptr = &retval;
  if (zend_call_function(&finfo, &fcache TSRMLS_CC) == FAILURE) {
    php_error_docref(NULL TSRMLS_CC, E_WARNING, "Failed calling %s()", name);
  }
  efree(name);
  if (retval) {
    RETVAL_ZVAL(retval, 1, 1);
  }
  zval_ptr_dtor(&arg);
}
/* }}} */

static zend_function_entry fcall_functions[] = {
  PHP_FE(fcall_callback, fcall_callback_arginfo)
  PHP_FE(fcall_byname, NULL)
  { NULL, NULL, NULL }
};

zend_module_entry fcall_module_entry = {
  STANDARD_MODULE_HEADER,
  "fcall", /* extname */
  fcall_functions,
  NULL,    /* MINIT */
  NULL,    /* MSHUTDOWN */
  NULL,    /* RINIT */
  NULL,    /* RSHUTDOWN */
  NULL,    /* MINFO */
  NO_VERSION_YET,
  STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_FCALL
ZEND_GET_MODULE(fcall)
#endif

