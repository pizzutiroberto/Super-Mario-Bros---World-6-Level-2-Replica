#include "Mario.h"
#include "Enemy.h"
#include "Game.h"
#include "Shell.h"
#include "Goomba.h"
#include "Paratroopa.h"
#include "Pipe.h"
#include "PiranhaPlant.h"
#include "Blooper.h"
#include "CheepCheep.h"
#include "HUD_Score_Popup.h"
#include "HUD_Life_Popup.h"
#include <QSound>

Mario::Mario(QPoint position) : Entity()
{
    marioStatus = BIG;
	moving  = false;
	running = false;
	bouncing = false;
	big = true;
    fire = false;
    invincible = false;
	crouch = false;
	transforming = false;
	sliding = false;
	climbing = false;
	on_pipe = false;
	v_pipe_animation_enter = false;
	v_pipe_animation_exit = false;
	h_pipe_animation = false;
	h_pipe_animation = false;
	transformation_counter = 0;
	transformation_duration = freeze_duration;
	invincible_counter = 0;
	invincible_duration = 800;
	pipe_animation_counter = 0;
	pipe_animation_duration = 100;
	climbing_counter = 0;
	climbing_duration = 300;
	jumping_duration = jump_duration_small;
	death_duration = 300;
	lives = Game::instance()->game_getMarioLives();

	// Standing texture
	texture_stand[0] = QPixmap(loadTexture(":/graphics/mario/small/stand.png"));
	texture_stand[1] = QPixmap(loadTexture(":/graphics/mario/big/stand.png"));
	texture_stand[2] = QPixmap(loadTexture(":/graphics/mario/fire/stand.png"));
	texture_stand[3] = QPixmap(loadTexture(":/graphics/mario/invincible-small/stand.png"));
	texture_stand[4] = QPixmap(loadTexture(":/graphics/mario/invincible-big/stand.png"));

	// Walking texture
	texture_walk[0][0] = QPixmap(loadTexture(":/graphics/mario/small/walk-0.png"));
	texture_walk[0][1] = QPixmap(loadTexture(":/graphics/mario/small/walk-1.png"));
	texture_walk[0][2] = QPixmap(loadTexture(":/graphics/mario/small/walk-2.png"));
	texture_walk[1][0] = QPixmap(loadTexture(":/graphics/mario/big/walk-0.png"));
	texture_walk[1][1] = QPixmap(loadTexture(":/graphics/mario/big/walk-1.png"));
	texture_walk[1][2] = QPixmap(loadTexture(":/graphics/mario/big/walk-2.png"));
	texture_walk[2][0] = QPixmap(loadTexture(":/graphics/mario/fire/walk-0.png"));
	texture_walk[2][1] = QPixmap(loadTexture(":/graphics/mario/fire/walk-1.png"));
	texture_walk[2][2] = QPixmap(loadTexture(":/graphics/mario/fire/walk-2.png"));
	texture_walk[3][0] = QPixmap(loadTexture(":/graphics/mario/invincible-small/walk-0.png"));
	texture_walk[3][1] = QPixmap(loadTexture(":/graphics/mario/invincible-small/walk-1.png"));
	texture_walk[3][2] = QPixmap(loadTexture(":/graphics/mario/invincible-small/walk-2.png"));
	texture_walk[4][0] = QPixmap(loadTexture(":/graphics/mario/invincible-big/walk-0.png"));
	texture_walk[4][1] = QPixmap(loadTexture(":/graphics/mario/invincible-big/walk-1.png"));
	texture_walk[4][2] = QPixmap(loadTexture(":/graphics/mario/invincible-big/walk-2.png"));

	// Jumping texture
	texture_jump[0] = QPixmap(loadTexture(":/graphics/mario/small/jump.png"));
	texture_jump[1] = QPixmap(loadTexture(":/graphics/mario/big/jump.png"));
	texture_jump[2] = QPixmap(loadTexture(":/graphics/mario/fire/jump.png"));
	texture_jump[3] = QPixmap(loadTexture(":/graphics/mario/invincible-small/jump.png"));
	texture_jump[4] = QPixmap(loadTexture(":/graphics/mario/invincible-big/jump.png"));

	// Hang-Climb texture
	texture_hang[0][0] = QPixmap(loadTexture(":/graphics/mario/small/climb-0.png"));
	texture_hang[0][1] = QPixmap(loadTexture(":/graphics/mario/small/climb-1.png"));
	texture_hang[1][0] = QPixmap(loadTexture(":/graphics/mario/big/climb-0.png"));
	texture_hang[1][1] = QPixmap(loadTexture(":/graphics/mario/big/climb-1.png"));
	texture_hang[2][0] = QPixmap(loadTexture(":/graphics/mario/fire/climb-0.png"));
	texture_hang[2][1] = QPixmap(loadTexture(":/graphics/mario/fire/climb-1.png"));
	texture_hang[3][0] = QPixmap(loadTexture(":/graphics/mario/invincible-small/climb-0.png"));
	texture_hang[3][1] = QPixmap(loadTexture(":/graphics/mario/invincible-small/climb-1.png"));
	texture_hang[4][0] = QPixmap(loadTexture(":/graphics/mario/invincible-big/climb-0.png"));
	texture_hang[4][1] = QPixmap(loadTexture(":/graphics/mario/invincible-big/climb-1.png"));

	// Swimming texture
	texture_swim[0][0] = QPixmap(loadTexture(":/graphics/mario/small/swim-0.png"));
	texture_swim[0][1] = QPixmap(loadTexture(":/graphics/mario/small/swim-1.png"));
	texture_swim[0][2] = QPixmap(loadTexture(":/graphics/mario/small/swim-2.png"));
	texture_swim[0][3] = QPixmap(loadTexture(":/graphics/mario/small/swim-3.png"));
	texture_swim[0][4] = QPixmap(loadTexture(":/graphics/mario/small/swim-4.png"));
	texture_swim[1][0] = QPixmap(loadTexture(":/graphics/mario/big/swim-0.png"));
	texture_swim[1][1] = QPixmap(loadTexture(":/graphics/mario/big/swim-1.png"));
	texture_swim[1][2] = QPixmap(loadTexture(":/graphics/mario/big/swim-2.png"));
	texture_swim[1][3] = QPixmap(loadTexture(":/graphics/mario/big/swim-3.png"));
	texture_swim[1][4] = QPixmap(loadTexture(":/graphics/mario/big/swim-4.png"));
	texture_swim[2][0] = QPixmap(loadTexture(":/graphics/mario/fire/swim-0.png"));
	texture_swim[2][1] = QPixmap(loadTexture(":/graphics/mario/fire/swim-1.png"));
	texture_swim[2][2] = QPixmap(loadTexture(":/graphics/mario/fire/swim-2.png"));
	texture_swim[2][3] = QPixmap(loadTexture(":/graphics/mario/fire/swim-3.png"));
	texture_swim[2][4] = QPixmap(loadTexture(":/graphics/mario/fire/swim-4.png"));
	texture_swim[3][0] = QPixmap(loadTexture(":/graphics/mario/invincible-small/swim-0.png"));
	texture_swim[3][1] = QPixmap(loadTexture(":/graphics/mario/invincible-small/swim-1.png"));
	texture_swim[3][2] = QPixmap(loadTexture(":/graphics/mario/invincible-small/swim-2.png"));
	texture_swim[3][3] = QPixmap(loadTexture(":/graphics/mario/invincible-small/swim-3.png"));
	texture_swim[3][4] = QPixmap(loadTexture(":/graphics/mario/invincible-small/swim-4.png"));
	texture_swim[4][0] = QPixmap(loadTexture(":/graphics/mario/invincible-big/swim-0.png"));
	texture_swim[4][1] = QPixmap(loadTexture(":/graphics/mario/invincible-big/swim-1.png"));
	texture_swim[4][2] = QPixmap(loadTexture(":/graphics/mario/invincible-big/swim-2.png"));
	texture_swim[4][3] = QPixmap(loadTexture(":/graphics/mario/invincible-big/swim-3.png"));
	texture_swim[4][4] = QPixmap(loadTexture(":/graphics/mario/invincible-big/swim-4.png"));

	// Crouch texture
	texture_crouch[0] = QPixmap(loadTexture(":/graphics/mario/big/crouch.png"));
	texture_crouch[1] = QPixmap(loadTexture(":/graphics/mario/fire/crouch.png"));
	texture_crouch[2] = QPixmap(loadTexture(":/graphics/mario/invincible-big/crouch.png"));

	// dead texture
	texture_dead	   = QPixmap(loadTexture(":/graphics/mario/small/dead.png"));

	// Transformation sequence textures
	texture_small_to_big[0] = texture_stand[0];
	texture_small_to_big[1] = QPixmap(loadTexture(":/graphics/mario/big/med-stand.png"));
	texture_small_to_big[2] = texture_stand[1];
	texture_small_to_big[3] = QPixmap(loadTexture(":/graphics/mario/big/med-stand.png"));

    setPixmap(texture_stand[marioStatus]);
	setPos(position-QPoint(0, pixmap().height()));

	setZValue(3);
}

