## 1. Templates

- Consider the ***DynArray-class*** we recently implemented
- Dynamic Array of *integers*
- What changes are required if you need a Dynamic Array of floats? *(booleans, GameObjects, ...)*

---

## 2. Code Sample
```c++
class CDynArray
{
	int* m_pxArray;
	int m_iSize;

public:
	CDynArray() : m_iSize(0)   { m_pxArray = new int[m_iSize]; } 
	~CDynArray()               { delete [] m_pxArray; }

	void AddEntry(const int& newValue)
	{
		int* pNewArray = new int[m_iSize+1];
		for(int i=0; i<m_iSize; ++i)
			pNewArray[i] = m_pxArray[i];
		pNewArray[m_iSize] = newValue;
		m_iSize++;
		delete [] m_pxArray;
		m_pxArray = pNewArray;
	}

	int GetSize() const	  { return m_iSize; }

	int& operator[](int iIndex) { return m_pxArray[iIndex]; }
};
```

---

## 3. Code Sample - 2
```c++
class CDynArray
{
	float* m_pxArray;
	int m_iSize;

public:
	CDynArray() : m_iSize(0)   { m_pxArray = new float[m_iSize]; } 
	~CDynArray()               { delete [] m_pxArray; }

	void AddEntry(const float& newValue)
	{
		float* pNewArray = new float[m_iSize+1];
		for(int i=0; i<m_iSize; ++i)
			pNewArray[i] = m_pxArray[i];
		pNewArray[m_iSize] = newValue;
		m_iSize++;
		delete [] m_pxArray;
		m_pxArray = pNewArray;
	}

	int GetSize() const	    { return m_iSize; }

	float& operator[](int iIndex) { return m_pxArray[iIndex]; }
};
```
---

## 4. Templates - 2

- You need to change datatype of member
  - Array type from `int` to `float`
- You need to change the return type / parameter types for some functions
- You need to change the type of some local variables
- It is **not** possible to do this using normal parameters or polymorphism
- Algorithms remain the same!
- Simple search and replace in code
- Need a mechanism to do it automatically 
- **What if you do it manually?**
  - It is very error-prone, tedious and difficult to maintain

---

## 5. Generic Programming

#### Idea: 
- Define complex data types independently from underlying basic data types
  - e.g. `DynArray` independently of types *int*, *float* etc.
<br></br>
- Define algorithms independently from data types
  - e.g. sorting algorithm is independent 
<br></br>
This is called ***Generic Programming*** or ***Meta-Programming***

---

## 6. Template Classes
```c++
template<typename T>
class CDynArray
{
	T* m_pxArray;
	int m_iSize;

public:
	CDynArray() : m_iSize(0)   { m_pxArray = new T[m_iSize]; } 
	~CDynArray()               { delete [] m_pxArray; }

	void AddEntry(const T& newValue)
	{
		T* pNewArray = new T[m_iSize+1];
		for(int i=0; i<m_iSize; ++i)
			pNewArray[i] = m_pxArray[i];
		pNewArray[m_iSize] = newValue;
		m_iSize++;
		delete [] m_pxArray;
		m_pxArray = pNewArray;
	}

	int GetSize() const        { return m_iSize; }

	T& operator[](int iIndex)  { return m_pxArray[iIndex]; }
};
```


- The class `DynArray` becomes a template class
  - i.e. a parameterized class
- Parameters can be anything, including type names!
- **Keyword:** `typename`
  - **Older version:** `keyword class`, but in fact, a parameter can be a basic type as well
- **Parameters can be used anywhere in the code**
- ***Template parameters must be provided in `<pointy brackets>` when instantiating a template class*** 

---

## 7. Template Classes
```c++
CDynArray<int> aiArray;
aiArray.AddEntry(1);
aiArray.AddEntry(2);
aiArray.AddEntry(3);
int iSize = aiArray.GetSize();

for(int i=0; i<iSize; ++i)
{
	cout << aiArray[i] << endl;
}
```
- These are called explicit template instantiation
- The code for a template class is generated only if the class is used, and only for the functions used
- Individual code is generated for every combination of template parameters

