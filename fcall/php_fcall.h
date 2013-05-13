#ifndef PHP_FCALL_H
#define PHP_FCALL_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

extern zend_module_entry fcall_module_entry;
#define fcall_module_ptr &fcall_module_entry

#endif /* PHP_FCALL_H */
