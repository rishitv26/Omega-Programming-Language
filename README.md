# Omega Programming Language

The Omega Programming Language (Omega) is a language that is a child of C++. What do I mean? Omega was specifically created to simplify 
C++, and retain its key features like speed and efficiency. Omega also aims to add an extra layer of abstraction without reducing 
performance significantly, where things like strings can be a primary datatype. We also aim for compatibility with other languages, like 
custom compilation, and library usage from other languages.

Please note that this is a project by some low life middle schooler (now a highschool freshman), so please take these claims with a grain 
of salt.

## Syntax

The syntax of Omega is going to be a blend of many major languages, and maybe something new. All syntax specific info is listed below. 
Please note that not everything has been fully implemented, so this is more like a "things to be added" list.

### Variables

Every basic program must have some variable manipulation going on. Here is how you can do that in Omega:

```
int Variable : 8 ;comments are semicolons.
string str : "Strings are only double quotes"
; note that line terminating semicolons are not required.

str : "I am modifying the variable value"
int NewVar : Variable - 89 ;assignment to expressions.
```

There are currently 8 builtin/primitive datatypes. These include:
* int (integer)
* string (string)
* bool (boolean)
* point (pointer)
* double (double)
* list (list)
* dict (dictionary / map)
* array (array)

All of them are mainly straight forward, except for pointer. Pointers in Omega can hold a pointer to ANY givin type, or just a raw memory location.
Here are a few usage example usages for every type:

#### Integers
```
int integer : 9 ;; an integer that stores the variable 9.
integer : integer - 1 ;; decrementation
```
*** EXPERIMENTAL ***
The integer type is made to be dynamic, allocating only the amount of size that is needed. For example, the variable 'integer' would currently be of type int, but if you give it a value of a long, it will become a long.

#### Strings
```
string str : "Hello Sire" ;; a string that stores "Hello Sire".
str.slice(6, 9) ;; slice the string from index 6 - 9, inclusive.
```
A string in Omega will look like a c array of chars with builtin methods.

#### Boolean
```
bool george : true ;; a boolean with a value of true, or 1
george.toggle() ;; toggle the value from true, to false
```
A boolean has only 1 method, which is toggle.

#### Point
```
point ptr : x00AF ;; a pointer to a raw location in memory
ptr.readAs(INT) ;; read location like an integer.

int var : 3 ;; to point
string str : "Hello Madam"

point ptr2 : #var ;; points to the location of var.
point ptr3 : #str ;; points to a DIFFERENT type.

```
The pointer type is special, as it can point to ANY datatype, or object. Unlike where in language like C, or C++, it is not possible in common practice.
