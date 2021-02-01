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
