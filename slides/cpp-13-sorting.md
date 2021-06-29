## 1. Sorting

#### Problem
- We have a list of data to be sorted
  - ***List*** simply refers to a sequential container type; the actual data type does not matter 
  - e.g. `static array` / `dynamic array` / `linked list`
- We have a comparison operator `R` that defines a linear order of elements
  - i.e. for two elements `a≠b`, either `aRb` or `bRa` must hold true, but **not both**
  - **e.g. operator `<`:** if `a≠b`, either `a<b` or `b<a`

#### Example
- **We have:** *5, 3, 2, 4, 1*
- Our comparison operator is `>`
- **We want:** *5, 4, 3, 2, 1*

---

## 2. Classification of Sorting Algorithms

#### Stable Sorting Algorithms
- Maintain the relative order of equal elements
  - **Example:**
  - **Orignal array:** *4, 31, 1, 2, 32, 5, 33*
  - (there are 3 equal *3* elements, the index is just there to distinguish them)
  - **Sorted array:** *1, 2, 31, 32, 33, 4, 5* 

#### Unstable Sorting Algorithms
- May change the relative order of equal elements
  - i.e. sorted example might be something like this: *1, 2, 32, 31, 33, 4, 5*

---

## 3. Classification of Sorting Algorithms

#### In-place Sorting Algorithms
- Require only a constant amount of additional memory
  - i.e. the memory required for sorting does not depend on the size of the list to be sorted
  - Typically works directly on the original list

#### Out-of-place Sorting Algorithms
- Require additional memory proportional to the size of the list to be sorted
  - e.g. algorithms that do not modify the original list but create a new one instead

---

## 4. Selection Sort
```c++
for(i=0; i<arraySize-1; ++i)
{
    smallestIndex = i;
    for(j=i+1; j<arraySize; ++j)
        if(array[j] < array[smallestIndex])
            smallestIndex = j;
    swap(array[i], array[smallestIndex]);
}
```

- **Other names:** `Selectsort`, `ExchangeSort`
- Very intuitive approach
  - Find the smallest element in the list *(linear search)*
  - Swap the smallest element with the first *(i.e. move it to its final place)*
  - Find the smallest element in the remaining list *(excluding the first element)*
  - Swap it with the second element ***and so on until the end of the list***

---

## 5. Assignment

#### Implement Selection Sort!
- Fill a huge `array` with **random numbers**
- Implement algorithm as a function *(we want to add more algorithms later)*
- Add a function that verifies the sorting
- **Measure the time needed** to sort the `array`
- Use the `QueryPerformanceCounter` function
- Use `__int64` ***instead of*** `LARGE_INTEGER`

---

## 6. Selection Sort - Properties

#### Selection Sort is Unstable
- Consider: 133234
- But stable implemenation is possible, but costs...! (how?)
- Selection sort works inplace 
  - The memory required for loop counters + swap space for one element

#### Complexity
- **Swap operations (worst case):** 
   - `n-1` *(for n elements)*
- **Compare operations:** 
  - `(n-1) + (n-2) + ... + 2 + 1`
  - `n² / 2 - n / 2`
  - `~ O(n²)`

---

## 7. Big O Notation

- **Other name:** Landau notation
- Describes the upper bound of a function in terms of another (simpler) function or, in other words: 
`f(x)` ***does not grow faster than*** `g(x)`

