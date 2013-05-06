#ifndef PHP_HELLO_H
#define PHP_HELLO_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

extern zend_module_entry hello_module_entry;
#define hello_module_ptr &hello_module_entry

#endif /* PHP_HELLO_H */