void Mario::die()
{
	lives--;

	setZValue(15);

	Entity::die();

	collidable = false;

	Game::instance()->get_death_sound()->play();
	Game::instance()->stopMusic();

	freeze();

	jumping_speed = 1;
	falling_speed = 1;
	startJumping();
}

void Mario::jump()
{
	if(jumping & !swimming)
		return;

    startJumping();

	if (jumping & !swimming)
		(marioStatus == BIG ? Game::instance()->get_jump_sound()->play() : Game::instance()->get_jump_small_sound()->play());
}

void Mario::mushroomEat(bool red)
{
	new HUD_Score_Popup(QPoint(x(), y()), SCORE1000);
	Game::instance()->addScore(1000);
	if(red)
	{
		if (marioStatus == SMALL)
		{
			marioStatus = BIG;
			big = true;
			jumping_duration = jump_duration_big;
			startTransformation();
		}
		Game::instance()->get_mushroom_eat_sound()->play();
	}
	else
		Game::instance()->get_oneup_sound()->play();
}

void Mario::flowerEat()
{
	new HUD_Score_Popup(QPoint(x(), y()), SCORE1000);
	Game::instance()->addScore(1000);
	Game::instance()->get_mushroom_eat_sound()->play();

	if (!invincible)
	{
		marioStatus = FIRE;
		fire = true;
		big = true;
		startTransformation();
	}
}

