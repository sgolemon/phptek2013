#include "php_objects3.h"

static zend_class_entry *hello_ce;
static zend_object_handlers hello_handlers;

typedef struct _hello_object {
  zend_object obj;

  char *name;
  int name_len;
  long age;
} hello_object;

#define HELLO_FETCH_OBJECT(zobj) (hello_object*)zend_objects_get_address((zobj) TSRMLS_CC)

/* {{{ proto Hello::__construct(string $name, int $age) */
ZEND_BEGIN_ARG_INFO(hello___construct_arginfo, 0)
  ZEND_ARG_INFO(0, name)
  ZEND_ARG_INFO(0, age)
ZEND_END_ARG_INFO()
static PHP_METHOD(Hello, __construct) {
  hello_object *objval = HELLO_FETCH_OBJECT(getThis());
  char *name;
  int name_len;
  long age;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
      "sl", &name, &name_len, &age) == FAILURE) {
    return;
  }

  objval->name = estrndup(name, name_len);
  objval->name_len = name_len;
  objval->age = age;
}
/* }}} */

/* {{{ proto Hello::greet() */
static PHP_METHOD(Hello, greet) {
  hello_object *objval = HELLO_FETCH_OBJECT(getThis());

  php_printf("Hello, ");
  PHPWRITE(objval->name, objval->name_len);
  php_printf(", you appear to be %ld years old\n", objval->age);
}
/* }}} */

