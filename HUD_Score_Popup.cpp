#include "HUD_Score_Popup.h"

HUD_Score_Popup::HUD_Score_Popup(QPoint position, scoreValue _value) : Entity()
{
	spawned_position = position;

	value = _value;

	if (value == SCORE50)
		texture_score = texture_score_50;
	else if (value == SCORE100)
		texture_score = texture_score_100;
	else if (value == SCORE200)
		texture_score = texture_score_200;
	else if (value == SCORE400)
		texture_score = texture_score_400;
	else if (value == SCORE500)
		texture_score = texture_score_500;
	else if (value == SCORE1000)
		texture_score = texture_score_1000;
	else if (value == SCORE1500)
		texture_score = texture_score_1500;
	else if (value == SCORE2000)
		texture_score = texture_score_2000;
	else if (value == SCORE2500)
		texture_score = texture_score_2500;
	else if (value == SCORE3000)
		texture_score = texture_score_3000;
	else if (value == SCORE3500)
		texture_score = texture_score_3500;
	else if (value == SCORE4000)
		texture_score = texture_score_4000;
	else if (value == SCORE4500)
		texture_score = texture_score_4500;
	else if (value == SCORE5000)
		texture_score = texture_score_5000;

	setPixmap(texture_score);
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

void HUD_Score_Popup::animate()
{
	if (falling && y() >= spawned_position.y())
		die();
}