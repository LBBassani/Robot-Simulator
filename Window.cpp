#include "Window.h"

/*----------------------------------------------------------------------------*/
window::window()
{
	g_bDoubleBuffered = GL_FALSE;
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
void
window::checkForGLXSupport()
{
	if( !glXQueryExtension( g_pDisplay, &errorBase, &eventBase ) )
	{
		// TODO return an error code instead of exit.
		fprintf(stderr, "glxsimple: %s\n", "X server has no OpenGL GLX extension");
		exit(1);
	}
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
window::initializeWindow()
{
	bool success = openXServerConnection();

	if (success)
	{
		checkForGLXSupport();
		bool successOnDoubleBufferedVisual = tryDoubleBufferedVisual();

		if( successOnDoubleBufferedVisual )
		{
			g_bDoubleBuffered = GL_TRUE;
		}
		else
		{
			/*
			If we can't find a double-bufferd visual,
			try for a single-buffered visual...
			*/

			g_bDoubleBuffered = GL_FALSE;
			bool successOnDoubleBufferedVisual = trySingleBufferedVisual();

			if( !successOnDoubleBufferedVisual )
			{
				// TODO return an error code instead of exit.
				fprintf(stderr,
						  "glxsimple: %s\n", "no RGB visual with depth buffer");
				exit(1);
			}
		}

		// Create an OpenGL rendering context
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

		// Create an X colormap since we're probably not using the default visual
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

		// Create an X window with the selected visual
		g_window = XCreateWindow( g_pDisplay,
								RootWindow(g_pDisplay, visualInfo->screen),
								0, 0,     // x/y position of top-left outside corner of the window
								800, 800, // Width and height of window
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
	}
	else
	{
		// TODO return an error code instead of exit.
		fprintf(stderr, "glxsimple: %s\n", "X server has no OpenGL GLX extension");
		exit(1);
	}
}



/*----------------------------------------------------------------------------*/
bool
window::processWindow(
                     void ( * mouseFunc )( int type, int button, int x, int y ),
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
				int x = mouseEvent->x;
				int y = mouseEvent->y;

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
window::showWindow()
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
