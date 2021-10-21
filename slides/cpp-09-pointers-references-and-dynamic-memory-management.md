## 1. Dynamic Memory Management

- **So far:** only *"static"* memory management
  - i.e. variables for values, arrays of fixed size
- Memory for `static` data types is reserved at compile time

- **What if memory requirements are unknown at compile time?**
  - Need a way to **acquire** arbitrary **amounts** memory
  - Need a way to **handle** arbitrary **blocks** of memory
    
---

## 2. Memory

- Device has main memory *(RAM, Random Access Memory)*
  - **RAM** holds all data needed to run the application, i.e. code, variables, data
  - **RAM** can be swapped to hard drive on PCs

- The smallest addressable unit of memory is a `byte` (on most systems)
- i.e. every byte of memory receives an **address** *(= consecutive numbering)*
  - Addressing depends on machine *(CPU)*
  - Also on the operating system
  - **DOS:** 20bit addresses
  - **Windows95 and later:** 32bit addresses per process (= program)
  - **64-bit systems:** 64 bit addresses (why?)
    
---

## 3. Pointers

- Memory addresses are just `unsigned integer` values
  - It is possible to store a memory address in a variable! &#8594; Pointers

- **But:** memory address points only to a single byte
  - It is only useful if you know the size and type of data at that address
    &#8594; Pointers need to have types!
    
---

## 4. Declaring Pointers
````c++
int* piNumber;			// pointer to int
int *piNumber1, *piNumber2; 	// two int pointers

void* pVoid;				// can point to anything
````
<sup>*The example above declares pointers to ints*</sup>
- `Pointers` are `variables` that store memory addresses
- You can declare `pointers` for any data type *(including own types and pointer types!)*
- `void*` is a special type; it makes no statement about type of data pointed to

- Declaring `pointers` does **not** reserve any memory for value, only memory for memory addresses!

---

## 5. Declaring Pointers - 2
````c++
int* piNumber = 0;   // typical init
````

