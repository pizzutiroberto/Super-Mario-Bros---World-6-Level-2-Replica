#include "HUD.h"
#include "Game.h"

HUD::HUD() : Inert()
{
	offset_y_second_row = 12;
	offset_x_coin = 25;
	offset_x_level = 10;
	offset_x_time = 5;
	score_posx = 25;
	score_posy = 12;
	lives_posx = 125;
	lives_posy = 12;
	coin_posx = 125;
	coin_posy = 8 + offset_y_second_row;
	level_posx = 225;
	level_posy = 12;
	time_posx = 335;
	time_posy = 12;

	animation_counter = 0;
	animation_step_duration = 10;
	onAnimation = false;

	// Digits textures
	digits[0] = QPixmap(loadTexture(":/graphics/HUD/0.png"));
	digits[1] = QPixmap(loadTexture(":/graphics/HUD/1.png"));
	digits[2] = QPixmap(loadTexture(":/graphics/HUD/2.png"));
	digits[3] = QPixmap(loadTexture(":/graphics/HUD/3.png"));
	digits[4] = QPixmap(loadTexture(":/graphics/HUD/4.png"));
	digits[5] = QPixmap(loadTexture(":/graphics/HUD/5.png"));
	digits[6] = QPixmap(loadTexture(":/graphics/HUD/6.png"));
	digits[7] = QPixmap(loadTexture(":/graphics/HUD/7.png"));
	digits[8] = QPixmap(loadTexture(":/graphics/HUD/8.png"));
	digits[9] = QPixmap(loadTexture(":/graphics/HUD/9.png"));

	// Mario text on the top of the score
	mario_text = QPixmap(loadTexture(":/graphics/HUD/mario.png"));
	
	// Mario icon for lives counter
	texture_mario_lives = QPixmap(loadTexture(":/graphics/mario/small/jump.png"));

	// Coin icon for coin counter
	texture_coin = QPixmap(loadTexture(":/graphics/items/coin-1.png"));

	// World 6-2 text
	world_text[0] = QPixmap(loadTexture(":/graphics/HUD/world-0.png"));
	world_text[1] = QPixmap(loadTexture(":/graphics/HUD/world-1.png"));

	// Time text on the top of the timer
	time_text = QPixmap(loadTexture(":/graphics/HUD/time.png"));

	//-----------Score section-------------//
	mario_text_view = Game::instance()->getScene()->addPixmap(mario_text);
	mario_text_view->setPos(score_posx + 5, score_posy);

	for (int i = 0; i < 6; i++)
	{
		score_view[i] = Game::instance()->getScene()->addPixmap(digits[0]);
		score_view[i]->setPos(score_posx + i * 10, score_posy + offset_y_second_row);
	}
	//---------End Score section------------//

	//-----------Lives section-------------//
	texture_mario_lives_view = Game::instance()->getScene()->addPixmap(texture_mario_lives);
	texture_mario_lives_view->setPos(lives_posx + 3, lives_posy - 6);
	
	lives_count[0] = Game::instance()->getScene()->addPixmap(digits[0]);
	lives_count[0]->setPos(lives_posx + offset_x_coin, lives_posy);
	lives_count[1] = Game::instance()->getScene()->addPixmap(digits[3]);
	lives_count[1]->setPos(lives_posx + offset_x_coin + 10, lives_posy);
	//---------End Lives section------------//

	//-----------Coin section-------------//
	texture_coin_view = Game::instance()->getScene()->addPixmap(texture_coin);
	texture_coin_view->setPos(coin_posx + 5, coin_posy);

	coin_count[0] = Game::instance()->getScene()->addPixmap(digits[0]);
	coin_count[0]->setPos(coin_posx + offset_x_coin, coin_posy + offset_y_second_row);
	coin_count[1] = Game::instance()->getScene()->addPixmap(digits[0]);
	coin_count[1]->setPos(coin_posx + offset_x_coin + 10, coin_posy + offset_y_second_row);
	//----------End Coin section-----------//

	//-----------Level section-------------//
	world_text_view[0] = Game::instance()->getScene()->addPixmap(world_text[0]);
	world_text_view[0]->setPos(level_posx, level_posy);
	world_text_view[1] = Game::instance()->getScene()->addPixmap(world_text[1]);
	world_text_view[1]->setPos(level_posx + offset_x_level, level_posy + offset_y_second_row);
	//----------End level section-----------//

	//-----------Timer section-------------//
	time_text_view = Game::instance()->getScene()->addPixmap(time_text);
	time_text_view->setPos(time_posx, time_posy);
	time_view[0] = Game::instance()->getScene()->addPixmap(digits[4]);
	time_view[0]->setPos(time_posx + offset_x_time, time_posy + offset_y_second_row);
	time_view[1] = Game::instance()->getScene()->addPixmap(digits[0]);
	time_view[1]->setPos(time_posx + offset_x_time + 10, time_posy + offset_y_second_row);
	time_view[2] = Game::instance()->getScene()->addPixmap(digits[0]);
	time_view[2]->setPos(time_posx + offset_x_time + 20, time_posy + offset_y_second_row);
	//----------End Timer section-----------//

	setZValue(1);
}

