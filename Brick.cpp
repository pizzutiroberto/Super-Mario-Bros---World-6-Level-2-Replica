#include <QSound>
#include "Brick.h"
#include "Mario.h"
#include "Game.h"
#include "BrickDebris.h"
#include "HUD_Score_Popup.h"

Brick::Brick(QPoint position, int type) : Inert()
{
	brick_type = type;
	if(brick_type == 0)
		setPixmap(QPixmap(loadTexture(":/graphics/scenary/brick.bmp")));
	else if (brick_type == 1)
		setPixmap(QPixmap(loadTexture(":/graphics/scenary/brick-underground.bmp")));
	else if (brick_type == 2)
		setPixmap(QPixmap(loadTexture(":/graphics/scenary/seaweed.png")));
	setPos(position);

	hitted = false;
	broken = false;
	hit_counter = 0;
}

void Brick::advance()
{
	if(this->isVisible() == 0)
		return;

	// Animation for bricks
	if(hitted)
	{
		if(hit_counter < 10)
			setY(y()-1);
		else if(hit_counter < 20)
			setY(y()+1);
		
		hit_counter++;

		if(hit_counter >= 20)
		{
			hitted = false;
			hit_counter = 0;
		}
	}
	// When a brick is broken, create debris
	else if(broken)
	{
		setVisible(false);
		new HUD_Score_Popup(QPoint(x(), y()), SCORE50);
		Game::instance()->addScore(50);
		new BrickDebris(QPoint(x(),                  y()-15), LEFT);
		new BrickDebris(QPoint(x()+pixmap().width(), y()-15), RIGHT);
		new BrickDebris(QPoint(x()-5,                  y()-5), LEFT);
		new BrickDebris(QPoint(x()+pixmap().width()+5, y()-5), RIGHT);
	}
}

void Brick::hit(Object *what, Direction fromDir)
{
	// Mario hits a brick from the bottom
	Mario* mario = dynamic_cast<Mario*>(what);
	if(mario && fromDir == DOWN)
	{
		if(!mario->isSmall())
		{
			if (brick_type != 2)
			{
				Game::instance()->get_block_break_sound()->play();
				broken = true;
			}
		}
		else
		{
			Game::instance()->get_block_hit_sound()->play();
			hitted = true;
			hit_counter = 0;
		}
	}
}