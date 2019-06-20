#include "HUD_Life_Popup.h"

HUD_Life_Popup::HUD_Life_Popup(QPoint position) : Entity()
{
	spawned_position = position;

	setPixmap(texture_1up);
	setPos(position.x(), position.y() - 20);

	collidable = false;
	moving = false;
	falling = false;
	jumping_speed = 1;
	falling_speed = 1;
	death_duration = 0;
	jumping_duration = 10;
	setZValue(10);

	startJumping();
}

void HUD_Life_Popup::animate()
{
	if (falling && y() >= spawned_position.y())
		die();
}