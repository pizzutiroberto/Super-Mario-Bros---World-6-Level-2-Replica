#include "Paratroopa.h"
#include "Mario.h"
#include "Game.h"
#include "HUD_Score_Popup.h"
#include <QSound>

Paratroopa::Paratroopa(QPoint position, Direction direction)
{
	texture_fly[0] = QPixmap(loadTexture(":/graphics/enemies/koopa/fly-0.png"));
	texture_fly[1] = QPixmap(loadTexture(":/graphics/enemies/koopa/fly-1.png"));

	dir = direction;
	
	jumping_duration = 40;
	jumping_speed = 1;

	moving = true;
	jumping = false;
	falling = true;
	slow = true;
	hurtable = true;

	setPixmap(texture_fly[0]);
	setPos(position - QPoint(0, pixmap().height()));
}

void Paratroopa::advance()
{
	// Flying animation
	prevPos = pos();
	if (dir == LEFT)
		setX(x() - moving_speed*0.5);
	else
		setX(x() + moving_speed*0.5);

	if (jumping) {
		setY(y() - jumping_speed);
		jump_counter += jumping_speed;

		if (jump_counter > jumping_duration)
			endJumping();
	}

	if (falling) {
		setY(y() + jumping_speed);
		jump_counter += 2*jumping_speed;

		if (jump_counter > jumping_duration*6) {
			jumping = true;
			falling = false;
			jump_counter = 0;
		}
	}

	solveCollisions();
}

void Paratroopa::animate()
{
	// Texture setting
	if (moving)
		setPixmap(texture_fly[(walk_counter++ / walk_div) % 2]);

	// Texture mirroring
	if (dir == RIGHT)
		setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

void Paratroopa::hit(Object *what, Direction fromDir)
{
	// Terrain bounce
	Mario *mario = dynamic_cast<Mario*>(what);
	if (fromDir == DOWN && !mario) {
		jumping = true;
		falling = false;
	}
	else if(mario && fromDir != UP && !mario->isInvincible())
		mario->hurt();
	else if (mario && fromDir == UP)
	{
		setVisible(false);
		Entity::die();
	}

	// Change direction
	if (fromDir == RIGHT || fromDir == LEFT)
		setDirection(inverse(dir));
}

void Paratroopa::hurt()
{
	// When paratroopa gets damage create a troopa
	new HUD_Score_Popup(QPoint(x(), y()), SCORE400);
	Game::instance()->addScore(400);
	new Troopa(QPoint(x(), y() + 25), dir);
}