void Mario::starEat()
{
	if (marioStatus == SMALL)
		marioStatus = INVINCIBLE_SMALL;
	else
		marioStatus = INVINCIBLE_BIG;
	invincible = true;
	new HUD_Score_Popup(QPoint(x(), y()), SCORE5000);
	Game::instance()->addScore(5000);
	Game::instance()->get_overworld_loop_sound()->stop();
	Game::instance()->get_star_sound()->play();
}

void Mario::hurt()
{
	if(marioStatus == BIG || marioStatus == FIRE)
	{
		jumping_duration = jump_duration_small;

		Game::instance()->get_shrink_sound()->play();

		startPhantom();
		startTransformation();
	}
	else
		die();

	fire = false;
	marioStatus = SMALL;
	big = false;
}

void Mario::increaseLives()
{
	lives++;
	new HUD_Life_Popup(QPoint(x(), y()));
	Game::instance()->get_oneup_sound()->play();
}

void Mario::startTransformation()
{
	transforming = true;
	transformation_counter = big ? 0 : 2 * transf_div;
    freeze();
}

void Mario::endTransformation()
{
	transforming = false;
	transformation_counter = 0;
	if (marioStatus == BIG)
	{
		int dy = pixmap().height() - (marioStatus == BIG ? texture_stand[1] : texture_stand[0]).height();
		setY(y() + dy);
	}
	setY(y() - 16);
}

void Mario::endVerticalEnterPipeAnimation()
{
	v_pipe_animation_enter = false;
	onAnimation = false;
	freezed = false;
	pipe_animation_counter = 0;
	setZValue(3);
	Game::instance()->setActiveSublevel(_next_active_sublevel);
	Game::instance()->setCameraMaxXTemp(pos().x());
	Game::instance()->get_overworld_loop_sound()->stop();
	if (Game::instance()->get_star_sound())
		Game::instance()->get_star_sound()->stop();

	// Enter into the correct sublevel
	if (_next_active_sublevel == 1)
	{
		Game::instance()->get_underground_sound()->play();
		Game::instance()->getScene()->setSceneRect(0, 250, 16 * 16, 225 + 300);
		Game::instance()->getScene()->setBackgroundBrush(QBrush(QColor(0, 0, 0)));
		setPos(QPoint(2.5 * 16, 200 + 300 - 11 * 16));
	}
	else if (_next_active_sublevel == 2)
	{
		Game::instance()->get_underground_sound()->play();
		Game::instance()->getScene()->setSceneRect(0, 0, 16 * 16, 225 + 300 + 300);
		Game::instance()->getScene()->setBackgroundBrush(QBrush(QColor(0, 0, 0)));
		setPos(QPoint(1.5 * 16, 200 + 300 + 300 - 11 * 16));
	}
	else if (_next_active_sublevel == 3)
	{
		Game::instance()->get_underwater_sound()->play();
		Game::instance()->getScene()->setSceneRect(0, 0, 10000, 225 + 300 + 300 + 300);
		Game::instance()->generateUnderWaterEnemies();
		Game::instance()->getScene()->setBackgroundBrush(QBrush(QColor(32, 56, 236)));
		setPos(QPoint(2.5 * 16, 200 + 300 + 300 + 300 - 11 * 16));
		underwater = true;
	}
	Game::instance()->setCameraMaxX(0);
	collidable = true;
}

