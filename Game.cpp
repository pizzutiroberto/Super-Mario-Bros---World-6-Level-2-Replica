#include <QApplication>
#include <QKeyEvent>
#include <QScrollBar>
#include <QWheelEvent>
#include <QSound>
#include <QThread>
#include "Game.h"
#include "Object.h"
#include "Entity.h"
#include "Mario.h"
#include "Fireball.h"
#include "CheepCheep.h"
#include "Blooper.h"
#include "HUD.h"

Game* Game::uniqueInstance = 0;
Game* Game::instance()
{
	if(uniqueInstance == 0)
		uniqueInstance = new Game();
	return uniqueInstance;
}


Game::Game(QGraphicsView *parent) : QGraphicsView(parent)
{
	scene = new QGraphicsScene();
	setScene(scene);
	scale(2.0,2.0);
	centerOn(0,0);
	setInteractive(false);
	setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
	setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
	scene->setSceneRect(0, 0, 10000, 225);

    QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));
    engine.setInterval(10);

	overworld_loop_sound->setLoops(QSound::Infinite);
	underwater_sound->setLoops(QSound::Infinite);
	underground_sound->setLoops(QSound::Infinite);

	mario = 0;

    this->setFixedWidth(800);
	this->setFixedHeight(450);

    reset();
}

void Game::reset()
{
	// Reset values and flags
	cur_state = READY;
	score = 0;
	level_timer = 0;
	timer_div = 100;
	coin_counter = 0;
	camera_max_x = 0;
	camera_max_x_temp = 0;
	new_game_menu_voice = true;
	exit_game_menu_voice = false;
	game_end = false;
	engine_stop = false;
	timeover = false;
	frenzy = false;

	// Stop engine and music
	engine.stop();
    stopMusic();

	scene->setSceneRect(0, 0, 10000, 225);

	// Chech for an existing Mario. If mario exist check lives. If not set the default lives value
	if (!mario)
	{
		mario = 0;
		mario_lives = 3;
	}
    else
		mario_lives = mario->getLives();

    if (mario_lives == 0)
    {
        force_reset = true;
        mario = 0;
        mario_lives = 3;
    }

    // Force reset is used when we manually resets game or Mario has 0 lives
    if (force_reset)
    {
        mario_lives = 3;
        force_reset = false;
        drawStartMenu();
    }
    else if(mario)
        start();
}

void Game::drawStartMenu()
{
	// Drawing start menu
	int scale = 16;
	int terrain_level = 200;

	scene->clear();
	centerOn(400/2, 450/2);
	scene->setBackgroundBrush(QBrush(QColor(99, 133, 251)));

	// Draw the hill
	menu_hill = scene->addPixmap(loadTexture(":/graphics/scenary/hill-big.png"));
	menu_hill->setPos(0 * scale, terrain_level - 2 * scale);

	// Draw the bush
	menu_bush = scene->addPixmap(loadTexture(":/graphics/scenary/bush-big.png"));
	menu_bush->setPos(20.5 * scale, terrain_level - 1 * scale);

	// Draw the title "Super Mario Bros"
	menu_title = scene->addPixmap(loadTexture(":/graphics/scenary/welcome.png"));
	menu_title->setPos(7 * scale, terrain_level - 12 * scale);

	// Draw the terrain
	for (int i = 0; i < 25; i++)
	{
		menu_terrain = scene->addPixmap(loadTexture(":/graphics/scenary/wall.png"));
		menu_terrain->setPos(i * scale, terrain_level);
		menu_terrain = scene->addPixmap(loadTexture(":/graphics/scenary/wall.png"));
		menu_terrain->setPos(i * scale, terrain_level + 1 * scale);
	}

	// Draw the lil Mario
	menu_mario = scene->addPixmap(loadTexture(":/graphics/mario/small/stand.png"));
	menu_mario->setPos(5.5 * scale, terrain_level - 1 * scale);

	// Draw the menu selectors "New Game" and "Exit" and the relative mushroom to point the selection
	menu_newgame = scene->addPixmap(loadTexture(":/graphics/scenary/new-game.png"));
	menu_newgame->setPos(10 * scale, terrain_level - 4.8 * scale);
	menu_exitgame = scene->addPixmap(loadTexture(":/graphics/scenary/exit-game.png"));
	menu_exitgame->setPos(10 * scale, terrain_level - 2.8 * scale);
	menu_mushroom = scene->addPixmap(loadTexture(":/graphics/items/mushroom-red.png"));
	if (new_game_menu_voice)
		menu_mushroom->setPos(8 * scale, terrain_level - 5 * scale);
	else if (exit_game_menu_voice)
		menu_mushroom->setPos(8 * scale, terrain_level - 3 * scale);

	// Draw the menu voice "hold tab to view commands"
	menu_holdtab = scene->addPixmap(loadTexture(":/graphics/scenary/hold-tab.png"));
	menu_holdtab->setPos(8.5 * scale, terrain_level - 0.9 * scale);
}

