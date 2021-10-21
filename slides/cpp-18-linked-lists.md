
## 1. Pros and Cons of Linked Lists

#### Pro:
- Adding, deleting are constant-time for all elements
- Unlimited size; never has to resize
<br></br>

#### Contra:
- Indexed access takes linear time
- Larger memory footprint (additional pointers!)
- Bad cache performance (elements distributed randomly across memory!)
- Dynamic allocation / deallocation takes significant amount of time

---

## 2. Pretty Table

|  **FUNCTION** | **DYNAMIC ARRAY**  | **SINGLE LINKED LIST**  |
|---|---|---|
| Add to front  | _linear_  | **constant**  |
| Add to back  | **constant**  |  _linear_ |
|  Insert in middle |  _linear_ | **constant**  |
|  Delete first | _linear_  | **constant**  |
| Delete last  | **constant**  |  _linear_ |
|  Delete in between | _linear_  | **constant**  |
| Access to n-th  |  **constant** | _linear_  |
| Resize   |  _linear_ | **constant**  |
|  Memory consumption | N*Elementsize  | N*(Elementsize + 4)  |

---

## 3. Pretty Table - 2

|  **FUNCTION** | **DYNAMIC ARRAY**  | **DOUBLE LINKED LIST**  |
|---|---|---|
| Add to front  | _linear_  | **constant**  |
| Add to back  | **constant**  |  **constant** |
|  Insert in middle |  _linear_ | **constant**  |
|  Delete first | _linear_  | **constant**  |
| Delete last  | **constant**  |  **constant** |
|  Delete in between | _linear_  | **constant**  |
| Access to n-th  |  **constant** | _linear_  |
| Resize   |  _linear_ | not necessary  |
|  Memory consumption | just the elements  | Elements + 2*(n+1) pointers  |
| Searching  |  _linear_ | _linear_  |

---

## 4. Linked List

<img width="783" alt="Screenshot 2021-07-14 at 12 26 15" src="https://user-images.githubusercontent.com/7360266/125607053-fcf96553-6fa7-4126-899b-6d1db357c501.png">

- Every element receives a *pointer* to the next element
- The element must be a class containing the payload and that pointer
- Must know pointer to first element in list

---

## 5. Linked List - 2

<img width="773" alt="Screenshot 2021-07-14 at 12 28 01" src="https://user-images.githubusercontent.com/7360266/125607376-d8ae99ba-ed7c-401a-b01c-458bba9d616e.png">

- Inserting elements is very efficient now, since only ***1*** pointer has to be modified; there is no need to move objects in memory
- It can be done in constant time *(i.e. does not depend on list size)*

---

## 6. Linked List - 3

<img width="774" alt="Screenshot 2021-07-14 at 12 29 16" src="https://user-images.githubusercontent.com/7360266/125607573-13c00d78-2dd6-4fb5-8afa-9bd42a5eec45.png">

***The same goes for deleting – it can be done in constant time now!***

---

## 7. Double Linked List

Screenshot 2021-07-14 at 12.30.32<img width="811" alt="Screenshot 2021-07-14 at 12 30 32" src="https://user-images.githubusercontent.com/7360266/125607758-1df942a4-a673-4424-8180-b47238fd77c1.png">

- Every element receives a pointer to the next, and one to the previous element
  - This allows to iterate back to front
  - This allows operations to insert before

---

## 8. Code Sample

```c++
int		m_iValue;
	CListElement*	m_pPrev;
	CListElement*	m_pNext;
};

class CLinkedList
{
	CListElement*	m_pFirst;
	CListElement*	m_pLast;
	int		m_iSize;
public:
	CLinkedList();
	~CLinkedList();

	CListElement*	AddToFront(int iValue);
	CListElement*	AddToBack(int iValue);
	CListElement*	InsertBefore(CListElement* pBeforeThis, int iValueToInsert);
	CListElement*	InsertAfter(CListElement* pAfterThis, int iValueToInsert);
	void		DeleteElement(CListElement* pElement);
	void		SwapElements(CListElement* pE1, CListElement* pE2);
	CListElement*	FindValue(int iValue);
	CListElement*	GetElementByIndex(int iIndex);
	CListElement*	GetFirstElement() const;
	CListElement*	GetLastElement() const;
	int		GetSize() const;
	void		Sort();
```

---
