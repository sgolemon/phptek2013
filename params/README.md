Examples of accepting arguments

Type specifiers to zend_parse_parameters()

Specifier | C type | Description
--- | --- | ---
`b` | zend_bool | Boolean
`l` | long | Integer with rollover (that's a lower-case L)
`L` | long | Integer with truncation
`d` | double | Float
`s` | char *, int | String (value and length)
`p` | char *, int | String with `\0` checks
`a` | zval * | Array as a zval
`h` | HashTable * | Array as a HashTable
`H` | HashTable * | Array or Object Properties
`r` | zval * | Resource
`o` | zval * | Object
`O` | zval *, zend_class_entry * | Object of specific class
`C` | zend_class_entry * | Class entry (user passes class name as string)
`f` | zend_fcall_info, zend_fcall_info_cache | Callable
`z` | zval * | Any variable
`Z` | zval ** | Any variable handle
`*` | zval ***, int | Variable args (0 or many)
`+` | zval ***, int | Variable args (1 or many)

**Note: With most type specifiers you pass a pointer to the variable you want populated by reference (e.g. "s", &str, &len ), however in the case of `O`, the second part is passed by value.  We're specifying what class we want, not receiving what class we got.**

Type modifiers

Modifier | Meaning
--- | ---
**(pipe)** | All specifiers beyond this point are optinal.  If an argument is not passed, the C variable is unmodified from what is passed in.  Optional arguments should typically be initialized before calling zend_parse_parameters().
`!` | If `NULL` is passed for this argument, ignore the value and leave the C variable unmodified.  As with other optional parameters, the C variable should be initialized first.
`/` | Separate value so that changes made to it by the C implementation do not effect the PHP variable passed to the function.

**Note: `(pipe)` above refers to the `|` character which github markdown gets confused about in tables.**

---

zval Access

C Type | Base Macro | `Z_TYPE(v)`
--- | --- | ---
| | `IS_NULL`
zend_uchar | `Z_BVAL(v)` | `IS_BOOL`
long | `Z_LVAL(v)` | `IS_LONG`
double | `Z_DVAL(v)` | `IS_DOUBLE`
char* | `Z_STRVAL(v)` | `IS_STRING`
int | `Z_STRLEN(v)` | `IS_STRING`
long | `Z_RESVAL(v)` | `IS_RESOURCE`
HashTable* | `Z_ARRVAL(v)` | `IS_ARRAY`
HashTable* | `Z_OBJPROP(v)` | `IS_OBJECT`
zend_class_entry* | `Z_OBJCE(v)` | `IS_OBJECT`
zend_object_value | `Z_OBJVAL(v)` | `IS_OBJECT`
int | `Z_OBJ_HANDLE(v)` | `IS_OBJECT`
zend_object_handlers* | `Z_OBJ_HT(v)` | `IS_OBJECT`
Object Handler | `Z_OBJ_HANDLER(v, h)` | `IS_OBJECT`
HashTable* | `Z_OBJDEBUG(v, &tmp)` | `IS_OBJECT`

Each of the above `Z_*()` macros accepts an immediate `zval`.  When working with a `zval*`, use `Z_*_P()`
When working with a `zval**`, use `Z_*_PP()`.

For example:

```
zval foo = getval();
if (Z_TYPE(foo) == IS_LONG) callFunc(Z_LVAL(foo));
```

```
zval *foo = getPval();
if (Z_TYPE_P(foo) == IS_LONG) callFunc(Z_LVAL_P(foo));
```

```
zval **foo = getPPval();
if (Z_TYPE_PP(foo) == IS_LONG) callFunc(Z_LVAL_PP(foo));
```

Additionally, `HASH_OF(v)` exists as a convenience for accessing either an `IS_ARRAY` `HashTable*` or
an `IS_OBJECT`'s property table, which is also a `HashTable*`.
Basically the following:

```
#define HASH_OF(pzv) ((Z_TYPE_P(pzv) == IS_ARRAY) ? Z_ARRVAL_P(pzv) : \
                      ((Z_TYPE_P(pzv) == IS_OBJECT) ? Z_OBJPROP_P(pzv) : NULL))
```
