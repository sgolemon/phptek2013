Complex OOP in PHP continued

This adds custom handlers for property access to the object from `objects2`.
One could also accomplish what this does by using __get/__set magic methods,
this is just meant to highlight a common set of handlers.

See Zend/zend_object_handlers.h for a complete list of object handler methods in **the best documented file in the PHP source tree, PERIOD**.
