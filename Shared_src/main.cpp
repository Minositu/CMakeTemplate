// CMakeProject2.cpp: define el punto de entrada de la aplicación.
//
#include "main.h"
#ifdef PLATFORM_LINUX
using namespace std;

#include <string.h>
#include <xcb/xcb.h>

int main()
{
	cout << "Hello CMake." << endl;
	xcb_connection_t* c;
	xcb_screen_t* screen;
	xcb_drawable_t       win;
	xcb_gcontext_t       foreground;
	xcb_gcontext_t       background;
	xcb_generic_event_t* e;
	uint32_t             mask = 0;
	uint32_t             values[2];

	char string[] = "Testing, testing 123 123 123 123 123 123 123";
	uint8_t string_len = strlen(string);

	xcb_rectangle_t rectangles[] = {
	  {40, 40, 20, 20},
	};

	c = xcb_connect(NULL, NULL);

	/* get the first screen */
	screen = xcb_setup_roots_iterator(xcb_get_setup(c)).data;

	/* root window */
	win = screen->root;

	/* create black (foreground) graphic context */
	foreground = xcb_generate_id(c);
	mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
	values[0] = screen->black_pixel;
	values[1] = 0;
	xcb_create_gc(c, foreground, win, mask, values);

	/* create white (background) graphic context */
	background = xcb_generate_id(c);
	mask = XCB_GC_BACKGROUND | XCB_GC_GRAPHICS_EXPOSURES;
	values[0] = screen->white_pixel;
	values[1] = 0;
	xcb_create_gc(c, background, win, mask, values);

	/* create the window */
	win = xcb_generate_id(c);
	mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	values[0] = screen->white_pixel;
	values[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;
	xcb_create_window(c,                             /* connection    */
		XCB_COPY_FROM_PARENT,          /* depth         */
		win,                           /* window Id     */
		screen->root,                  /* parent window */
		0, 0,                          /* x, y          */
		450, 450,                      /* width, height */
		10,                            /* border_width  */
		XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class         */
		screen->root_visual,           /* visual        */
		mask, values);                 /* masks         */

	xcb_change_property(c, XCB_PROP_MODE_REPLACE, win, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, strlen("Hello CMake!"), "Hello CMake!");

	/* map the window on the screen */
	xcb_map_window(c, win);

	xcb_flush(c);

	while ((e = xcb_wait_for_event(c))) {
		switch (e->response_type & ~0x80) {
		case XCB_EXPOSE:
			//xcb_poly_rectangle(c, win, foreground, 1, rectangles);
			xcb_image_text_8(c, string_len, win, background, 20, 20, string);
			xcb_flush(c);
			break;
		case XCB_KEY_PRESS:
			break;
		}
		free(e);
	}

	//cout << "He" << endl;
	return 0;
}
#endif

#ifdef PLATFORM_WIN32
#include <windows.h>

static LRESULT WindowProc(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
/* More info at [2] */
    switch(msg)
    {
        /*                                                              */
        /* Add a win32 push button and do something when it's clicked.  */
        /* Google will help you with the other widget types.  There are */
        /* many tutorials.                                              */
        /*                                                              */
        case WM_CREATE: {
            HWND hbutton=CreateWindow("BUTTON","Hey There",  /* class and title */
                                      WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON, /* style */
                                      0,0,100,30,            /* position */
                                      h,                     /* parent */
                                      (HMENU)101,            /* unique (within the application) integer identifier */
                                      GetModuleHandle(0),0   /* GetModuleHandle(0) gets the hinst */
                                      );
        } break;

        case WM_COMMAND: {
            switch(LOWORD(wp)) {
                case 101: /* the unique identifier used above. These are usually #define's */
                    PostQuitMessage(0);
                    break;
                default:;
            }
        } break;


        /*                                 */
        /* Minimally need the cases below: */
        /*                                 */
        case WM_CLOSE: PostQuitMessage(0); break;
        default: 
            return DefWindowProc(h,msg,wp,lp);
    }
    return 0;
}

int WinMain(HINSTANCE hinst,
            HINSTANCE hprev,
            LPSTR     cmdline,
            int       show) {
    if(!hprev){
        WNDCLASS c={0};
        c.lpfnWndProc=WindowProc;
        c.hInstance=hinst;
        c.hIcon=LoadIcon(0,IDI_APPLICATION);
        c.hCursor=LoadCursor(0,IDC_ARROW);
        c.hbrBackground= WHITE_BRUSH;
        c.lpszClassName="MainWindow";
        RegisterClass(&c);
    }

    HWND h=CreateWindow("MainWindow",          /* window class name*/
                   "WindowTitle",              /* title  */
                   WS_OVERLAPPEDWINDOW,        /* style */
                   CW_USEDEFAULT,CW_USEDEFAULT,/* position */
                   CW_USEDEFAULT,CW_USEDEFAULT,/* size */
                   0,                          /* parent */
                   0,                          /* menu */
                   hinst,                      
                   0                           /* lparam -- crazytown */
                   );
    ShowWindow(h,show);

    while(1) {  /* or while(running) */
        MSG msg;
        while(PeekMessage(&msg,0,0,0,PM_REMOVE)) { /* See Note 3,4 */
            if(msg.message==WM_QUIT)
                return (int)msg.wParam;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }        
    }
    return 0;
}

/* NOTES
 1. when googling for api docs, etc. prefix everything with msdn.  e.g: msdn winmain
 2. prefer msdn docs to stack overflow for most things.
    When in doubt look for Raymond Chen's blog "The Old New Thing."

 3. Overview of the event loop is at [1].
 4. This event-loop spins when no events are available, consuming all available cpu.
    Also see GetMessage, which blocks until the next message is received.

    Use PeekMessage when you want your application loop to do something while not recieving
    events from the message queue.  You would do that work after the while(PeekMessage(...))
    block.
*/
/* REFERENCES
  [1] : https://msdn.microsoft.com/en-us/library/windows/desktop/ms644927%28v=vs.85%29.aspx
  [2]: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633570(v=vs.85).aspx#designing_proc
*/
#endif