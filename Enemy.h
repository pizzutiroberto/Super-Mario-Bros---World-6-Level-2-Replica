#pragma once

#include "Entity.h"

class Enemy : public Entity
{
	protected:

		bool hurtable;

	public:

		Enemy();

		bool isHurtable() { return hurtable; }

		virtual std::string name() = 0;
		virtual void animate()     = 0;
		virtual void hit(Object *what, Direction fromDir) = 0;
		virtual void hurt() = 0;
};