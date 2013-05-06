#ifndef PHP_INIS_H
#define PHP_INIS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

ZEND_BEGIN_MODULE_GLOBALS(inis)
  zend_bool enable;
  char *name;
  long level;
ZEND_END_MODULE_GLOBALS(inis)

#ifdef ZTS
# define INIS_G(v) TSRMG(inis_globals_id, zend_inis_globals *, v)
#else
# define INIS_G(v) (inis_globals.v)
#endif

extern zend_module_entry inis_module_entry;
#define inis_module_ptr &inis_module_entry

#endif /* PHP_INIS_H */
