#include "Beetle.h"
#include "Mario.h"
#include "Game.h"
#include "Shell.h"
#include "Fireball.h"
#include "HUD_Score_Popup.h"
#include <QSound>

Beetle::Beetle(QPoint position, Direction direction)
{
	texture_walk[0] = QPixmap(loadTexture(":/graphics/enemies/buzzy-beetle/walk-0.png"));
	texture_walk[1] = QPixmap(loadTexture(":/graphics/enemies/buzzy-beetle/walk-1.png"));

	dir = direction;
	falling = true;
	moving = true;

	setPixmap(texture_walk[0]);
	setPos(position - QPoint(0, pixmap().height()));
}

void Beetle::animate()
{
	// Set proper texture
	if (moving)
		setPixmap(texture_walk[(walk_counter++ / walk_div) % 2]);

	// Mirror texture on change direction
	if (dir == RIGHT)
		setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

void Beetle::hit(Object *what, Direction fromDir)
{
	// Beetle ignores collision with a fireball
	Fireball *fireball = dynamic_cast<Fireball*>(what);
	if ((fromDir == RIGHT || fromDir == LEFT) && !fireball)
		setDirection(inverse(dir));
}

void Beetle::hurt()
{
	// Hurting a beetle create a shell object
	walkable = true;
	moving = false;
	Game::instance()->get_stomp_sound()->play();
	setVisible(false);
	Entity::die();
	new HUD_Score_Popup(QPoint(x(), y()), SCORE100);
	Game::instance()->addScore(100);
	new Shell(QPoint(x(), y() + 16), dir, BEETLE);
}
