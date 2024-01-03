# Modularization of the code

## .h files and .cpp files

The code is modularized into .h files and .cpp files. The .h files contain the class definitions and the .cpp files contain the class implementations. The .h files are included in the .cpp files using the `#include` preprocessor directive.

### Header guards

The .h files contain header guards to prevent multiple inclusions of the same file. The header guards are defined using the `#ifndef`, `#define`, and `#endif` preprocessor directives.

* `#ifndef` checks if the header guard has not been defined.
* `#define` defines the header guard.
* `#endif` ends the header guard definition.

Header guards do the following:

* Prevent multiple inclusions of the same file.
* Prevent redefinition of the same class, function, or variable.
* Prevent circular dependencies between classes. That means that class A cannot include class B, and class B cannot include class A.

### namespaces

The .cpp files contain the class implementations. The class implementations are defined in the `ExchangeCore` namespace. The `ExchangeCore` namespace is defined in the `ExchangeCore.h` file.