- Initial value of `pointer` is *(possibly)* random
- `pointers` that point **“nowhere”** can be assigned the value **0**
  - **old-fashioned:** `NULL` *(#define NULL 0)*
  - `"Null-Pointer"`
  - `0` is – in theory – a valid memory address, but it is never used in user programs
  - `nullptr`: C++ 11 and higher (why?)

````c++
int* piNumber = 4;		// Error! int* is not int!
int* piNumber = (int*) 4;	// type cast – ok (syntactically)
int** piNumber;			// ok! pointer to pointer to int 
````
- `Pointers` are **independent** data types!

---

## 6. Adress-Operator &
````c++
int i = 10;
cout << i << endl;	// print value of i
cout << &i << endl;	// print address of i

int* pi = &i;		// assign address of i to pointer

float f = 1.0f;
pi = &f; 		// Error – type mismatch int* vs. float*
````
#### **How to obtain legal values for pointers (except 0, which is always valid)?**

- **Address-Operator** `&` gives address of any variable
  - In fact, even of functions (more later!)
  - Unary operator
    - operators that act upon a single operand to produce a new value
  - **Do not confuse** with binary `AND &` (which is a binary operator)

---

## 7. Sizeof - Operators

````c++
cout << sizeof (double) << endl;

char c;
cout << sizeof (c) << endl;

bool abBoolArray[12];
cout << sizeof (abBoolArray) << endl;
````
- `sizeof` gives us size of a data type in bytes
- `sizeof` is a built-in C/C++ operator *(not a function!)*
- It works with both type names and variable names
- Static information, i.e. evaluated at compile time
- It can therefore not be used to determine size of (dynamic) arrays and such
- The size of a `pointer` is always the same *(WIntel: 4 bytes)* regardless of `pointer` type!

---

## 8. Dereferencing Pointers
````c++
int i = 10;
int* pi = &i;

cout << pi << endl;		// show memory address
cout << *pi << endl;		// show value

*pi = 666;			// manipulate value
*pi++;				// ...some more
cout << i << endl;		// this affects i!
````
- Operations with `pointer` variable operate with `pointer` value
  - i.e. the memory address!
- *How do we access the memory the pointer points to?*

- `pointersO are dereferenced by putting `*` in front of the pointer name
- The operation now accesses the value pointed to

- You cannot dereference a pointer of type `void*` (why?)
- Dereferencing of `Null-Pointer` (or pointer with invalid value) causes crash (why?) 
- – but not always (why?)

---

## 9. Casting Pointers
````c++
float f = 0.1f;
float* pf = &f;

int* pi = (int*) pf;
cout << *pi << endl;

void* p = pf;
cout << (float*) p << endl;
````
- `pointers` can be type cast like any other data type
- `void pointers` are compatible with any other `pointer` type without a type cast
- again: `void pointers` **cannot** be dereferenced and must be cast to a valid type first

---

## 10. Arrays vs. Pointers
````c++
int aiArray[20] = {0};
cout << aiArray << endl;			// prints address!
cout << &aiArray << endl;			// same here
cout << &aiArray[0] << endl;		// and here
````
<sup>Example that `arrays` are `pointers`! (full stop)</sup>

- The `array` variable stores `pointer` to first `array` element
- It's equivalent to address of first element 
- Use of Address-Operator on `array` variable is **not** necessary
- Any suitable `pointer` can store address of `array`  
<sub>aiArray</sub>
![image](https://user-images.githubusercontent.com/7360266/120779284-33e56480-c527-11eb-9f6c-5d2f99044b4c.png)


---

## 11. Array vs. Pointers - 2
````c++
int aiArray[20] = {0};
int* pi = aiArray;

pi[2] = 5;
cout << aiArray[2] << endl;
````
- `[ ]` - operator can be used on **any** `pointer`
  - **Remember:** no bounds check!

- `[ ]` - operator is a way to dereference a `pointer`

___

## 12. Pointer Arithmetic 
````c++
int ai[5] = {0, 1, 2, 3, -1};	
int* pi = ai;

cout << *(pi+2) << endl;
````
- Can do calculations with `pointers`!
  - Very useful mainly for `arrays`, but possible with any pointer but void pointers!
<br></br>
    
**Valid pointer operations:**
- `pointer` + `int`
- `pointer` – `int`
- `pointer++`  or  `++pointer`
- `pointer--`  or  `--pointer`
- `pointer` – `pointer`  for pointers of same type

- All `pointer` operations use size of underlying data type
  - Adding 2 to an `int*` increases the address by `2*sizeof(int)`
  -  i.e. by 8 bytes, not by 2!

---

## 13. Pointer Arthmetic - 2
````c++
	int ai[5] = {0, 1, 2, 3, 4};	

	int* pi = ai;

	while(pi < &ai[5])
	{
		cout << *pi << endl;
		pi++;
	}
````
- An `array` is really just a set of sequentially stored values of the same type!
- `Pointers` can be compared using `==`, `!=`, `<`, `>`, `>=` and `<=`

---

## 14. Pointer Arithmetic - 3
````c++
int ai[5] = {0, 1, 2, 3, 4};	

cout << 3[ai] << endl;
cout << 3["Hello"] << endl;
````
- `p[n]`  is the same as  `*(p + n)`
- Which means that `p[2]` is the same as `2[p]`
---

## 15. References
````c++
int i = 10;
int &ri = i;	// ri points to i (note: no address-op!)

ri = 11; 	// note: no dereferencing
cout << i << endl; // i is now 11
````
- Introduced in `C++`
- Similar to `pointers` but:
- `&` instead of `*`
- No pointer arithmetic
- References behave like normal variables, but are pointers inside!
- Must always point to valid target
  - i.e. must be initialized when declared
  - Cannot be assigned 0
  - Cannot change their target
  - No need to dereference
  - Does not support `[ ]` - operator

---

## 16. Call by Reference
````c++
void Swap(int* piA, int* piB)
{
	int iTemp = *piA;
	*piA = *piB;
	*piB = iTemp;
}

int i=3, j=5;
Swap(&i, &j);
````
- `Parameters` as `pointers` or `references`
- Cannot pass values to function any more, must pass `variables`
- Function manipulates original `variables`!

---

## 17. Out-Parameters
````c++
void Divide(int iOp1, int iOp2, int& po_riResult, int& po_riRest)
{
	po_riResult = iOp1 / iOp2;
	po_riRest = iOp1 % iOp2;	
}

...

int iResult, iRest;
Divide (10, 3, iResult, iRest);
````
- Call-By-Reference-Parameters can be used to return values from functions
  - i.e. bypass the restriction of having only one return value

---

## 18. Out-Parameters - 2
````c++
void Divide(int iOp1, int iOp2, int* po_piResult, int* po_piRest = 0)
{
	*po_piResult = iOp1 / iOp2;
	if(po_piRest)
	{
		*po_piRest = iOp1 % iOp2;
	}
}
````
- The caller must declare `variables` that receive results
- **Attention:** `parameters` could be used for both input and output!
  - `parameters` often classified as in, out, inout
  - Use comments / coding conventions to make this clear to the user!

- You can use `pointers` to make `out-parameters` optional, as seen in the example above

---

## 19. Words of Warning
- Never return a `pointer` / `reference` to a local `variable`!
- Remember that `pointers` survive even if their targets are destroyed!
  - If the target goes out of scope
  - If the target is deleted manually

- There is absolutely no way to tell if a `pointer` is still valid or still pointing to the original object
- You must keep track of object life cycle manually!


---

## 20. Const
````c++
const int i = 10;
i = 5;				// Error – const object!
````

- `variables` can be declared as const
  -  This means they cannot be modified after the declaration
  - It can also be done with `parameters`
    
---

## 21. Const References

- `const` often used to make per-reference `parameters` constant
  <br></br>
- #### **Why?**
    - `parameter` cannot be modified!
  - Function behaves as if *call-by-value*
  - But `parameters` are **not** copied!
<br></br>
- Copying of large `parameters` (`strings`, `classes` etc. is slow)
- Copying of same data types is **not** possible (more later)
- Some things have to be passed per value

- `arrays` are always passed per reference! (why?)
  - **Dangerous!** function could accidentally overwrite data

- If a function should not modify a per-reference `parameter`, it should not be able to!


---

## 22. Const References - 2
````c++
void PrintArray(const int ai[5])
{
	for(int i=0; i<5; ++i)
	{
		cout << ai[i] << " ";
	}
	cout << endl;
}

...
int blubb[5] = {0};
PrintArray(blubb);
````
<sup>**How can `PrintArray` be modified to support `arrays` of arbitrary size?**</sup>

---

## 23. Call By Reference - Why?

#### Function wants to manipulate `variables`, not values
  - For instance swap-function
<br></br>
#### Out-Parameters – ability to have more than one return parameter
  - Can even have optional return parameters
    <br></br>
#### Can make normal parameters optional
  - Just pass `Null-Pointer` if parameter is not needed
    <br></br>
#### Pass large parameters to function without having to copy
  - Usually passed as const-reference
  - Copy is slow
  - Sometimes copy is not possible for different reasons (more later!)


---

## 24. Malloc and Free
````c++
int* pi = (int*) malloc(4 * sizeof(int));
pi[3] = 555;
````
- `malloc` reserves given number of bytes (allocation)
  - Use `sizeof()` to determine number of bytes needed for a data type
  - Returns `void*` - need to cast
- Can be used to reserve `arrays`!
  - **Remember:** `[ ]` can be used on any pointer!
    
````c++
free(pi);
pi = 0;	    // pi is invalid now; good idea to set it to 0
````
- Frees the memory again

---

## 25. New and Delete

- `C++`replaces `malloc` and `free` by operators `new` and `delete`
  - `new` and `delete` are operators (implications – later ☺)
  - While `malloc` and `free` were functions

- There is actually 4 operators:
  - `new`
  - `new [ ]`
  - `delete`
  - `delete [ ]`
    
---

## 26. New and Delete - 2
````c++
int* pi = new int;		// a single int
*pi = 666;
delete pi;

int* piArray = new int[1000];
...
delete [] piArray;
````
- `new` creates a single instance
- `new [ ]` creates an `array` of instances

- If you use `new [ ]`, you have to use ´delete [ ]`
  - There is no warning or error, but bad things may happen if you don‘t!
  - (`new` / `delete` calls one constructor / destructor; `new [ ]` / `delete [ ]` calls as many constructors / destructors as needed)
    
---

## 27. Detecting Memory Leaks
````c++
#include <crtdbg.h>
...
_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);

