## 1. Structs
````c++
struct TFoo
{
	int iCount;
	char* pcString;	
} MyFoo;
````
````c++
struct TFoo
{
	int iCount;
	char* pcString;	
};

TFoo xMyFoo;
TFoo* pxMyFooPointer = new TFoo;
````
- Declares new compound data type
  - Can be used like any other data type (as `variables`, `pointers`, `arrays`, `parameters`, `return values`)
 - Size equals at least size of compound members
- **Attention:** may be larger due to alignment issues

---

## 2. sizeof(structs)
#### **Size 8**
````c++
struct TFoo
{
  int  iInt;
  char cChar;	
};
````
<br></br>
#### **Size 12**
````c++
struct TFoo
{
    char cChar;
    int  iInt;
    char cChar2;	
};
````
<br></br>
#### **Size 8**
````c++
struct TFoo
{
  int  iInt;
  char cChar;
  char cChar2;	
};
````
<br></br>
#### **Size 6**
````c++
#pragma pack(1)
struct TFoo
{
  int  iInt;
  char cChar;
  char cChar2;	
};
````

- Ordering of members is preserved by compiler
- Compiler will pump up size to multiple of 4 by default (4-byte alignment for array elements)
- Compiler will align members to 4-byte boundaries by default
  - i.e. ordering of members will affect the size of the struct!
  - **Rule of thumb:** if order does not matter, sort from big to small, use `chars` to fill holes
- Alignment can be turned off using `#pragma` pack *(compiler dependant!)*

---

## 3. Access to Struct Elements

```c++
struct TFoo
{
	int iCount;
	char* pcString;	
};

TFoo xMyFoo;
TFoo* pxFooPtr = new TFoo;
```
# <center> &#8597;</center>
````c++
xMyFoo.iCount = 0;
xMyFoo.pcString = “OK!”;

(*pxFooPtr).iCount = 0;
(*pxFooPtr).pcString = 0;

pxFooPtr->iCount = 0;
pxFooPtr->pcString = 0;
````

- Access to `struct` elements using `.`
- Access to `struct` pointers either by:
  - `dereferencing` and `.` *(attention: precedence!)*
  - Or using operator `->` *(same as *(exp).)*
    
---

## 4. Unions

```c++
struct TCollisionObject
{
    Type m_eType;
    union Parameters
    {
        float m_fRadius; // if type = circle
        TRect m_xRect;   // if type = rect
    } m_xParameters;
};
```

````c++
enum Type
{
    Circle,
    Rectangle
};

struct TRect
{
    int x, y, w, h;
};
````

````c++
TCollisionObject x;
x.m_eType = Circle;
x.m_xParameters.m_fRadius = 5;
````

- `struct` where all members occupy the same memory
  - i.e. size of union = size of largest member
  - Often used to conserve space if members are never used at the same time
    
---

## 5. Bitfields
````c++
struct Date 
{ 
    unsigned nWeekDay : 3;  // 0..6 (3 bits) 
    unsigned nMonthDay : 6; // 0..30 (6 bits) 
    unsigned nMonth : 5;    // 0..11(5 bits) 
    unsigned nYear : 8;     // 0..100 (8 bits) 
}; 
````

- Special use of `structs` / `unions`
- Can be used to declare data types smaller than `integral` types *(i.e. < 8 bit)*
  - Specify signed/unsigned for each member*
  - e.g. 1 bit signed can only store 0 or -1 (2-Complement!)
and size in bits
- Can be accessed like normal members
   - **But:** do not have adresses, i.e. cannot point to them
    
---

## 6. Bitfields - 2
````c++
struct Date 
{ 
    unsigned nWeekDay : 3;  // 0..7 (3 bits) 
    unsigned nMonthDay : 6; // 0..31 (6 bits)
    unsigned : 0;           // Force alignment
    unsigned nMonth : 5;    // 0..12 (5 bits) 
    unsigned nYear : 8;     // 0..100 (8 bits) 
}; 
````
- **Careful:** Ordering inside `struct` is not guaranteed
  - *(Microsoft: order is same as in struct, starting at the lowest bit)*
- Can specify size of 0 bits to force alignment to next machine word
  - Whatever a machine word is on your machine
    
---

## 7. Principles of Object Orientation

- Forming `classes`

- Data hiding

- Inheritance

- Polymorphism

---

