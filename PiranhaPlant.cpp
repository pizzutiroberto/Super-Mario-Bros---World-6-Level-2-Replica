#include "PiranhaPlant.h"
#include "Mario.h"
#include "Game.h"
#include "Fireball.h"
#include "HUD_Score_Popup.h"
#include <QSound>

PiranhaPlant::PiranhaPlant(QPoint position)
{
	setShapeMode(QGraphicsPixmapItem::MaskShape);

	collidable = true;
	moving = false;
	falling = false;
	animation_freeze = false;

	// randomize the inizial spawn
	rand() % 2 == 0 ? descend = false : descend = true;
	inPipe = descend ? false : true;

	animation_freeze_counter = 0;
	animation_freeze_duration = 100;
	cycle_counter = 0;
	spawned_position = position;

	texture_plant[0] = QPixmap(loadTexture(":/graphics/enemies/piranha-plant/piranha-0.png"));
	texture_plant[1] = QPixmap(loadTexture(":/graphics/enemies/piranha-plant/piranha-1.png"));

	setPixmap(texture_plant[0]);

	// Set or correct the spawn position
	setPos(spawned_position.x(), spawned_position.y()+5);
	if (descend)
		setY(spawned_position.y() - pixmap().height());
	
    setZValue(1);
}

void PiranhaPlant::animate()
{
	Mario* mario = Game::instance()->getMario();

	// do nothing if mario is on the relative pipe
	if (mario->isOnPipe() && (mario->getPosX() >= pos().x() - 23 && mario->getPosX() < pos().x() + 23) && inPipe)
		return;

	// freeze the plants if mario is going down the pipe
	if (animation_freeze)
	{
		animation_freeze_counter++;
		if (animation_freeze_counter < animation_freeze_duration)
			return;
		else
		{
			animation_freeze_counter = 0;
			animation_freeze = false;
			collidable = true;
			if (mario->getPosX() == pos().x())
				setPos(spawned_position.x(), spawned_position.y()+5);
		}
	}

	if (mario->isOnAnimation())
	{
		collidable = false;
		animation_freeze = true;
		return;
	}

	// Moving animation
	if (descend)
	{
		setY(y() + 1);
		if (cycle_counter >= 26)
		{
			setY(y() - 1);
			if (cycle_counter >= 300)
			{
				cycle_counter = 0;
				descend = false;
				inPipe = true;
			}
		}
	}
	else
	{
		inPipe = false;
		setY(y() - 1);
		if (cycle_counter >= 26)
		{
			setY(y() + 1);
			if (cycle_counter >= 200)
			{
				cycle_counter = 0;
				descend = true;
			}
		}
	}

	// Texture setting
	setPixmap(texture_plant[(walk_counter++ / moving_speed_div / 15) % 2]);
	prevPos = pos();
	cycle_counter++;
}

void PiranhaPlant::hit(Object *what, Direction fromDir)
{
	// A fireball hits the plant
	Fireball *fireball = dynamic_cast<Fireball*>(what);
	if (fireball)
	{
		new HUD_Score_Popup(QPoint(x(), y()), SCORE200);
		Game::instance()->addScore(200);
		bounceOnInvincible();
		Entity::die();
	}
}