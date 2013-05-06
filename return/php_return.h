#ifndef PHP_RETURN_H
#define PHP_RETURN_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

extern zend_module_entry return_module_entry;
#define return_module_ptr &return_module_entry

#endif /* PHP_RETURN_H */