void Mario::startHorizontalPipeAnimation()
{
	prevPos = pos();
	setX(x() + 1);
	pipe_animation_counter++;

	// Mario exit the sublevel and return to the overworld
	if (pipe_animation_counter >= pipe_animation_duration/2)
	{
		h_pipe_animation = false;
		v_pipe_animation_exit = true;
		pipe_animation_counter = 0;
		falling_speed = 2;
		setPos(QPoint(exit_pipe_posx, 200));
		Game::instance()->setCameraMaxX(Game::instance()->getCameraMaxXTemp());
		Game::instance()->setActiveSublevel(_next_active_sublevel);
		Game::instance()->getScene()->setSceneRect(0, 0, 10000, 225);
		Game::instance()->getScene()->setBackgroundBrush(QBrush(QColor(99, 133, 251)));
		Game::instance()->get_underground_sound()->stop();
		Game::instance()->get_underwater_sound()->stop();
		Game::instance()->get_overworld_loop_sound()->play();
	}
}

void Mario::startVerticalExitPipeAnimation()
{
	prevPos = pos();
	setY(y() - 0.5);
	if (big ? pos().y() == exit_pipe_posy - 16 : pos().y() == exit_pipe_posy)
	{
		big ? setPos(QPoint(exit_pipe_posx, exit_pipe_posy - 16)) : setPos(QPoint(exit_pipe_posx, exit_pipe_posy));
		v_pipe_animation_exit = false;
		onAnimation = false;
		freezed = false;
		falling = true;
		setZValue(3);
		collidable = true;
		swimming = false;
	}
}

