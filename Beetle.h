#pragma once

#include "Enemy.h"

class Beetle : public Enemy
{
protected:

	QPixmap texture_walk[2];

	static const int walk_div = 10;

public:

	Beetle() {}
	Beetle(QPoint position, Direction direction = RIGHT);

	virtual std::string name() { return "Buzzy Beetle"; }
	virtual void animate();
	virtual void hit(Object *what, Direction fromDir);
	virtual void hurt();
};