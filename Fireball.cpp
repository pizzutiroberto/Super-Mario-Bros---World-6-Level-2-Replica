#include <QSound>
#include "Fireball.h"
#include "Enemy.h"
#include "Mario.h"
#include "Game.h"
#include "Beetle.h"
#include "Shell.h"
#include "Paratroopa.h"
#include "HUD_Score_Popup.h"

Fireball::Fireball(QPointF position) : Entity()
{
    texture_fireball[0] = QPixmap(loadTexture(":/graphics/items/fireball-0.bmp"));
    texture_fireball[1] = QPixmap(loadTexture(":/graphics/items/fireball-1.bmp"));
    texture_fireball[2] = QPixmap(loadTexture(":/graphics/items/fireball-2.bmp"));
    texture_fireball[3] = QPixmap(loadTexture(":/graphics/items/fireball-3.bmp"));

    setPixmap(texture_fireball[0]);

	y0 = position.y() + 10;
	dir = Game::instance()->getMario()->getDirection();

	// Adjusting the spawn position of a fireball by direction of Mario
    dir == RIGHT ? setX(position.x() + 16) : setX(position.x() - 6);
	setY(y0);

    collidable = true;
	descend = false;

	Game::instance()->get_fireball_sound()->play();

    setZValue(3);
}

void Fireball::advance()
{
	// Fireball moving animation
    prevPos = pos();

	dir == RIGHT ? setX(x() + 1) : setX(x() - 1);

	if (descend)
	{
		if (y() <= y0)
			setY(y() + 0.5);
		else
			setY(y() + 0.8);
	}
	else
	{
		setY(y() - 0.5);
		if (y() <= y0 - 3)
			descend = true;
	}

    if (prevPos.x() == x() && prevPos.y() == y())
    {
        setVisible(false);
        Entity::die();
    }

    solveCollisions();
}

void Fireball::animate()
{
    setPixmap(texture_fireball[(walk_counter++ / 5) % 4]);
}

void Fireball::hit(Object *what, Direction fromDir)
{
	Enemy* enemy = dynamic_cast<Enemy*>(what);
	Beetle* beetle = dynamic_cast<Beetle*>(what);
	Shell* shell = dynamic_cast<Shell*>(what);
	Paratroopa* paratroopa = dynamic_cast<Paratroopa*>(what);

	// Fireball despawn on a beetle
	if ((shell && shell->isBeetleShell()) || beetle)
	{
		setVisible(false);
		Entity::die();
		return;
	}

	// Fireball hits an enemy (not beetle)
	if (enemy)
	{
		if (paratroopa)
		{
			new HUD_Score_Popup(QPoint(paratroopa->x(), paratroopa->y()), SCORE1000);
			Game::instance()->addScore(1000);
		}
		else
		{
			new HUD_Score_Popup(QPoint(enemy->x(), enemy->y()), SCORE200);
			Game::instance()->addScore(200);
		}
		enemy->bounceOnInvincible();
		enemy->Entity::die();
		setVisible(false);
		Entity::die();
	}

	// Terrain bounce
	if (fromDir == DOWN)
	{
		descend = false;
		y0 = y0 + 2;
	}
	// Despawn when hit a wall
	else if (fromDir != DOWN)
	{
		setVisible(false);
		Entity::die();
	}
}
