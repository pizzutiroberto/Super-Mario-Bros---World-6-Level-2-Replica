#include "Mushroom.h"
#include "Mario.h"
#include "Game.h"
#include <QSound>

Mushroom::Mushroom(QPoint position, bool _red) : Entity()
{
	red = _red;
	setPixmap(loadTexture(red ? ":/graphics/items/mushroom-red.png": ":/graphics/items/mushroom-green.png"));
	setPos(position);

	collidable = false;
	moving = true;
	dir = UP;
	falling = false;
	moving_speed = 1;
	falling_speed = 1;
	moving_speed_div = 6;
	slow = true;
	setZValue(2);
	spawned_position = position;
	death_duration = 0;

	Game::instance()->get_mushroom_appear_sound()->play();
}

void Mushroom::animate()
{
	walk_counter++;

	if(y() == spawned_position.y()-pixmap().height())
	{
		collidable = true;
		falling = true;
		dir = RIGHT;
		moving_speed_div = 2;
	}
}

void Mushroom::hit(Object *what, Direction fromDir)
{
	// Mario hits a mushroom
	Mario* mario = dynamic_cast<Mario*>(what);
	if(mario)
	{
		mario->mushroomEat(red);
		die();
		return;
	}

	// Change direction
	if(fromDir == RIGHT || fromDir == LEFT)
		setDirection(inverse(dir));
}