![image](https://user-images.githubusercontent.com/7360266/121686746-e0908a80-cac1-11eb-9f3c-07b577257d53.png)

---

## 8. Complexity Classes

![image](https://user-images.githubusercontent.com/7360266/121686964-1897cd80-cac2-11eb-8712-96478f5c29df.png)

#### O(1) – constant
- ***Behavior does not depend on size of problem***
<br></br>

![image](https://user-images.githubusercontent.com/7360266/121687117-40873100-cac2-11eb-8f56-bdc860134390.png)
#### O(log n) – logarithmic
- ***Grows by constant factor when problem size doubles***
- ***Base of the logarithm does not matter***  
<br></br>  

![image](https://user-images.githubusercontent.com/7360266/121687141-48df6c00-cac2-11eb-8695-fd6e6540d1ff.png)
#### O(n) – linear
- Resource use grows linearly with size of problem
  - i.e. problems size doubles &#8594; resouces use doubles  
<br></br>  

![image](https://user-images.githubusercontent.com/7360266/121687295-7a583780-cac2-11eb-9212-edfcbd0bd47b.png)
#### O(n log n) - linear-logarithmic  
<br></br>  

![image](https://user-images.githubusercontent.com/7360266/121687402-9a87f680-cac2-11eb-891d-7cf3329da846.png)
#### O(n²) – quadratic
- ***Grows 4x when problem size doubles***  
<br></br>  

![image](https://user-images.githubusercontent.com/7360266/121687419-9fe54100-cac2-11eb-991e-dbfaa89f7074.png)
#### O(2n) – exponential
- ***Grows 2x when problem size increases by one***


---

## 9. Evaluation of Sorting Algorithms

### These Can Look At:
- The memory requirements of the algorithms, which is contant for in-place algorithms
- The time behavior of the algorithm
  - Number of comparison operations
  - Number of swap operations depending on problem size *(i.e. list length)*
<br></br>
- Swapping may be much more expensive than comparing,  or the other way round *(depends on your data!)*
- Access pattern of the algorithm may be an issue
  - Consider sorting an archive of 1000 magnetic tapes with only 1 or 2 tape drives!

---

## 10. Special Cases

#### How Does an Algorithm Behave
- In the best case?
- In the worst case? *(and how likely is that?)*
- In the average case? *(what is your average case?)*

#### Special Cases – ***What If...***
- the list is already sorted?
- The list is almost sorted *(only 1 new element at wrong position?)*
- The list is sorted in reverse order *(is that the worst case?)*

---

## 11. Bubblesort
```c++
do
{
    swapped = false;
    for(i=0; i<arraySize-1; ++i)
        if(array[i+1] < array[i])
        {
            swap(array[i+1], array[i]);
            swapped = true;
        }
} while(swapped);
```

- This is an extremely naive sorting algorithm
  - It has little practical value; mostly used as a bad example
- It compares two neighboring elements and swaps them if necessary
- It does this for the whole list; stops when no more swaps happen

---

## 12. Bubblesort - 2
```c++
n = arraySize;
do
{
    swapped = false;
    n = n-1;
    for(i=0; i<n; ++i)
        if(array[i+1] < array[i])
        {
            swap(array[i+1], array[i]);
            swapped = true;
        }
} while(swapped);
```

- **Optimization:**
  - Largest element is guaranteed to be at the correct position after first pass
  - It can decrement sorting area size after every pass!

---

## 13. Bubblesort - Properties

- Bubblesort is stable
- Bubblesort works inplace

- **Complexity:**
  - Swap operations (worst case): `½ (n² - n)` `~ O(n²)`
 
- Compare operations (worst case): 
  - Same as swap operations

- ***Optimal best case!***

---

## 14. Quicksort

- Very fast sorting algorithm
- **Idea:**
  - Divide and conquer
  - Split problem in half, solve each half independently and combine the results
  - You can split as often as necessary!

- **Realization:**
  - Split the list in two
  - Make sure that every element in the left half is smaller than every element in the right half
  - Recursively repeat with both halves
  - Stop at lists of length 1 or 0 (they are already sorted!)

---

## 15. Quicksort - 2

- [ ] Pick a pivot element
  - [ ] Pivot is the „middle“ element between the left and right half of the list
  - [ ] Really does not matter how we pick it
  - [ ] move pivot out of the way
  - [ ] e.g. swap with rightmost element

- **Step 2:** 
  - [ ] Two pointers (***left*** and ***right***) scan starting from the left and the right
  - [ ] The ***left pointer*** is looking for an element ***>*** `pivot`
  - [ ] The ***right*** one is looking for an element ***<*** `pivot`
  - [ ] i.e. both points are looking for an element that is on the wrong side of the `pivot`
  - [ ] When both pointers have found something we ***swap the elements***
  - [ ] ***We stop when the two pointers meet***
  - [ ] Swap `pivot` back ***(swap with left pointer if left pointer > pivot)***

![image](https://user-images.githubusercontent.com/7360266/121894538-88ef5a80-cd1f-11eb-830e-c100105cedbc.png)
<br></br>
- **Step 3:** 
  - [ ] We split the list at the `pivot`
  - [ ] `pivot` element is at its final position now!
  - [ ] It does not matter which list the pivot itself belongs to
  - [ ] The choice of pivot determines size of the two halves
  - [ ] Equally sized halves would be ideal... *(but are not a must!)*

- **Attention:** must not have a „half“ with size 0!
  - This can lead to endless recursion!
  - You must pick a new `pivot` (does not happen if pivot is random anyway)
  - **Another trick:** `pivot` belongs to neither half (pivot is already at correct position now!)

![image](https://user-images.githubusercontent.com/7360266/121894999-0f0ba100-cd20-11eb-9298-5e1371efe8d1.png)
<br></br>

- **Step 4:**
  - [ ] Recursively call quicksort for the ***left*** and ***right*** half
  - [ ] i.e. repeat steps 1 – 4 for each half
  - [ ] Stop if you have a list of size 1 or 0 *(it is already sorted)*

![image](https://user-images.githubusercontent.com/7360266/121895430-7e819080-cd20-11eb-837a-b31876607cbe.png)

---

## 16. Quicksort - Code Example
```c++
void QuickSort(int* array, int iFirst, int iLast)
{
    assert(iFirst < iLast);
    if(iFirst == iLast)
        return;

    int iLeft  = iFirst; 
    int iRight = iLast-1; 
    int iPivot = array[iLast]; 
    do {
        while(array[iLeft]  <= iPivot &&  iLeft  < iLast) iLeft++; 
        while(array[iRight] >= iPivot &&  iRight > iLeft) iRight--; 
        if(iLeft < iRight)
        {
            swap(array[iLeft], array[iRight]); 
        }
    } while(iLeft < iRight);

    if(array[iLeft] > iPivot)
        swap(array[iLast], array[iLeft]);
 
    if(iFirst < iLeft-1)
        QuickSort(array, iFirst,  iLeft-1);
    if(iLeft+1 < iLast)
        QuickSort(array, iLeft+1, iLast); 
}
```
---

## 17. Quicksort - 3

- ***The choice of `pivot` is important***
  - **Worst case:** The list of `n` elements is always split into list sized `(n-1)` and list sized 1
  - It happens if `pivot` is always the smallest / biggest element!
  - It leads to complexity of `n²` *(like SelectionSort)*

- **Alternatives:**
  - Pick `pivot` randomly *(reduces chance of many bad cases)*
  - Pick **3** *(random of fixed)* elements, median value becomes the `pivot`
  - `pivot` value does not have to be an actual value of the list!

---

## 18. Quicksort - 4

#### Optimizations
- `Quicksort` has better complexity behavior than `InsertionSort`, but may still be slower for very small lists
  - i.e. `Quicksort` could call e.g. `InsertionSort` when list size is below a certain threshold
  - Determine threshold with benchmarks
  - You could handle lists with size 2 as special case

---

## 19. Quicksort - Properties

- *Quicksort* is ***unstable***
- *Quicksort* works ***inplace***
  - However, it is recursive and requires `log n` additional stack space in the average case

- *Quicksort* requires efficient (i.e. constant-time) random access to all elements
  - i.e. index access like in an `array`
  - Algorithm is not very suitable for linked lists
  - Compare Insertion Sort

- **Complexity**
  - **Average case:** `n` log `n`
  - **Worst case:** `n²`, which is extremely unlikely if you pick `pivot` cleverly. 
It can pick perfect pivot and guarantee `n` log `n`, but additional overhead makes this impractical

---

## 19. Other Sorting Algorithms

#### Heapsort
- `O(n log n)`
- Improved selection sort

#### Mergesort
- `O(n log n)`
- Like Quicksort, but stable
but requires O(n) additional memory

#### Introsort
- `O(n log n)`
- A version of `Quicksort` that falls back to other algorithms like `Heapsort` in bad cases 
- It is the fastest known stable sorting algorithm
- It is used in C Standard Lib

---
