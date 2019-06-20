#pragma once

#include "Inert.h"

enum spawnable_t {
	COIN,
	MULTICOIN,
	POWERUP,
	LIFE,
	VINE,
	STAR
};

enum visibility_t {
	VISIBLE,
	BRICKED,
	BRICKEDUND,
	INVISIBLE
};

class Box : public Inert
{
	protected:

		QPixmap texture_cycle[3];
		QPixmap texture_used[2];
		QPixmap texture_brick[2];

		bool used;
		bool hitted;
		bool wasUndeground;

		visibility_t visibility;
		spawnable_t spawnable;

		static const int anim_div = 40;

		int hit_counter;
		int multicoin_counter = 13;		// Number of coins in the multicoin box

	public:

		Box(QPoint position, visibility_t _visibility = VISIBLE, spawnable_t _spawnable = COIN);

		visibility_t getVisibility() { return visibility; }		// Return the visibility status of the block

		virtual std::string name() {return "Box";}
		virtual void animate();
		virtual void advance();
		virtual void hit(Object *what, Direction fromDir);
};