void Mario::animate()
{
	// Mario reach the end level castle
	if (x() >= Game::instance()->getEndLevel())
	{
		setVisible(false);
		freezed = true;
		moving = false;
		Game::instance()->setGameEnd(true);
	}
	// Sliding animation (end pole)
	else if (sliding)
	{
		freezed = true;
		prevPos = pos();
		setY(y() + 1);
		solveCollisions();
	}
	// Climbing animation (vine)
	else if (climbing)
	{
		freezed = true;
		prevPos = pos();
		dir == RIGHT ? setX(climb_x_correction - 6) : setX(climb_x_correction + 6);
		setY(y() - 0.5);
		climbing_counter++;

		// Mario enter into the sky sublevel
		if (climbing_counter >= climbing_duration / 2)
		{
			Game::instance()->setActiveSublevel(4);
			Game::instance()->getScene()->setSceneRect(0, 0, 10000, -250);
			Game::instance()->getScene()->setBackgroundBrush(QBrush(QColor(99, 133, 251)));
		}

		if (climbing_counter >= climbing_duration)
			endVineClimb();
		solveCollisions();
	}
	// Vertical pipe enter animation
	else if (v_pipe_animation_enter)
	{
		setZValue(1);
		freezed = true;
		onAnimation = true;
		prevPos = pos();
		setY(y() + 0.5);
		pipe_animation_counter++;
		if (pipe_animation_counter >= pipe_animation_duration)
			endVerticalEnterPipeAnimation();
	}
	// Horizontal pipe enter animation
	else if (h_pipe_animation)
	{
		setZValue(1);
		freezed = true;
		onAnimation = true;
		startHorizontalPipeAnimation();
	}
	// Vertical pipe exit animation
	else if (v_pipe_animation_exit)
	{
		setZValue(1);
		freezed = true;
		onAnimation = true;
		falling = false;
		moving = false;
		startVerticalExitPipeAnimation();
	}
	// Underwater animations
	else if (underwater)
	{
        if (y() == 200 + 300 + 300 + 300 - 12 * 16)
		{
			swimming = false;
            falling = false;
			falling_speed = 2;
            startJumping();
		}
		else
		{
            falling = true;
			swimming = true;
			falling_speed = 1;
		}
	}
	// Jumping animation
    else if(!jumping && bouncing)
	{
        bouncing = false;
        jumping_duration = marioStatus != SMALL ? jump_duration_big : jump_duration_small;
	}

	// Phantom animation
	if(phantom)
	{
		phantom_counter++;
		if(phantom_counter > phantom_duration)
			endPhantom();
	}

	// Tranforming animation
	if(transforming)
	{
		transformation_counter++;
		if(transformation_counter > transformation_duration)
			endTransformation();

		if (marioStatus == BIG)
		{
			int prev = ((transformation_counter - 1) / transf_div) % 4;
			int curr = (transformation_counter / transf_div) % 4;
			int dy = texture_small_to_big[prev].height() - texture_small_to_big[curr].height();
			setPixmap(texture_small_to_big[(transformation_counter / transf_div) % 4]);
			setY(y() + dy);
		}
		if (marioStatus == FIRE)
			walk_counter++ / (running ? running_div : walk_div) % 2 == 0 ? setOpacity(0.7) : setOpacity(1);
	}

    // Set swimming flag
    if (y() < 200 + 300 + 300 + 300 - 12 * 16)
        underwater = false;
    else
        underwater = true;

	// Setting the proper jump value
	jumping_duration = (marioStatus == SMALL)|| (marioStatus == INVINCIBLE_SMALL) ? jump_duration_small : jump_duration_big;

	//---------- Texture Setting -----------//
	if(dying || dead)
		setPixmap(texture_dead);
	else if (sliding)
		setPixmap(texture_hang[marioStatus][1]);
	else if (climbing)
		setPixmap(texture_hang[marioStatus][(walk_counter++ / (running ? running_div : walk_div)) % 2]);
	else if(moving && !jumping && !falling)
		setPixmap(texture_walk[marioStatus][(walk_counter++/ (running ? running_div : walk_div)) % 3]);
	else if (underwater && !swimming && moving)
		setPixmap(texture_walk[marioStatus][(walk_counter++ / (running ? running_div : walk_div)) % 3]);
	else if (underwater && swimming)
		setPixmap(texture_swim[marioStatus][(walk_counter++ / (running ? running_div : walk_div)) % 5]);
	else if(jumping || falling)
		setPixmap(texture_jump[marioStatus]);
	else if (crouch)
	{
		if (marioStatus == BIG)
			setPixmap(texture_crouch[0]);
		else if (marioStatus == FIRE)
			setPixmap(texture_crouch[1]);
		else if (marioStatus == INVINCIBLE_BIG)
			setPixmap(texture_crouch[2]);
	}
	else
	{
		setPixmap(texture_stand[marioStatus]);
		setOpacity(1.0);
	}

	// Invincible mario animation (star)
	if (invincible)
	{
		walk_counter++ / (running ? running_div : walk_div) % 2 == 0 ? setOpacity(0.7) : setOpacity(1);
		invincible_counter++;
		if (invincible_counter >= invincible_duration)
		{
			marioStatus = marioStatus == INVINCIBLE_BIG ? BIG : SMALL;
			invincible = false;
			invincible_counter = 0;
			setOpacity(1);
			Game::instance()->get_star_sound()->stop();
			int sublvl = Game::instance()->getActiveSublevel();
			if(sublvl == 0)
				Game::instance()->get_overworld_loop_sound()->play();
			else if (sublvl == 1 || sublvl == 2)
				Game::instance()->get_underground_sound()->play();
			else if (sublvl == 3)
				Game::instance()->get_underwater_sound()->play();
		}
	}
	//---------End Texture Setting ---------//

	// Texture mirroring
	if(dir == LEFT)
		setPixmap(pixmap().transformed(QTransform().scale(-1,1)));
}

void Mario::bounce()
{
	falling = false;
	bouncing = true;
    jumping_duration = jump_duration_tiny;
	startJumping();
}

void Mario::setRunning(bool _running)
{
	if (!jumping)
	{
		if (running == _running)
			return;

		running = _running;

		if (running)
			moving_speed *= 2;
		else
			moving_speed /= 2;
	}
}

