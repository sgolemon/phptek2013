PHP_ARG_ENABLE(objects2,
               whether to enable objects2 module,
[ --enable-objects2   Enable objects2 support ])

if test "$PHP_OBJECTS2" != "no"; then
  PHP_NEW_EXTENSION(objects2, php_objects2.c, $ext_shared)
fi