void Game::gameover()
{
	// Stop engine and music
	cur_state = GAME_OVER;
	engine.stop();
	overworld_loop_sound->stop();

	// Draw the correct scene when mario dies or time ends
	if (timeover)
		game_over_screen = scene->addPixmap(loadTexture(":/graphics/HUD/time-over.png"));
	else if (mario_lives == 0)
		game_over_screen = scene->addPixmap(loadTexture(":/graphics/HUD/game-over.png"));

	if (mario_lives == 0 || timeover)
	{
		gameover_sound->play();
		if (camera_max_x < 200)
			game_over_screen->setPos(0, 0);
		else
			game_over_screen->setPos(camera_max_x - 200, 0);
		game_over_screen->setZValue(20);
	}
}

void Game::start()
{
	if(cur_state == READY)
	{
		// Start the engine, create a Mario and load the level
		scene->clear();
		engine.start();
        mario = new Mario(QPoint(2.5 * 16, 200));
		LevelManager::load("World-6-2", scene);
		active_sublevel = 0;
        level_timer = 20000;
		_endLevelCoord = 222 * 16;

		if (!mario)
		{
			scene->setBackgroundBrush(QBrush(QColor(242, 204, 204)));
			QGraphicsTextItem* text = scene->addText("Error when loading level");
			text->setPos(300, 90);
			centerOn(text);
		}
		else
            overworld_loop_sound->play();

		cur_state = RUNNING;
	}
}

void Game::tooglePause()
{
	if(cur_state == RUNNING)
	{
		engine.stop();
		paused_screen = scene->addPixmap(loadTexture(":/graphics/HUD/paused.png"));
		if(camera_max_x < 200)
			paused_screen->setPos(200 - 75, 90);
		else
			paused_screen->setPos(camera_max_x - 75, 90);
		paused_screen->setZValue(20);
		stopMusic();
		cur_state = PAUSE;
		pause_sound->play();
	}
	else if(cur_state == PAUSE)
	{
		scene->removeItem(paused_screen);
		engine.start();
		if (active_sublevel == 0)
			overworld_loop_sound->play();
		else if (active_sublevel == 1 || active_sublevel == 2)
			underground_sound->play();
		else if (active_sublevel == 3)
			underwater_sound->play();
		cur_state = RUNNING;
	}
}

void Game::stopMusic()
{
	if (overworld_loop_sound)
		overworld_loop_sound->stop();

    if (underground_sound)
        underground_sound->stop();

    if(underwater_sound)
        underwater_sound->stop();

	if (levelend_sound)
		levelend_sound->stop();

	if (star_sound)
		star_sound->stop();
}

void Game::addCoinCount()
{
	coin_counter++;
	// Collecting 100 coins, Mario gain a life
	if (coin_counter == 100)
	{
		coin_counter = 0;
		mario->increaseLives();
	}
}

