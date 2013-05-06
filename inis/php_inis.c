#include "php_inis.h" /* Our header */
#include "php_ini.h" /* PHP's header */

ZEND_DECLARE_MODULE_GLOBALS(inis);

PHP_INI_BEGIN()
  STD_PHP_INI_ENTRY("inis.enable", "1", PHP_INI_SYSTEM, OnUpdateBool, enable, zend_inis_globals, inis_globals)
  STD_PHP_INI_ENTRY("inis.name", "", PHP_INI_PERDIR|PHP_INI_USER, OnUpdateString, name, zend_inis_globals, inis_globals)
  STD_PHP_INI_ENTRY("inis.level", "0", PHP_INI_ALL, OnUpdateLong, level, zend_inis_globals, inis_globals)
PHP_INI_END()

static PHP_FUNCTION(inis_report) {
  if (!INIS_G(enable)) {
    php_error_docref(NULL TSRMLS_CC, E_WARNING, "Inis extension not enabled");
    return;
  }

  php_printf("Name: %s\n", INIS_G(name));
  php_printf("Level: %ld\n", INIS_G(level));
}

static zend_function_entry inis_functions[] = {
  PHP_FE(inis_report, NULL)
  { NULL, NULL, NULL }
};

static PHP_MINIT_FUNCTION(inis) {
  REGISTER_INI_ENTRIES();
  return SUCCESS;
}

zend_module_entry inis_module_entry = {
  STANDARD_MODULE_HEADER,
  "inis", /* extname */
  inis_functions,
  PHP_MINIT(inis),
  NULL,    /* MSHUTDOWN */
  NULL,    /* RINIT */
  NULL,    /* RSHUTDOWN */
  NULL,    /* MINFO */
  NO_VERSION_YET,
  PHP_MODULE_GLOBALS(inis),
  NULL,    /* GINIT */
  NULL,    /* GSHUTDOWN */
  NULL,    /* RPOSTSHUTDOWN */
  STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_INIS
ZEND_GET_MODULE(inis)
#endif

