#include "Goomba.h"
#include "Mario.h"
#include "Game.h"
#include <QSound>

Goomba::Goomba(QPoint position, Direction direction)
{
    texture_walk[0] = QPixmap(loadTexture(":/graphics/enemies/goomba/walk-0.png"));
    texture_walk[1] = QPixmap(loadTexture(":/graphics/enemies/goomba/walk-1.png"));
    texture_dead = QPixmap(loadTexture(":/graphics/enemies/goomba/dead.png"));

	dir = direction;

	setPixmap(texture_walk[0]);
	setPos(position - QPoint(0, pixmap().height()));
}

void Goomba::animate()
{
	// Texture setting
	if(dying || dead)
		setPixmap(texture_dead);
    else if(moving)
        setPixmap(texture_walk[(walk_counter++/walk_div)%2]);

	// Texture mirroring
	if (dir == RIGHT)
		setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

void Goomba::hit(Object *what, Direction fromDir)
{
	// Change direction
	if(fromDir == RIGHT || fromDir == LEFT)
		setDirection(inverse(dir));
}

void Goomba::hurt()
{
	Entity::die();
}
