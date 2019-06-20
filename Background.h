#pragma once

#include "Inert.h"

class Background : public Inert
{
	protected:

		std::string texture_path;

	public:

		Background(QPoint position, std::string _texture_path);

		virtual std::string name() {return std::string("Background (") + texture_path + ")";}
		virtual void hit(Object *what, Direction fromDir) { };
};