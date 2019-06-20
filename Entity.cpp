#include "Entity.h"
#include "Game.h"
#include "Mario.h"
#include "Box.h"
#include "Enemy.h"
#include "Coin.h"
#include "Fireball.h"

Entity::Entity() : Object()
{
	moving_speed = 1;
	jumping_speed = 2;
	falling_speed = 2;
	moving_speed_div = 2;

	dir = RIGHT;
	moving = true;
	jumping = false;
	falling = true;
	swimming = false;
	underwater = false;
	phantom = false;
	dying = false;
	dead = false;
	freezed = false;
	slow = false;
	onAnimation = false;
    invincible_bounce = false;

	jump_counter = 0;
	death_counter = 0;
	walk_counter = 0;
	phantom_counter = 0;
	freeze_counter = 0;

	jumping_duration = 30;
	death_duration = 100;
	phantom_duration = 250;
	freeze_duration = 80;

	walkable_object = 0;
}

void Entity::startJumping()
{
	if (swimming)
		jumping = true;

    if (swimming && y() < 200 + 300 + 300 + 300 - 13 * 16)
        jumping = false;

	if(!falling && !jumping)
	{
		walkable_object = 0;
		jumping = true;
	}
}

void Entity::endJumping()
{
	if(jumping)
	{
		jumping = false;
		jump_counter = 0;
		falling = true;
	}
}


void Entity::startPhantom()
{
	if(!phantom)
	{
		phantom = true;
		phantom_counter = 0;
		setOpacity(0.5);
	}
}

void Entity::endPhantom()
{
	if(phantom)
	{
		phantom = false;
		phantom_counter = 0;
		setOpacity(1.0);
	}
}

void Entity::bounceOnInvincible()
{
    collidable = false;
    moving = false;
    falling = false;
    jumping_duration = rand()%50;
    slow = true;
    invincible_bounce = true;
    setDirection(dir);
    setZValue(10);
    setPixmap(pixmap().transformed(QTransform().scale(1, -1)));
	Game::instance()->get_stomp_sound()->play();
    startJumping();
}

void Entity::advance()
{
	// Die if go at the left of valid game space
	if (pos().x() < Game::instance()->getCameraMaxX() - 220)
		die();

	// Freezing: cant move 
	if(freezed)
	{
		freeze_counter++;
		if (freeze_counter > freeze_duration)
		{
			freezed = false;
			freeze_counter = 0;
		}
		else
			return;
	}

	// Moving animation
    if(moving)
    {
        prevPos = pos();

		if(slow)
			moving_speed = walk_counter % moving_speed_div == 0;
		
		if (dir == RIGHT)
			setX(x() + moving_speed);
		else if (dir == LEFT)
			setX(x() - moving_speed);
		else if (dir == UP)
			setY(y() - moving_speed);
		else if (dir == DOWN)
			setY(y() + moving_speed);
	
        solveCollisions();
    }

	// Jumping animation
    if(jumping)
    {
		prevPos = pos();
	
        setY(y() - jumping_speed);
	
        jump_counter += jumping_speed;

        if(Game::instance()->getMario()->isBouncing())
            jumping_duration = 30;
        if(jump_counter > jumping_duration)
            endJumping();
	
        solveCollisions();
    }

	if(walkable_object && !touchingDirection(walkable_object))
		falling = true;

	// Falling animation
	if(falling)
	{
		prevPos = pos();

		setY(y() + falling_speed);

		solveCollisions();
	}

	// Die if fall under the valid game space (under the terrain level)
	if(y() > Game::instance()->getScene()->sceneRect().height() && Game::instance()->getMario()->getPosY() >= 0 && !dying)
		die();

	// Dying animation
	if(dying)
	{
		death_counter++;
		if (death_counter > death_duration)
			dead = true;
	}

	if (Game::instance()->isFrenzy())
		slow = false;
}

void Entity::solveCollisions()
{
	if(!collidable || dead)
		return;

    QList<QGraphicsItem*> colliding_items = collidingItems();

	bool revert = false;	

    for(auto & ci : colliding_items)
    {
		//---------- Ignored collisions-------------//
		Object *obj = dynamic_cast<Object*>(ci);
		if(!obj)
			continue;

		if( ! obj->isCollidable())
			continue;

		// Entity is in phantom mode
		Entity* entity_obj = dynamic_cast<Entity*>(obj);
		if(entity_obj && (entity_obj->isPhantom() || phantom))
			continue;

        Direction coll_dir = collisionDirection(obj);
   
        if(!coll_dir)
            continue;

		// Ignore collisions from the bottom of coins this is necessary to avoid the stop jumping from the bottom of the coin
		Coin* coin = dynamic_cast<Coin*>(obj);
		if (coin && coll_dir == UP)
			return;

		// Ignore collisions from two fireballs
		Fireball* fireball1 = dynamic_cast<Fireball*>(obj);
		Fireball* fireball2 = dynamic_cast<Fireball*>(this);
		if (fireball1 && fireball2)
			continue;

		// Ignore collisions from a fireball and Mario
		Mario* mario1 = dynamic_cast<Mario*>(obj);
		Mario* mario2 = dynamic_cast<Mario*>(this);
        if ((mario1 && fireball2) || (mario2 && fireball1))
			continue;
		//---------End Ignored collisions------------//

		// Waling on an object
        if(coll_dir == DOWN && falling && obj->isWalkable())
        {
            falling = false;
            walkable_object = obj;
        }

        if(coll_dir == UP && jumping)
            endJumping();

        obj->hit(this, inverse(coll_dir));
		this->hit(obj, coll_dir);

		revert = true;
    }

	if(revert)
		setPos(prevPos);
}

void Entity::die()
{
    if((!dying && !dead) || invincible_bounce)
	{
		dying = true;
		death_counter = 0;
		phantom = true;
		moving = false;
	}
}
