#include "Troopa.h"
#include "Mario.h"
#include "Game.h"
#include "Shell.h"
#include <QSound>

Troopa::Troopa(QPoint position, Direction direction)
{
	texture_walk[0] = QPixmap(loadTexture(":/graphics/enemies/koopa/walk-0.png"));
	texture_walk[1] = QPixmap(loadTexture(":/graphics/enemies/koopa/walk-1.png"));

	dir = direction;
	falling = true;
	moving = true;

	setPixmap(texture_walk[0]);
	setPos(position - QPoint(0, pixmap().height()));
}

void Troopa::animate()
{
	// Texture setting
	if (moving)
		setPixmap(texture_walk[(walk_counter++ / walk_div) % 2]);
	
	// Texture mirroring
	if(dir == RIGHT)
		setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

void Troopa::hit(Object *what, Direction fromDir)
{
	// Change direction
	if (fromDir == RIGHT || fromDir == LEFT)
		setDirection(inverse(dir));
}

void Troopa::hurt()
{
	// When hurt create a shell
    walkable = true;
    moving = false;
    Game::instance()->get_stomp_sound()->play();
	setVisible(false);
	Entity::die();
	new Shell(QPoint(x(), y() + 16), dir, KOOPA);
}
