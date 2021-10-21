## 1. Problem

- We are looking for an object in a list
  - **Example:**
  - List of names + phone numbers
  - Find phone number for given name
<br></br>
- If we use a ***Dynamic Array*** or ***Linked List*** for this problem,
what is the time behavior of the search?

---

## 2. Intelligent Searching

Searching in a phone book does not take linear time, because the phone book is ordered.  
An ordered data structure can significantly speed up a search!

---

## 3. Divide and Conquer

**Let‘s play a game**
1. I pick a number between *1* and *100*
2. You have to guess the number
3. For every guess, I reply *higher*, *lower* or *correct*
<br></br>
**What strategy do you use?**
1. First guess should be *50*
2. The answer will eliminate half of the possible numbers!
<br></br>
This is the divide and Conquer strategy, it finds a solution in `log2n` steps, `O(log n)`

---

## 4. Binary Search

#### Applying the Divide and Conquer Idea to Search

1. **Problem:** Find a name in a list, or find out the name is not there
2. **Prerequisite:** List is sorted
3. **Algorithm:** 
  - Go to the middle element of the list
  - If this is the wanted name  bingo!
  - If not, decide if wanted name is before or after that name, eliminating half the list
4. Repeat



| Names      | 
| :---        |   
|  Adam    |
| Bertil   |
| Cesar     |
|  David |
|   Filip   |
|  Gustav  |
|   Helge   |
| Ivar   |
|   Johan   |
|  Kalle  |
|    Ludvig  |
|  Martin  |
| Niklas     |
| Olof   |
|  Petter    |
|  Qvintus  |

---

## 5. The Binary Tree

