## 1. Multiple Inheritance

- Can derive a `class` from more than one base `class`
  - i.e `class` will inherit from ***multiple classes*** and has ***multiple base classes***
- Will inherit data members and member functions from all ***base classes***

---

## 2. Memory Layout
```c++
class CFlyingAnimal
{
public:
	float m_fFlightSpeed;
	virtual void Fly()  { cout << "CFlyingAnimal - fly!" << endl; }
};

class CWalkingAnimal
{
public:
	float m_fWalkingSpeed;
	virtual void Walk()  { cout << "CWalkingAnimal - walk!" << endl; }
};

class CPegasus : public CFlyingAnimal, public CWalkingAnimal
{
	int		m_iValue;
};
```
```c++
CPegasus xPegasus;

xPegasus.Fly();
xPegasus.Walk();

cout << "CFlyingAnimal size: “  << sizeof(CFlyingAnimal)   << endl;  
cout << "CWalkingAnimal size: " << sizeof(CWalkingAnimal)  << endl;  
cout << "CPegasus size: "	      << sizeof(CPegasus)        << endl;
```

- The `class` `CPegasus` has combined size of ***base classes*** `CFlyingAnimal` and `CWalkingAnimal`, plus the **size** of the `CPegasus` members
- **But:** `CFlyingAnimal` and `CWalkingAnimal` both have a ***vtable*** pointer!
- `CPegasus` must have ***two VTables***

- `CPegasus` will share merged ***VTable*** with ***primary base `class` *** *(i.e. CFlyingAnimal)*
- Secondary base classes have own ***VTable***; necessary for downcast
<br></br>
#### **CFlyingAnimal**
  - `VTable Ptr`
  - `m_fFlightSpeed`
<br></br>
#### **CWalkingAnimal**
  - `VTable Ptr`
  - `m_fWalkingSpeed`
<br></br>
#### **Pegasus**
  - `m_iValue`

---

## 3. Memory Layout - 2
```c++
CPegasus	xPegasus;
	
CPegasus*       pxPegasus       = &xPegasus;
CWalkingAnimal* pxWalkingAnimal = &xPegasus;
CFlyingAnimal*  pxFlyingAnimal  = &xPegasus;
	
cout << pxPegasus << endl;
cout << pxWalkingAnimal << endl;
cout << pxFlyingAnimal << endl;
```

- Multiple inheritance will change object identity
- Comparing of pointers is **not possible** any more

