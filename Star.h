#pragma once

#include "Entity.h"

class Star : public Entity
{
    protected:

        QPoint spawned_position;

    public:

        Star(QPoint position);

        virtual std::string name() { return "Star"; }
        virtual void animate();
        virtual void hit(Object *what, Direction fromDir);
};