static zend_function_entry hello_methods[] = {
  PHP_ME(Hello, __construct, hello___construct_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
  PHP_ME(Hello, greet,       NULL,                      ZEND_ACC_PUBLIC)
  { NULL, NULL, NULL }
};

#if PHP_VERSION_ID > 50399
# define ZLK , const struct _zend_literal *key
#else
# define ZLK
#endif

#define ISSTR(pzv, str) ((Z_STRLEN_P(pzv) == strlen(str)) && !strcmp(Z_STRVAL_P(pzv), str))

static zval *hello_read_prop(zval *object, zval *member, int type ZLK TSRMLS_DC) {
  zval tmp, *ret = EG(uninitialized_zval_ptr);

  if (Z_TYPE_P(member) != IS_STRING) {
    ZVAL_ZVAL(&tmp, member, 1, 0);
    convert_to_string(&tmp);
    member = &tmp;
  }

  if (ISSTR(member, "name")) {
    hello_object *objval = HELLO_FETCH_OBJECT(object);
    MAKE_STD_ZVAL(ret);
    ZVAL_STRINGL(ret, objval->name, objval->name_len, 1);
    Z_SET_REFCOUNT_P(ret, 0);
  } else if (ISSTR(member, "age")) {
    hello_object *objval = HELLO_FETCH_OBJECT(object);
    MAKE_STD_ZVAL(ret);
    ZVAL_LONG(ret, objval->age);
    Z_SET_REFCOUNT_P(ret, 0);
  } else {
    php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Undefined property %s", Z_STRVAL_P(member));
  }

  if (member == &tmp) {
    zval_dtor(&tmp);
  }

  return ret;
}

static void hello_write_prop(zval *object, zval *member, zval *value ZLK TSRMLS_DC) {
  zval tmp;

  if (Z_TYPE_P(member) != IS_STRING) {
    ZVAL_ZVAL(&tmp, member, 1, 0);
    convert_to_string(&tmp);
    member = &tmp;
  }

  if (ISSTR(member, "name")) {
    hello_object *objval = HELLO_FETCH_OBJECT(object);
    if (objval->name) {
      efree(objval->name);
      objval->name = NULL;
    }
    if (Z_TYPE_P(value) == IS_STRING) {
      objval->name = estrndup(Z_STRVAL_P(value), Z_STRLEN_P(value));
      objval->name_len = Z_STRLEN_P(value);
    } else {
      zval str;
      ZVAL_ZVAL(&str, value, 1, 0);
      convert_to_string(&str);
      objval->name = Z_STRVAL(str);
      objval->name_len = Z_STRLEN(str);
      /* Skipping zval_dtor because we stole the underlying pointer */
    }
  } else if (ISSTR(member, "age")) {
    hello_object *objval = HELLO_FETCH_OBJECT(object);
    if (Z_TYPE_P(value) == IS_LONG) {
      objval->age = Z_LVAL_P(value);
    } else {
      zval lval;
      ZVAL_ZVAL(&lval, value, 1, 0);
      convert_to_long(&lval);
      objval->age = Z_LVAL(lval);
      zval_dtor(&lval);
    }
  } else {
    php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Undefined property %s", Z_STRVAL_P(member));
  }

  if (member == &tmp) {
    zval_dtor(&tmp);
  }
}

static int hello_has_prop(zval *object, zval *member, int has_set_exists ZLK TSRMLS_DC) {
  zval tmp;
  int retval = 1;

  if (Z_TYPE_P(member) != IS_STRING) {
    ZVAL_ZVAL(&tmp, member, 1, 0);
    convert_to_string(&tmp);
    member = &tmp;
  }

  if (ISSTR(member, "name")) {
    if (has_set_exists == 1) { /* set */
      hello_object *objval = HELLO_FETCH_OBJECT(object);
      retval = (objval->name && (objval->name[0]));
    }
  } else if (ISSTR(member, "age")) {
    if (has_set_exists == 1) { /* set */
      hello_object *objval = HELLO_FETCH_OBJECT(object);
      retval = (objval->age != 0);
    }
  }
  else {
    retval = 0;
  }

  if (member == &tmp) {
    zval_dtor(&tmp);
  }

  return retval;
}

static void hello_unset_prop(zval *object, zval *member ZLK TSRMLS_DC) {
  php_error_docref(NULL TSRMLS_CC, E_WARNING, "Class Hello does not allow its properties to be unset");
}

static void hello_dtor(hello_object *objval TSRMLS_DC) {
  if (objval->name) {
    efree(objval->name);
  }
  zend_object_std_dtor(&(objval->obj) TSRMLS_CC);
  efree(objval);
}

static zend_object_value hello_ctor_ex(hello_object **pobjval, zend_class_entry *ce TSRMLS_DC) {
  hello_object *objval = ecalloc(1, sizeof(hello_object));
  zend_object_value retval;

  zend_object_std_init(&(objval->obj), ce TSRMLS_CC);
  retval.handle = zend_objects_store_put(objval, (zend_objects_store_dtor_t)zend_objects_destroy_object, (zend_objects_free_object_storage_t)hello_dtor, NULL TSRMLS_CC);
  retval.handlers = &hello_handlers;

  if (pobjval) {
    *pobjval = objval;
  }

  return retval;
}

static zend_object_value hello_ctor(zend_class_entry *ce TSRMLS_DC) {
  return hello_ctor_ex(NULL, ce TSRMLS_CC);
}

static zend_object_value hello_clone(zval *zobject TSRMLS_DC) {
  hello_object *old_object = HELLO_FETCH_OBJECT(zobject);
  hello_object *new_object;
  zend_object_value retval = hello_ctor_ex(&new_object, old_object->obj.ce TSRMLS_CC);

  zend_objects_clone_members(&(new_object->obj), retval,
                             &(old_object->obj), Z_OBJ_HANDLE_P(zobject) TSRMLS_CC);

  if (old_object->name) {
    new_object->name = estrndup(old_object->name, old_object->name_len);
    new_object->name_len = old_object->name_len;
  }
  new_object->age = old_object->age;

  return retval;
}

static PHP_MINIT_FUNCTION(objects3) {
  zend_class_entry ce;

  INIT_CLASS_ENTRY(ce, "Hello", hello_methods)
  hello_ce = zend_register_internal_class(&ce TSRMLS_CC);

  hello_ce->create_object = hello_ctor;
  memcpy(&hello_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
  hello_handlers.clone_obj = hello_clone;

  hello_handlers.read_property   = hello_read_prop;
  hello_handlers.write_property  = hello_write_prop;
  hello_handlers.has_property    = hello_has_prop;
  hello_handlers.unset_property  = hello_unset_prop;
  hello_handlers.get_property_ptr_ptr = NULL;

  return SUCCESS;
}

zend_module_entry objects3_module_entry = {
  STANDARD_MODULE_HEADER,
  "objects3", /* extname */
  NULL,    /* functions */
  PHP_MINIT(objects3),
  NULL,    /* MSHUTDOWN */
  NULL,    /* RINIT */
  NULL,    /* RSHUTDOWN */
  NULL,    /* MINFO */
  NO_VERSION_YET,
  STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_OBJECTS3
ZEND_GET_MODULE(objects3)
#endif

