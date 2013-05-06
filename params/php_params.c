#include "php_params.h"

/* {{{ proto int params_add(int $a, int $b) */
ZEND_BEGIN_ARG_INFO(params_add_arginfo, 0)
  ZEND_ARG_INFO(0, a)
  ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()
static PHP_FUNCTION(params_add) {
  long a, b;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &a, &b) == FAILURE) {
    return;
  }

  RETURN_LONG(a + b);
}
/* }}} */

/* {{{ proto void params_dump(mixed $arg) */
ZEND_BEGIN_ARG_INFO(params_dump_arginfo, 0)
  ZEND_ARG_INFO(0, arg)
ZEND_END_ARG_INFO()
static PHP_FUNCTION(params_dump) {
  zval *arg;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &arg) == FAILURE) {
    return;
  }

  switch (Z_TYPE_P(arg)) {
    case IS_NULL:
      php_printf("NULL\n");
      break;
    case IS_BOOL:
      php_printf("bool(%s)\n", Z_BVAL_P(arg) ? "true" : "false");
      break;
    case IS_LONG:
      php_printf("int(%ld)\n", Z_LVAL_P(arg));
      break;
    case IS_DOUBLE:
      php_printf("float(%f)\n", Z_DVAL_P(arg));
      break;
    case IS_STRING:
      php_printf("string(%d) \"", Z_STRLEN_P(arg));
      PHPWRITE(Z_STRVAL_P(arg), Z_STRLEN_P(arg));
      php_printf("\"\n");
      break;
    case IS_ARRAY:
      php_printf("array(%d) { ... }\n", zend_hash_num_elements(Z_ARRVAL_P(arg)));
      break;
    case IS_RESOURCE: {
      const char *type_name = zend_rsrc_list_get_rsrc_type(Z_RESVAL_P(arg) TSRMLS_CC);
      php_printf("resource#%ld(%s)\n", Z_RESVAL_P(arg), type_name ? type_name : "Unknown");
      break;
    }
    case IS_OBJECT: {
      const zend_class_entry *ce = Z_OBJCE_P(arg);
      php_printf("object#%u(%s)\n", Z_OBJ_HANDLE_P(arg), (ce && ce->name) ? ce->name : "Unknown");
      break;
    }
    default:
      php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unknown type: %d\n", Z_TYPE_P(arg));
  }
}
/* }}} */

/* {{{ proto void params_hello(string $name) */
ZEND_BEGIN_ARG_INFO(params_hello_arginfo, 0)
  ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()
static PHP_FUNCTION(params_hello) {
  char *name;
  int name_len;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len) == FAILURE) {
    return;
  }

  /* If you aren't worried about binary safety:
     php_printf("Hello %s\n", name);

     Otherwise: */
  php_printf("Hello ");
  PHPWRITE(name, name_len);
  php_printf("\n");
}
/* }}} */

/* {{{ proto void params_hello2(string $name[, Array $options = NULL]) */
ZEND_BEGIN_ARG_INFO(params_hello2_arginfo, 0)
  ZEND_ARG_INFO(0, name)
  ZEND_ARG_ARRAY_INFO(0, options, 1)
ZEND_END_ARG_INFO()
static PHP_FUNCTION(params_hello2) {
  char *name;
  int name_len;
  HashTable *options = NULL;
  zval **zgreet;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|h!", &name, &name_len, &options) == FAILURE) {
    return;
  }

  if (options &&
      (zend_hash_find(options, "greeting", (strlen("greeting") + 1), (void**)&zgreet) == SUCCESS) &&
      (Z_TYPE_PP(zgreet) == IS_STRING)) {
    PHPWRITE(Z_STRVAL_PP(zgreet), Z_STRLEN_PP(zgreet));
    PHPWRITE(" ", 1);
  } else {
    php_printf("Hello ");
  }
  PHPWRITE(name, name_len);
  php_printf("\n");
}
/* }}} */

/* {{{ proto void params_hello_varargs(...) */
ZEND_BEGIN_ARG_INFO(params_hello_varargs_arginfo, 0)
  ZEND_ARG_INFO(0, name)
  /* ... */
ZEND_END_ARG_INFO()
static PHP_FUNCTION(params_hello_varargs) {
  zval ***argv;
  int argc, i;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "+", &argv, &argc) == FAILURE) {
    return;
  }

  for (i = 0; i < argc; ++i) {
    if (Z_TYPE_PP(argv[i]) != IS_STRING) {
      php_error_docref(NULL TSRMLS_CC, E_WARNING, "Non-string argument provided, ignoring.");
      continue;
    }
    php_printf("Hello ");
    PHPWRITE(Z_STRVAL_PP(argv[i]), Z_STRLEN_PP(argv[i]));
    php_printf("\n");
  }
  efree(argv);
}
/* }}} */

/* {{{ proto float params_muldiv(float $a, float $b[, bool $divide = false]) */
ZEND_BEGIN_ARG_INFO(params_muldiv_arginfo, 0)
  ZEND_ARG_INFO(0, a)
  ZEND_ARG_INFO(0, b)
  ZEND_ARG_INFO(0, divide)
ZEND_END_ARG_INFO()
static PHP_FUNCTION(params_muldiv) {
  double a, b;
  zend_bool divide = 0;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd|b", &a, &b, &divide) == FAILURE) {
    return;
  }

  if (divide) {
    RETURN_DOUBLE(a / b);
  } else {
    RETURN_DOUBLE(a * b);
  }
}
/* }}} */

/* {{{ proto bool params_ref_arg(double $numerator, double $denominator, double &$dividend) */
ZEND_BEGIN_ARG_INFO(params_ref_arg_arginfo, 0)
  ZEND_ARG_INFO(0, numerator)
  ZEND_ARG_INFO(0, denominator)
  ZEND_ARG_INFO(1, dividend)
ZEND_END_ARG_INFO()
static PHP_FUNCTION(params_ref_arg) {
  double numerator, denominator;
  zval *dividend;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddz", &numerator, &denominator, &dividend) == FAILURE) {
    return;
  }
  zval_dtor(dividend);

  if (denominator == 0.0) {
    ZVAL_NULL(dividend);
    php_error_docref(NULL TSRMLS_CC, E_WARNING, "Division by zero");
    RETURN_FALSE;
  }

  ZVAL_DOUBLE(dividend, numerator / denominator);
  RETURN_TRUE;
}
/* }}} */

static zend_function_entry params_functions[] = {
  PHP_FE(params_add, params_add_arginfo)
  PHP_FE(params_dump, params_dump_arginfo)
  PHP_FE(params_hello, params_hello_arginfo)
  PHP_FE(params_hello2, params_hello2_arginfo)
  PHP_FE(params_hello_varargs, params_hello_varargs_arginfo)
  PHP_FE(params_muldiv, params_muldiv_arginfo)
  PHP_FE(params_ref_arg, params_ref_arg_arginfo)
  { NULL, NULL, NULL }
};

zend_module_entry params_module_entry = {
  STANDARD_MODULE_HEADER,
  "params", /* extname */
  params_functions,
  NULL,    /* MINIT */
  NULL,    /* MSHUTDOWN */
  NULL,    /* RINIT */
  NULL,    /* RSHUTDOWN */
  NULL,    /* MINFO */
  NO_VERSION_YET,
  STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PARAMS
ZEND_GET_MODULE(params)
#endif

