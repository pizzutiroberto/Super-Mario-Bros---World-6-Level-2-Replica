#include "Vine.h"
#include <qpainter.h>
#include "Mario.h"
#include "Game.h"

Vine::Vine(QPoint position) : Inert()
{
	texture_vine_full = QPixmap(loadTexture(":/graphics/scenary/vine.png"));

    spawned_position = position;

	collidable = false;
	spawn = true;
	draw = false;

	spawn_index = 0;
	spawn_counter = 0;
    spawn_duration = 2;

	Game::instance()->get_vine_sound()->play();

	setZValue(1);
}

void Vine::animate()
{
	// Spawn animation (vine growing up)
    if(spawn)
    {
        spawn_counter++;
        if(spawn_counter >= spawn_duration)
        {
			spawn_index++;
			QRect rect(0, 0, 16, spawn_index);
			texture_vine_cropped = texture_vine_full.copy(rect);
			setPixmap(texture_vine_cropped);
			setY(spawned_position.y() - spawn_index);
			setX(spawned_position.x());
			spawn_counter = 0;

			if (spawn_index >= 40)
				collidable = true;

			if (spawn_index == 160)
				spawn = false;
        }
    }
}

void Vine::hit(Object *what, Direction fromDir)
{
	// Mario hit the vine to climb it
	Mario *mario = dynamic_cast<Mario*>(what);
	if (mario)
	{
        collidable = true;
        mario->freeze();
        mario->startVineClimb(spawned_position.x());
	}
}
