#pragma once

#include "Enemy.h"

enum fishType { RED, GREY };

class CheepCheep : public Enemy
{
	protected:

		QPixmap texture_fish[2][2];
	
		int cycle_counter;
		int walk_div = 30;
		float walk_speed;
		int walk_spread;
		bool descend;
		fishType type;

	public:

		CheepCheep(QPoint position, Direction direction, fishType f_type);

		virtual std::string name() { return "CheepCheep"; }
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);
		virtual void hurt() { }
};