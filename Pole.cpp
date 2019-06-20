#include "Pole.h"
#include <QBrush>
#include <QPainter>
#include "Mario.h"
#include "HUD_Score_Popup.h"
#include <QSound>
#include "Game.h"

Pole::Pole(QPoint position) : Inert()
{
	setShapeMode(QGraphicsPixmapItem::MaskShape);

	hitted = false;
	hit_counter = 0;
	hit_duration = 16*9;
	ended = false;

	QPixmap collage(loadTexture(":/graphics/scenary/end-line.bmp"));
	collage = collage.scaled(16, 10*16);
	QPainter painter(&collage);
	QPixmap single_block(loadTexture(":/graphics/scenary/end-line.bmp"));
	for(int y=0; y<160; y += single_block.height())
		painter.drawPixmap(0, y, single_block);
	setPixmap(collage);

	endpole = new Background(position - QPoint(0,11*16), ":/graphics/scenary/end-dot.bmp");
	flag = new Background(position - QPoint(8,10*16), ":/graphics/scenary/end-flag.bmp");

	setZValue(0);

	setPos(position - QPoint(0,11*16));
}

void Pole::advance()
{
	// Slide animation
	if(hitted)
	{
		hit_counter++;
		if(hit_counter < hit_duration)
			flag->setY(flag->y()+1);
		else
		{
			hit_counter = 0;
			hitted = false;
			ended = true;
			
			Game::instance()->getMario()->endSlide();
		}
	}
}

void Pole::hit(Object *what, Direction fromDir)
{
	if(ended)
		return;

	Mario *mario = dynamic_cast<Mario*>(what);
	if(mario)
	{
		Game::instance()->stopMusic();

		hitted = true;
		collidable = false;
		mario->freeze();

		// Assign points where mario jumps
		int mario_y = mario->y();
		if (mario_y < 200 - 10 * 16)
		{
			new HUD_Score_Popup(QPoint(mario->x(), mario->y()), SCORE5000);
			Game::instance()->addScore(5000);
		}
		else if (mario_y < 200 - 9 * 16)
		{
			new HUD_Score_Popup(QPoint(mario->x(), mario->y()), SCORE4500);
			Game::instance()->addScore(4500);
		}
		else if (mario_y < 200 - 8 * 16)
		{
			new HUD_Score_Popup(QPoint(mario->x(), mario->y()), SCORE4000);
			Game::instance()->addScore(4000);
		}
		else if (mario_y < 200 - 7 * 16)
		{
			new HUD_Score_Popup(QPoint(mario->x(), mario->y()), SCORE3500);
			Game::instance()->addScore(3500);
		}
		else if (mario_y < 200 - 6 * 16)
		{
			new HUD_Score_Popup(QPoint(mario->x(), mario->y()), SCORE3000);
			Game::instance()->addScore(3000);
		}
		else if (mario_y < 200 - 5 * 16)
		{
			new HUD_Score_Popup(QPoint(mario->x(), mario->y()), SCORE2500);
			Game::instance()->addScore(2500);
		}
		else if (mario_y < 200 - 4 * 16)
		{
			new HUD_Score_Popup(QPoint(mario->x(), mario->y()), SCORE2000);
			Game::instance()->addScore(2000);
		}
		else if (mario_y < 200 - 3 * 16)
		{
			new HUD_Score_Popup(QPoint(mario->x(), mario->y()), SCORE1500);
			Game::instance()->addScore(1500);
		}
		else if (mario_y < 200 - 2 * 16)
		{
			new HUD_Score_Popup(QPoint(mario->x(), mario->y()), SCORE1000);
			Game::instance()->addScore(1000);
		}
		else if (mario_y < 200 - 1 * 16)
		{
			new HUD_Score_Popup(QPoint(mario->x(), mario->y()), SCORE500);
			Game::instance()->addScore(500);
		}

		mario->startSlide();

		Game::instance()->get_levelend_sound()->play();
	}
}