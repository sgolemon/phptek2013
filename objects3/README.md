Complex OOP in PHP

This transforms the class from `objects1` into a custom PHP Object Type.
Instead of (optionally in addition to) storing properties in the userspace
accessible properties table, we can store arbitrary C data in the object structure
itself for faster and cleaner access.

The next directory `objects3` builds on this by adding other custom handlers.
