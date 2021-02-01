#ifndef PLAYER_H_
#define PLAYER_H_
#define COOLDOWN 60;
#define NULL ((void *)0)
enum BulletTeam
{PLAYER = 997, ENEMY};
struct PlayerShip
{
	int x, y;
	int maxhp, hp;
	int scd;
};
struct ShipBullet
{
	int x, y;
	int vx, vy;
	enum BulletTeam team;
};
struct ShipBullet *PlayerShoot(const struct PlayerShip *player);
void PlayerTick(void);
#endif /* PLAYER_H_ */
