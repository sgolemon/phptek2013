#ifndef PHP_GLOBAL_H
#define PHP_GLOBAL_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

ZEND_BEGIN_MODULE_GLOBALS(global)
  long counter;
  char *name;
  int name_len;
ZEND_END_MODULE_GLOBALS(global)

#ifdef ZTS
# define GLOBAL_G(v) TSRMG(global_globals_id, zend_global_globals *, v)
#else
# define GLOBAL_G(v) (global_globals.v)
#endif

extern zend_module_entry global_module_entry;
#define global_module_ptr &global_module_entry

#endif /* PHP_GLOBAL_H */
