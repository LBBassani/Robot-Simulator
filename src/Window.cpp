#include "Window.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>		/* BitmapOpenFailed, etc.    */
#include <X11/cursorfont.h>	/* pre-defined crusor shapes */

/*----------------------------------------------------------------------------*/
window::window(int w, int h)
{
    width = w;
    height = h;
	g_bDoubleBuffered = GL_FALSE;
	initialize();
	open();
}



/*----------------------------------------------------------------------------*/
bool
window::openXServerConnection()
{
	bool success;
	g_pDisplay = XOpenDisplay( NULL );

	if( g_pDisplay == NULL )
	{
		fprintf(stderr, "glxsimple: %s\n", "could not open display");
		success = false;
	}
	else
	{
		success = true;
	}
	return success;
}



/*----------------------------------------------------------------------------*/
bool
window::checkForGLXSupport()
{
	bool status =  glXQueryExtension( g_pDisplay, &errorBase, &eventBase );
    if(!status)
	{
		fprintf(stderr, "glxsimple: %s\n", "X server has no OpenGL GLX extension");
	}
    return status;
}



/*----------------------------------------------------------------------------*/
bool
window::tryDoubleBufferedVisual()
{
	int doubleBufferVisual[]  =
	{
		GLX_RGBA,           // Needs to support OpenGL
		GLX_DEPTH_SIZE, 16, // Needs to support a 16 bit depth buffer
		GLX_DOUBLEBUFFER,   // Needs to support double-buffering
		None                // end of list
	};

	visualInfo = glXChooseVisual( g_pDisplay, DefaultScreen(g_pDisplay),
														   doubleBufferVisual );
	return ( visualInfo != NULL );
}



/*----------------------------------------------------------------------------*/
bool
window::trySingleBufferedVisual()
{
	int singleBufferVisual[] =
	{
		GLX_RGBA,           // Needs to support OpenGL
		GLX_DEPTH_SIZE, 16, // Needs to support a 16 bit depth buffer
		None                // end of list
	};

	visualInfo = glXChooseVisual( g_pDisplay, DefaultScreen(g_pDisplay),
														   singleBufferVisual );
	return ( visualInfo != NULL );
}



/*----------------------------------------------------------------------------*/
void
window::createOpenGLRenderingContext()
{
	glxContext = glXCreateContext( g_pDisplay,
								visualInfo,
								NULL,      // No sharing of display lists
								GL_TRUE ); // Direct rendering if possible

	if( glxContext == NULL )
	{
		// TODO return an error code instead of exit.
		fprintf(stderr, "glxsimple: %s\n", "could not create rendering context");
		exit(1);
	}
}




/*----------------------------------------------------------------------------*/
void
window::createXColorMap()
{
	colorMap = XCreateColormap( g_pDisplay,
								RootWindow(g_pDisplay, visualInfo->screen),
								visualInfo->visual,
								AllocNone );

	windowAttributes.colormap     = colorMap;
	windowAttributes.border_pixel = 0;
	windowAttributes.event_mask   = ExposureMask           |
									VisibilityChangeMask   |
									KeyPressMask           |
									KeyReleaseMask         |
									ButtonPressMask        |
									ButtonReleaseMask      |
									PointerMotionMask      |
									StructureNotifyMask    |
									SubstructureNotifyMask |
									FocusChangeMask;
}



/*----------------------------------------------------------------------------*/
void
window::initialize()
{
	bool success = openXServerConnection();

	if (success)
	{
		if(!checkForGLXSupport()) return;
		bool successOnDoubleBufferedVisual = tryDoubleBufferedVisual();

		if( successOnDoubleBufferedVisual )
		{
			g_bDoubleBuffered = GL_TRUE;
		}
		else
		{
			g_bDoubleBuffered = GL_FALSE;
			bool successOnDoubleBufferedVisual = trySingleBufferedVisual();

			if( !successOnDoubleBufferedVisual )
			{
				// TODO return an error code instead of exit.
				fprintf(stderr, "glxsimple: %s\n", "no RGB visual with depth buffer");
				exit(1);
			}
		}

		createOpenGLRenderingContext();
		createXColorMap();

		// Create an X window with the selected visual
		g_window = XCreateWindow( g_pDisplay,
								RootWindow(g_pDisplay, visualInfo->screen),
								0,0,     // x/y position of top-left outside corner of the window
								width, height, // Width and height of window
								0,        // Border width
								visualInfo->depth,
								InputOutput,
								visualInfo->visual,
								CWBorderPixel | CWColormap | CWEventMask,
								&windowAttributes );

		const char * const name = "Warehouse Computer Graphics";
		XSetStandardProperties( g_pDisplay, g_window,
								name,
								name,
								None,
								NULL,
								0,
								NULL );

		// Bind the rendering context to the window
		glXMakeCurrent( g_pDisplay, g_window, glxContext );

		// Request the X window to be displayed on the screen
		XMapWindow( g_pDisplay, g_window );

		Cursor font_cursor,		/* handles for the cursors we will create.   */
		icon_cursor;

		/* create a 'watch' cursor. */
	    font_cursor = XCreateFontCursor(g_pDisplay, XC_sailboat);
	    /* attach this cursor to our window. */
	    XDefineCursor(g_pDisplay, g_window, font_cursor);
	    XSync(g_pDisplay, False);

	}
	else
	{
		// TODO return an error code instead of exit.
		fprintf(stderr, "glxsimple: %s\n", "X server has no OpenGL GLX extension");
		exit(1);
	}
}



/*----------------------------------------------------------------------------*/
void
window::open()
{
	XMapWindow( g_pDisplay, g_window );
}



/*----------------------------------------------------------------------------*/
bool
window::process( void ( * mouseFunc )( int type, int button, int x, int y ),
                void ( * keyPress )(int code), void ( * keyRelease )(int code) )
{
	XEvent event;

	while( XPending(g_pDisplay) > 0)
	{
		XNextEvent( g_pDisplay, &event );

		switch( event.type )
		{
			case KeyPress:
			{
				int code = event.xbutton.button;
				keyPress(code);
                break;
			}

			case KeyRelease:
			{
				int code = event.xbutton.button;
				keyRelease(code);
                break;
			}

			case MotionNotify:
			case ButtonPress:
			case ButtonRelease:
			{
				XButtonEvent* mouseEvent = (XButtonEvent*)(&event);

				int type =  mouseEvent->type;
				int button = mouseEvent->button;
				int x = mouseEvent->x - width/ 2;
				int y = mouseEvent->y - height/2;

				mouseFunc(type, button, x, y);
                break;
			}

			case ConfigureNotify:
			{
				glViewport( 0, 0, event.xconfigure.width,
                                                      event.xconfigure.height );
                break;
			}

			case DestroyNotify:
			{
				return false;
			}
		}
	}

	return true;
}



/*----------------------------------------------------------------------------*/
void
window::update()
{
	if( g_bDoubleBuffered )
	{
        // Buffer swap does implicit glFlush
        glXSwapBuffers( g_pDisplay, g_window );
    }
	else
	{
        glFlush();
    }
}
