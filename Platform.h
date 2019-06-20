#pragma once

#include "Inert.h"

class Platform : public Inert
{
	protected:

		QPixmap texture_platform[2];
		Direction dir;
		bool move;
		int move_counter;
		int move_duration;

	public:

		Platform(QPoint position, int duration, int type, Direction direction);

		virtual std::string name() { return "Platform"; }
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);
};