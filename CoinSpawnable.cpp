#include "CoinSpawnable.h"
#include "Game.h"
#include <QSound>

CoinSpawnable::CoinSpawnable(QPoint position) : Entity()
{
	spawned_position = position;

	texture_cycle[0] = loadTexture(":/graphics/items/coin-0.png");
	texture_cycle[1] = loadTexture(":/graphics/items/coin-1.png");
	texture_cycle[2] = loadTexture(":/graphics/items/coin-2.png");
	texture_cycle[3] = loadTexture(":/graphics/items/coin-3.png");

	setPixmap(texture_cycle[0]);
	setPos(position);

	collidable = false;
	moving = false;
	falling = false;
	jumping_speed = 1;
	falling_speed = 1;
	death_duration = 0;
	setZValue(10);

	startJumping();

	Game::instance()->get_coin_sound()->play();
}


void CoinSpawnable::animate()
{
	// Spawn and despawn animation from a box
	if(falling && y() >= spawned_position.y())
		die();
	else
		setPixmap(texture_cycle[(walk_counter++/anim_div)%3]);
}