## 8. Declaring a Class
````c++
class CVector
{
	....
};
````
- Keyword `class` + `arbitrary` class name
  - Note semicolon!
  - Declares a new type; does not reserve memory
  - Can be done anywhere
  - It is usually done in header file 
  - **Rule:** 1 `class` = 1 `header`
  - Can nest `classes`, i.e. declare a class inside another class
    
---

## 9. Class Members
````c++
class CVector
{
	void Normalize(); 
	float x, y, z;
};
````
<br></br>
#### **Classes have members:**
- Data members or member variables
- Member functions
- **Remember:** OO = union of data and functions!

---

## 10. Data Hiding

- Some members should not be accessible from the outside!
  - `functions` or `variables` which are only used internally

- **Why?**
  - Reduces complexity for the reader (blackbox-principle, need-to-know-principle)
  - Prevents user from breaking functionality by calling internal functions / modifying internal values
    
---

## 11. Data Hiding - 2
````c++
class CFoo
{
public:
	int m_iNumber;
private:
	void Foo();
       void Bar();	

protected:
	int m_iEntries;

public:
	void Blubb();

}
````
- **Public**
  - Accessible to everyone; even from the outside  
    <br></br>
 - **Protected**
  - Not accessible from the outside
  - Accessible from own member `functions` and derived `classes` *(later!)*  
    <br></br>
- **Private**
- Not accessible from the outside
- Not accessible from derived `functions`
- Only from own `functions`

---

## 12. Data Hiding - 3
```c++
class CCircle
{
public:
	void SetRadius(float fValue) { m_fRadis = fValue; }
	float GetRadius() const      { return m_fRadius; } 	
private:
	float m_fRadius;
};
```
- **Best practice:**
- Make data as private as possible!
- Almost never use public (error-prone!)
- Use protected if derived `classes` need access
- Use private otherwise
  <br></br>
- **Accessor methods:**
- a.k.a. `Get/Set-Methods`, `Getters`/`Setters`
- Pake data private
- Provide public (or protected) methods to read / write data 

---

