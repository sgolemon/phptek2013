PHP_ARG_ENABLE(global,
               whether to enable global module,
[ --enable-global   Enable global support ])

if test "$PHP_GLOBAL" != "no"; then
  PHP_NEW_EXTENSION(global, php_global.c, $ext_shared)
fi

