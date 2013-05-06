Examples of returning values from functions

Macros:
* `RETURN_NULL()` - Return `NULL`
* `RETURN_BOOL(v)` - Return `true` if `v` is non-zero, `false` otherwise
* `RETURN_TRUE` - Return `true`
* `RETURN_FALSE` - Return `false`
* `RETURN_LONG(v)` - Return an interger value `v`
* `RETURN_DOUBLE(v)` - Return a float value `v`
* `RETURN_STRING(v, c)` - Return a `\0` terminated string `v`, copying to engine memory if `c` is 1, adopting as engine memory if `c` is 0
* `RETURN_STRINGL(v, l, c)` - Return a string `v` of length `l`, copying to engine memory (if `c` == 1, as above)

Each of the above has a RETVAL_* form which sets the return value (local variable `return_value`), but does not immediately return.
* `RETVAL_NULL()`
* `RETVAL_BOOL(v)`
* etc...

The RETVAL form is, in turn, a convenience wrapper around ZVAL_* forms fo the macros which specify the special `return_value` variable
* `ZVAL_NULL(pzv)` - Set pzv to represent a userspace `NULL`
* `ZVAL_BOOL(pzv, v)` - Set pzv as a boolean true (v!=0) or false(v==0)
* etc...

The declarations of these macros can be thought of as:

```
static inline ZVAL_LONG(zval *pzv, long l) {
  pzv->type = IS_LONG;
  pzv->value.lval = l;
}

#define RETVAL_LONG(l)  ZVAL_LONG(return_value, l)

#define RETURN_LONG(l)  { RETVAL_LONG(l); return; }
```
