#include<stdlib.h>
#include"bullets.h"
struct BulletCollection *InitCollection(struct ShipBullet *bullet)
{
	struct BulletCollection *node = malloc(sizeof(struct BulletCollection));
	node->bullet = bullet;
	node->prev = NULL;
	node->next = NULL;
	return node;
}
int collidesWithBullet(const struct ShipBullet *bu, const struct ShipBullet *bv)
{
	return collidesWithRect(bu, bv->x - 3, bv->y - 3, 6, 6);
}
int collidesWithRect(const struct ShipBullet *bu, int x, int y, unsigned width, unsigned height)
{
	int right = x + width - 1, bottom = y + height - 1;
	int xc = bu->x - 3 <= right && bu->x + 2 >= x;
	int yc = bu->y - 3 <= bottom && bu->y + 2 >= y;
	return xc * yc;
}
void RemoveBullet(struct BulletCollection *node)
{
	free(node->bullet);
	if(node->next)
		node->next->prev = node->prev;
	if(node->prev)
		node->prev->next = node->next;
	free(node);
}
void AddAfter(struct BulletCollection *node, struct ShipBullet *bullet)
{
	struct BulletCollection *new = malloc(sizeof(struct BulletCollection));
	new->bullet = bullet;
	new->prev = node;
	new->next = node->next;
	node->next = new;
	if(new->next)
		new->next->prev = new;
}
