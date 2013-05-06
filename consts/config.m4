PHP_ARG_ENABLE(consts,
               whether to enable consts module,
[ --enable-consts   Enable consts support ])

if test "$PHP_CONSTS" != "no"; then
  PHP_NEW_EXTENSION(consts, php_consts.c, $ext_shared)
fi