---

## 8. Template Classes - 2
```c++
CDynArray<int> aiIntArray;
CDynArray<float> aiIntArray;
CDynArray< CDynArray<int> > aaiDoubleArray;  // attention: Spaces necessary

typedef CDynArray<int> IntArray;
typedef CDynArray<float> FloatArray;
```

You can now declare `DynArray` of any type, including template types.
When using multiple templates, you must use spaces between the pointy brackets. 
The compiler will recognize `>>` as an operator.
A tip is to use typedefs to shorten syntax of frequent combinations.
<br></br>

Template code is **NOT** compiled like ordinary code! Template code is compiled when first used, and
therefore, it must be in a header file since the compiler must be able to *"see"* it when using it.

---

## 9. Template Classes - 3

- Errors in template code are **not** found unless code is really used
  - i.e. real code is generated from the template code 
- The template code may work for one type and not work for another. For instance, 
`DynArray` class assumes that type T has public default constructor. It will not work (e.g. cause compile-time error) for types that don’t
- The template code must be visible from code instantiating the template
  - i.e. should always put complete template code in header/inline files
- Template code in a cpp file can only be used within that file. ***Otherwise: linker error!***
---

## 10. Template Classes - 4
```c++
template<typename T>
CDynArray<T>::CDynArray() : m_iSize(0) 
{ 
	m_pxArray = new T[m_iSize]; 
} 

template<typename T>
CDynArray<T>::~CDynArray() 
{ 
	delete [] m_pxArray; 
}
```

When defining template class member functions outside the class body,
every function must receive template header and the class name needs template argument list.

---

## 11. Code Samples - 3
```c++
template<typename T>
class CDynArray
{
  T* m_pxArray;
  int m_iSize;

public:
  CDynArray();
  ~CDynArray();

  void AddEntry(const T& newValue);
  int GetSize() const;

  T& operator[](int iIndex);
};


template<typename T>
CDynArray<T>::CDynArray() : m_iSize(0) 
{ 
  m_pxArray = new T[m_iSize]; 
} 

template<typename T>
CDynArray<T>::~CDynArray() 
{ 
  delete [] m_pxArray; 
}
```

```c++
template<typename T>
void 
CDynArray<T>::AddEntry(const T& newValue)
{
  T* pNewArray = new T[m_iSize+1];
  for(int i=0; i<m_iSize; ++i)
  pNewArray[i] = m_pxArray[i];
  pNewArray[m_iSize] = newValue;
  m_iSize++;
  delete [] m_pxArray;
  m_pxArray = pNewArray;
}

template<typename T>
int 
CDynArray<T>::GetSize() const	
{ 
  return m_iSize; 
}

template<typename T>
T& 
CDynArray<T>::operator[](int iIndex) 
{ 
  return m_pxArray[iIndex]; 
}
```

---

## 12. Template Classes - 5 
```c++
template class CDynArray<int>;		// force instantiation with int
template class CDynArray<float>;		// force instantiation with float
```
You can force the compiler to instantiate a template with given parameters.
This will force instantiation of **all** member functions, even if the template is not really used in code
<br></br>
This opens up the possibility to put function definitions into the  cpp file, 
but you will need to explicitly instantiate all versions of template class you want to use.
***Otherwise: linker error.***

---

## 13. Template Classes - 6
```c++
template<int columns, int rows>
class CMatrix
{
	float values[columns][rows];
};

cout << sizeof(CMatrix<1,1>) << endl;
cout << sizeof(CMatrix<3,3>) << endl;
```

Template parameters can also be normal types.
These can be used in places where normal parameters cannot be used.
Remember that template instantiation is still code generation!

---

## 14. Template Functions
```c++
template<typename T>
void swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

int a = 2, b = 1;
::swap(a, b);

float f = 0.5; g = 1.0f;
::swap(f, g);
```

Single functions can also be templates.
They are similar to preprocessor macros, but are much safer and much more powerful.

---

## 15. Template Functions - 2
```c++
int a = 2, b = 1;
::swap(a, b);

float f = 0.5, g = 1.0f;
::swap<float>(f, g);
```

