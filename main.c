#include<pthread.h>
#include<stdbool.h>
#include<stdio.h>
#include<unistd.h>
#include<X11/Xlib.h>
#include"bullets.h"
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
struct BulletCollection *volatile bullets, *volatile bend;
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
	struct BulletCollection *tmp, *other, *tmpb;
	struct PlayerShip player;
	player.x = WIDTH / 2;
	player.y = HEIGHT * 2 / 3;
	player.vx = 0;
	player.scd = COOLDOWN;
	pthread_t th;
	pthread_create(&th, NULL, &keyhandler, &player);
	running = 1;
	while(running)
	{
		XSetForeground(d, gc, 0);
		XFillRectangle(d, win, gc, 0, 0, WIDTH, HEIGHT);
		tmp = bullets;
		while(tmp != NULL)
		{
			XSetForeground(d, gc, 0xffffff);
			XFillRectangle(d, win, gc, tmp->bullet->x - 3, tmp->bullet->y - 3, 6, 6);
			tmp->bullet->x += tmp->bullet->vx;
			tmp->bullet->y += tmp->bullet->vy;
			other = tmp;
			while(other != NULL)
			{
				if(tmp != other)
				{
					if(tmp->bullet->team != other->bullet->team)
					{
						if(collidesWithBullet(tmp->bullet, other->bullet))
						{
							tmpb = tmp->prev;
							RemoveBullet(tmp);
							RemoveBullet(other);
							other = bend;
							tmp = tmpb;
						}
					}
				}
				other = other->next;
			}
			tmp = tmp->next;
		}
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
    XCheckWindowEvent(d, win, EVTMASK, &evt);
    struct ShipBullet *tmp;
    while(evt.type != KeyPress || evt.xkey.keycode != 9)
    {
    	//printf("%d %u\n", b, evt.xkey.keycode);
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
                	tmp = PlayerShoot(player);
                	if(tmp)
                	{
                    	if(bullets == NULL)
                    		bend = bullets = InitCollection(tmp);
                    	else
                    	{
                    		AddAfter(bend, tmp);
                    		bend = bend->next;
                    	}
                	}
                	break;
                case 39:
                	player->vx = 0;
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
        XCheckWindowEvent(d, win, EVTMASK, &evt);
    }
    running = 0;
    return NULL;
}