![image](https://user-images.githubusercontent.com/7360266/123813216-0062e380-d8f5-11eb-9ef9-7c073eef460d.png)

- A ***binary tree*** is a special data structure, ideal for binary search
  - Every node has *0*, *1* or *2* children, called **left** and **right** child
  - Every node is the root of its own sub tree (i.e. every node a a left and right sub tree)
  - A ***root node*** has no parent node and ***leaf nodes*** have no children
- This can be implemented in diffent ways

---

## 6. Heaps

![image](https://user-images.githubusercontent.com/7360266/123813733-6f403c80-d8f5-11eb-9ddd-e6525bc0a232.png)

A ***Heap***, also called ***partially ordered tree*** or ***binary search tree***, 
is a binary tree that fulfills a special heap condition.  
For every node, all elements in the left sub tree are smaller than all elements in the right sub tree.

---

## 7. Heaps - Operations
```c++
if(!root)
    root = newElement
else
    currentNode = root
    while(currentNode)
        if(newElement < currentNode)
	    if(!currentNode->leftChild
                 currentNode->leftChild = newElement
                 break
             else
                 currentNode = currentNode->leftChild
        else
	    if(!currentNode->rightChild
                 currentNode->rightChild = newElement
                 break
             else
                 currentNode = currentNode->rightChild
 ```
 
#### Inserting an Element Into the Heap
- Crawl down the heap, go left / right depending on current node being < or > new element
- Insert new element when you reach a leaf node
- Searching an element in a heap works almost the same way!


---

## 8. Heaps - Implementation
```c++
template<typename T>
class CBinaryTreeNode
{
public:
    T  m_xData;

    CBinaryTreeNode<T>*	m_pLeft;
    CBinaryTreeNode<T>*	m_pRight;
};
```
```c++
template<typename T>
class CBinaryTree
{
    CBinaryTreeNode<T>*	m_pRoot;
public:
    CBinaryTreeNode<T>*   Find(T);
    CBinaryTreeNode<T>*   Add(T);
};
```

#### Implementation, Version 1: 
- Using pointers, similar to linked list
  - (we assume that T supports operators < and ==)

---

## 9. Heaps - Implementation - 2

![image](https://user-images.githubusercontent.com/7360266/123815862-1e314800-d8f7-11eb-9a79-02b32a82f16b.png)

#### Implementation, Version 2:
- **Using a normal array:**
  - Root is saved at position `0`
  - Left child of n is at `2*n + 1`
right child of n is at `2*n + 2`
<br></br>
- The array contains tree level by level, some locations in the array may be empty
- Some people call this particular implementation of binary trees a heap

---

## 10. Heaps - Deleting Elements

*How do you delete an element in the middle of a binary tree?*  
Deleting is easy, but you have to preserve the heap condition. Disconnecting node `p`
reinserts `p`‘s children *(the full subtrees!)* into the tree, just like new elements.
Then, delete `p`

---

## 11. Tree Traversal

- ***Traversal*** = Traveling through the tree, "visiting" each node
- Unlike with linear list *(who have a beginning and an end)*, there are different methods to traverse a tree,
as an example:
  - Preorder
  - Inorder
  - Postorder
  - Level-order

---

## 12. Tree Traversal - 2
```c++
Traverse(node n)
{
    Visit(n);
    Traverse(n.leftchild);
    Traverse(n.rightchild);
}
```
<sup>Preorder Traversal, or Depth-First-Traversal</sup>
<br></br>
```c++
Traverse(node n)
{
    Traverse(n.leftchild);
    Visit(n);
    Traverse(n.rightchild);
}
```
<sup>Inorder Traversal, or Symmetric Traversal</sup>
<br></br>
```c++
Traverse(node n)
{
    Traverse(n.leftchild);
    Traverse(n.rightchild);
    Visit(n);
}
```
<sup>Postorder Traversal</sup>
<br></br>
```c++
Queue.AddToBack(root);
while(not Queue.Empty())
    e = Queue.RemoveFrontElement();    
    Visit(e);
    if(e.leftchild)  Queue.AddToBack(e.leftchild);
    if(e.rightchild) Queue.AddToBack(e.rightchild);
}
```
<sup>Level-Order-Traversal, or Symmetric Traversal</sup>

---

## 13. Bringing Balance to the Force

![image](https://user-images.githubusercontent.com/7360266/123992575-05df2d00-d9cc-11eb-9c79-e6613afe037e.png)

- Trees can be unbalanced if input comes in the *wrong* order, 
this is also called ***degenerated trees***
- The search time in the tree above is *linear*
- Memory consumption for an array-implementation is *abysmal*
- In a balanced tree, most non-leaf nodes have **two** children
  - i.e. all levels except the last one are *(almost)* fully populated
- To keep search speed up, you may need to balance the tree
- to balance the tree, we could either *rebuild the entire tree* or *randomize the tree*
- It is also possible to use a balanced tree building approach, like *red-black trees* and *AVL-trees*

---

## 14. Bringing Balance to the Force - 2

![image](https://user-images.githubusercontent.com/7360266/123994117-5a36dc80-d9cd-11eb-86e7-3eec64c5777b.png)

#### Rebuilding the Tree
- **Version 1:** 
  - Random, insert elements into the new tree in random order; which leads to a high chance for a balanced tree
- **Version 2 (picture):**
  - Create a new, sorted list of entries; then build a new tree
  - Insert the middle element first, splitting the list in two
  - Insert two middle elements of the two sub-lists next, splitting the list in *4*
  - Insert the `4` middle elements etc.
  - ***This is somewhat similar to quicksort!***

---

## 15. Tree Rotation

- A tree rotation is an algorithm that **changes the structure of a tree**, but preserves the ordering of elements
- This is used by many balancing algorithms

---

## 16. Tree Rotation - 2

![image](https://user-images.githubusercontent.com/7360266/123994979-29a37280-d9ce-11eb-8630-0d27f02f1bb2.png)

#### Left Pivot
- `pivot` = `root.left`
- `root.left` = `pivot.right`
- `pivot.right` = `root`
- *(and correct child pointer of old 
root‘s parent to pivot)*

#### Right Pivot
- `pivot` = `root.right`
- `root.right` = `pivot.left`
- `pivot.left` = `root`
- *(and correct child pointer of old
root‘s parent to pivot)*
<br></br>
- **Observe** that the rotation lowers root 1 level and lifts pivot up 1 level. 
- It also moves pivot into roots original position

---

## 17. AVL-Trees

![image](https://user-images.githubusercontent.com/7360266/123995806-fad9cc00-d9ce-11eb-96b6-38b18d9a0ddc.png)

- BST with special self-balancing add algorithm
- It is named after its two inventors, G.M. Adelson-Velsky and E.M. Landis (1962)
- Every node receives a ***balance factor*** *(stored in the node)*
  - This means that the height of ***right sub-tree*** equals the height of ***left sub-tree***
  - The empty tree is assumed to have the height of ***0***
- A valid ***AVL*** tree has a balance factor of ***-1***, ***1*** or ***0*** for every node
  - i.e. always stays balanced
  - This guarantees a maximum search time of `O(log n)`

---

## 18. AVL-Trees - 2

- **Again:** The balance factors must be ***-1***, ***1*** or ***0***
- *When you add a new child to node `p`, 3 things can happen to balance factor of x:*
  - Balance of `p` changes from ***0*** to ***1*** or ***-1*** 
  - Balance of `p` changes from ***-1*** or ***1*** to ***0*** 
  - Balance of `p` changes from ***-1*** or ***1*** to ***-2*** or ***2***
- If the balance factor of the parent node becomes ***2*** or ***-2***, a rebalance operation must be performed

---

## 19. AVL-Trees - 3

- **Rebalancing:**
  - There are ***4*** different cases *(2 mirrored pairs)*
  - Balance can be restored with a single or a double rotation
  - Double rotation means ***rotate right*** followed by ***rotate left***, or the other way around
- This must be done recursively for all parent nodes of the newly inserted node, up to the root
  - But only if the balance factor is ***-2*** or ***2***

---

## 20. AVL-Trees - 4

![image](https://user-images.githubusercontent.com/7360266/123997378-a0416f80-d9d0-11eb-8536-515545a5fbf5.png)

---
