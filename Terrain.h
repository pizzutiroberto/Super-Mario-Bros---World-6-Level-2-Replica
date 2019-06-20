#pragma once

#include "Inert.h"

class Terrain : public Inert
{
	public:

		Terrain(QRect rect, int terrain_type);

        virtual std::string name() { return "Terrain"; }
        virtual void hit(Object *what, Direction fromDir) { }
};