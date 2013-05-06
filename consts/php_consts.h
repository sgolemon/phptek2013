#ifndef PHP_CONSTS_H
#define PHP_CONSTS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

extern zend_module_entry consts_module_entry;
#define consts_module_ptr &consts_module_entry

#endif /* PHP_CONSTS_H */
