#pragma once

#include "Inert.h"

class Block : public Inert
{
	public:

		Block(QPoint position);

        virtual std::string name() { return "Block"; }
        virtual void hit(Object *what, Direction fromDir);
};