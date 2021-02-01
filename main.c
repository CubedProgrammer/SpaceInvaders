#include<pthread.h>
#include<unistd.h>
#include<X11/Xlib.h>
#define WIDTH 1024
#define HEIGHT 576
#define NAME "Space Invaders"
#define SPACE 0x41
#define LEFT 38
#define RIGHT 40
volatile int running;
Display *d;
int s;
Window root, win;
GC gc;
XEvent evt;
void *keyhandler(void *arg);
int main(int argl, char *argv[])
{
	d = XOpenDisplay(NULL);
	s = DefaultScreen(d);
	root = RootWindow(d, s);
	win = XCreateSimpleWindow(d, root, 0, 0, WIDTH, HEIGHT, 1, 0, 0);
	gc = DefaultGC(d, s);
	XMapWindow(d, win);
	XStoreName(d, win, NAME);
	XSelectInput(d, win, ExposureMask | KeyPressMask);
	pthread_t th;
	pthread_create(&th, NULL, &keyhandler, NULL);
	running = 1;
	while(running)
	{
		XSetForeground(d, gc, 0);
		XFillRectangle(d, win, gc, 0, 0, WIDTH, HEIGHT);
		usleep(16666);
	}
	return 0;
}
void *keyhandler(void *arg)
{
    XNextEvent(d, &evt);
    while(evt.type != KeyPress || evt.xkey.keycode != 9)
    {
        if(evt.type == KeyPress)
        {
            switch(evt.xkey.keycode)
            {
                case 38:

                    break;
                case 40:

                    break;
            }
        }
        XNextEvent(d, &evt);
    }
    running = 0;
    return NULL;
}
