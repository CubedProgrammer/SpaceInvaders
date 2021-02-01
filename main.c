#include<pthread.h>
#include<stdbool.h>
#include<stdio.h>
#include<unistd.h>
#include<X11/Xlib.h>
#include"player.h"
#define WIDTH 1024
#define HEIGHT 576
#define NAME "Space Invaders"
#define SPACE 0x41
#define LEFT 38
#define RIGHT 40
#define EVTMASK (KeyPressMask | KeyReleaseMask)
volatile int running;
Display *d;
int s;
Window root, win;
GC gc;
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
	struct PlayerShip player;
	player.x = WIDTH / 2;
	player.y = HEIGHT * 2 / 3;
	player.vx = 0;
	pthread_t th;
	pthread_create(&th, NULL, &keyhandler, &player);
	running = 1;
	while(running)
	{
		XSetForeground(d, gc, 0);
		XFillRectangle(d, win, gc, 0, 0, WIDTH, HEIGHT);
		PlayerTick(&player);
		XSetForeground(d, gc, 0xffffff);
		XFillRectangle(d, win, gc, player.x - 16, player.y - 16, 32, 32);
		usleep(16666);
	}
	return 0;
}
void *keyhandler(void *arg)
{
	struct PlayerShip *player = arg;
	XEvent evt;
    bool b = XCheckWindowEvent(d, win, EVTMASK, &evt);
    while(evt.type != KeyPress || evt.xkey.keycode != 9)
    {
    	printf("%d %u\n", b, evt.xkey.keycode);
        if(evt.type == KeyPress)
        {
            switch(evt.xkey.keycode)
            {
                case 38:
                	player->vx = -3;
                    break;
                case 40:
                	player->vx = 3;
                    break;
                case 65:
                	break;
            }
        }
        else if(evt.type == KeyRelease)
        {
            switch(evt.xkey.keycode)
            {
                case 38:
                	player->vx = 0;
                    break;
                case 40:
                	player->vx = 0;
                    break;
            }
        }
        usleep(16666);
        b = XCheckWindowEvent(d, win, EVTMASK, &evt);
    }
    running = 0;
    return NULL;
}
