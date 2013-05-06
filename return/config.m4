PHP_ARG_ENABLE(return,
               whether to enable return module,
[ --enable-return   Enable return support ])

if test "$PHP_RETURN" != "no"; then
  PHP_NEW_EXTENSION(return, php_return.c, $ext_shared)
fi

