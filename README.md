# AC_LIB - multi-purpose, modular c library

## Contents:
* AC_STRING

# AC_STRING functions
* Create
* Destroy
* Get
* Match
* Change

## Details on AC_STRING functions
* ### Create function:
Takes in a _"char * "_ aka a _"string literal"_.\
Outputs ac_string_t object.

* ### Destory function:
Takes in a _"ac_string_t"_ object.\
Clears, frees it and destroys it.

* ### Get function:
Takes in a _"ac_string_t"_ object.\
Doesn't modify the object.\
Returns _"const char * "_ aka _"const string literal"_.

* ### Match function:
Takes in two _"const ac_string_t"_ object.\
Doesn't modify either object.\
Returns _0_ for _'found'_ | _1_ for _'not found'_.

* ### Change function:
Takes in a _"ac_string_t"_ object, _"const char * "_ aka a _"cosnt string literal"_.\
Doesn't modify the _"const char * "_ primitive.\
Modifies the _"ac_string_t"_ object.


## Object & class provided
Each module from AC_LIB contains a object type and a class.\
For example in the AC_STRING module, you have the _"ac_string_t"_ object type and the _"ac_string"_ class.\
- _ac_string_t_ contains the characters data and the lenght.\
- _ac_string_ class provides functions with which to process or use the _ac_string_t_ objects.

This structure provides safety and ease of use. Avoiding any unexpected or undefined behaviour
expected from manual use of string literals.


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
