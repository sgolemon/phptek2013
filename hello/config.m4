PHP_ARG_ENABLE(hello,
               whether to enable hello module,
[ --enable-hello   Enable hello support ])

if test "$PHP_HELLO" != "no"; then
  PHP_NEW_EXTENSION(hello, php_hello.c, $ext_shared)
fi

