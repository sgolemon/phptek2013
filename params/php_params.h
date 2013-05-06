#ifndef PHP_PARAMS_H
#define PHP_PARAMS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

extern zend_module_entry params_module_entry;
#define params_module_ptr &params_module_entry

#endif /* PHP_PARAMS_H */
