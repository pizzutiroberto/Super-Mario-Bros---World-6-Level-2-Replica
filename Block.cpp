#include "Block.h"
#include "Mario.h"
#include "Game.h"
#include <QSound>

Block::Block(QPoint position) : Inert()
{
	setPixmap(QPixmap(loadTexture(":/graphics/scenary/block.png")));
	setPos(position);

	setZValue(1);
}

void Block::hit(Object *what, Direction fromDir)
{
	// Mario hits a block from the bottom
	Mario *mario = dynamic_cast<Mario*>(what);
    if(fromDir == DOWN && mario)
		Game::instance()->get_block_hit_sound()->play();
}
