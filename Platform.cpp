#include "Platform.h"
#include "Mario.h"

Platform::Platform(QPoint position, int duration, int type, Direction direction) : Inert()
{
	texture_platform[0] = loadTexture(":/graphics/scenary/platform-0.png");
	texture_platform[1] = loadTexture(":/graphics/scenary/platform-1.png");
	
	if (type == 0)
		setPixmap(texture_platform[0]);
	else if (type == 1)
		setPixmap(texture_platform[1]);

	setPos(position);

	move = false;
	dir = direction;
	move_counter = 0;
	move_duration = duration * 15 / 0.7;

	setZValue(2);
}

void Platform::animate()
{
	// Moving animation
	if (move_counter >= move_duration)
	{
		dir = inverse(dir);
		move_counter = 0;
	}

	if (move)
	{
		if (dir == RIGHT)
			setX(x() + 0.7);
		if (dir == LEFT)
			setX(x() - 0.7);

		move_counter++;
	}
}

void Platform::hit(Object *what, Direction fromDir)
{
	// Mario jumps on the platform
	Mario *mario = dynamic_cast<Mario*>(what);
	if (fromDir == UP && mario)
		move = true;
}