![image](https://user-images.githubusercontent.com/7360266/121322064-ec881b00-c90e-11eb-9f9b-84a6f02cfecd.png)



---

## 4. Memory Layout - 3

- Virtual base `classes` **always come in front in the memory layout**
  - i.e if `class` inherits from several classes and primary base `class` *(i.e. first `~`)* has no virtual members, all base classes with virtual members will come first in the memory layout
  - “primary” base `class` is moved to the back; a different “primary” is chosen instead

---

## 5. M.I and Name Clashes
```c++
class CFlyingAnimal
{
public:
	float m_fFlightSpeed;
	virtual float GetSpeed() { return m_fFlightSpeed; }
};

class CWalkingAnimal
{
public:
	float m_fWalkingSpeed;
	virtual float GetSpeed() { return m_fWalkingSpeed; }
};
```
```c++
	CPegasus	xPegasus;
	float f = xPegasus.GetSpeed();
  ```
  
- It is easy to inherit unrelated functions with the same name
- This leads to ambiguities

---

## 6. M.I and Name Clashes - 2
```c++
float f1 = xPegasus.CWalkingAnimal::GetSpeed();
float f2 = xPegasus.CFlyingAnimal::GetSpeed();
```
- These must use fully qualified function names to **disambiguate**
- The same applies to name clashes between data members

---

## 7. The Dreaded Diamond

![image](https://user-images.githubusercontent.com/7360266/121328787-ec8b1980-c914-11eb-9509-15d2016221ac.png)

- It's possible to unintentionally inherit a single `class` multiple times 
- This is called the **“diamond problem”** or **“dreaded diamond”** because of the shape of the inheritance diagram

---

## 8. Code Examples

```c++
class CAnimal
{
public: 
	char* m_pcName;
};

class CFlyingAnimal : public CAnimal
{
public:
	float m_fFlightSpeed;
	virtual void Fly()  { cout << "CFlyingAnimal - fly!" << endl; }
};

class CWalkingAnimal : public CAnimal
{
public:
	float m_fWalkingSpeed;
	virtual void Walk()  { cout << "CWalkingAnimal - walk!" << endl; }
};

class CPegasus : public CFlyingAnimal, public CWalkingAnimal
{
public:
	int		m_iValue;
};
```
---

## 9. Dreaded Diamond - 2
```c++
CPegasus	xPegasus;
xPegasus.m_pcName = "Peggy";	// Error! ambiguous!
```
- Pegasus has inherited `CAnimal` **twice*'
  - i.e. has member `m_pcName` twice
  - `m_pcName` has a name clash with itself
- ***You must disambiguate using the names of the intermediate classes***

```c++
CPegasus	xPegasus;
	
xPegasus.CFlyingAnimal::m_pcName = "Peggy";
xPegasus.CWalkingAnimal::m_pcName = "Bob";
```
---

## 10. Virtual Base Classes

- Inheriting a `class` several times is **undesirable**
  - **Solution:** *Virtual base classes*
- Inherit `class` using keyword ***virtual***
- It will now inherit class only **once**, even if inheriting it indirectly several times
- **Attention:** It must inherit virtual on all inheritance pathes!

---

## 11. Code Examples
```c++
class CAnimal
{
public: 
	char* m_pcName;
};

class CFlyingAnimal : virtual public CAnimal
{
public:
	float m_fFlightSpeed;
	virtual void Fly()  { cout << "CFlyingAnimal - fly!" << endl; }
};

class CWalkingAnimal : virtual public CAnimal
{
public:
	float m_fWalkingSpeed;
	virtual void Walk()  { cout << "CWalkingAnimal - walk!" << endl; }
};

class CPegasus : public CFlyingAnimal, public CWalkingAnimal
{
public:
	int		m_iValue;
};
```
```c++
CPegasus	xPegasus;
xPegasus.m_pcName = "Peggy";	// works!
```
---

## 12. Virtual Base Classes -2 

- If virtual inheritance and non-virtual inheritance are mixed and a `class A` is inherited several times, 
there is a single *virtual A* and a *non-virtual A* for each non-virtual inheritance path to A. 

---

## 13. Multiple Inheritance

#### **Is multiple inheritance bad?**
  - No, it is a tool that may or may not fit your needs
  - There are alternatives to multiple inheritance!
  - For example, ***nested generalization*** and ***bridge pattern*** (i.e. aggregation)

#### **Be aware of the problems of multiple inheritance!**
  - No pointer identity 
  - Member name clashes possible
  - Diamond-problem
  - The need to use dynamic_cast and RTTI for downcasting if you use virtual base classes
  
---

## 14. Downcasting Virtual Base Classes
```c++
CPegasus* pxPegasus = new CPegasus;
CAnimal* pxAnimal = pxPegasus;                    // ok!
CPegasus* pxPegasusAgain = (CPegasus*) pxAnimal;  // error!
```
- Casting ***virtual base class*** to ***derived class*** is **not possible** using static or C-style cast!
  - You must use `dynamic_cast`
- ***Virtual base class must be polymorphic type (i.e. have virtual functions)***
  - It requires `RTTI` enabled or `reinterpret_cast`; but this will probably not provide the result we want

```c++
CPegasus* pxPegasus = new CPegasus;
CAnimal* pxAnimal = pxPegasus;                    // ok!
CPegasus* pxPegasusAgain = dynamic_cast<CPegasus*>(pxAnimal);  // ok!
```

---

## 15. Interfaces

#### **Often:** 
- Use multiple inheritance for interfaces only

#### Interface: 
- Abstract `class`
- Has no data members
- All functions pure virtual *(well, not necessarily)*

#### Advantages:
- No data member clashes *(because: no data members)*
- Diamond not harmful *(because: cannot inherit data members multiple times)*  

There is still no pointer identity!

---

## 16. Delegate to a Sister Class
```c++
 class Base {  public:    virtual void foo() = 0;    virtual void bar() = 0;  };    class Der1 : public virtual Base {  public:    virtual void foo();  };    void Der1::foo()  { bar(); }    class Der2 : public virtual Base {  public:    virtual void bar();  };    class Join : public Der1, public Der2 {  public:    ...  }; 
 ```
 ```c++
 Join xJoin;
 xJoin.foo();
 ```
 
 - Class `Der1` will call function of class `Der2` even though the classes are unrelated!

---