## 13. Data Hiding - 4
````c++
void SetRadius(float fValue) 
{ 
	assert(fValue >= 0);

	if(fValue >= 0)	{ m_fRadis = fValue; }
	else		{ m_fRadius = 0; }
}
````
- **Accessors, advantages:**
- Can do sanity checks when modifying value
- Can enforce constraints on value
- Can make variable read-only (`provide`, `Get()`, but no set
- Can change `class` internals without changing interface
<br></br>
- **Accessors, disadvantages:**
- More work
- Hard to see if `Get()` *returns* value or *calculates* value

---

## 14. Const Member Functions
````c++
class CVector
{
	float x, y, z;
	
	void Print() const
	{
		cout << x << “ “ << y << “ “ << z << endl;
	}
}
````

- Member functions can be declared as `const`
- It causes all data members to be treated as `const` *(i.e. they are read-only)*
- **Rule:**
  - `const` is for your own safety!
  - Try to make `functions` `const` whenever possible!
    
---

## 15. Class Member Functions - 2
````c++
class CVector
{
	float x, y, z;
	
	void Print() const;
};
````
````c++
void Print(const CVector& rVector)
{
	rVector.Print();
}

const CVector xVector;
xVector.Print();
````

- `const` function promises not to modify its `class` instance

- Can only call `const` member functions **if** `variable` is `const` or is a `const` reference *(often call-by-const-reference)*
- `const` functions can only call `const` functions

___

## 16. Mutable
````c++
class CCircle
{
private:
    float        m_fRadius;
    mutable int  m_iAccessCounter;  // counts access to radius
public:
	
    float GetRadius() const
    {
        m_iAccessCounter++;  // const function, but mutable member
        return m_fRadius;
    }
};
````
- `mutable` members can be modified even if the `object`/function is const
use carefully; bypasses const checks!
useful e.g. for
access counters (like the example
caches (cache and reuse recent calculation results)

---

## 17. Volatile
```c++
volatile int i;	// i must be read from memory when accessed
```
- Exists since `C` (… and does not really belong in this context, but still…) states that a `variable` may change outside the context of the program
  - i.e. it cannot be cached in a register and must be read from memory every time
- **It is used for:**
  - Memory-Mapped Hardware Ports
  - Memory shared between Threads/Processes

---

## 18. Constructors
```c++
class CVector
{
    float x, y, z;
	
    CVector()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    void Print() const;
};
```
- `constructors` are special functions that are called automatically when an object is created
  - Same name as class
  - No return type *(not even void!)*
  - May have parameters

- Typically initializes members of the object, allocate memory


---

## 19. Constructors - 2
```c++
class CVector
{
    float x, y, z;
	
    CVector(float X, float Y, float Z)
    {
        x = X;
        y = Y;
        z = Z;
    }

    void Print() const;
};

...

CVector v(1.0f, 0.0f, 0.0f);

CVector* p = new CVector(1, 0, 0);
```

- **If no `constructor` exists:** 
  - `C++` creates one for you, *(default constructor)*

- **If a `constructor` with parameters exists:**
  - You must provide the parameters when constructing the object
  - A default `constructor` is no longer created *(but you are still free to write one)*

---

## 20. Constructors - 3
```c++
class CVector
{
    float x, y, z;
	
    CVector(float X, float Y, float Z) : x(X), y(Y), z(Z)
    {
    }
};
```
- Instead of setting members in the body of a `constructor`, you can use an `initializer list`
- `Initializer list` is like a `constructor` call *(where primitive types are assumed to have a constructor)*
- `Initializer` list may be more efficient than initializing in the body or even required in some cases *(see next part)*

---

## 21. Constructors - 4
```c++
class CCounter
{
public:
    CCounter(int iStartValue) : m_iCounter(iStartValue) {}
    int m_iCounter;
};

class CWord
{
public:
    CWord() : m_xCounter(0) {}    // MUST initialize m_xCounter this way

    CCounter   m_xCounter;	
};
```
- Initializing a member in the `initializer list` is **required** if that member is of a `class` type with no parameterless `constructors`
- If there is a parameterless `constructor` and you do initialize the member in the `constructors` body, you initialize twice! *(no problem, but inefficient)*

---

## 22. Destructors
```c++
class CWord
{
    CWord(int iLength)
    {
        m_pcString = new char[iLength];
    }

    ~CWord()
    {
        delete [] m_pcString;
    }

   char* m_pcString;
};
```
- `destructor` is a special function called automatically when an object is destroyed
  - It has the same name as `class`, with `~` in front
  - It has no return type *(not even void!)*
  - It may not have parameters
  - **There can be only one `destructor!`**
- Typically cleans up, deallocates memory, undoes stuff the `constructor` has done

---

## 23. Static Data Members
```C++
class CCircle
{
	static int ms_iCircleCount; 
}
```
```c++
int CCircle::ms_iCircleCount = 0; 
```
- Are not bound to an instance
 i.e. shared by all instances

- Static members are effectively global variables, but inside the namespace of the `class`
- Must be declared and initialized in a `c++` file
- **Otherwise:** linker error!


---

## 24. Static Data Members- 2
```c++
class CCircle
{
	static int ms_iCircleCount; 
}
```
```c++
CCircle::ms_iCircleCount = 666;
CCircle xMyCircle;
xMyCircle.ms_iCircleCount = 0;	// Attention: same Variable, overwrites 666
```
- Static members are not bound to an instance, i.e. can be accessed using their full name *(provided they are not private or something)*
- They can also be accessed like normal members
- Member functions can access them like normal members

---

## 25. Static Data Members - 2
```c++
class CCircle
{
	static int ms_iCircleCount;

	static void IncrCount()
	{
		ms_iCircleCount++;
	} 
};
```
- Can be accessed from any member function
- Obeys protection modifiers

---

## 26. Static Member Functions

- Can be called directly using full name *(without an instance!)*
- Can still be called on instances
- Can use static members *(data + functions)*, but not normal members

---

## 27. Excursion: Static

- `static` has no less than **4** meanings in `C++`

- Static member functions (C++)
- Static data members (C++)
- Static global functions (C)
- Become file-local

- **Static local variable  (C)**
  - Effectively become global; value survives across calls
  - Use still restricted to function scope
  - No name clashes with outside

---

## 28. Classes in .h and .cpp
```c++
class CCircle
{
public:
	int m_iRadius;

	CCircle() 		{ m_iRadius = 0; }
	CCircle(int r) 		{ m_iRadius = r; }
	int GetRadius() const	{ return m_iRadius; }
};
```
- **Version 1:** Everything in header file

- Functions that are defined inside a `class` declaration are always considered `inline functions`
  - i.e. if functions has a body inside the `class` declaration, no code is generated for the obj file
  - Keyword inline is **not** necessary


---

## 29. Classes in .h and .cpp - 2

#### Circle.h
```c++
class CCircle
{
public:
	int m_iRadius;

	CCircle();
	CCircle(int r);
	int GetRadius() const;
};
```

#### Circle.cpp
```c++
#include “circle.h”

CCircle::CCircle() { 
  m_iRadius = 0; 
}
CCircle::CCircle(int r) {
  m_iRadius = r
}
int CCircle::GetRadius() const {
  return m_iRadius;
}
```
- **Version 2:**
  - Function and data member declaration in header file
  - Function definition in source file

- The ource file **must include a matching header file**
- The ource file **must use fully qualified names of functions for definition** 
  - But you can use short names inside the functions code

---

## 30. Classes in .h and .ccp - 3

#### Circle.h
```c++
class CCircle
{
public:
	int m_iRadius;

	CCircle();
	CCircle(int r);
	int GetRadius() const;
};

inline CCircle::CCircle() 		{ m_iRadius = 0; }
inline CCircle:: CCircle(int r) 		{ m_iRadius = r; }
inline int CCircle::GetRadius() const	{ return m_iRadius; }
```
- **Version 3:**
  - Functions inlined; but defined outside of class body
  - Matter of taste: keeps `class` body *“clean”*
  - Must use inline keyword now
  - Must use fully qualified function names


---

## 31. Classes in .h and .cpp - 4

#### Circle.h
```c++
class CCircle
{
public:
	int m_iRadius;

	CCircle();
	CCircle(int r);
	int GetRadius() const;
};

#include “circle.inl”
```

#### Circle.inl
```c++
inline CCircle::CCircle() { 
  m_iRadius = 0; 
}

inline CCircle::CCircle(int r) {
  m_iRadius = r
}

inline int CCircle::GetRadius() const {
  return m_iRadius;
}
```

- **Version 4:**
  - Put definition into inline file *(e.g `*.inl` – there is no standard extension)*
  - Keeps header completely clean
  - Header must include **inline file**
  - Must use inline keyword **now**
  - Must use **fully qualified function names**

---

## 32. Classes in .h and .cpp - 5

- **Version 5: Mix and Mingle!**

- Can and should mix all versions
- Inline files are a matter of taste – some like them, others don’t
  - i.e class would consist of header, source and inline file
- Small functions should be inlined
  - i.e. must go to the header or an inline file
- Larger functions should go to the `cpp` file

---

## 33. Class Forward Declaration
```c++
#include “Mouse.h”

class CCat
{
    void Catch(CMouse m);
};
```

```c++
#include “Cat.h”

class CMouse
{
    void FleeFrom(CCat c);
};
```
- `Classes` can be **forward-declared** just like `functions`
- They are sometimes necessary when two classes need each other, because a **bidirectional include** does not work!

---

## 34. Class Forward Declarations - 2
```c++
class CMouse;

class CCat
{
    void Catch(CMouse& m);
};
```
```c++
class CCat;

class CMouse
{
    void FleeFrom(CCat& c);
};
```

- **Forward declaration:** `class` `<classname>`
- Forward sufficient to declare `pointers` or `references` to this `class`
- It is **not sufficient** if you need to use `members` *(member declaration missing)*
- It is **not sufficient** if you need to declare a `member` per value

---

## 35. Class Forward Declarations - 3

- Try to avoid `includes` in **include files**
  - `include` structure grows exponentially
  - It increases compile times and makes dependency structure unclear
- Use **forward declarations** whenever possible, unless classes need to declare or pass other `classes` per value *(you should pass classes per reference most of the time anyway!)*

---

## 36. Friend Classes
```c++
class A
{
	...
	friend class B;		// give class B access to private members
};

class B
{
	...
};
```

- Can declare another `class` as a **friend**
- Acts as a forward declaration for that `class`
- Is one-way *(i.e. **B** is friend of **A**, but **A** is not fried of **B**)*	
- Grants `friend class` access to **all** members, ignoring protection modifiers
- Make sure you don’t use it too often, it destroys the data hiding mechanism

---

## 37. Friend Functions
```c++
class A
{
	...
	friend void foo();     // give void foo() access to private members
};

void foo()
{
}
```
- It is also possible to declare another `function` as a friend!
  - It works with *global* and *member* `functions` 
  - And operators count as functions!
- Grants the `friend function` full access to private/protected members
- Counts as a `function` forward declaration

---

## 38. Struct vs. Class
```c++
struct CFoo
{
	....
}
```
# &#11021;

```c++
class CFoo
{
public:
	....
}
```
<sup> *The examples above are equal to each other* </sup>

- **C++:** `classes` and `structs` are the same
- `structs` can have member `functions`, `constructors`, `operators` etc!
- Can use *public*, *protected*, *private* inside a `struct`
- **Only difference:** `struct` members are **public by default**

---

## 39. This-pointer
```c++
class CPoint
{
    int x,y;

    void CPoint()
    {
        x = y = 0;
        Foo();
    }

    void Foo() {...}
};
```
```c++
class CPoint
{
    int x,y;

    void CPoint()
    {
        this->x = this->y = 0;
        this->Foo();
    }

    void Foo() {...}
};
```
- `this` – keyword of the language `C++`
- The expression can be used in any non-static member function of a `class` / `struct`
- Is a `pointer` that **always refers to the current instance**
- It can be used to access own members *(not necessary)*
- It can be returned by `functions`
- It's passed to other `functions` as a `parameter`

---

## 40. This-pointer - 2

#### **C++ behind the scenes:**
- `This-pointer` is an implicit, hidden `parameter` of every non-static member `function`
- Access to data member or call to member `function` is done by dereferencing `this pointer`
- It is done implicitly, but can also be done explicitly

- In a `const-function`, the `this pointer` is `const`!
  - **Effect:** All members are read-only!
- **Popular coding convention:** explicitly use this when accessing members *(instead of having “m_” in front of members)*

---

## 41. Overloading Operators
```c++
class CVector3 { ... };

CVector3 a = CVector3(1, 0, 0);
CVector3 b = CVector3(0, 0, 1);
CVector3 result;

result = a.Add(b);
result = a + b;
```
- **Can define operators for own classes**
  - i.e. define an operator `+` that allows adding instances of my own 3D-Vector class

- Could also be done through normal `functions` *(“Add”-Function)*
  - **But:** operators feel more natural in some places and can make code easier to read

- **Rule of thumb:** Define operators that feel natural and are self-explaining; do not confuse users with non-standard operators!

---

## 42. Overloading Operators - 2

#### **The Rules:**

- You can only redefine **existing** operators
  - i.e. you can define your own `+`, `-`, `*`, `>>` or `->`
  - You cannot invent an operator `$` or `§`

- You cannot change the number of operands
  - i.e. `+` will **always** be *binary*, `!` will **always** be *unary*

- You cannot change operator precedence
  - i.e. `*` always takes precedence before `+`

- You cannot redefine the following operators:
  - `.` *(C, member access)*
  - `?:` *(C, conditional expression)*
  - `sizeof` *(C, data type size)*
  - `::` *(C++, namespace concatenation)*
  - `.*` *(C++, member function pointer call)*

- At least one operand of every operator must be a user-defined type
  - i.e. you cannot write a new `int + int` or a new `char* == char*`

---

## 43. Overloading Operators - 3


- The expression `c = a + b;` resolves either to `c = operator+(a, b);` **if `operator+` is a global function**  
**or** `c = a.operator+(b);` **if `operator+` is a member of a’s class type**

- **Operators resolve to `function` calls**
  - `function` name is `operator<sign>`
  - e.g. `operator+`, `operator==`, `operator[]` etc.

- **Two ways to define operators:**
  - `class` member operators
  - Global operators
---

## 44. Example of a Member Operator

```c++
class CVector3 
{
public:
    CVector3(float x, float y, float z) { ... }
 
    CVector3 operator+(const CVector3& xOp2)
    {
        return CVector3(x + xOp2.x, y+xOp2.y, z+xOp2.z);
    }

private:
    float x, y, z;
};

CVector3 a = CVector3(1, 0, 0);
CVector3 b = CVector3(0, 0, 1);
CVector3 result;

result = a + b;
```



---

## 45. Example of a Global Operator
```c++
class CVector3 
{
    […]	
private:
    float x, y, z;

    // if global operator needs private members, just declare it a friend
    friend CVector3 operator*(float, const CVector3&);
};

CVector3 operator*(float f, const CVector3& v)
{
    return CVector3(v.x * f, v.y * f, v.z * f);
}
```

- **Advantage:** First `parameter` can be non-class type! *(float in this example)*

---

## 46. Overloading Operators - 4
```c++
(a += b) += c;
```
- While some operators like `+`, `-` return a new value, others may need to return a **reference** to one of the arguments
  - e.g. operator `+=`
- Use this pointer to return a reference to self
- Required to chain operations like in the example

---

## 47. Prefix / Postfix Operators
```c++
class CTest
{
    void operator++()	{ … }	// Preinkrement ++CTest
    void operator++(int)  { … }	// Postinkrement CTest++
};
```
- **How is `++x`and `x++` distinguished?** *(same for `--`)*
  - Postfix operator has an unused `int` parameter!
  - Dirty hack, but that is how it is
- If **Postfix** operator is used but not declared, **Prefix** form is used automatically, but not the other way around


---

## 48. Cast-operators
```c++
class CTimer
{
public:
    operator int() { return m_iTime; }
private:
    int m_iTime;
};

CTime xTimer;
int i = xTimer; 		// works now
```
- Can define operators for type conversions
- Are invoked when implicit / explicit cast happens
- Can define conversion to any type; including user-defined types

---

## 49. Operator Overloading

**Words of warning:**
- Overloaded versions of `&&` and `||` do not do expression short-cutting!
  - i.e. both branches are evaluated
  - Confuses users, so better not overload these


---

## 50. Copy-constructor ans Assignment-operator

```C++
class CMyClass { 	... Whatever ... };
void foo(CMyClass x) { ... Whatever ... }

CMyClass xInstance;
CMyClass xAnotherInstance = xInstance; 	// copy ctor call
CMyClass xYetAnoterhInstance(xInstance);	// copy ctor call (explicit)
foo(xInstance);				// copy ctor call (call by value)
```
- This is a special constructor used when creating an object from another object, i.e:
  - When initializing an object with another object *(note the difference between)* 
  - When passing an object by value

---

## 51. Copy-contructor and Assignment-operator - 2
```c++
class CVector3
{ 
    CMyClass(const CMyClass& other) : x(other.x), y(other.y), z(other.z) {}


    float x, y, z;
};
```
- **Copy constructor** accepts `const ref` to same `class`
- The argument must be `ref` because call by value is not possible
- **Copy constructor** is always generated if not present
- Even if other constructor have been defined
 - Default implementation does a shallow copy *i.e. copies all members 1:1)*


---

## 52. Copy-constructor and Assignment-operator
```c++
class CVector3
{ 
    CMyClass(const CMyClass& other) : x(other.x), y(other.y), z(other.z) {}

    CMyClass& operator=(const CMyClass& other)
    { 
        x = other.x; y = other.y; z = other.z;
        return *this;
    }

    float x, y, z;
};			
```
- Assignment operator is similar to copy constructor
  - But can of course accept any `parameter`, not just same `class`
- It is used for all assignments **except for initialization**
- Generated automatically if not present
- Default implementation will do shallow copy

---

## 53. Copy-constructor and Assignment-operator
```c++
class CKeyboard
{
public:
    CKeyboard() {...}
private:
    CKeyboard(const CKeyboard&);             // no implementation necessary!
    CKeyboard& operator=(const CKeyboard&);  // no implementation necessary!
}

CKeyboard xKeyboard;	                 // ok
CKeyboard xAnotherKeyboard = xKeyboard; 	// error (copy ctor private)
xAnotherKeyboard = xKeyboard;		// error (assignment op private)
```

- Can be used to make `classes` “copy protected”
  - **Example:** Keyboard class
  - There is only one keyboard, should never be copied
- Make `copy-ctor` and assignment operator private
  - Not necessary to actually implement them

---

## 54. Implicit Constructors
```c++
class CPlayer
{
public:
    CPlayer() {...}
    CPlayer(const char* pcName) {...}
}

CPlayer xPlayer;
xPlayer  = “Bob”;		// implicit type cast
```
- Compiler performs automatic type conversion sometimes
- It does this by calling appropriate constructor when converting to a user `class`
- You can use keyword explicit to prevent this!

---

## 55. Explicit Constructors
```c++
class CPlayer
{
public:
    CPlayer() {...}
    explicit CPlayer(const char* pcName) {...}
}

CPlayer xPlayer;
xPlayer  = “Bob”;		    // error – no longer possible

xPlayer = CPlayer(“Bob”);	    // OK!
```