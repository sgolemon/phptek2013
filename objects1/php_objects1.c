#include "php_objects1.h"

static zend_class_entry *hello_ce;

/* {{{ proto Hello::__construct(string $name, int $age) */
ZEND_BEGIN_ARG_INFO(hello___construct_arginfo, 0)
  ZEND_ARG_INFO(0, name)
  ZEND_ARG_INFO(0, age)
ZEND_END_ARG_INFO()
static PHP_METHOD(Hello, __construct) {
  char *name;
  int name_len;
  long age;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
      "sl", &name, &name_len, &age) == FAILURE) {
    return;
  }

  zend_update_property_stringl(hello_ce, getThis(),
       "name", sizeof("name") - 1, name, name_len TSRMLS_CC);
  zend_update_property_long(hello_ce, getThis(),
       "age", sizeof("age") - 1, age TSRMLS_CC);
}
/* }}} */

/* {{{ proto Hello::greet() */
static PHP_METHOD(Hello, greet) {
  zval *name = zend_read_property(hello_ce, getThis(), "name", sizeof("name") - 1, 0 TSRMLS_CC);
  zval *age  = zend_read_property(hello_ce, getThis(), "age",  sizeof("age")  - 1, 0 TSRMLS_CC);
  long lage;

  php_printf("Hello, ");

  if (Z_TYPE_P(name) == IS_STRING) {
    PHPWRITE(Z_STRVAL_P(name), Z_STRLEN_P(name));
  } else {
    zval tmp;
    ZVAL_ZVAL(&tmp, name, 1, 0);
    convert_to_string(&tmp);
    PHPWRITE(Z_STRVAL(tmp), Z_STRLEN(tmp));
    zval_dtor(&tmp);
  }

  if (Z_TYPE_P(age) == IS_LONG) {
    lage = Z_LVAL_P(age);
  } else {
    zval tmp;
    ZVAL_ZVAL(&tmp, age, 1, 0);
    convert_to_long(&tmp);
    lage = Z_LVAL(tmp);
    zval_dtor(&tmp);
  }
  php_printf(", you appear to be %ld years old\n", lage);
}
/* }}} */

static zend_function_entry hello_methods[] = {
  PHP_ME(Hello, __construct, hello___construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
  PHP_ME(Hello, greet,       NULL,                      ZEND_ACC_PUBLIC)
  { NULL, NULL, NULL }
};

static PHP_MINIT_FUNCTION(objects1) {
  zend_class_entry ce;

  INIT_CLASS_ENTRY(ce, "Hello", hello_methods)
  hello_ce = zend_register_internal_class(&ce TSRMLS_CC);

  zend_declare_property_string(hello_ce, "name", sizeof("name") - 1, "", ZEND_ACC_PUBLIC TSRMLS_CC);
  zend_declare_property_long(hello_ce, "age", sizeof("age") - 1, 0, ZEND_ACC_PUBLIC TSRMLS_CC);

  return SUCCESS;
}

zend_module_entry objects1_module_entry = {
  STANDARD_MODULE_HEADER,
  "objects1", /* extname */
  NULL,    /* functions */
  PHP_MINIT(objects1),
  NULL,    /* MSHUTDOWN */
  NULL,    /* RINIT */
  NULL,    /* RSHUTDOWN */
  NULL,    /* MINFO */
  NO_VERSION_YET,
  STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_OBJECTS1
ZEND_GET_MODULE(objects1)
#endif