void Game::keyPressEvent(QKeyEvent *e)
{
	// UP and Down arrows to navigate in the start menu
	if ((e->key() == Qt::Key_Down || e->key() == Qt::Key_Up) && cur_state == READY)
	{
		new_game_menu_voice = !new_game_menu_voice;
		exit_game_menu_voice = !exit_game_menu_voice;

		fireball_sound->play();
		drawStartMenu();
	}

	// Return key to make the selection in the start menu
	if (e->key() == Qt::Key_Return && cur_state == READY)
	{
		coin_sound->play();
		if (new_game_menu_voice)
			start();
		if (exit_game_menu_voice)
			QCoreApplication::quit();
	}

	// R key to restart the game
    if (e->key() == Qt::Key_R)
    {
        force_reset = true;
		gameover_sound->stop();
		death_sound->stop();
		reset();
	}

    // Return key on mario death to continue
    if (cur_state == GAME_OVER && e->key() == Qt::Key_Return)
    {
        if (mario_lives == 0)
            force_reset = true;
        gameover_sound->stop();
        death_sound->stop();
        reset();
    }

	// P key for pause
	if(e->key() == Qt::Key_P)
		tooglePause();

	// Tab key to show commands
	if (e->key() == Qt::Key_Tab)
	{
		engine.stop();
		commands_screen = scene->addPixmap(loadTexture(":/graphics/HUD/show-commands.png"));
		if (camera_max_x < 200)
			commands_screen->setPos(0, 0);
		else
			commands_screen->setPos(camera_max_x - 200, 0);
		commands_screen->setZValue(20);
	}

	if(cur_state != RUNNING)
		return;

	// Enable mario moving only if not on in a locked animation
	if (!mario->isOnAnimation())
	{
		if (e->key() == Qt::Key_Right || e->key() == Qt::Key_Left)
		{
			mario->setMoving(true);
			mario->setDirection(e->key() == Qt::Key_Right ? Direction::RIGHT : Direction::LEFT);

			// Horizontal pipe entrance
			if (e->key() == Qt::Key_Right && mario->getPosX() >= 12 * 16 && (mario->isBig() ? mario->getPosY() == 200 + 300 - 2 * 16 : mario->getPosY() == 200 + 300 - 1 * 16))
			{
				mario->setPipeAnimation(RIGHT, 0);
				mario->setExitPipePosX(35.5 * 16);
				mario->setExitPipePosY(200 - 3 * 16);
			}

			// Horizontal pipe entrance
			if (e->key() == Qt::Key_Right && mario->getPosX() >= 61 * 16 && (mario->isBig() ? mario->getPosY() == 200 + 300 + 300 + 300 - 6 * 16 : mario->getPosY() == 200 + 300 + 300 + 300 - 5 * 16))
			{
				mario->setPipeAnimation(RIGHT, 0);
				mario->setExitPipePosX(115.5 * 16);
				mario->setExitPipePosY(200 - 3 * 16);
			}

			// Horizontal pipe entrance
			if (e->key() == Qt::Key_Right && mario->getPosX() >= 12 * 16 && (mario->isBig() ? mario->getPosY() == 200 + 300 + 300 - 2 * 16 : mario->getPosY() == 200 + 300 + 300 - 1 * 16))
			{
				mario->setPipeAnimation(RIGHT, 0);
				mario->setExitPipePosX(179.5 * 16);
				mario->setExitPipePosY(200 - 3 * 16);
			}
		}

		if (e->key() == Qt::Key_Down && cur_state == RUNNING)
		{
			if (mario->isBig())
				mario->setCrouch(true);

			// Vertical pipe entrance
			if (mario->getPosX() >= 19 * 16 && mario->getPosX() <= 20 * 16 && (mario->isBig() ? mario->getPosY() == 200 - 6 * 16 : mario->getPosY() == 200 - 5 * 16))
				mario->setPipeAnimation(DOWN, 1);

			// Vertical pipe entrance
			if (mario->getPosX() >= 56 * 16 && mario->getPosX() <= 57 * 16 && (mario->isBig() ? mario->getPosY() == 200 - 7 * 16 : mario->getPosY() == 200 - 6 * 16))
				mario->setPipeAnimation(DOWN, 3);

			// Vertical pipe entrance
			if (mario->getPosX() >= 153 * 16 && mario->getPosX() <= 154 * 16 && (mario->isBig() ? mario->getPosY() == 200 - 5 * 16 : mario->getPosY() == 200 - 4 * 16))
				mario->setPipeAnimation(DOWN, 2);
		}

		// SPACE for jump
		if (e->key() == Qt::Key_Space)
			mario->jump();

		// Z for run
		if (e->key() == Qt::Key_Z)
			mario->setRunning(true);

		// X to fire
        if (e->key() == Qt::Key_X && mario->isFire())
            new Fireball(mario->getPos());

		// Testing cheat M to instantly power up Mario
		if (e->key() == Qt::Key_M)
		{
			if (mario->isSmall())
				mario->mushroomEat();
			else if (mario->isBig() && !mario->isFire() && !mario->isInvincible())
				mario->flowerEat();
			else if (mario->isFire())
				mario->hurt();
		}
	}
}

