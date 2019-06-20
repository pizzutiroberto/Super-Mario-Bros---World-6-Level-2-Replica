#pragma once

#include "Inert.h"

class Pipe : public Inert
{
    public:

        Pipe(QPoint position, int size);

        virtual std::string name() { return "Pipe"; }
        virtual void hit(Object *what, Direction fromDir) { }
};