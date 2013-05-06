PHP_ARG_WITH(libs,
               whether to enable libs module,
[ --with-libs=DIR   Enable libs support ])

if test "$PHP_LIBS" != "no"; then
  AC_MSG_CHECKING(for cURL)
  for i in $PHP_LIBS /usr /usr/local; do
    if test -f "$i/include/curl/curl.h"; then
      AC_MSG_RESULT(found in $i)
      PHP_LIBS_CURL=$i
      break
    fi
  done

  if test -z "$PHP_LIBS_CURL"; then
    AC_MSG_RESULT(not found)
    AC_MSG_ERROR(Please install the libcurl distribution)
  fi

  PHP_ADD_INCLUDE($PHP_LIBS_CURL/include)
  PHP_ADD_LIBRARY_WITH_PATH(curl, $PHP_LIBS_CURL/lib, LIBS_SHARED_LIBADD)
  PHP_SUBST(LIBS_SHARED_LIBADD)

  PHP_NEW_EXTENSION(libs, php_libs.c, $ext_shared)
fi