... put application source code here ...

_CrtDumpMemoryLeaks();
````

- Enables memory leak detection
- Will dump memory leaks at shutdown in debug output
- To set a breakpoint to an allocation, do this:
  - Program must be deterministic for this to work!
    
````c++
[3576] Dumping objects ->
[3576] {387} 
[3576] normal block at 0x00933110, 4 bytes long.
[3576]  Data: <    > CD CD CD CD 
[3576] {386} 
[3576] normal block at 0x009330E0, 4 bytes long.
[3576]  Data: <    > CD CD CD CD 
[3576] {385} 
[3576] normal block at 0x009330B0, 4 bytes long.
[3576]  Data: <    > CD CD CD CD 

[3576] Object dump complete.
````
# <center>&#8595; </center>

````c++
_CrtSetBreakAlloc(387);
````

---

## 28. Asserts
````c++
#include <assert.h>
...
assert (pMyPointer != 0);
````
- `assert` will raise an exception *(i.e. “crash” the program)* if given condition proves wrong
- `asserts` are removed in Release Version *(How?)*

- `asserts` make errors easier to detect!
- Use them often and everywhere!

---

## 29. Debug Output
````c++
OutputDebugString(“Hello”);
````

- Writes `strings` to the debug output
- Appears in visual studio output window *(if debugger is attached)* and external debug viewers

