#pragma once

#include "Entity.h"

class Mushroom : public Entity
{
	protected:

		QPoint spawned_position;
		bool red;
	
	public:

		Mushroom(QPoint position, bool _red = true);

		virtual std::string name() {return "Mushroom";}
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);
};