void HUD::animate()
{
	if (onAnimation)
		startEndAnimation();
	else
	{
		// update values
		int score = Game::instance()->getScore();
		int coin_counter = Game::instance()->getCoinCounter();
		int level_time = Game::instance()->getLevelTimer();
		int mario_lives = Game::instance()->getMario()->getLives();

		// convert values
		scoreConverter(score);
		timerConverter(level_time);

		// update positions
		int camera_max_x = Game::instance()->getCameraMaxX();
		if (camera_max_x < 200)
		{
			score_posx = 25;
			lives_posx = 125;
			coin_posx = 125;
			level_posx = 225;
			time_posx = 335;
		}
		else
		{
			score_posx = camera_max_x - 175;
			lives_posx = camera_max_x - 75;
			coin_posx = camera_max_x - 75;
			level_posx = camera_max_x + 25;
			time_posx = camera_max_x + 135;
		}

		// Update HUD with new values and new positions
		Game::instance()->getScene()->removeItem(mario_text_view);
		mario_text_view = Game::instance()->getScene()->addPixmap(mario_text);
		mario_text_view->setPos(score_posx + 5, score_posy);

		for (int i = 0; i < 6; i++)
		{
			Game::instance()->getScene()->removeItem(score_view[i]);
			score_view[i] = Game::instance()->getScene()->addPixmap(digits[index_score[i]]);
			score_view[i]->setPos(score_posx + i * 10, score_posy + offset_y_second_row);
		}

		Game::instance()->getScene()->removeItem(texture_mario_lives_view);
		Game::instance()->getScene()->removeItem(lives_count[0]);
		Game::instance()->getScene()->removeItem(lives_count[1]);
		texture_mario_lives_view = Game::instance()->getScene()->addPixmap(texture_mario_lives);
		texture_mario_lives_view->setPos(lives_posx + 3, lives_posy - 6);
		lives_count[0] = Game::instance()->getScene()->addPixmap(digits[mario_lives / 10]);
		lives_count[0]->setPos(lives_posx + offset_x_coin, lives_posy);
		lives_count[1] = Game::instance()->getScene()->addPixmap(digits[mario_lives % 10]);
		lives_count[1]->setPos(lives_posx + offset_x_coin + 10, lives_posy);

		Game::instance()->getScene()->removeItem(texture_coin_view);
		Game::instance()->getScene()->removeItem(coin_count[0]);
		Game::instance()->getScene()->removeItem(coin_count[1]);
		texture_coin_view = Game::instance()->getScene()->addPixmap(texture_coin);
		texture_coin_view->setPos(coin_posx + 5, coin_posy);
		coin_count[0] = Game::instance()->getScene()->addPixmap(digits[coin_counter / 10]);
		coin_count[0]->setPos(coin_posx + offset_x_coin, score_posy + offset_y_second_row);
		coin_count[1] = Game::instance()->getScene()->addPixmap(digits[coin_counter % 10]);
		coin_count[1]->setPos(coin_posx + offset_x_coin + 10, score_posy + offset_y_second_row);

		Game::instance()->getScene()->removeItem(world_text_view[0]);
		Game::instance()->getScene()->removeItem(world_text_view[1]);
		world_text_view[0] = Game::instance()->getScene()->addPixmap(world_text[0]);
		world_text_view[0]->setPos(level_posx, level_posy);
		world_text_view[1] = Game::instance()->getScene()->addPixmap(world_text[1]);
		world_text_view[1]->setPos(level_posx + offset_x_level, level_posy + offset_y_second_row);

		Game::instance()->getScene()->removeItem(time_text_view);
		Game::instance()->getScene()->removeItem(time_view[0]);
		Game::instance()->getScene()->removeItem(time_view[1]);
		Game::instance()->getScene()->removeItem(time_view[2]);
		time_text_view = Game::instance()->getScene()->addPixmap(time_text);
		time_text_view->setPos(time_posx, time_posy);
		time_view[0] = Game::instance()->getScene()->addPixmap(digits[index_time[0]]);
		time_view[0]->setPos(time_posx + offset_x_time, time_posy + offset_y_second_row);
		time_view[1] = Game::instance()->getScene()->addPixmap(digits[index_time[1]]);
		time_view[1]->setPos(time_posx + offset_x_time + 10, time_posy + offset_y_second_row);
		time_view[2] = Game::instance()->getScene()->addPixmap(digits[index_time[2]]);
		time_view[2]->setPos(time_posx + offset_x_time + 20, time_posy + offset_y_second_row);

		if (Game::instance()->getGameEnd() && !onAnimation)
		{
			onAnimation = true;
			timeToScore(level_time);
		}
	}
}

