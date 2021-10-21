## 1. Inheritance

- If two classes form an is-a relationship,
i.e. a `Cat` is an `Animal`, 
they should be modeled using inheritance.

- The `Cat` will inherit all properties from `Animal`
  - It may add properties of its own
  - It may also redefine some properties

- **Vocabulary:**
  - `Animal` is a generalization of `Cat`
  - i.e. `Animal` is the more general class

- `Cat` is a specialization of `Animal`
  - i.e. the class `Cat` is more specialized than the class `Animal`

---

## 2. Inheritance - 2

#### Vocabulary (cont’d)
- Class `Cat` inherits from class `Animal`
- `Cat` is derived from `Animal`
- `Cat` is a child class of `Animal`

- `Animal` is the base class of `Cat`
  - **or:** ~ is the super class of `Cat`
- `Animal` is the parent class of `Cat`

---

## 3. Inheritance - Syntax
```c++
class CAnimal
{
	float m_fWeight;
	char* m_pcName;
};

class CCat : public CAnimal
{
	char* m_pcFurColor;
};
```
```c++
CCat xMyCat;
xMyCat.m_fWeight = 2.5f;
xMyCat.m_pcName = "Tabby";
xMyCat.m_pcFurColor = "brown";
```

- Class `Cat` is derived from class `Animal`
- `Cat` will inherit all Members *(data and functions)* of class `Animal`
- `Cat` is free to declare own, additional members

---

## 4. Inheritance - Memory Layout
```c++
class CAnimal
{
	float m_fWeight;
	char* m_pcName;
};

class CCat : public CAnimal
{
	char* m_pcFurColor;
};
```