- Only prints `strings`, use `sprintf()` to create more sophisticated outputs

---

## 30. Dude, Where is My Variable?
- `Variables` in `C` or `C++` can be in 3 different places:

  - **On the stack:** local `variables`, function `parameters`
  - **On the heap:** dynamically allocated vars, `new` or `malloc`
  - **In a special memory area:** global variables

 -Member `variables` of classes/structs are located inside their parent object

 ---

## 31. The Stack


|   |
|---|
| local variables of bar(): a, b|
| bar()‘s return address to foo()  |
| parameters for foo: i, j  |
|  foo()‘s return address to main() |

# <center>&#8593;</center>

  ```c++
void main()
```

### calls

```c++
void foo(int i, int j)
  ```
###  calls
```c++
void bar()
{
   int a, b;
}
```
- Working memory (local `vars`, `parameters`, return adresses)
- Fixed maximum size
- Can allocate arbirary-sized blocks…
- But ony free in reverse order *(like a stack of plates; cannot pull something from the middle)*
- Very efficient
---

## 32. The Heap

![image](https://user-images.githubusercontent.com/7360266/120779114-0993a700-c527-11eb-8005-f539f7dc55e9.png)


- Special Memory Area, managed by the Runtime libraries
  - Can allocate Arbitrary-sized memory blocks
  - Can free memory blocks in any order
  - May lead to fragmentation!
- **Internal function:**
  - Holds a list of used blocks
  - Less efficient that stack
    - Needs to check list for empty blocks
    - Needs to select best block (trying to prevent fragmentation)
- Gets more memory from the OS if necessary (and possible)

---

## 33. Global Memory

- Global `variables` are in a special memory area that is created before the program starts and freed after the program has ended

- Location of this special area is implementation dependant
  - Typically a special segment (“data segment”) that is linked into the executable
  - That is why global `variables` are pre-initialized and do not have "random" values

- It is also possible to put a `variable` at a fixed memory address, if you know what you are doing
- Typically done to map special hardware I/O registers etc.

---
