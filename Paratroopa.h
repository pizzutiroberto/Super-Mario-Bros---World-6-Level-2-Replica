#pragma once

#include "Troopa.h"

class Paratroopa : public Troopa
{
protected:

	QPixmap texture_fly[2];

	static const int walk_div = 10;

public:

	Paratroopa(QPoint position, Direction direction = RIGHT);

	virtual std::string name() { return "Koopa Paratroopa"; }
	virtual void advance();
	virtual void animate();
	virtual void hit(Object *what, Direction fromDir);
	virtual void hurt();
};