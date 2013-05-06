#include "php_consts.h"
#include <stdlib.h>
#include <time.h>

static PHP_MINIT_FUNCTION(consts) {
  REGISTER_LONG_CONSTANT("MEANING_OF_LIFE", 42, CONST_CS | CONST_PERSISTENT);
  REGISTER_DOUBLE_CONSTANT("pi", 3.1415926535, CONST_PERSISTENT);
  REGISTER_STRING_CONSTANT("CONSTS_NAME", "const", CONST_CS | CONST_PERSISTENT);

  return SUCCESS;
}

static PHP_RINIT_FUNCTION(consts) {
  char buffer[40];
  srand((int)time(NULL));
  snprintf(buffer, sizeof(buffer), "%d", rand());
  REGISTER_STRING_CONSTANT("CONSTS_RAND", estrdup(buffer), CONST_CS);
  return SUCCESS;
}

zend_module_entry consts_module_entry = {
  STANDARD_MODULE_HEADER,
  "consts", /* extname */
  NULL,     /* functions */
  PHP_MINIT(consts),
  NULL,    /* MSHUTDOWN */
  PHP_RINIT(consts),
  NULL,    /* RSHUTDOWN */
  NULL,    /* MINFO */
  NO_VERSION_YET,
  STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_CONSTS
ZEND_GET_MODULE(consts)
#endif

