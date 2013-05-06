PHP_ARG_ENABLE(params,
               whether to enable params module,
[ --enable-params   Enable params support ])

if test "$PHP_PARAMS" != "no"; then
  PHP_NEW_EXTENSION(params, php_params.c, $ext_shared)
fi

