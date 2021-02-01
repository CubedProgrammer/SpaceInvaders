#include"player.h"
struct ShipBullet *PlayerShoot(const struct PlayerShip *player)
{
	if(player->scd == 0)
	{
		player->scd = COOLDOWN;
		struct ShipBullet *pbul = malloc(sizeof(struct ShipBullet));
		pbul->x = player->x;
		pbul->y = player->y;
		pbul->vy = -4;
		pbul->team = PLAYER;
		return pbul;
	}
	else
		return NULL;
}
