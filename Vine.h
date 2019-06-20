#pragma once

#include "Inert.h"

class Vine : public Inert
{
	private:

		QPixmap texture_vine_full;
		QPixmap texture_vine_cropped;

		QPoint spawned_position;
		QPointF prevPos;
		bool spawn;
        bool draw;
		int spawn_index;
        int spawn_counter;
        int spawn_duration;

	public:

		Vine(QPoint position);

		virtual std::string name() { return "Vine"; }
		virtual void hit(Object *what, Direction fromDir);
		virtual void animate();
};
