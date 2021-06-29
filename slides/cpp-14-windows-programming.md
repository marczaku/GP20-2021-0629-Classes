## 1. Windows Programming

#### Now: The "old way"
- i.e. C-Style
- “Petzold-Style”
<br></br>
#### Alternatives:
- MFC / ATL
- requires good knowledge of Object Orientation and Templates
- Perfect for tools, but not for games!
<br></br>
#### C# / .NET / Windows Forms
- The future!

---

## 2. Windows Basics

Unlike console programs, windows applications share the system with many other programs.
For example, it does the following:

- ***Shares the processor***
  - i.e. cannot eat up all processing time
  - Should yield processor to others whenever possible
<br></br>
- ***Shares the screen***
  - Cannot draw something where they want to and not when they want to
  - Can be partially or completely covered by other windows
  - Can be minimized, maximized, resized at any time
<br></br>
- ***Share input***
  - Window can gain and lose focus
  - Keyboard only works in active window
  - Mouse clicks may hit other applications

---

## 3. Messages

Windows Applications receive messages from the system. Applications can also send messages to each other
#### *Messages are:*
- Stored in a message queue for each application and processed asynchronously or processed immediately *(synchronously)*
- Windows Application must implement appropriate reactions to many messages
<br></br>
#### *Messages can be:*
- Keyboard and Mouse Input
  - Mouse button pressed / released; mouse moved, mouse dragged, key pressed / released
<br></br>
#### *Window-Messages*
- Window Size changed
- Window Position changed
- Minimize / Maximize / Close-Button
<br></br>
#### *Drawing Requests*
- If window was covered and must be partially redrawn
<br></br>
#### *More Messages:*

- Application Life Cycle
  - Window Creation, Window Destruction, Application Shutdown

- Timer Messages
  - Can set up “alarm clocks” for application

- System Messages
  - Shutdown, Suspend, Registry changed etc.

---

## 4. Message Format
```c++
typedef struct { 
	HWND hwnd; 
	UINT message; 
	WPARAM wParam; 
	LPARAM lParam; 
	DWORD time; 
	POINT pt; 
} MSG;
```

