#pragma once

#include "Inert.h"

class HUD : public Inert
{
	protected:

		QPixmap digits[10];									// Digits textures
		QPixmap mario_text;									// Mario text
		QPixmap texture_mario_lives;						// Mario icon
		QPixmap texture_coin;								// Coin icon
		QPixmap world_text[2];								// World and level text
		QPixmap time_text;									// Time text
		QGraphicsPixmapItem* score_view[6];					// 6 digits for score
		QGraphicsPixmapItem* mario_text_view;				// Placing mario text in the scene
		QGraphicsPixmapItem* texture_coin_view;				// Placing coin texture in the scene
		QGraphicsPixmapItem* texture_mario_lives_view;		// Placing mario texture in the scene
		QGraphicsPixmapItem* lives_count[2];				// 2 digits for lives counter
		QGraphicsPixmapItem* coin_count[2];					// 2 digits for coin counter
		QGraphicsPixmapItem* world_text_view[2];			// Placing level and world text in the scene
		QGraphicsPixmapItem* time_text_view;				// Placing time text in the scene
		QGraphicsPixmapItem* time_view[3];					// 3 digits for timer

		// X and Y positions for the HUD elements in the scene
		int score_posx;
		int score_posy;
		int lives_posx;
		int lives_posy;
		int coin_posx;
		int coin_posy;
		int level_posx;
		int level_posy;
		int time_posx;
		int time_posy;
		int offset_y_second_row;
		int offset_x_coin;
		int offset_x_level; 
		int offset_x_time;

		int index_score[6];					// Result in digits of score conversion
		int index_time[3];					// Result in digits of timer conversion
		int end_level_timer;				// End value of the timer. Used for the end animation
		int animation_counter;				// End animation counter
		int animation_step_duration;		// End animation duration
		bool onAnimation;					// If true freezes all to avoid problems during end animation

		void timeToScore(int timer);		// Convert Timer into Score
		void startEndAnimation();			// Enable end animation
		void scoreConverter(int _score);	// Convert raw score into a correct view form
		void timerConverter(int _timer);	// Convert raw timer into a correct view form

    public:

        HUD();

        virtual std::string name() { return "HUD"; }
		virtual void animate();
        virtual void hit(Object *what, Direction fromDir) { }
};