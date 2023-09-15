# Omega Programming Language

The Omega Programming Language (Omega) is a language that is a child of C++. What do I mean? Omega was specifically created to simplify 
C++, and retain its key features like speed and efficiency. Omega also aims to add an extra layer of abstraction without reducing 
performance significantly, where things like strings can be a primary datatype. We also aim for compatibility with other languages, like 
custom compilation, and library usage from other languages.

Please note that this is a project by some low life middle schooler (now a highschool freshman), so please take these claims with a grain 
of salt.

## Syntax

The syntax of Omega is going to be a blend of many major languages, and maybe something new. In general, we promote snake casing like in python, but Camel case will work fine. All syntax specific info is listed below. 
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
* int (integer)    --\
* string (string)    |
* bool (boolean)     |-- primary types
* point (pointer)    |
* double (double)  --/
* list (list)               --\
* dict (dictionary / map)     |-- secondary types (not yet thought out)
* array (array)             --/

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
ptr2 : #str ;; points to a DIFFERENT type.
;; $ptr2 stores what ptr 2 was pointing to
printline ($ptr2) ;; more on this later.

```
The pointer type is special, as it can point to ANY datatype, or object. Unlike where in language like C, or C++, it is not possible in common practice.
This can be used for high precision memory operations, and even better, a way to reference to ANY type.

#### Double
```
double decimal : 3.90 ;; set to a decimal, or a double
;; ----------------------------- EXPERIMENTAL:
double crazysmall : 10e-2 ;; set using scientific notation.
;; -------------------------------------------
```
The double type is how you would want to store any decimal. Floats are not a part of the language, but doubles can get any float-related job done.

### Builtin Utility Functions / Methods (BUF)
#### Referencing any imported function
Omega is planed to provide a variety of BUF's, and also keep the effieciecy as close to C++ as possible. To achieve this, functions imported from a module (more later) must be explicitly marked for compilation, in order to use them.
Here is an example:

```
import "file-location.omgm" ;; the file extension for a module
							;; file extension of omega executble: filename.omg
use function_in_module as fin; ;;<- semicolons are not neccessary, they are just treated as blank comments...

fin() ;; use function.
```

Using ```use``` and ```as``` make it easy to specify what functions should the compiler worry about, so the program can consume less memory, and thus increase performance.

#### Using printline()
The printline function, well, prints to the console, with a new line.
Its child, the print function, prints the word without the '\n'.

```
use printline; <- when any executable is compiled, the builtin.omgm (where the built-in stuff is contained) is automatically a dependency of the omega executable

string hello : "Howdy"
string yourname : "..."

print(hello); <- again, semicolons are optional.
print(" ");
print(yourname);
printline("!");
```

### Builtin Objects Represent Parts of the System.

There are some builtin objects in Omega, that represent some part of the system. These objects are called native objects, as they are native to the language. for example, the Heap Object, which controls the heap memory allocated for a program. More on memory specific items later.

```
use heap_memory as heap

;; make a variable in heap, and return pointer to it.
point heap_var = heap.allocate(POINT, x908) ;; var type, var value
printline($heap_var) ;; should print out '0x908'
```

note that there is no need to delete heap pointers, as that is done automatically when an executables terminates.


