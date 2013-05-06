#include "php_libs.h"
#include <curl/curl.h>

static PHP_FUNCTION(libs_curl_version) {
  RETURN_STRING(curl_version(), 1);
}

static zend_function_entry libs_functions[] = {
  PHP_FE(libs_curl_version, NULL)
  { NULL, NULL, NULL }
};

zend_module_entry libs_module_entry = {
  STANDARD_MODULE_HEADER,
  "libs", /* extname */
  libs_functions,
  NULL,    /* MINIT */
  NULL,    /* MSHUTDOWN */
  NULL,    /* RINIT */
  NULL,    /* RSHUTDOWN */
  NULL,    /* MINFO */
  NO_VERSION_YET,
  STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_LIBS
ZEND_GET_MODULE(libs)
#endif

