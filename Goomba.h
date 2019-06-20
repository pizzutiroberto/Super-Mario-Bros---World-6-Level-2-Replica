#pragma once

#include "Enemy.h"

class Goomba : public Enemy
{
    protected:

        QPixmap texture_walk[2];
        QPixmap texture_dead;

		static const int walk_div = 10;

    public:

        Goomba(QPoint position, Direction direction = RIGHT);

        virtual std::string name(){ return "Goomba";}
        virtual void animate();
        virtual void hit(Object *what, Direction fromDir);
		virtual void hurt();
};