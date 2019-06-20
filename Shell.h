#pragma once

#include "Enemy.h"

enum shell_type {KOOPA, BEETLE};

class Shell : public Enemy
{
	protected:

		QPixmap texture_shell[3];

		shell_type type;

		static const int walk_div = 10;

		bool transforming;
		int transformation_counter;
		int transformation_duration;
		int shell_counter;
		int shell_duration;


	public:

		Shell(QPoint position, Direction direction, shell_type shelltype);

		bool isBeetleShell() { return type == BEETLE ? true : false; }

		virtual std::string name() { return "Shell"; }
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);
		virtual void hurt() { }
};