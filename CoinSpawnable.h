#pragma once

#include "Entity.h"

class CoinSpawnable : public Entity
{
	protected:

		QPoint spawned_position;
		QPixmap texture_cycle[4];

		static const int anim_div = 6;

	public:

		CoinSpawnable(QPoint position);

		virtual std::string name() {return "CoinSpawnable";}
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir){}
};