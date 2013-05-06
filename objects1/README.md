Simple OOP in PHP Extensions

Accessor Flags
---
Flag | Notes
--- | ---
`ZEND_ACC_PUBLIC` |
`ZEND_ACC_PROTECTED` |
`ZEND_ACC_PRIVATE` |
`ZEND_ACC_CTOR` | Only apply this to the __construct method
`ZEND_ACC_DTOR` | Only apply this to the __destruct method
`ZEND_ACC_STATIC` | Should not use getThis()
`ZEND_ACC_ALLOW_STATIC` |  **DEPRECATED** Instance method which may be called statically

