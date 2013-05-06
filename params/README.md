Examples of accepting arguments

Type specifiers to zend_parse_parameters()

Specifier | C type | Description
--- | --- | ---
`b` | zend_bool | Boolean
`l` | long | Integer with rollover (that's a lower-case L)
`L` | long | Integer with truncation
`d` | double | Float
`s` | char *, int | String (value and length)
`p` | cahr *, int | String with `\0` checks
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
