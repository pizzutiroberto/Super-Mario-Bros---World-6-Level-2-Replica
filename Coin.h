#pragma once

#include "Entity.h"

class Coin : public Entity
{
protected:

	QPoint spawned_position;
	QPixmap texture;

public:

	Coin(QPoint position);

	virtual std::string name() { return "Coin"; }
	virtual void animate() {};
	virtual void hit(Object *what, Direction fromDir);
    virtual void die() {};
};
