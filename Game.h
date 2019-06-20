#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QSound>
#include <string>
#include "Mario.h"
#include "LevelManager.h"

class Game : public QGraphicsView
{
	Q_OBJECT

		enum game_state { READY, RUNNING, PAUSE, GAME_OVER };

private:

	static Game* uniqueInstance;
	Game(QGraphicsView *parent = 0);

	QGraphicsScene *scene;
	QGraphicsScene *old_scene;
	Mario *mario;
	QTimer engine;
	game_state cur_state;

	// Load sounds at start
	QSound *overworld_loop_sound = new QSound(":/sounds/overworld.wav");
	QSound *gameover_sound = new QSound(":/sounds/gameover.wav");
	QSound *pause_sound = new QSound(":/sounds/pause.wav");
	QSound *stomp_sound = new QSound(":/sounds/stomp.wav");
	QSound *block_hit_sound = new QSound(":/sounds/block-hit.wav");
	QSound *block_break_sound = new QSound(":/sounds/block-break.wav");
	QSound *coin_sound = new QSound(":/sounds/coin.wav");
	QSound *mushroom_appear_sound = new QSound(":/sounds/mushroom-appear.wav");
	QSound *mushroom_eat_sound = new QSound(":/sounds/mushroom-eat.wav");
	QSound *jump_sound = new QSound(":/sounds/jump-big.wav");
	QSound *jump_small_sound = new QSound(":/sounds/jump-small.wav");
	QSound *oneup_sound = new QSound(":/sounds/oneup.wav");
	QSound *shrink_sound = new QSound(":/sounds/shrink.wav");
	QSound *death_sound = new QSound(":/sounds/death.wav");
	QSound *levelend_sound = new QSound(":/sounds/levelend.wav");
	QSound *vine_sound = new QSound(":/sounds/vine.wav");
	QSound *kick_sound = new QSound(":/sounds/kick.wav");
	QSound *fireball_sound = new QSound(":/sounds/fireball.wav");
	QSound *star_sound = new QSound(":/sounds/star.wav");
	QSound *time_warning_sound = new QSound(":/sounds/time-warning.wav");
	QSound *underwater_sound = new QSound(":/sounds/underwater.wav");
	QSound *underground_sound = new QSound(":/sounds/underground.wav");
	QSound *time_to_score_sound = new QSound(":/sounds/time-to-score.wav");

	// Graphics items for Menu and Screens
	QGraphicsPixmapItem* menu_hill;
	QGraphicsPixmapItem* menu_bush;
	QGraphicsPixmapItem* menu_terrain;
	QGraphicsPixmapItem* menu_title;
	QGraphicsPixmapItem* menu_mario;
	QGraphicsPixmapItem* menu_newgame;
	QGraphicsPixmapItem* menu_exitgame;
	QGraphicsPixmapItem* menu_holdtab;
	QGraphicsPixmapItem* menu_mushroom;
	QGraphicsPixmapItem* game_over_screen;
	QGraphicsPixmapItem* paused_screen;
	QGraphicsPixmapItem* commands_screen;

	int _endLevelCoord;				// End level coordinates
	int level_timer;				// Game timer
	int timer_div;					// Timer div to convert game timer into seconds
	int score;						// Score earned
	int coin_counter;				// Coin collected counter
	int active_sublevel;			// Actual active sublevel
	int camera_max_x;				// X Coord used to block the camera on the left
	int camera_max_x_temp;			// Temporary X Coord
	bool new_game_menu_voice;		// "New Game" menu item flag (if true is selected)
	bool exit_game_menu_voice;		// "Exit Game"  menu item flag (if true is selected)
	bool game_end;					// if true ends the game
	bool engine_stop;				// if true stops the engine
	bool timeover;					// true if timer reaches 0
	bool frenzy;					// true if game is in frenzy mode (time left below 20 seconds). Frenzy mode: enemies are faster
	int mario_lives;				// mario lives counter
	bool force_reset;				// if true forces a reset. Go to main menu

	void drawStartMenu();			// draw the main menu

protected:

	virtual void keyPressEvent(QKeyEvent *e);
	virtual void keyReleaseEvent(QKeyEvent *e);
	virtual void wheelEvent(QWheelEvent *e);

public:

	static Game* instance();

	QGraphicsScene* getScene() { return scene; }								// Get the current scene
	Mario* getMario() { return mario; }											// Get Mario object

	//------------------------ Sound Getters ---------------------------//
	QSound* get_overworld_loop_sound() { return overworld_loop_sound; }
	QSound* get_gameover_sound() { return gameover_sound; }
	QSound* get_pause_sound() { return pause_sound; }
	QSound* get_stomp_sound() { return stomp_sound; }
	QSound* get_block_hit_sound() { return block_hit_sound; }
	QSound* get_block_break_sound() { return block_break_sound; }
	QSound* get_coin_sound() { return coin_sound; }
	QSound* get_mushroom_appear_sound() { return mushroom_appear_sound; }
	QSound* get_mushroom_eat_sound() { return mushroom_eat_sound; }
	QSound* get_jump_sound() { return jump_sound; }
	QSound* get_jump_small_sound() { return jump_small_sound; }
	QSound* get_oneup_sound() { return oneup_sound; }
	QSound* get_shrink_sound() { return shrink_sound; }
	QSound* get_death_sound() { return death_sound; }
	QSound* get_levelend_sound() { return levelend_sound; }
	QSound* get_vine_sound() { return vine_sound; }
	QSound* get_kick_sound() { return kick_sound; }
	QSound* get_fireball_sound() { return fireball_sound; }
	QSound* get_star_sound() { return star_sound; }
	QSound* get_time_warning_sound() { return time_warning_sound; }
	QSound* get_underwater_sound() { return underwater_sound; }
	QSound* get_underground_sound() { return underground_sound; }
	QSound* get_time_to_score_sound() { return time_to_score_sound; }
	//--------------------- End Sound Getters ---------------------------//

	int getEndLevel() { return _endLevelCoord; }								// Get end level coordinates
	int getActiveSublevel() { return active_sublevel; }							// Get the active sublevel
	int getCameraMaxX() { return camera_max_x; }								// Get the x coord of the camera
	int getCameraMaxXTemp() { return camera_max_x_temp; }						// Get the x coord temp of the camera
	void setActiveSublevel(int value) { active_sublevel = value; }				// Change the active sublevel
	void setCameraMaxX(int value) { camera_max_x = value; }						// Update x coord of the camera
	void setCameraMaxXTemp(int value) { camera_max_x_temp = value; }			// Update x coord temp of the camera
	void generateUnderWaterEnemies();											// Generate bloopers and cheep cheeps
	void addScore(int points) { score += points; }								// Update score
	int getScore() { return score; }											// Get the actual score
	void addCoinCount();														// Update coin counter
	int getCoinCounter() { return coin_counter; }								// Get the number of coins collected
	int getLevelTimer() { return level_timer / timer_div; }						// Get the remaining level timer
	void setGameEnd(bool value) { game_end = value; }							// Set the game end status
	bool getGameEnd() { return game_end; }										// Get the game end status
	void setEngineStop(bool value) { engine_stop = value; }						// Stop-Start engine
	int game_getMarioLives() { return mario_lives; }							// Get mario lives saved in the game istance
	bool isFrenzy() { return frenzy; }											// Get Frenzy mode status

public slots:

	void advance();
	void tooglePause();				// Pause-Unpause the game
	void reset();					// Reset the game
	void start();					// Start selected level
	void gameover();				// Gameover -> go to main menu / restart level
	void stopMusic();				// Stop music
};
