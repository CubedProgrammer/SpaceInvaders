#ifndef PLAYER_H_
#define PLAYER_H_
#define COOLDOWN 60;
enum BulletTeam
{PLAYER = 997, ENEMY};
struct PlayerShip
{
	int x, y;
	int scd;
	int vx;
};
struct ShipBullet
{
	int x, y;
	int vx, vy;
	enum BulletTeam team;
};
struct ShipBullet *PlayerShoot(struct PlayerShip *player);
void PlayerTick(struct PlayerShip *player);
#endif /* PLAYER_H_ */
