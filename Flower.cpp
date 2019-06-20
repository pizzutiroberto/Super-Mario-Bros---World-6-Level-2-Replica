#include "Flower.h"
#include "Mario.h"
#include "Game.h"
#include <QSound>

Flower::Flower(QPoint position) : Entity()
{
	texture_cycle[0] = loadTexture(":/graphics/items/flower-0.bmp");
	texture_cycle[1] = loadTexture(":/graphics/items/flower-1.bmp");
	texture_cycle[2] = loadTexture(":/graphics/items/flower-2.bmp");
	texture_cycle[3] = loadTexture(":/graphics/items/flower-3.bmp");
	setPixmap(texture_cycle[0]);
	setPos(position);

	collidable = false;
	dir = UP;
	moving = true;
	falling = false;
	moving_speed = 1;
	moving_speed_div = 6;
	slow = true;
	setZValue(2);
	spawned_position = position;
	death_duration = 0;

	Game::instance()->get_mushroom_appear_sound()->play();
}

void Flower::animate()
{
	// Spawn animation
	walk_counter++;

	if(y() == spawned_position.y()-pixmap().height())
	{
		collidable = true;
		moving = false;
	}

	setPixmap(texture_cycle[(walk_counter/anim_div)%4]);
}

void Flower::hit(Object *what, Direction fromDir)
{
	// Mario hit the flower
	Mario* mario = dynamic_cast<Mario*>(what);
	if(mario)
	{
		mario->flowerEat();
		die();
		return;
	}
}