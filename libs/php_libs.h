#ifndef PHP_LIBS_H
#define PHP_LIBS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

extern zend_module_entry libs_module_entry;
#define libs_module_ptr &libs_module_entry

#endif /* PHP_LIBS_H */
