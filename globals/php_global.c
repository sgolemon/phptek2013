#include "php_global.h"

ZEND_DECLARE_MODULE_GLOBALS(global);

static PHP_RINIT_FUNCTION(global) {
  GLOBAL_G(counter) = 0;
  GLOBAL_G(name) = NULL;

  return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(global) {
  if (GLOBAL_G(name)) {
    efree(GLOBAL_G(name));
    GLOBAL_G(name) = NULL;
  }

  return SUCCESS;
}

static PHP_FUNCTION(global_inc) {
  GLOBAL_G(counter)++;
}

static PHP_FUNCTION(global_get) {
  RETURN_LONG(GLOBAL_G(counter));
}

ZEND_BEGIN_ARG_INFO(global_name_arginfo, 0)
  ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()
static PHP_FUNCTION(global_name) {
  char *name = NULL;
  int name_len = 0;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s!", &name, &name_len) == FAILURE) {
    return;
  }

  if (GLOBAL_G(name)) {
    if (name) {
      /* GLOBAL_G(name) is about to be overwritten,
       * so we can give its current value away
       */
      RETVAL_STRINGL(GLOBAL_G(name), GLOBAL_G(name_len), 0);
    } else {
      /* Read-only operation, so we need to make a new copy */
      RETVAL_STRINGL(GLOBAL_G(name), GLOBAL_G(name_len), 1);
    }
  }

  if (name) {
    GLOBAL_G(name) = estrndup(name, name_len);
    GLOBAL_G(name_len) = name_len;
  }
}

static zend_function_entry global_functions[] = {
  PHP_FE(global_inc, NULL)
  PHP_FE(global_get, NULL)
  PHP_FE(global_name, NULL)
  { NULL, NULL, NULL }
};

zend_module_entry global_module_entry = {
  STANDARD_MODULE_HEADER,
  "global", /* extname */
  global_functions,
  NULL,    /* MINIT */
  NULL,    /* MSHUTDOWN */
  PHP_RINIT(global),
  PHP_RSHUTDOWN(global),
  NULL,    /* MINFO */
  NO_VERSION_YET,
  PHP_MODULE_GLOBALS(global),
  NULL,    /* GINIT */
  NULL,    /* GSHUTDOWN */
  NULL,    /* RPOSTSHUTDOWN */
  STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_GLOBAL
ZEND_GET_MODULE(global)
#endif