void HUD::timeToScore(int timer)
{
	end_level_timer = timer;
	startEndAnimation();
}

void HUD::startEndAnimation()
{
	// Animation for ending time-score conversion
	animation_counter++;
	if (animation_counter > animation_step_duration)
	{
		int score = (200 - end_level_timer) * 100;

		scoreConverter(score);
		timerConverter(end_level_timer);

		for (int i = 0; i < 6; i++)
		{
			Game::instance()->getScene()->removeItem(score_view[i]);
			score_view[i] = Game::instance()->getScene()->addPixmap(digits[index_score[i]]);
			score_view[i]->setPos(score_posx + i * 10, score_posy + offset_y_second_row);
		}

		Game::instance()->getScene()->removeItem(time_view[0]);
		Game::instance()->getScene()->removeItem(time_view[1]);
		Game::instance()->getScene()->removeItem(time_view[2]);
		time_view[0] = Game::instance()->getScene()->addPixmap(digits[index_time[0]]);
		time_view[0]->setPos(time_posx + offset_x_time, time_posy + offset_y_second_row);
		time_view[1] = Game::instance()->getScene()->addPixmap(digits[index_time[1]]);
		time_view[1]->setPos(time_posx + offset_x_time + 10, time_posy + offset_y_second_row);
		time_view[2] = Game::instance()->getScene()->addPixmap(digits[index_time[2]]);
		time_view[2]->setPos(time_posx + offset_x_time + 20, time_posy + offset_y_second_row);

		Game::instance()->get_time_to_score_sound()->play();

		end_level_timer--;
		animation_counter = 0;

		if (end_level_timer == 0)
		{
			Game::instance()->setEngineStop(true);
			Game::instance()->getScene()->removeItem(time_view[2]);
			time_view[2] = Game::instance()->getScene()->addPixmap(digits[0]);
			time_view[2]->setPos(time_posx + offset_x_time + 20, time_posy + offset_y_second_row);
		}

		timeToScore(end_level_timer);
	}
}

void HUD::scoreConverter(int _score)
{
	index_score[0] = _score / 100000;
	index_score[1] = _score / 10000 % 10;
	index_score[2] = _score / 1000 % 10;
	index_score[3] = _score / 100 % 10;
	index_score[4] = _score / 10 % 10;
	index_score[5] = _score % 10;
}

void HUD::timerConverter(int _timer)
{
	index_time[0] = _timer / 100 % 10;
	index_time[1] = _timer / 10 % 10;
	index_time[2] = _timer % 10;
}
