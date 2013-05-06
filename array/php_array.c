#include "php_array.h"

/* {{{ proto void array_greet(Array $names[, Array $options = NULL]) */
ZEND_BEGIN_ARG_INFO(array_greet_arginfo, 0)
  ZEND_ARG_ARRAY_INFO(0, names, 0)
  ZEND_ARG_ARRAY_INFO(0, options, 1)
ZEND_END_ARG_INFO()
static PHP_FUNCTION(array_greet) {
  HashTable *names, *options = NULL;
  HashPosition pos;
  zval **val;
  zend_bool hello = 1;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "h|h!", &names, &options) == FAILURE) {
    return;
  }

  if (options &&
      zend_hash_find(options, "hello", sizeof("hello"), (void**)&val) == SUCCESS) {
    hello = zend_is_true(*val);
  }

  for (zend_hash_internal_pointer_reset_ex(names, &pos);
       zend_hash_current_value_ex(names, (void**)&val, &pos) == SUCCESS;
       zend_hash_move_forward_ex(names, &pos)) {
    if (Z_TYPE_PP(val) != IS_STRING) {
      php_error_docref(NULL TSRMLS_CC, E_WARNING, "All names must be strings, ignoring");
      continue;
    }

    php_printf("%s ", hello ? "Hello" : "Goodbye");
    PHPWRITE(Z_STRVAL_PP(val), Z_STRLEN_PP(val));
    php_printf("\n");
  }
}
/* }}} */

/* {{{ proto void array_greet2(Array $names[, Array $options = NULL])
 * Identical to array_greet() in functionality, but uses callback based
 * iteration, rather than walk based.
 */
static int greet_person(void *pDest, void *argument TSRMLS_DC) {
  zval **val = (zval**)pDest;
  zend_bool *hello = (zend_bool*)argument;

  if (Z_TYPE_PP(val) != IS_STRING) {
    php_error_docref(NULL TSRMLS_CC, E_WARNING, "All names must be strings, ignoring");
    ZEND_HASH_APPLY_KEEP;
  }

  php_printf("%s ", *hello ? "Hello" : "Goodbye");
  PHPWRITE(Z_STRVAL_PP(val), Z_STRLEN_PP(val));
  php_printf("\n");

  return ZEND_HASH_APPLY_KEEP;
}

static PHP_FUNCTION(array_greet2) {
  HashTable *names, *options = NULL;
  zval **val;
  zend_bool hello = 1;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "h|h!", &names, &options) == FAILURE) {
    return;
  }

  if (options &&
      zend_hash_find(options, "hello", sizeof("hello"), (void**)&val) == SUCCESS) {
    hello = zend_is_true(*val);
  }

  zend_hash_apply_with_argument(names, (apply_func_arg_t)greet_person, &hello TSRMLS_CC);
}
/* }}} */

/* {{{ proto int array_sum(Array $vals) */
ZEND_BEGIN_ARG_INFO(array_sum_arginfo, 0)
  ZEND_ARG_ARRAY_INFO(0, vals, 0)
ZEND_END_ARG_INFO()
static PHP_FUNCTION(array_sum) {
  HashTable *vals;
  HashPosition pos;
  zval **val;
  long total = 0;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "h", &vals) == FAILURE) {
    return;
  }

  for (zend_hash_internal_pointer_reset_ex(vals, &pos);
       zend_hash_current_key_ex(vals, (void**)&val, &pos) == SUCCESS;
       zend_hash_move_forward_ex(vals, &pos)) {
    zval *copyval = NULL;
    if (Z_TYPE_PP(val) != IS_LONG) {
      MAKE_STD_ZVAL(copyval);
      ZVAL_ZVAL(copyval, *val, 1, 0);
      convert_to_long(copyval);
      val = &copyval;
    }
    total += Z_LVAL_PP(val);
    if (copyval) {
      zval_ptr_dtor(&copyval);
    }
  }
}
/* }}} */

static zend_function_entry array_functions[] = {
  PHP_FE(array_greet, array_greet_arginfo)
  PHP_FE(array_greet2, array_greet_arginfo)
  PHP_FE(array_sum, array_sum_arginfo)
  { NULL, NULL, NULL }
};

zend_module_entry array_module_entry = {
  STANDARD_MODULE_HEADER,
  "array", /* extname */
  array_functions,
  NULL,    /* MINIT */
  NULL,    /* MSHUTDOWN */
  NULL,    /* RINIT */
  NULL,    /* RSHUTDOWN */
  NULL,    /* MINFO */
  NO_VERSION_YET,
  STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_ARRAY
ZEND_GET_MODULE(array)
#endif

