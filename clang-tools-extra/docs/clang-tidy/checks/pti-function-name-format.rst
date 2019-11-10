.. title:: clang-tidy - pti-function-name-format

pti-function-name-format
========================

Checks for function name style mismatch.

PTI style states that all function must have a capitalized MODULE_ prefix
and a PascalCase function name. This includes all private and public function 
calls. Macros and function pointers are exempt from this rule.

.. code-block:: c

  void myFunction(void);        // Bad - Missing prefix and PascalCase
  void MODULE_MyFunction(void); // Good