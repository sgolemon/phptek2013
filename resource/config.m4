PHP_ARG_ENABLE(resource,
               whether to enable resource module,
[ --enable-resource   Enable resource support ])

if test "$PHP_RESOURCE" != "no"; then
  PHP_NEW_EXTENSION(resource, php_resource.c, $ext_shared)
fi