There is two ways to instantiate a template function, either:

#### Implicitly: 
- Compiler will try to deduce template arguments from type of function arguments
<br></br>
#### Explicitly:  
- Template arguments specified in pointy brackets

---

## 16. Template Functions - 3

As stated before, template code may work for one type and not work for another.
For instance, a max function will only work for types that support operator `<`
will cause compile-time error for others

![image](https://user-images.githubusercontent.com/7360266/123251050-0e76c580-d4eb-11eb-8f9d-ad2d963db46e.png)

---

## 17. Template Specialisation
```c++
template <typename T>
T max(T x, T y)
{
  if (x < y)
    return y;
  else
    return x;
}
```
```c++
cout << max("Bob", "Alice") << endl;
```

Template specialisation can override template-generated code and provide a custom version for specific types
For example, the “max”-template function will not work for C-strings!
(why not?)

---

## 18. Template Specialisation - 2
```c++
template <typename T>
T max(T x, T y)
{
  if (x < y)
    return y;
  else
    return x;
}
```
```c++
template<>
const char* max(const char* a, const char* b)
{
	return strcmp(a, b) > 0 ? a : b;
}
```
```c++
cout << max("Bob", "Alice") << endl;
```

#### Solution
- Leave the template the way it is since it works for most types. But make sure to provide specialization for type char*!
<br></br>
#### Redeclare the Function
- Leave the pointy brackets empty and use the desired type instead of template argument

---

## 19. Template Specailisation - 3
```c++
template<>
class CDynArray<bool>
{
	...
};
```
This also works with template classes. Again, empty template argument list declaration, 
but provide desired argument values instead

- **Example:**
  - Implement special version of `CDynArray` for type ***bool***
  - Use bitfields; will use 1Bit per bool instead of 4 bytes!
  - 32x smaller than standard version! *(but somewhat slower)*

---

## 20. Template Specialisation - 4
```c++
template<>
inline
void CDynArray<char*>::Sort()
{
	// insert custom sort function that works with char pointers...
}
```

It is even possible to specialize a single member function of a template class.
For instance, implement custom `DynArray::Sort()` for type const `char*`.
The rest of the template class remains the same for that type!
<br></br>
**Attention:** `template<>` does not count as inline, but `template<args>` does.

---

## 21. Partial Specialisation
```c++
template<int rows, int cols>
class CMatrix {
	float values[rows][cols];
};

template<int rows>
class CMatrix<rows, 1> {
	float values[rows];
};
```

You can also specialize the template with only some arguments bound. 
You should know that only more recent compilers support this, for example, 
*Visual Studio* since the 2003 version

---

## 22. Templates and Static

- Each class template instance has its own copies of static members.
- Each function template instance has its own copies of static local variables
  - i.e. `CDynArray<int>` and `CDynArray<float>` **do not share static members**

---

## 23. Templates and Friends
```c++
template<typename T>
class X
{
    friend void foo(); 	  // foo is friend of X<whatever>
    friend class Y; 	  // Y is friend of X<whatever>

    friend class Z<T>;	  // Z<int> is friend of X<int>
		          // Z<float> is friend of X<float> etc...

    friend foo(X<T>&);     // foo(X<int>&) is friend of X<int> etc...
};
```

Template classes can define friend classes / functions. 
However, template does only syntactic replacements but consequences should be easy to deduct.

---

## 24. Automatic Type Discovery
```c++
template<typename T>
void foo(T)
{
   CDynArray<T> xArray;
   ...
};
```

- Template Functions can be instantiated implicitly, 
i.e. Template Parameters are bound automatically depending on Function Parameters. 
Bound parameters can be used to explicitly instantiate other templates including template classes. 
This relieves user of having to specify template arguments

---

## 25. Task

- ***Change `CDynArray-class`to template!***
  - Make sure `Sort()`-Function works with any type now – including `char*` 
  - Implement memory-saving template specialization for `CDynArray<bool>`
  - Using only 1 bit per bool *(instead of 4 bytes)*!

---