![image](https://user-images.githubusercontent.com/7360266/124092134-d1648300-da56-11eb-9522-54feedfd3ee2.png)

- Looking at the memory layout, `CCat` is in fact a `CAnimal`
  - Size = size of base call + size of new members
  - Casting a `CCat` pointer to type `CAnimal` is trivial, because object of base class type is already at same address!

---

## 5. Inheritance Protection Modifiers

#### It Can Inherit a Class As:
- **Public**
  - Inherited members have same protection as in base class
- **Protected**
  - Inherited public members become protected
  - Inherited protected, private members stay that way
- **Private**
  - All inherited members become private
- 99% of all inheritance is public
  - Other languages do not allow anything but public inheritance

---

## 6. Constructor / Destructor Chaining
```c++
class A {
	A();  
}
class B : public A {
	B();			// will implicitly call A();
}
class C : public B {
	C();			// will implicitly call B();
}
```

- The constructor will automatically call the constructor of a parent class before executing own ctor code
  - i.e. constructors are called in ascending order
- The destructor will call parent destructor after own code
  - i.e. destructors are called in reverse order

---

## 7. Passing Args to Parent ctor
```c++
class A {
	A(int i) {};  
}
class B : public A {
	B() : A(10) {};		// must specify argument of parent ctor
}
```

- You can call a specific parent constructor with arguments by placing “constructor call” into the initializer list
  - You must do so if the parent class does not have a default ctor
- ***Make sure not to call constructors directly!***
  - *(unless you know exactly what you’re doing)*

---

## 8. Polymorphism

- The word derives from greek and translates to  *“in many shapes”*
- A derived class can be used everywhere where its base class can be used
- The type `CCat` is compatible to type `CAnimal`
- ~ `Cat` is ***covariant*** to type `CAnimal`
  - **In fact:** every instance of `CCat` is a `CAnimal`, and also a `CCat`
- Variables of type `CAnimal` can store a `CCat`
- Functions that expect parameters of type `CAnimal` will accept a `CCat`

---

## 9. Polymorphism - 2
```c++
CAnimal xAnimal = xMyCat;			// works, but loses
						// furcolor

CCat xMyCatAgain = (CCat) xAnimal;	// Error
```

#### Attention:
- `sizeof(CAnimal)` **<** `sizeof(CCat)`
- “squeezing” a value of type `CCat` into a variable of type `CAnimal` works, but loses all `CCat` members
- Putting a `CAnimal` into a `CCat` is not possible!

---

## 10. Overriding Methods
```c++
class CAnimal
{
public:
	float m_fWeight;
	char* m_pcName;

	void Walk() {}; 
	void Walk(float fDistance) {};
};

class CCat : public CAnimal
{
public:
	char* m_pcFurColor;

	void Walk(int iSteps) {};
};

CCat xMyCat;
xMyCat.Walk();		// Error	
xMyCat.CAnimal::Walk();	// works!
```

- Deriving class is free to define methods that already exist in the base class
- It will hide all methods with the same name in base the class
  - i.e. all overloads
  - Same for constructors
- You can still use qualified name to access old methods
  - Also within my member functions

---

## 11. Polymorphism - 3
```c++
CCat xMyCat;

CCat* pCat = &xMyCat;
CAnimal* pAnimal = &xMyCat;

cout << pAnimal << endl;
cout << pCat<< endl;	  // same!
```

![image](https://user-images.githubusercontent.com/7360266/124098153-95ccb780-da5c-11eb-8e98-0fce518e50db.png)

- To fully exploit polymorphism, you need to use pointers or references
- Assigning `Cat*` to `Animal*` will not change the object
  - **Think:** Memory layout – every pointer to class is also a valid pointer to base class

---

## 12. Early Binding and Late Binding
```c++
class CAnimal
{
public:
	void SaySomething()		{ cout << "---" << endl; }
};

class CCat : public CAnimal
{
public:
	void SaySomething()		{ cout << "meeow!" << endl; }
};

...
CCat* pCat = &xMyCat;
CAnimal* pAnimal = &xMyCat;

pCat->SaySomething();			// meeow
pAnimal->SaySomething();			// ---
```

- In the example above, both pointers point to cat, but the called function depends on the pointers type
- This is called ***early binding***
- By default, the compiler decides which function to call at compile time, and will always follow the variable type
  - It's because this is the most efficient way to call a function

```c++
CCat* pCat = &xMyCat;
CAnimal* pAnimal = &xMyCat;

pCat->SaySomething();			// meeow
pAnimal->SaySomething();			// ---
```

---

## 13. Early Binding and Late Binding - 2
```c++
class CAnimal
{
public:
	virtual void SaySomething()	{ cout << "---" << endl; }
};

class CCat : public CAnimal
{
public:
	virtual void SaySomething()	{ cout << "meeow!" << endl; }
};

...
CCat* pCat = &xMyCat;
CAnimal* pAnimal = &xMyCat;

pCat->SaySomething();			// meeow
pAnimal->SaySomething();			// meeow!
```

- The keyword `virtual` in front of the function will tell the compiler to resolve function call at run-time
  - This is called late binding
  - The function called now depends on the real object type, not the pointer type
- **Rule:** A virtual function will always be virtual in all derived classes
  - The keyword `virtual` in class `CCat` is optional

```c++
CCat* pCat = &xMyCat;
CAnimal* pAnimal = &xMyCat;

pCat->SaySomething();			// meeow
pAnimal->SaySomething();			// meeow
```

---

## 14. Late Binding - Behind the Scenes

![image](https://user-images.githubusercontent.com/7360266/124101422-9fa3ea00-da5f-11eb-8f89-9c5ce5996a66.png)

- Every class with virtual methods receives a pointer to a virtual function table
  - Short: ***VTable***
  - i.e. this is a hidden member (can observe type size change!)
  - ***VTable*** exists once for every class (not per instance!)
  - ***VPtr*** (Ptr to VTable) is always first member
- ***VTable*** contains pointers to correct functions for this type
- Every function call will do lookup in objects ***vtable***

---

## 15. Late Binding

- ***VTable*** is initialized in constructor
  - Therefore do not call constructors directly! The constructor does more than your code shows!
- ***Do not call own virtual functions in constructor!***	
  - **Think:** The constructor of your child classes has not been executed yet!
  - This may lead to wrong function calls, or even pure virtual function calls 
if the function pointer is still *0* (because the function is pure virtual in your class)

---

## 16. Abstract Base Classes
```c++
class CAnimal
{
public:
	virtual void SaySomething()	= 0;
};

...
CAnimal  xAnimal; 	// Error
CAnimal* pAnimal;		// OK!
```

- It is possible to intentionally not implement a function
- Denote by `= 0` after virtual function declaration
  - i.e. function pointer in vtable is *0*
  - Do not provide a body for the function
- This is called a pure ***virtual function*** or ***abstract function***

---

## 17. Abstract Base Classes - 2
```c++
class CAnimal
{
public:
	virtual void SaySomething()	= 0;
};

...
CAnimal  xAnimal; 	// Error
CAnimal* pAnimal;		// OK!
```

- You cannot instantiate an abstract class, instead, you must derive and override the abstract functions
- A derived class can still be abstract if not all pure virtual functions were defined
- But it can declare pointers to abstract class (exploit polymorphism)

---

## 18. Virtual Destructors

- If a class has one or more virtual functions, you should also make the destructor virtual
  - **Otherwise:** The wrong destructor may be called (late binding!)
- You cannot make destructor pure virtual
  - The syntax allows this, but the child class will still attempt to call parent destructor which leads to Linker error
- Constructors cannot be virtual
- Static functions cannot be virtual, either

---

## 19.  Return Types of Virtual Functions
```c++
class CAnimal
{
public:
	virtual CAnimal* Clone()	{...}
};

class CCat : public CAnimal
{
public:
	virtual CCat* Clone()	{...}
};
```

- It is possible to override a virtual function with the same parameters list but a different return type,
if the new return type is covariant to the old one
  - **Otherwise:** This is not allowed, the return type must be the same or the parameter list must be different (it will hide inherited functions)

---
