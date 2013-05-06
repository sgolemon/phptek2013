**Before** arriving at php|tek, make sure you have the following:

* A laptop you can build PHP software on.  Preferably `Linux` or `Mac OS X`.
* A `git` checkout of [PHP](http://github.com/php/php-src/) and all dependent libraries.
* [The files in this archive](http://github.com/sgolemon/phptek2013)

While you can build PHP Extensions using the devel packages provided by most distros, you're recommended to build your own copy for development purposes (possibly in a VM) with the following command (and any additional options you might want).

```
$ git checkout git://github.com/php/php-src.git
$ cd php-src
$ ./buildconf
$ ./configure --enable-debug --enable-maintainer-zts
$ make all
$ sudo make install
```

These two additional `./configure` options will ensure that you find the most common bugs (memory leaks, missing TSRMLS_CC) during development rather than after deployment.

To be certain that everything works right, you should prepare your machine ahead of time as wifi is never guaranteed at hotel venues.

To build any one of the provided projects:

```
$ cd hello
$ phpize
$ ./configure
$ make
$ ./test -r 'hello_world();'
```

The `test` script is a convenience I've included with each project in this package to load up PHP without its normal php.ini and add in your new extension.  The `./test` line above is equivalent to:

```
$ php -n -dextension_dir=modules -dextension=hello.so -r 'hello_world();'
```

