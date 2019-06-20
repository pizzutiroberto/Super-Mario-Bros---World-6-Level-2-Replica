#pragma once

#include "Enemy.h"

class PiranhaPlant : public Enemy
{
	protected:

		QPixmap texture_plant[2];

		int cycle_counter;					// duration of the movement cycle
		bool descend;						// is the plant going down or up?
		bool animation_freeze;				// freeze plant
		bool inPipe;						// plant is inside the pipe

		// Freeze animation variables
		int animation_freeze_counter;
		int animation_freeze_duration;

	public:

		PiranhaPlant(QPoint position);
		QPoint spawned_position;

		virtual std::string name() { return "Piranha Plant"; }
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);
		virtual void hurt() { }
};