void Game::keyReleaseEvent(QKeyEvent *e)
{
	// When tab is released the command popup disappears
	if (e->key() == Qt::Key_Tab)
	{
		scene->removeItem(commands_screen);
		if (cur_state == RUNNING)
			engine.start();
	}

	if(cur_state != RUNNING)
		return;

	if (e->key() == Qt::Key_Down)
		mario->setCrouch(false);

	if (!mario->isOnAnimation())
	{
		if (e->key() == Qt::Key_Right || e->key() == Qt::Key_Left)
			mario->setMoving(false);

		if (e->key() == Qt::Key_Z)
			mario->setRunning(false);
	}
}

void Game::wheelEvent(QWheelEvent *e)
{
    if(e->delta() > 0)
        scale(1.1, 1.1);
    else
        scale(1/1.1, 1/1.1);
}

void Game::advance()
{
	//printf("mario.x(): %f,\t", mario->x());
	//printf("mario.y(): %f,\n", mario->y());

	// Decrease timer every 10ms
	if (cur_state == RUNNING && !game_end)
		level_timer--;

	// stop engine
	if (engine_stop)
		engine.stop();
		
	// At 20 secs left play a warning sound and enable Frenzy Mode
	if (level_timer == 2000)
	{
		time_warning_sound->play();
		frenzy = true;
	}

	// Game over when timer expires
	if (level_timer == 0)
	{
		timeover = true;
        force_reset = true;
		gameover();
	}

	// When mario dies fetch the actual lives and go to game over status
	if (mario->isDead())
	{
		mario_lives = mario->getLives();
		gameover();
	}

	// Mario cant go on the left of the camera or offmap
	Direction dir = mario->getDirection();
    if (((mario->x() <= camera_max_x - 200 || (mario->x() <= 0 && dir == LEFT)) && dir == LEFT) ||
		(mario->x() > 231 && mario->y() >= 290 && mario->y() <= 310 && dir == RIGHT) ||
		(mario->x() > 1025 && mario->y() >= 820 && mario->y() <= 910 && dir == RIGHT))
		mario->setMoving(false);

	if(cur_state != RUNNING)
		return;

	if(mario->isDying() || mario->isTransforming())
	{	
		mario->animate();
		mario->advance();
		return;
	}

    for(auto & item : scene->items())
    {
		Object* obj = dynamic_cast<Object*>(item);
		if(obj)
		{
			obj->animate();
			obj->advance();

			Entity* entity_obj = dynamic_cast<Entity*>(obj);
			if(entity_obj && entity_obj->isDead())
			{
				scene->removeItem(entity_obj);
				delete entity_obj;
			}
		}
    }

	// Overworld - Sky transition
	if (mario->y() == 200 - 250 + 2 * 16)
	{
		active_sublevel = 0;
		scene->setSceneRect(0, 0, 10000, 225);
		scene->setBackgroundBrush(QBrush(QColor(99, 133, 251)));
	}

	// Update the value of the camera max x to block the camera to the left of the screen
	if (mario->x() >= camera_max_x)
		camera_max_x = mario->x();

	// Set the correct centerOn for every sublevel
	if (active_sublevel == 0)										// Overworld
		centerOn(camera_max_x, mario->y());
	else if (active_sublevel == 1)									// Underground 1
		centerOn(8 * 16, 200 + 300 - 5 * 16);
	else if (active_sublevel == 2)									// Underground 2
		centerOn(8 * 16, 200 + 300 + 300 - 5 * 16);
	else if (active_sublevel == 3)									// Underwater
		centerOn(camera_max_x, 200 + 300 + 300 + 300 - 5 * 16);
	else if (active_sublevel == 4)									// Sky
		centerOn(camera_max_x, 200 - 250);			
}

void Game::generateUnderWaterEnemies()
{
	int scale = 16;
	int terrain_level = 200 + 300 + 300 + 300;

	new CheepCheep(QPoint(27.5 * scale, terrain_level - 8 * scale), LEFT, GREY);
	new CheepCheep(QPoint(38.5 * scale, terrain_level - 2.5 * scale), LEFT, GREY);
	new CheepCheep(QPoint(48.5 * scale, terrain_level - 5 * scale), LEFT, RED);
	new CheepCheep(QPoint(53 * scale, terrain_level - 10 * scale), LEFT, GREY);

	new Blooper(QPoint(17 * scale, terrain_level - 3 * scale));
	new Blooper(QPoint(34 * scale, terrain_level - 3 * scale));
	new Blooper(QPoint(44 * scale, terrain_level - 3 * scale));
}
