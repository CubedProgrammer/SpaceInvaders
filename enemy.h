#ifndef ENEMY_H_
#define ENEMY_H_
#include<math.h>
#include<stdlib.h>
#include"bullets.h"
#define MAX_ENEMY_HP 6
struct EnemyShip
{
	int x, y;
	int hp;
	int scd, mscd;
};
static inline struct ShipBullet *EnemyShoot(struct EnemyShip *enemy, int x, int y)
{
	if(enemy->scd == 0)
	{
		enemy->scd = enemy->mscd;
		struct ShipBullet *bullet = malloc(sizeof(struct ShipBullet*));
		bullet->team = ENEMY;
		bullet->x = enemy->x;
		bullet->y = enemy->y;
		int dx = x - enemy->x, dy = enemy->y;
		int dist = sqrt(dx * dx + dy * dy);
		bullet->vx = dx * 12 / dist;
		bullet->vy = dy * 12 / dist;
		return bullet;
	}
	else
		return NULL;
}
static inline void EnemyTick(struct EnemyShip *enemy)
{
	if(enemy->scd)
		--enemy->scd;
}
static inline int EnemyColour(int hp)
{
	if(hp == 6)
		return 0xee12ee;
	else if(hp == 5)
		return 0x1212ee;
	else if(hp == 4)
		return 0x12eeee;
	else if(hp == 3)
		return 0x12ee12;
	else if(hp == 2)
		return 0xeeee12;
	else if(hp == 1)
		return 0xee1212;
	else
		return 0;
}
#endif /* ENEMY_H_ */
