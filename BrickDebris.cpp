#include <QSound>
#include "BrickDebris.h"

BrickDebris::BrickDebris(QPoint position, Direction dir) : Entity()
{
	setPixmap(QPixmap(loadTexture(":/graphics/scenary/brick-debris.bmp")));
	setPos(position);

	collidable = false;

	moving = true;
	setDirection(dir);
	slow = true;

	setZValue(10);

	falling = false;

	jumping_duration = rand()%15;
	startJumping();
}