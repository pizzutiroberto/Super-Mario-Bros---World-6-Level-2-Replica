#include "Blooper.h"
#include "Mario.h"
#include "Game.h"
#include "Fireball.h"
#include <QSound>

Blooper::Blooper(QPoint position)
{
	cycle_counter = 0;
	falling = false;
	collidable = true;
	moving = false;
	direction = UPLEFT;

	texture_blooper[0] = QPixmap(loadTexture(":/graphics/enemies/blooper/blooper-0.png"));
	texture_blooper[1] = QPixmap(loadTexture(":/graphics/enemies/blooper/blooper-1.png"));
	
	setPixmap(texture_blooper[0]);
	setPos(position);
	setZValue(4);
}

void Blooper::animate()
{
	cycle_counter++;

	int mario_posx = Game::instance()->getMario()->getPosX();
	int mario_posy = Game::instance()->getMario()->getPosY();

	// Setting the direction to catch Mario
	if (mario_posx <= pos().x())
		direction = mario_posy <= pos().y() ? UPLEFT : BOTTOMLEFT;
	else
		direction = mario_posy <= pos().y() ? UPRIGHT : BOTTOMRIGHT;

	// Moving animation. Blooper moves following 4 directions: UP RIGHT, UP LEFT, BOTTOM RIGHT and BOTTOM LEFT
	if (direction == UPLEFT)
	{
		setX(x() - 0.2);
		setY(y() - 0.2);
	}
	else if (direction == BOTTOMLEFT)
	{
		setX(x() - 0.2);
		setY(y() + 0.2);
	}
	else if (direction == UPRIGHT)
	{
		setX(x() + 0.2);
		setY(y() - 0.2);
	}
	else if (direction == BOTTOMRIGHT)
	{
		setX(x() + 0.2);
		setY(y() + 0.2);
	}

	if (pos().y() <= 200 + 300 + 300 + 300 - 11 * 16)
		setY(y() + 0.2);

	// Texture setting
	setPixmap(texture_blooper[(walk_counter++ / walk_div) % 2]);

	// Texture mirroring
	if (direction == UPRIGHT || direction == BOTTOMRIGHT)
		setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

void Blooper::hit(Object *what, Direction fromDir)
{
	// Blooper hit by a Fireball
	Fireball *fireball = dynamic_cast<Fireball*>(what);
	if (fireball)
	{
		bounceOnInvincible();
		Entity::die();
	}
}