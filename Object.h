#pragma once

#include <string>
#include <QGraphicsPixmapItem>
#include "utils.h"

class Object : public QGraphicsPixmapItem
{	
	protected:

		bool walkable;
		bool collidable;

	public:

		Object();

		bool isWalkable()   {return walkable;  }
		bool isCollidable() {return collidable;}

		virtual std::string name() = 0;
        virtual void animate() = 0;
        virtual void advance() = 0;
        virtual void solveCollisions() = 0;
		virtual void hit(Object *what, Direction fromDir) = 0;
        virtual Direction collisionDirection(Object* item);
        virtual Direction touchingDirection(Object* item);
};
