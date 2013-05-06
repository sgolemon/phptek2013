#include "php_resource.h"

static int person_le;

typedef struct _person {
  char *name;
  int name_len;
  int age;
} person;

/* {{{ proto Person person_create(string $name, int $age) */
ZEND_BEGIN_ARG_INFO(person_create_arginfo, 0)
  ZEND_ARG_INFO(0, name)
  ZEND_ARG_INFO(0, age)
ZEND_END_ARG_INFO()
static PHP_FUNCTION(person_create) {
  char *name;
  int name_len;
  long age;
  person *new_person;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sl",
      &name, &name_len, &age) == FAILURE) {
    return;
  }

  new_person = emalloc(sizeof(person));
  new_person->name = estrndup(name, name_len);
  new_person->name_len = name_len;
  new_person->age = age;

  RETURN_RESOURCE(zend_list_insert(new_person, person_le TSRMLS_CC));
}
/* }}} */

/* {{{ proto void person_greet(Person $person) */
ZEND_BEGIN_ARG_INFO(person_greet_arginfo, 0)
  ZEND_ARG_INFO(0, person)
ZEND_END_ARG_INFO()
static PHP_FUNCTION(person_greet) {
  zval *zperson;
  person *p;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
      "r", &zperson) == FAILURE) {
    return;
  }

  ZEND_FETCH_RESOURCE(p, person*, &zperson, -1, "Person", person_le);
  php_printf("Hello ");
  PHPWRITE(p->name, p->name_len);
  php_printf(", you seem to be %ld years old\n", p->age);
}
/* }}} */

/* {{{ proto void person_age_set(Person $person, int $age) */
ZEND_BEGIN_ARG_INFO(person_age_set_arginfo, 0)
  ZEND_ARG_INFO(0, person)
  ZEND_ARG_INFO(0, age)
ZEND_END_ARG_INFO()
static PHP_FUNCTION(person_age_set) {
  zval *zperson;
  person *p;
  long age;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
      "rl", &zperson, &age) == FAILURE) {
    return;
  }

  ZEND_FETCH_RESOURCE(p, person*, &zperson, -1, "Person", person_le);
  p->age = age;
}
/* }}} */

static zend_function_entry resource_functions[] = {
  PHP_FE(person_create, person_create_arginfo)
  PHP_FE(person_greet, person_greet_arginfo)
  PHP_FE(person_age_set, person_age_set_arginfo)
  { NULL, NULL, NULL }
};

static void person_dtor(void *pers) {
  person **p = (person**)pers;
  if (p && *p) {
    if ((*p)->name) {
      efree((*p)->name);
    }
    efree(*p);
  }
}

static PHP_MINIT_FUNCTION(resource) {
  person_le = zend_register_list_destructors_ex(person_dtor, NULL, "Person", module_number);

  return SUCCESS;
}

zend_module_entry resource_module_entry = {
  STANDARD_MODULE_HEADER,
  "resource", /* extname */
  resource_functions,
  PHP_MINIT(resource),
  NULL,    /* MSHUTDOWN */
  NULL,    /* RINIT */
  NULL,    /* RSHUTDOWN */
  NULL,    /* MINFO */
  NO_VERSION_YET,
  STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_RESOURCE
ZEND_GET_MODULE(resource)
#endif

