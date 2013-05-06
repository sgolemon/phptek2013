Declaring constants

Macros for scalar types
---
* `REGISTER_LONG_CONSTANT(name, lval, flags)`
* `REGISTER_DOUBLE_CONSTANT(name, dval, flags)`
* `REGISTER_STRING_CONSTANT(name, strval, flags)`
* `REGISTER_STRINGL_CONSTNAT(name, strval, strlen, flags)`
* `REGISTER_NS_LONG_CONSTANT(ns, name, lval, flags)`
* `REGISTER_NS_DOUBLE_CONSTANT(ns, name, dval, flags)`
* `REGISTER_NS_STRING_CONSTANT(ns, name, strval, flags)`
* `REGISTER_NS_STRINGL_CONSTNAT(ns, name, strval, strlen, flags)`

Flags | Meaning
--- | ---
`CONST_CS` | Case-Sensitive
`CONST_PERSISTENT` | Persistent across requests.<br/>Generally, use this flag from MINIT, but not from RINIT

**Note: When registering non-persistent string constants, you'll need to allocate the value in engine memory such as in the following.**

```
PHP_RINIT_FUNCTION(myext) {
  REGISTER_STRING_CONSTANT("CONST_FOO", estrdup("BAR"), CONST_CS);
  return SUCCESS;
}
```
