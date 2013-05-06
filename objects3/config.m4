PHP_ARG_ENABLE(objects3,
               whether to enable objects3 module,
[ --enable-objects3   Enable objects3 support ])

if test "$PHP_OBJECTS3" != "no"; then
  PHP_NEW_EXTENSION(objects3, php_objects3.c, $ext_shared)
fi

