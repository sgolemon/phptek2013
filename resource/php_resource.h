#ifndef PHP_RESOURCE_H
#define PHP_RESOURCE_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

extern zend_module_entry resource_module_entry;
#define resource_module_ptr &resource_module_entry

#endif /* PHP_RESOURCE_H */
