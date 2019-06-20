#pragma once

#include "Inert.h"

class Brick : public Inert
{

	protected:

		bool hitted;
		bool broken;
		int hit_counter;
		int brick_type;

	public:

		Brick(QPoint position, int type);

		virtual std::string name() {return "Brick";}
		virtual void advance();
		virtual void hit(Object *what, Direction fromDir);
};