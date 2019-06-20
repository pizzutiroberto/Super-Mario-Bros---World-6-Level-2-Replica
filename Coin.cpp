#include "Coin.h"
#include "Mario.h"
#include "Game.h"
#include "HUD_Score_Popup.h"
#include <QSound>

Coin::Coin(QPoint position) : Entity()
{
	spawned_position = position;

	texture = loadTexture(":/graphics/items/coin-1.png");

	setPixmap(texture);
	setPos(position);

	collidable = true;
	walkable = false;
    falling = false;
    moving = false;
    jumping = false;

	
	setZValue(3);
}

void Coin::hit(Object *what, Direction fromDir)
{
	// Mario hit a coin (collect a coin)
	Mario* mario = dynamic_cast<Mario*>(what);
	if (mario) {
		setVisible(false);
		new HUD_Score_Popup(QPoint(x(), y()), SCORE50);
		Game::instance()->addScore(50);
		Game::instance()->addCoinCount();
		Game::instance()->get_coin_sound()->play();
	}
}
