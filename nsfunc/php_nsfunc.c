#include "php_nsfunc.h"

static PHP_FUNCTION(hello) {
  php_printf("This was called as NsFunc\\hello() (or via use)\n");
}

static PHP_FUNCTION(nsfunc_hello2) {
  php_printf("This was called as Nsfunc\\hello2() (or via use)\n");
}

static PHP_NAMED_FUNCTION(nsfunc_hello3) {
  php_printf("This was called as Nsfunc\\hello3() (or via use)\n");
}

static zend_function_entry nsfunc_functions[] = {
  ZEND_NS_FE("NsFunc", hello, NULL)
  ZEND_NS_FENTRY("NsFunc", hello2, PHP_FN(nsfunc_hello2), NULL, 0)
  ZEND_NS_FENTRY("NsFunc", hello3, nsfunc_hello3, NULL, 0)
  { NULL, NULL, NULL }
};

zend_module_entry nsfunc_module_entry = {
  STANDARD_MODULE_HEADER,
  "nsfunc", /* extname */
  nsfunc_functions,
  NULL,    /* MINIT */
  NULL,    /* MSHUTDOWN */
  NULL,    /* RINIT */
  NULL,    /* RSHUTDOWN */
  NULL,    /* MINFO */
  NO_VERSION_YET,
  STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_NSFUNC
ZEND_GET_MODULE(nsfunc)
#endif

