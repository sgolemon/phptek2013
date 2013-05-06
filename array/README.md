Reading and Writing arrays

PHP arrays have no C counterpart, therefore we must always act on the underlying `zval*`, or the `HashTable*` which lies under that.  The following tables show the C API, and it's PHP equivalent for reference. `pzv` represents a `zval*` containing an Array (once you've called `array_init()`, that is).

Creating
---
C | PHP | Notes
--- | --- | ---
`array_init(pzv);` | `$pzv = array();` | `pzv` must be an already allocated `zval *`

Appending
---
C | PHP
--- | ---
`add_next_index_null(pzv);` | `$pzv[] = null;`
`add_next_index_boo(pzv, bv);` | `$pzv[] = (bool)$bv;`
`add_next_index_long(pzv, lv);` | `$pzv[] = (int)$lv;`
`add_next_index_double(pzv, dv);` | `$pzv[] = (double)$dv;`
`add_next_index_string(pzv, sv, cp);` | `$pzv[] = (string)$sv;`<br/>Duplicate `\0` terminated string `sv` into engine memory if `cp` is `1`, assume it already is if `cp` is `0`.
`add_next_index_stringl(pzv, sv, len, cp);` | `$pzv[] = (string)$sv;`<br/>Same as above, but explicitly specify length so that `\0` can appear in the string.
`add_next_index_zval(pzv, item);` | `$pzv[] = $item;`

Adding numerically indexed items
---
C | PHP
--- | ---
`add_index_null(pzv, idx);` | `$pzv[$idx] = null;`
`add_index_boo(pzv, idx, bv);` | `$pzv[$idx] = (bool)$bv;`
`add_index_long(pzv, idx, lv);` | `$pzv[$idx] = (int)$lv;`
`add_index_double(pzv, idx, dv);` | `$pzv[$idx] = (double)$dv;`
`add_index_string(pzv, idx, sv, cp);` | `$pzv[$idx] = (string)$sv;`<br/>See "appending" for details about `cp` and `len`
`add_index_stringl(pzv, idx, sv, len, cp);` | `$pzv[$idx] = (string)$sv;`
`add_index_zval(pzv, idx, item);` | `$pzv[$idx] = $item;`

Adding associatively indexed items
---
C | PHP
--- | ---
`add_assoc_null(pzv, key);` | `$pzv[$key] = null;`
`add_assoc_boo(pzv, key, bv);` | `$pzv[$key] = (bool)$bv;`
`add_assoc_long(pzv, key, lv);` | `$pzv[$key] = (int)$lv;`
`add_assoc_double(pzv, key, dv);` | `$pzv[$key] = (double)$dv;`
`add_assoc_string(pzv, key, sv, cp);` | `$pzv[$key] = (string)$sv;`<br/>See "appending" for details about `cp` and `len`
`add_assoc_stringl(pzv, key, sv, len, cp);` | `$pzv[$key] = (string)$sv;`
`add_assoc_zval(pzv, key, item);` | `$pzv[$key] = $item;`

---

The remaining APIs for reading, checking existence, and unsetting are notably more... annoying.  In all cases `ht` represents a `HashTable*` containing an Array.

Get a `HashTable*` from a `zval*`
---
```
HashTable *ht = Z_ARRVAL_P(pzv);
```

Checking for existence
---
C | PHP
--- | ---
`zend_hash_index_exists(ht, idx);` | `isset($ht[$idx]);`
`zend_hash_exists(ht, key, key_len);` | `isset($ht[$key]);`
`zend_hash_symtable_exists(ht, key, key_len);` | `isset($ht[$key]);`

In the APIs above, `zend_hash_index_exists` takes a long `idx` and will only look for numeric keys.  `zend_hash_exists` will _only_ search for string keys.  If you pass a numeric string (e.g. `"42"`), then `zend_hash_exists` will almost certainly fail, since it would have been added as a numeric key.  To work with `char *` keys which may contain numeric strings, use `zend_symtable_exists` instead.  This applies to all further `zend_symtable_*` APIs as well.

**Note: Unlike with the `add_*` API, string lengths used here _include_ the trailing `\0` character.  (e.g. `key_len` for "hello" would be `6`, not `5`)**

Unsetting
---
C | PHP
--- | ---
`zend_hash_index_del(ht, idx);` | `unset($ht[$idx]);`
`zend_hash_del(ht, key, key_len);` | `unset($ht[$key]);`
`zend_hash_symtable_del(ht, key, key_len);` | `unset($ht[$key]);`

Reading
---

Reading is performed by calling one of the following three functions and checking for a return value of `SUCCESS` or `FAILURE`.  The actual value will be a `zval**` returned by reference from the last parameter.

* `zend_hash_index_find(ht, idx, &ppzv)`
* `zend_hash_find(ht, key, key_len, &ppzv)`
* `zend_symtable_find(ht, key, key_len, &ppzv)`

**Note: The **`zval**`** is still attached to the array you pulled it from.  If you need to modify it, be sure to separate and/or copy it first.**
