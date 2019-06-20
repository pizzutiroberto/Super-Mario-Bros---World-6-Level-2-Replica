#pragma once

#include "Enemy.h"

class Blooper : public Enemy
{
	enum BlooberDirection { UPLEFT, UPRIGHT, BOTTOMLEFT, BOTTOMRIGHT };

	protected:

		QPixmap texture_blooper[2];
		BlooberDirection direction;
		int cycle_counter;
		int walk_div = 30;

	public:

		Blooper(QPoint position);

		virtual std::string name() { return "Blooper"; }
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);
		virtual void hurt() { }
};