void Mario::setPipeAnimation(Direction dir, int next_active_sublevel)
{
	collidable = false;
	_next_active_sublevel = next_active_sublevel;
	if (dir == DOWN)
		v_pipe_animation_enter = true;
	if (dir == UP)
		v_pipe_animation_exit = true;
	if (dir == RIGHT)
		h_pipe_animation = true;
}

void Mario::startSlide()
{
	jumping = false;
	jump_counter = 0;
	falling = false;
	sliding = true;
	onAnimation = true;
	prevPos = pos();
	setX(x() + 6);
}

void Mario::endSlide()
{
	sliding = false;
	freezed = false;
	onAnimation = true;
	setX(x() + 18);
	setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
	setMoving(true);
	falling = true;
	dir = RIGHT;
}

void Mario::startVineClimb(int xpos)
{
	jumping = false;
	falling = false;
	climbing = true;
	collidable = false;
	onAnimation = true;
	climb_x_correction = xpos;
}

void Mario::endVineClimb()
{
	dir = RIGHT;
	setX(climb_x_correction + 16);
	climbing = false;
	falling = true;
	collidable = true;
	onAnimation = false;
	jumping = true;
	moving = false;
}

void Mario::hit(Object *what, Direction fromDir)
{
	Enemy *enemy = dynamic_cast<Enemy*>(what);
	if (enemy)
	{
		Goomba *goomba = dynamic_cast<Goomba*>(enemy);
		Shell *shell = dynamic_cast<Shell*>(enemy);
		Paratroopa *paratroopa = dynamic_cast<Paratroopa*>(enemy);
		PiranhaPlant *piranhaplant = dynamic_cast<PiranhaPlant*>(enemy);
		Blooper *blooper = dynamic_cast<Blooper*>(enemy);
		CheepCheep *cheepcheep = dynamic_cast<CheepCheep*>(enemy);

		// Mario is invincible and kill everything
		if (invincible)
		{
			new HUD_Score_Popup(QPoint(enemy->x(), enemy->y()), SCORE400);
			Game::instance()->addScore(400);
			enemy->bounceOnInvincible();
			enemy->Entity::die();
		}
		// Mario kicks a shell
		else if (shell && !shell->isMoving())
		{
			new HUD_Score_Popup(QPoint(shell->x(), shell->y()), SCORE400);
			Game::instance()->addScore(400);
			shell->setMoving(true);
			Game::instance()->get_kick_sound()->play();
			if (fromDir == LEFT || fromDir == RIGHT)
				enemy->setDirection(fromDir == LEFT ? LEFT : RIGHT);
			else if (fromDir == DOWN)
				enemy->setDirection(RIGHT);
		}
		// Mario stops a moving shell jumping on it
		else if (shell && shell->isMoving() && fromDir == DOWN)
		{
			new HUD_Score_Popup(QPoint(shell->x(), shell->y()), SCORE200);
			Game::instance()->addScore(200);
			shell->setMoving(false);
			bounce();
			Game::instance()->get_stomp_sound()->play();
		}
		// Mario downgrade a paratroopa with a jump on it
		else if (fromDir == DOWN && paratroopa)
		{
			Game::instance()->get_stomp_sound()->play();
			bounce();
			enemy->hurt();
		}
		// Mario get damage from piranha plant, blooper and cheep cheep
		else if (piranhaplant || blooper || cheepcheep)
			hurt();
		// Mario hurt enemies
		else if (fromDir == DOWN && enemy->isHurtable())
		{
			if (paratroopa)
			{
				new HUD_Score_Popup(QPoint(enemy->x(), enemy->y()), SCORE400);
				Game::instance()->addScore(400);
			}
			else if (goomba)
			{
				new HUD_Score_Popup(QPoint(enemy->x(), enemy->y()), SCORE100);
				Game::instance()->addScore(100);
			}
			else
			{
				new HUD_Score_Popup(QPoint(enemy->x(), enemy->y()), SCORE200);
				Game::instance()->addScore(200);
			}

			Game::instance()->get_stomp_sound()->play();
			bounce();
			enemy->hurt();
		}
		else
			hurt();
	}

	// on_pipe is used to block the piranha plant animation when mario is on the relative pipe
	Pipe *pipe = dynamic_cast<Pipe*>(what);
	if (pipe && fromDir == DOWN)
		on_pipe = true;
	else
		on_pipe = false;
}
