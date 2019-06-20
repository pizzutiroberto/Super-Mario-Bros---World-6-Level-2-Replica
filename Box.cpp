#include "Box.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Flower.h"
#include "Vine.h"
#include "Star.h"
#include "CoinSpawnable.h"
#include "Game.h"
#include "HUD_Score_Popup.h"
#include <QSound>

Box::Box(QPoint position, visibility_t _visibility, spawnable_t _spawnable) : Inert()
{
	texture_cycle[0] = loadTexture(":/graphics/scenary/box-0.bmp");
	texture_cycle[1] = loadTexture(":/graphics/scenary/box-1.bmp");
	texture_cycle[2] = loadTexture(":/graphics/scenary/box-2.bmp");
	texture_used[0]  = loadTexture(":/graphics/scenary/box-used.bmp");
	texture_used[1]  = loadTexture(":/graphics/scenary/box-underground-used.bmp");
	texture_brick[0] = loadTexture(":/graphics/scenary/brick.bmp");
	texture_brick[1] = loadTexture(":/graphics/scenary/brick-underground.bmp");

	used = false;
	hitted = false;
	wasUndeground = false;
	hit_counter = 0;
	visibility = _visibility;
	spawnable = _spawnable;
	if(visibility == INVISIBLE)
		this->setOpacity(0.0);

	setPixmap(texture_cycle[0]);
	setPos(position);

	setZValue(3);
}

void Box::animate()
{
	// Change visibility
	if (visibility == INVISIBLE)
		Game::instance()->getMario()->getPosY() >= pos().y() + 16 ? setVisible(true) : setVisible(false);

	// Texture setting
	if (used) {
		if (wasUndeground)
			setPixmap(texture_used[1]);
		else
			setPixmap(texture_used[0]);
	}
	else if(visibility == BRICKED)
		setPixmap(texture_brick[0]);
	else if (visibility == BRICKEDUND)
		setPixmap(texture_brick[1]);
	else
		setPixmap(texture_cycle[(hit_counter++/anim_div)%3]);
}

void Box::advance()
{
	// Box hit animation
	if(hitted)
	{
		if (visibility == BRICKED)
			wasUndeground = false;
		else if (visibility == BRICKEDUND)
			wasUndeground = true;
		if(spawnable != MULTICOIN)
			visibility = VISIBLE;
		setOpacity(1.0);

		if(hit_counter < 10)
			setY(y()-1);
		else if(hit_counter < 20)
			setY(y()+1);

		if(hit_counter > 20)
			hitted = false;

		hit_counter++;
	}
}

void Box::hit(Object *what, Direction fromDir)
{
	// Mario hit a box from the bottom
	Mario* mario = dynamic_cast<Mario*>(what);
	if(mario && fromDir == DOWN)
	{
		if(used)
			Game::instance()->get_block_hit_sound()->play();
		else
		{
			// Spawn a coin
			if (spawnable == COIN)
			{
				new CoinSpawnable(QPoint(x(), y() - 20));
				new HUD_Score_Popup(QPoint(x(), y() - 20), SCORE200);
				Game::instance()->addScore(200);
				Game::instance()->addCoinCount();
			}
			// Spawn a multi-coin sequence
			else if (spawnable == MULTICOIN)
			{
				new CoinSpawnable(QPoint(x(), y() - 20));
				used = false;
				multicoin_counter--;
				new HUD_Score_Popup(QPoint(x(), y() - 20), SCORE200);
				Game::instance()->addScore(200);
				Game::instance()->addCoinCount();
				if (multicoin_counter != 0)
				{
					hitted = true;
					hit_counter = 0;
					return;
				}
			}
			// Spawn a powerup (mushrooms, flowers, vines and stars)
			else if (spawnable == POWERUP)
			{
				if (mario->isBig())
					new Flower(QPoint(x(), y()));
				else
					new Mushroom(QPoint(x(), y()));
			}
			else if (spawnable == LIFE)
				new Mushroom(QPoint(x(), y()), false);
			else if (spawnable == VINE)
				new Vine(QPoint(x(), y()));
			else if (spawnable == STAR)
				new Star(QPoint(x(), y()));

			hitted = true;
			used = true;
			hit_counter = 0;
		}
	}
}