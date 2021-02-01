#ifndef BULLETS_H_
#define BULLETS_H_
#include"player.h"
struct BulletCollection
{
	struct BulletCollection *prev, *next;
	struct ShipBullet *bullet;
};
struct BulletCollection *InitCollection(struct ShipBullet *bullet);
void AddAfter(struct BulletCollection *node, struct ShipBullet *bullet);
void RemoveBullet(struct BulletCollection *node);
#endif /* BULLETS_H_ */
