PHP_ARG_ENABLE(fcall,
               whether to enable fcall module,
[ --enable-fcall   Enable fcall support ])

if test "$PHP_FCALL" != "no"; then
  PHP_NEW_EXTENSION(fcall, php_fcall.c, $ext_shared)
fi

