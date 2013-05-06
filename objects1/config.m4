PHP_ARG_ENABLE(objects1,
               whether to enable objects1 module,
[ --enable-objects1   Enable objects1 support ])

if test "$PHP_OBJECTS1" != "no"; then
  PHP_NEW_EXTENSION(objects1, php_objects1.c, $ext_shared)
fi

