#include "php_return.h"

/* {{{ proto bool return_bool() */
static PHP_FUNCTION(return_bool) {
  RETURN_BOOL(1);

  /* Equivalent to any of the following:

  RETURN_TRUE;

  RETVAL_BOOL(1);
  return;

  ZVAL_BOOL(return_value, 1);
  return;
  */
}
/* }}} */

/* {{{ proto int return_long() */
static PHP_FUNCTION(return_long) {
  RETURN_LONG(42);

  /* Equivalent to either of the following:

  RETVAL_LONG(42);
  return;

  ZVAL_LONG(return_value, 42);
  return;

  */
}
/* }}} */

/* {{{ proto long return_string() */
static PHP_FUNCTION(return_string) {
  RETURN_STRING("Hello", 1);

  /* Equivalent to any of the following:

  RETURN_STRINGL("Hello", strlen("Hello"), 1);

  char *hello = estrdup("Hello");
  RETURN_STRING(hello, 0);

  RETVAL_STRING("Hello", 1);
  return;

  ZVAL_STRING(return_value, "Hello", 1);
  return;
  */
}
/* }}} */

/* {{{ proto array return_array() */
static PHP_FUNCTION(return_array) {
  zval *sub;

  /* $ret = array(); */
  array_init(return_value);

  /* $ret[] = true; */
  add_next_index_bool(return_value, 1);

  /* $ret[5] = "Alive"; */
  add_index_string(return_value, 5, "Alive", 1);

  /* $ret["life"] = 42; */
  add_assoc_long(return_value, "life", 42);

  /* $sub = array(); */
  MAKE_STD_ZVAL(sub);
  array_init(sub);

  /* $sub["pi"] = 3.1415926535; */
  add_assoc_double(sub, "pi", 3.1415926535);

  /* $ret[] = $sub; */
  add_next_index_zval(return_value, sub);

  /* Implicit return $ret; */
}
/* }}} */

/* {{{ proto object return_object() */
static PHP_FUNCTION(return_object) {
  /* $ret = new stdClass; */
  object_init(return_value);
  /* Or: object_init(return_value, zend_standard_class_def); */

  /* $ret->e = 2.718281828459 */
  zend_update_property_double(NULL, return_value, "e", strlen("e"), 2.718281828459 TSRMLS_CC);

  /* Implicit return $ret; */
}
/* }}} */

static zend_function_entry return_functions[] = {
  PHP_FE(return_bool, NULL)
  PHP_FE(return_long, NULL)
  PHP_FE(return_string, NULL)
  PHP_FE(return_array, NULL)
  PHP_FE(return_object, NULL)
  { NULL, NULL, NULL }
};

zend_module_entry return_module_entry = {
  STANDARD_MODULE_HEADER,
  "return", /* extname */
  return_functions,
  NULL,    /* MINIT */
  NULL,    /* MSHUTDOWN */
  NULL,    /* RINIT */
  NULL,    /* RSHUTDOWN */
  NULL,    /* MINFO */
  NO_VERSION_YET,
  STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_RETURN
ZEND_GET_MODULE(return)
#endif