#### Struct MSG
- `HWND` = int = Handle to Window
- Message = id-number (#defines!)
- `WPARAM`, `LPARAM`
  - **Originally:** *Word-Param*, *Long-Param*
  - They are now both ints
  - Their meaning depends on message
- **Time:** when the message was posted
- **Pt:** screen coordinates of mouse at time of posting

---

## 5. Message Loop
```c++
while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
  ```
  
- **Other name:** *Message Pump*
- It is the main loop of the application
- It fetches messages from message queue and dispatches messages to indiviual windows

---

## 6. Message Loop - 2
```c++
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
  ```
- `GetMessage` retrieves message from the message queue for either:
  - A particular window *(specify HWND)*
  - Or all windows of the calling thread *(specify NULL)*
<br></br>
- `TranslateAccelerator` translates Menu-Hotkeys
  - i.e. catches key messages, sends new special command messages

---

## 7. Message Loop - 3
```c++
while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
  ```
  
- `TranslateMessage` translates Key-Messages to Character-Messages, 
think of it as characters that depend on keyboard type and local settings
<br></br>
- `DispatchMessage` sends the message to the approprite window proc, in other words, 
the message contains HWND of target window

---

## 8. Message Proc
```c++
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case WM_PAINT:		... 
	case WM_DESTROY:		...
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
```

- The application must provide a function that receives messages for every window
- It is typically one large switch statement
- It must return ***0*** if the message was processed
- It should call `DefWindowProc()` to process messages it does not handle itself (does the default handling)

---

## 9. Resources

- ***Executables*** or ***DLLs*** can carry a “payload” of data such as:
- Icons
- Bitmaps
- Mouse cursors
- Menus (= text markup)
- Keyboard shortcuts
- Window layouts (= text markup)
- String table (for easy translation!)
- File/version/copyright info
- *Any data you want!*

- No separate data files is needed
- `exe` / `dll` contains its own icon, version info

---

## 10. Resources - 2

- Resource script `(*.rc)` describes all resources
- Visual studio offers graphical editors for most resource types
- Resource compiler generates binary package from resource script
- Linker puts code and resources together

- Resources can be loaded at run-time using special functions
  - `loadString`
  - `loadAccelerator`
  - `loadBitmap`
  - `loadIcon`
  - `loadCursor`


---

## 11. Application Startup
```c++
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	...
}
```

#### EntryPoint:  WinMain
- `HINSTANCE`: Handle to an Application Instance (i.e. integer identifying a task)
- `hInstance` – this instance
- `hPrevInstance` – not used any more, always NULL
  - (used to be handle to app of same type)
- `lpCmdLine`  - Command Line
- `nCmdShow` – how the window is shown
  - `SW_SHOWMAXIMIZED`, `SW_SHOWMINIMIZED`, `SW_SHOWNORMAL` etc.
  - Pass to ShowWindow

---

## 12. Application Startup - 2
```c++
WNDCLASSEX wcex;

wcex.cbSize = sizeof(WNDCLASSEX); 

wcex.style		= CS_HREDRAW | CS_VREDRAW;
wcex.lpfnWndProc		= (WNDPROC)WndProc;
...
wcex.lpszMenuName		= (LPCTSTR)IDC_SIMPLEWINDOWSAPP;
wcex.lpszClassName	= szWindowClass;
wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

return RegisterClassEx(&wcex);
```

#### Register a window class
- Declare struct of type `WNDCLASSEX`
- Fill structure with window description
  - Icon, cursors, background color...
  - Window proc!
- Pass to `RegisterClassEX`

---

## 13. Application Startup - 3
```c++
 hWnd = CreateWindow(szWindowClass, szTitle, 
	WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 
	0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
  ```

- [ ] Create the window
- [ ] Call CreateWindow specifying new window class
- [x] Returns a HWND (handle to window)

- **It can specify:** 
  - Title
  - Initial size
  - Initial position
  - Parent window
  - Additional window styles

---

## 14. Application Startup - 4
```c++
ShowWindow(hWnd, nCmdShow);
UpdateWindow(hWnd);
```

- `ShowWindow` sets the window status
  - Maximized, minimized, normal etc
  - Initially pass value passed into ***WinMain***

- `UpdateWindow` sends a ***WM_PAINT*** to the window
  - Only if the invalid region is not empty

- *And now enter the message loop!*

---

## 15. WM_CREATE

- Sent to window after it has been created (via CreateWindow)

- **Parameters:**
  - `LPARAM` – `Pointer to CREATESTRUCT`
  - `CREATESTRUCT` contains window title, position, size, parent window etc.

---

## 16. WN_CLOSE

- This is sent to window when the user has requested the window to close, either by:
  - Clicking the ***X-Button***
  - Choosing close from the system menu
  - Pressing ***ALT + F4***

- The application can decide what to do now
  - e.g. display a safety-dialog such as *“Do you really want to quit?”*
  - The application should call `DestroyWindow()` to comply with the request

---

## 17. WM_DESTROY

- Sent to window upon destruction
- Sent after window is removed from screen
- Typically, the main window will call `PostQuitMessage()` when destroyed
- This will post a `WM_QUIT` to the application

---

## 18. WM_QUIT

- Tells the application to terminate
- `GetMessage` will return ***0*** when encountering a `WM_QUIT`
- Application message loop is responsible for reacting to this

---

## 19. WM_MOUSE
```c++
#include “windowsx.h”
...
int xPos = GET_X_LPARAM(lParam); 
int yPos = GET_Y_LPARAM(lParam); 
```

- `WM_LBUTTONDOWN` / `WM_LBUTTONUP`
- `WM_RBUTTONDOWN` / `WM_RBUTTONUP`
- `WM_LBUTTONDBLCLCK` / ...
- `WM_MBUTTON`
- `WM_MOUSEMOVE`
etc!

- Mouse Event while Mouse was above this window
- `WParam`: indicates Alt, Control status
- `LParam`: encodes mouse coordinates

---

## 20. WM_SIZE
```c++
int iWidth  = LOWORD(lParam); 
int iHeight = HIWORD(lParam); 
```
- Sent when window has been resized

- **wParam:**
  - `SIZE_MAXIMIZED`
  - `SIZE_MINIMIZED`
  - `SIZE_RESTORED`

- `lParam`: new window size

---

## 21. Creating Child Windows

- Windows are created using `CreateWindow`
- Windows offers many pre-defined window classes such as:
  - Button - `BUTTON`
  - `PushButton`, `RadioButton`, `CheckBox`
  - ComboBox - `COMBOBOX`
  - Edit Control - `EDIT`
  - Rich-Edit Control - `RICHEDIT_CLASS`
  - Listbox - `LISTBOX`
  - Scrollbar - `SCROLLBAR`
  - Scrollbar / Slider
  - Static Text / Bitmap - `STATIC`

---

## 22. Example: Creating a Button
```c++
HWND hButton = CreateWindow(
	“BUTTON”, 
	“MyButton”,
	WS_CHILDWINDOW | BS_PUSHBUTTON, 	
	10, 10,
	200, 50,
	hWnd,
	NULL,
	NULL,
	NULL);
ShowWindow(hButton, SW_SHOW);
```

- ***See MSDN Libary: CreateWindow***
  - Class Name: “BUTTON”
  - Offers own Window Styles (BS_... – chooses Button type!)
  - Must specify` WS_CHILDWINDOW` (i.e. not top-level)
  - Call `ShowWindow()` to make Button visible

---

## 23. Example: Reacting to my Button
```c++
case WM_COMMAND:
  {
    WORD wEvent = HIWORD(wParam);
    if (wEvent == BN_CLICKED  &&  lParam == (LPARAM) hButton)
    {
      // do something here
    }
  }
  break;
  ```
  
- Button sends a `WM_COMMAND` notification to parent window
- Hi-Word of `wParam` contains event code 
  - *(see MSDN for list of possible events for each control type)*
- Lo-Word contains HWND of Button

---

## 24. Communicating with Child Windows

- You cannot call methods on child windows, because we have no classes for them
- Instead, use generic methods that work for all windows, such as:
  - `EnableWindow()`
  - `SetWindowPos()`
- For specific functions, you must send messages to the windows
  - Using `SendMessage()`
  - e.g. `BM_SETCHECK` / `BM_GETCHECK` set or retrieve check state of a CheckBox control

---

## 25. Painting

- Window is only supposed to paint as a reaction to `WM_PAINT` message
- Window must be able to react to `WM_PAINT` at any time
  - i.e. must always be able to completely paint itself

- Can draw stuff using GDI *(Graphics Device Interface)*
  - Windows Graphics API


---

## 26. Paint - 2
```c++
case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);
		...
		EndPaint(hWnd, &ps);
		break;
	}
  ```
  
- Painting started using `BeginPaint()`
- Painting ended using `EndPaint()`
- `BeginPaint()` returns HDC
  - HDC = Handle to Device Context (= integer value)
  - Identifies target output region, i.e. the window
  - All drawing functions require HDC
<br></br>
- **PAINTSTRUCT:**
  - Declared by user, filled by windows (call by reference!)
  - Contains HDC (again)
  - Bool fErase – tells user to draw background or not
  - RECT rcPaint – area that needs repainting
  - Output is restricted (“clipped”) to that area anyway
  - Can optimize application by repainting only needed area!

---

## 27. Drawing Functions

- `MoveTo`
- `LineTo`
- `Ellipse`
- `Rectangle`
- `FillRect`
- `Pie`
- `RoundRect`
- `Polygon`
- `Chord`

---

## 28. Pens
```c++
HPEN hPen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0)); 
HANDLE hOldPen = SelectObject(hdc, hPen);
...
SelectObject(hdc, hOldPen);
DeleteObject(hPen);
```

- **Pens:** Used for drawing lines
  - Different colors
  - Different patterns (dashed, dotted etc.)
- CreatePen = HPEN (Handle to Pen)
- RGB macro = COLORREF
- You must select the pen into the device context *(will return old pen!)*
- All subsequent operations will use it
- When finished, should set old pen again
- Must destroy Pen using DeleteObject

---

## 29. Brushes
```c++
HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); 
HANDLE hOldBrush = SelectObject(hdc, hBrush);
...
SelectObject(hdc, hOldBrush);
DeleteObject(hBrush);
```

- **Brushes:** Used to fill shapes
  - Different colors
  - Different patterns

- `CreateSolidBrush` will create a solid brush, i.e. no pattern
- Use just like Pens, i.e. select, unselect, delete
- See also: `CreateHatchBrush`, `CreatePatternBrush`
- Used by functions like `FillRect`

---

## 30. Invalid Regions
```c++
InvalidateRect(hWnd, NULL, true);

RECT r;
r.top = ..; r.bottom = ..; r.left = ..; r.right = ..;
InvalidateRect(hWnd, &r, true);
```

- Windows keeps list of invalid regions of a window
  - i.e. regions that need repainting after window resize or uncovering of window
- Sends `WM_PAINT` – Message to windows whose invalid region is not empty
- Can declare regions as invalid manually
- Correct way to trigger redraw
- **Parameter 2:** rect to invalidate (optional; NULL = everything)
- **Parameter 3:** erase background yes / no

---

## 31. Timers

- You can create Timers that notify the window when a specified amount of time has elapsed
- Use `SetTimer` to create a timer
  - Specify Timer id *(arbitrary number)*
  - Specify the amount of time
- Windows will send `WM_TIMER-Message` when that time has elapsed
- `wParam` will specify Timer id
- Use `KillTimer` to destroy a timer before it elapses

---

## 32. Asynchronous Keyboard Input

- `GetAsyncKeyState` will return status of key
<br></br>
- Use virtual key codes
  - Not the key codes the hardware uses, but some abstraction of that
  - `VK_UP`, `VK_DOWN`, `VK_A` etc...
<br></br>
- **Or mouse buttons:** `VK_LBUTTON`, `VK_RBUTTON`
<br></br>
- Can query different shift, control, alt keys independently: `VK_LSHIFT`, `VK_RSHIFT`, or query if either of them is down: `VK_SHIFT`
<br></br>
- **Return value:** `SHORT`, most significant bit set if key is down

---

## 33. Drawing Bitmaps
```c++
HBITMAP hbm = (HBITMAP) LoadImage(NULL, “ship.bmp”, IMAGE_BITMAP, 
		0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);

	HDC hdcMem = CreateCompatibleDC(NULL);
	SelectObject(hdcMem,hbm);
  ```
 
- You can load ***Bitmaps*** using `LoadImage` or `LoadBitmap`
  - This will return `HBITMAP`
<br></br>
- Bitmap must be selected into a compatible Device Context
  - Compatible = same color depth and color format as output window
- - i.e. bitmap must be converted to correct format
<br></br>
- Can create a memory Device Context using `CreateCompatibleDC`
  - Pass `NULL` to make it compatible to desktop
  
---

## 34. Drawing Bitmaps - 2 
```c++
BITMAP bm;
	GetObject(hbitmap, sizeof(bm), &bm);
	int iWidth  = bm.bmWidth;
	int iHeight = bm.bmHeight;
  ```
  
- Query information about Bitmap using `GetObject()`
- Generic query-information function for all kinds of GDI objects
- It will fill different structures depending on type of handle passed
- For bitmap handles, pass pointer to `BITMAP` struct
- It ill provide size, color depth etc.
- **Remember:**
  - Destroy bitmap handle with `DeleteObject()`
  - Destory Device Context with `DeleteDC()`

---

## 35. Drawing Bitmaps - 3
```c++
BitBlt(hdc, xpos, ypos, xsize, ysize, hdcMem, 0, 0, SRCCOPY);
```

- You can draw bitmaps using Blt-Functions, pronounced “Blit”
  - Blt = *Block Transfer* or *Bit-Block-Transfer*
  - i.e. copying a chunk of memory to another
- Bitmap is already in correct format in Memory-DC and can now be copied to window-DC!

- BitBlt: specify:
  - Source HDC, target HDC
  - Target rectangle, source position (upper-left corner)
  - Copy mode: SRCCOPY = make identical copy

---

## 36. Bitmap Scaling
```c++
StretchBlt(	hdc, xpos, ypos, bmpxsize*5, bmpysize*5, hdcMem, 
		0, 0, bmpxsize, bmpysize, SRCCOPY);
```
- The `StretchBlt` function is able to scale bitmap on the fly
- It is the same as `BitBlt` but can specify both target and source rectangle
- The size does not have to match
- Needs to know size of bitmap

---

## 37. Transparent Bitmaps
```c++
TransparentBlt(hdc,xpos,ypos,xsize,ysize,hdcMem,
		0,0,bmpxsize, bmpysize, RGB(0,255, 0));
```

- `TransparentBlt` is able to make areas of the bitmap transparent
  - It works just like `StretchBlt` but takes a color key instead of copy mode
  - i.e. can choose a color which will be treated as transparent
- **Attention:** 
  - You must link with `Msimg32.lib`

---

## 38. Task

#### Make A Class For: 
- [ ] Windows GDI bitmaps
- [ ] Bitmap Animations
- [ ] Sprites

---

## 39. Double Buffering

- Drawing objects on top of each will cause screen to *“flicker”*
- **Why?**
  - Contents of video memory shown in regular intervals *(sent to monitor)*
  - 60 – 120Hz, depending on monitor and resolution
  - Image may be displayed before everything is ready
  - e.g. between clear screen and drawing sprites

![image](https://user-images.githubusercontent.com/7360266/123093911-8af69f00-d42c-11eb-878a-f714e888d37d.png)
<br></br>
#### Solution
- Do not assemble the image in video memory, instead, assemble in main memory. ***Display only when finished***

![image](https://user-images.githubusercontent.com/7360266/123094091-c6916900-d42c-11eb-8438-9ca3ea4aebaf.png)
<sup>Double Buffering with off-screen surface</sup>

---

## 40. Double Buffering - 2
```c++
RECT r;
GetClientRect(hWnd, &r);
HDC hdc = GetDC(hWnd);
HDC memDC = CreateCompatibleDC(hdc);
HBITMAP hMemBmp = CreateCompatibleBitmap(hdc, r.right, r.bottom);
SelectObject(memDC, hMemBmp);
ReleaseDC(hWnd, hdc)
```

#### How To Create An Off-screen Surface:
- [ ] Find out window size using `GetClientRect`
  - [ ] **Attention:** will change with window resize!
- [ ] Get your window DC using `GetDC`
- [ ] Create a compatible bitmap with required size using `CreateCompatibleBitmap` 
- [ ] Select new bitmap into new DC using `CreateCompatibleDC` and `SelectObject`

---

## 41. Double Buffering - 3
```c++
case WM_PAINT:
	... draw everything into memDC ...

	RECT r;
	GetClientRect(hWnd, &r);
	HDC hdc = BeginPaint(hWnd, &ps);
	BitBlt(hdc, 0, 0, r.right, r.bottom, memDC, 0, 0, SRCCOPY);
	EndPaint(hWnd, &ps);
  ```
- Do all the drawing into the off-screen hdc first
- Blit this to screen using `BitBlt`
- ***Don’t forget to delete bitmap and DC at program shutdown!***

---
