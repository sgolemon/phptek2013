#include "php_hello.h"

static PHP_FUNCTION(hello_world) {
  php_printf("Hello World\n");
}

static zend_function_entry hello_functions[] = {
  PHP_FE(hello_world, NULL)
  { NULL, NULL, NULL }
};

zend_module_entry hello_module_entry = {
  STANDARD_MODULE_HEADER,
  "hello", /* extname */
  hello_functions,
  NULL,    /* MINIT */
  NULL,    /* MSHUTDOWN */
  NULL,    /* RINIT */
  NULL,    /* RSHUTDOWN */
  NULL,    /* MINFO */
  NO_VERSION_YET,
  STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_HELLO
ZEND_GET_MODULE(hello)
#endif

