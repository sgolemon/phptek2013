PHP_ARG_ENABLE(array,
               whether to enable array module,
[ --enable-array   Enable array support ])

if test "$PHP_ARRAY" != "no"; then
  PHP_NEW_EXTENSION(array, php_array.c, $ext_shared)
fi

