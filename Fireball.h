#pragma once

#include "Entity.h"

class Fireball : public Entity
{
    protected:

        QPixmap texture_fireball[4];
		int y0;
		bool descend;
		Direction dir;

	public:

        Fireball(QPointF position);

        virtual std::string name() {return "Fireball";}
        virtual void advance();
        virtual void animate();
        virtual void hit(Object *what, Direction fromDir);
};
