#include "Shell.h"
#include "Mario.h"
#include "Game.h"
#include "Troopa.h"
#include "Beetle.h"
#include "Fireball.h"
#include "HUD_Score_Popup.h"
#include <QSound>

Shell::Shell(QPoint position, Direction direction, shell_type shelltype)
{
	texture_shell[0] = QPixmap(loadTexture(":/graphics/enemies/koopa/shell-0.png"));
	texture_shell[1] = QPixmap(loadTexture(":/graphics/enemies/koopa/shell-1.png"));
	texture_shell[2] = QPixmap(loadTexture(":/graphics/enemies/buzzy-beetle/shell.png"));

	dir = direction;
	transformation_duration = 2*freeze_duration;
	transformation_counter = 0;
	shell_counter = 0;
	shell_duration = 500;
	falling = true;
	moving = false;
	transforming = false;
	walkable = true;

	type = shelltype;

	if (type == KOOPA)
		setPixmap(texture_shell[0]);
	else if(type == BEETLE)
		setPixmap(texture_shell[2]);
	setPos(position - QPoint(0, pixmap().height()));
}

void Shell::animate()
{
	// transforming animation (from shell to non shell form)
	if (transforming)
	{
		transformation_counter++;
		type == KOOPA ? setPixmap(texture_shell[(walk_counter++ / walk_div) % 2]) : setPixmap(texture_shell[2]);
		if (transformation_counter > transformation_duration)
		{
			transforming = false;
			moving = true;
			transformation_counter = 0;
			shell_counter = 0;
			setVisible(false);
			Entity::die();
			// Create the relative object (koopa or beetle)
			if (type == KOOPA)
				new Troopa(QPoint(x(), y()), dir);
			else
				new Beetle(QPoint(x(), y()), dir);
		}
	}

	// Texture setting
	if (moving)
		type == KOOPA ? setPixmap(texture_shell[0]) : setPixmap(texture_shell[2]);
	else if (shell_counter < shell_duration) {
		type == KOOPA ? setPixmap(texture_shell[0]) : setPixmap(texture_shell[2]);
		moving = false;
		shell_counter++;
	}
	else if (shell_counter >= shell_duration)
		transforming = true;
	
	// Texture mirroring
	if(dir == RIGHT)
		setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
}

void Shell::hit(Object *what, Direction fromDir)
{
	// En enemy is hitted by a sliding shell
	Enemy *enemy = dynamic_cast<Enemy*>(what);
	if (enemy  && enemy->isHurtable() && moving && fromDir != DOWN)
	{
		new HUD_Score_Popup(QPoint(enemy->x(), enemy->y()), SCORE200);
		Game::instance()->addScore(200);
		enemy->bounceOnInvincible();
	}

	// Change direction
	Mario *mario = dynamic_cast<Mario*>(what);
	Fireball *fireball = dynamic_cast<Fireball*>(what);
	if ((fromDir == RIGHT || fromDir == LEFT) && !(mario || fireball) && !(enemy && moving))
		setDirection(inverse(dir));
}