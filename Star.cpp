#include "Star.h"
#include "Game.h"
# include "Mario.h"

Star::Star(QPoint position)
{
	setPixmap(loadTexture( ":/graphics/items/star.png"));
	
	setPos(position);

    collidable = false;
    moving = true;
    falling = false;
    jumping = false;
    slow = true;

    dir = UP;

    moving_speed = 1;
    falling_speed = 1;
    moving_speed_div = 3;
	spawned_position = position;
	death_duration = 0;
	
	Game::instance()->get_mushroom_appear_sound()->play();

    setZValue(2);
}

void Star::animate()
{
	// Spawn animation
    walk_counter++;

    if (y() == spawned_position.y() - pixmap().height())
    {
        collidable = true;
        falling = true;
        jumping = false;
        dir = RIGHT;
    }
	
	// Moving animation
    prevPos = pos();
    if (dir == RIGHT)
        setX(x() - moving_speed / moving_speed_div);
    else
        setX(x() + moving_speed / moving_speed_div);
}

void Star::hit(Object * what, Direction fromDir)
{
	// mario hits the star
	Mario* mario = dynamic_cast<Mario*>(what);
	if (mario)
	{
        mario->starEat();
		die();
		return;
	}

	// Star bounce on the terrain
    if (fromDir == DOWN && !mario)
    {
		jumping = true;
		jumping_speed = 10;
		falling = false;
	}

	// Change direction
    if (fromDir == RIGHT || fromDir == LEFT)
		setDirection(inverse(dir));
}