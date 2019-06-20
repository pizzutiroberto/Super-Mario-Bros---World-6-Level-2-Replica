#pragma once

#include "Inert.h"
#include "Background.h"

class Pole : public Inert
{
	private:

		Background* endpole;
		Background* flag;

		bool hitted;
		int hit_counter;
		int hit_duration;
		bool ended;

	public:

		Pole(QPoint position);

		virtual std::string name() { return "Pole"; }
		virtual void hit(Object *what, Direction fromDir);
		void advance();
};