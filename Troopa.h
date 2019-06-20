#pragma once

#include "Enemy.h"

class Troopa : public Enemy
{
protected:

	QPixmap texture_walk[2];

	static const int walk_div = 10;

public:

	Troopa() {}
	Troopa(QPoint position, Direction direction = RIGHT);

	virtual std::string name() { return "Koopa Troopa"; }
	virtual void animate();
	virtual void hit(Object *what, Direction fromDir);
	virtual void hurt();
};