PHP_ARG_ENABLE(nsfunc,
               whether to enable nsfunc module,
[ --enable-nsfunc   Enable nsfunc support ])

if test "$PHP_NSFUNC" != "no"; then
  PHP_NEW_EXTENSION(nsfunc, php_nsfunc.c, $ext_shared)
fi

