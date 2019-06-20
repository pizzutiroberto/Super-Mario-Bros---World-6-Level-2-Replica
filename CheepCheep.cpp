#include "CheepCheep.h"
#include "Mario.h"
#include "Game.h"
#include "Fireball.h"
#include <QSound>

CheepCheep::CheepCheep(QPoint position, Direction direction, fishType f_type)
{
	dir = direction;
	type = f_type;
	cycle_counter = 0;
	descend = false;
	falling = false;
	collidable = true;
	moving = true;

	// Setting walking speed and the movement spread for cheep cheep
	if (type == RED)
	{
		walk_speed = 0.5;
		walk_spread = 30;
	}
	else
	{
		walk_speed = 0.2;
		walk_spread = 20;
	}

	// Red cheep cheep textures
	texture_fish[0][0] = QPixmap(loadTexture(":/graphics/enemies/cheep-cheep/red-0.png"));
	texture_fish[0][1] = QPixmap(loadTexture(":/graphics/enemies/cheep-cheep/red-1.png"));
	// Grey cheep cheep textures
	texture_fish[1][0] = QPixmap(loadTexture(":/graphics/enemies/cheep-cheep/grey-0.png"));
	texture_fish[1][1] = QPixmap(loadTexture(":/graphics/enemies/cheep-cheep/grey-1.png"));
	
	setPixmap(texture_fish[type][0]);
	setPos(position);
	setZValue(2);
}

void CheepCheep::animate()
{
	// Moving animation
	cycle_counter++;

	if (descend)
	{
		setY(y() - walk_speed);
		if (cycle_counter >= walk_spread)
		{
			cycle_counter = 0;
			descend = false;
		}
	}
	else
	{
		setY(y() + walk_speed);
		if (cycle_counter >= walk_spread)
		{
			cycle_counter = 0;
			descend = true;
		}
	}

	// Texture setting
	if (moving)
		setPixmap(texture_fish[type][(walk_counter++ / walk_div) % 2]);

	// Texture mirroring
	if (dir == RIGHT)
		setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

void CheepCheep::hit(Object *what, Direction fromDir)
{
	// Cheep Cheep hit by a fireball
	Fireball *fireball = dynamic_cast<Fireball*>(what);
	if (fireball)
	{
		bounceOnInvincible();
		Entity::die();
	}

	// Change direction
	if (fromDir == RIGHT || fromDir == LEFT)
		setDirection(inverse(dir));
}