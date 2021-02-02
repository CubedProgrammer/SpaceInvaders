#ifndef BULLETS_H_
#define BULLETS_H_
#include"player.h"
struct BulletCollection
{
	struct BulletCollection *prev, *next;
	struct ShipBullet *bullet;
};
struct BulletCollection *InitCollection(struct ShipBullet *bullet);
int collidesWithBullet(const struct ShipBullet *bu, const struct ShipBullet *bv);
int collidesWithRect(const struct ShipBullet *bu, int x, int y, unsigned width, unsigned height);
void AddAfter(struct BulletCollection *node, struct ShipBullet *bullet);
void RemoveBullet(struct BulletCollection *node);
#endif /* BULLETS_H_ */
