# AC_LIB - multi-purpose, modular c library, statically linked


## Contents:
* AC_STRING
* AC_VECTOR


## How to use a module?
First of all _"ac_lib.h"_ is just a wrapper for all the modules.\
Before you include it in your source files you have to define a macro for each module you want to include.\
For example, I want to include the _AC_STRING module_. Thus i'll define the following macro:
```
#define AC_LIB_STRING
```
then i can use the module after i include the _ac_lib.h_ wrapper.
```
#include "ac_lib.h"
```

## How to build

In this documentation i'll explain assuming you'll use cmake. If not do it your own way.
1. Clone the repository.\
1.1 modify the CMakeLists.txt file and change the variable called "BUILD_TESTS" to OFF.
2. run the configuration.sh file if you aren't on windows.\
2.1 if you are on windows then run this command which in the same directory as the CMakeLists.txt file:

```
cmake -S . -G "Ninja" .. -B "./build" -DCMAKE_BUILD_TYPE=Release
```
Note: in the above example i use the ninja build tool. You may not have it. Instead you could use something like
visual studio or makefiles or other options. Consult this
[link](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html).\
\
3. Now you have compiled the library and can use it.\
4. Copy the library file from build directory, and the header files from src into your own project and you're done.


## Structure of all modules:
Each module from AC_LIB contains a object type and a class.\
For example in the AC_STRING module, you have the _"ac_string_t"_ object type and the _"ac_string"_ class.
- _ac_string_t_ contains the characters data and the lenght.
- _ac_string_ class provides functions with which to process or use the _ac_string_t_ objects.

This structure provides safety and ease of use. Avoiding any unexpected or undefined behaviour
expected from manual use of string literals.


# AC_STRING functions
* Create
* Destroy
* Get
* Match
* Change

# AC_VECTOR functions
* Create
* Destroy
* Get
* Change
* Push
* Pop

## Documentation is provided in the header & source files for each module. Very clearly explained.
