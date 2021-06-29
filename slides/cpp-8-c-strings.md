## 1. Strings In C
```c++
char acArray[32] = { 0 };
cin >> acArray;
    
cout << acArray << endl;
```

 - `Strings` are `arrays` of `characters`!
- **Convention:** last `character` = 0 to indicate end of `string`(null-terminated)
- All `string` functions expect this
- **Remember:** There is no way to tell the size of an `array` at run-time!
- *Attention:* `0-char` must be within `array` bounds

---

## 2. String Input
````c++
char acMyString[32];

cout << "Enter your name: ";
cin >> acMyString;
cout << "Hello, " << acMyString << "!" << endl;
````

- `cin` can read `strings` from the command line
- But there is no way to tell `cin` the size of the `array`
- **32** `chars` &#8594; user can enter up to **31** characters *(remember: terminating 0 is always appended)*
if user enters more than that &#8594; **crash!**
  
___

## 3. Better String Input
````c++
char acMyString[32];

cout << "Enter your name: ";
cin.getline(acMyString, 32,‘\n‘);
cout << "Hello, " << acMyString << "!" << endl;
````

 #### `cin` has **two** serious problems:
  - It does not know the buffer size; will crash if input is longer than buffer
  - It uses spaces as delimiters, i.e. input will stop at first space character
- **Better:** `cin.getline()`
  - **Function**, requires input buffer size and end-of-input `character`
    
---

## 4. Working With Strings
```c++
char acMyString[32];

cout << "Enter your name: ";
cin >> acMyString;
if(acMyString == "David")  // this is NEVER true!
{
	cout` << "Welcome, David!" << endl;
}
```
- `strings` are `arrays` and **not** `integral` data types!
- They cannot use standard operators like `==` or `+` on them, you have to treat them like arrays!
- As an example, the one above **does not work**

---

## 5. String Function

````c++
from string.h

strlen	- determine length

strcmp	- compare
returns -1, 0 or 1 for <, = and >
strcpy	- copy
target array must be large enough!
strcat 	- concatenate
target array must be large enough!
````

- From `string.h`

- `strlen`	- determine length

- `strcmp`	- compare
  - Returns `-1`, `0` or `1` for `<`, `=` and `>`
- `strcpy`	- copy
  - target `array` must be large enough!
- `strcat` 	- concatenate
  - target `array` must be large enough!
  
---

## 6. Printf
````c++
void printf (char* formatstring, ...)

printf(“%d + %d = %d”, 3, 4, 3+4);
````
A function with variable number of parameters!

---

## 7. Printf -Format String

| **CHARACTER**  |  **TYPE**  |
|  ---  |  ---  |
|  `d`  |  integer, decimal (signed) |
| `o`  | integer, octal  | 
| `X`, `x`  |  integer, Hex using A-F or a-f | 
| `e`  | double, exponential format  | 
| `f` | double, decimal format  | 
| `G`  | like e or like f, whatever is shorter  | 
| `S`, `s`  | string (wider or wprintf)  | 
| `C`, `c`  | character, (wide or wprintf)  | 
| `i`  | integer, signed  | 
| `u`  | integer, unsigned  |
| `p`  |  pointer | 

- Insert `parameter` using `%` and format spec
- `%[flags] [width] [.precision] [{h | l | I | I32 | I64}]type`
- Unrecognized char after % is printed (i.e. %% prints a %)

---

## 8. Printf - Format String - 2

|  **ESCAPE SEQUENCE** | **MEANING**  |
|---|---|
| `\n`  | Newline  |
|  `\r` |  Carriage return |
| `\b`  | Bell  |
| `\t`  |  Tabulator |
| `\0`  | ASCII Zero  |


|  **ESCAPE SEQUENCE** | **MEANING**  |
|---|---|
| `-`  | Left Align  |
| `+`  | Always prefiz with sign (even + ) |
|  `0` |  Pad with leading zeros |
| `Blank" "`  | Pad with leading blanks  |
|  `#` | Prefix hex numbers with `0x` or `0X`  |

---

## 9. Printf - Versions

- `sprintf` – print `string` into `string`
- `fprintf` – print `string` into `file`
- `wprintf` – wide `strings` (i.e. 2 bytes per char)

---

## 10. Printf - Problems

#### No type checks!
- Uses format `string` to determine type of parameters
- May not match

#### Not even number of parameters checked!

#### No bounds check on format string and strings provided as parameters
- May cause protection fault

#### Order of parameters must match order in format string
- International translations of format `strings` might need to change parameter order

---

## 11. Scanf

- Input equivalent to `printf`
- Takes pointer as arguments

