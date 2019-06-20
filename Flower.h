#pragma once

#include "Entity.h"

class Flower : public Entity
{
	protected:

		QPixmap texture_cycle[4];
		QPoint spawned_position;

		static const int anim_div = 5;

	public:

		Flower(QPoint position);

		virtual std::string name() {return "Flower";}
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);
};