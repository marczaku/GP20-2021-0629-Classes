## 1. Namespaces
#### **Problem:**
- Applications use **libraries** *(often many different ones!)*
- Libraries may use more libraries
- Using implies including of headers
- Headers contain declarations
- Declared names must be non-ambiguous
- Danger of name clashes

#### **Concerns:**
- Global `variables`
- Global `functions`
- `classes`
- Preprocessor-Directives, i.e. macros, all other `#defines`  

**Solutions?**

---

## 2. Namespaces - 2

#### **Solution 1:** 
- Precede all identifiers with a prefix
- **Examples:**
  - Nebula-Engine begins class names with `n`, e.g. `nRoot`, `nSceneManager`, `nKernel` etc.
  - TinyXML-Library begins all class names with `TiXml`, e.g. `TiXmlDoc`, `TiXmlNode` etc.

#### **Bottom Line:**
- Adequate solution!
- Works everywhere: `classes`, `functions`, `variables`, `pre-processor`
- Name clashes not ruled out, only more unlikely 
- Conflict can only be resolved by renaming all identifiers concerned

---

## 3. Namespaces - 3

#### **Solution 2:** 
- Just like with variables
- Define "scopes" for identifiers
- Can be nested and allows "hiding" of identifiers with same name

#### **Name spaces**
- Introduced in 1998
- Language feature of `C++`
- Does therefore not for pre-processor!
- Because: pre-processor is not part of the language
- Program analysis done after pre-processing

---

## 4. Namespace - Syntax
```c++
namespace A 
{

class CFoo
{
	...
};

}

A::CFoo xMyFoo;
```

- Key word `namespace`, followed by `{ }` -block (mandatory!)
- All declarations within become part of `namespace`
- Fully qualified name of `CFoo` is `A::CFoo`
- `::` is a binary operator
- Qualified name must be used outside `namespace`, can be used inside

---

## 5. Namespaces - Syntax - 2
```c++
namespace A
{

	void foo() { cout << "Here is A::foo" << endl; }

	namespace B
	{
		void foo() { cout << "Here is B::foo" << endl; }
		void bar() { foo(); }
	}
}
```
- `Namespaces` can be **nested**
- Same hiding rules as with scopes of variables
- Ambiguities cause error messages (ambigues symbol / call)
- Use qualified name if necessary!

---

## 6. Global Namespace

- Identifiers outside of all `namespaces` are located inside the **global namespace**
- It can be qualified using `::Identifier`
- `::` is a special unary operator

---

## 7. Namespaces in Source and Header Files

- **Declarations must be surrounded by namespace**
  - Normally the whole `.h-file`
  - Except for `#includes` and `forward-declarations` (why?)

- **Implementations can be inside namespace**
  - i.e. whole cpp-file surrounded by `namespace
  - **Again:** except for `#includes`, `forwards`

- Implementation could also use fully qualified names instead

---

## 8. Namespaces and Forward Declarations
```c++
namespace A 
{
	namespace B
	{
		class CFoo;
		void Foo(int iBlubb, iBlah);
	}
}
```
 <sup> The correct way </sup>
<br></br>
```c++
namespace A {}		// works
namespace A::B {}	// does NOT work

class A::B::CFoo;	// does NOT work either
```
<sup> The wrong way </sup>

---

## 9. Using

- Saves tedious (?) writing-out of qualified names
- Makes source code more readable *(most of the time)*
- **There is two versions:**
  - Using namespace `<name>`
  - Using `<identifier>`

- Acts like a **"search path"** for identifiers
- There is no defined search order! 
- The use of identifiers **must be non-ambiguous**
- Qualifying always works!

---

## 10. Using - 2
```c++
namespace A
{
	class CA {};
}


namespace B
{
	using namespace A;

	CA a1;
}

namespace C
{
	using namespace B;

	CA a2;   // works!
}

namespace B
{
	CA a3;	// works!
}
```
- **Scope of using:**
  - Current `namespace`
  - Current file

- Careful with `using` in header files!
- `using` is transitive across namespaces!

---
