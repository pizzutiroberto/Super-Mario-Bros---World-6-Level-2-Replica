#pragma once

#include "Entity.h"

class Mario : public Entity
{
    enum marioStatus {SMALL, BIG, FIRE, INVINCIBLE_SMALL, INVINCIBLE_BIG};

	protected:

		// Jump durations
		static const int jump_duration_tiny = 20;
		static const int jump_duration_small = 70;
		static const int jump_duration_big = 90;

		// Movement divisors
		static const int walk_div = 6;
		static const int running_div = 4;
		static const int transf_div = 5;

		// Mario textures
		QPixmap texture_stand[5];
		QPixmap texture_walk[5][3];
		QPixmap texture_jump[5];
		QPixmap texture_hang[5][2];
		QPixmap texture_swim[5][5];
		QPixmap texture_crouch[3];
		QPixmap texture_dead;
		QPixmap texture_small_to_big[4];

        marioStatus marioStatus;			// Current Mario status

		bool big;							// Mario is big?
		bool fire;							// Mario is on fire?
        bool invincible;					// Mario is invincible?
		bool bouncing;						// Mario is bouncing?
		bool crouch;						// Mario is crouched?
		bool running;						// Mario is running?
		bool transforming;					// Mario is transforming? (small to big | big to small)
		bool sliding;						// Mario is sliding?
		bool climbing;						// Mario is climbing?
		bool v_pipe_animation_enter;		// Mario is entering vertically into a pipe?
		bool v_pipe_animation_exit;			// Mario is exiting vertically from a pipe?
		bool h_pipe_animation;				// Mario is entering horizontally into a pipe?
		bool on_pipe;						// Mario is on a Pipe (block the piranha plant movement undder him)

		// Transformation animation variables
		int transformation_counter;
		int transformation_duration;

		// Invincible animation variables
		int invincible_counter;
		int invincible_duration;
		 
		// Pipe animation variables
		int pipe_animation_counter;
		int pipe_animation_duration;

		// Climbing animation variables
		int climbing_counter;
		int climbing_duration;

		int _next_active_sublevel;			// Value of the next active sublevel. Used when mario have to change sublevel
		int climb_x_correction;				// X correction during the climbing
		int lives;							// Mario lives?

		// X and Y Exit pipe position
		qreal exit_pipe_posx;
		qreal exit_pipe_posy;

		void startTransformation();					// Start mario transformation
		void endTransformation();					// End mario transformation
		void endVerticalEnterPipeAnimation();		// End vertical pipe enter animation
		void startVerticalExitPipeAnimation();		// Start vertival pipe exit animation
		void startHorizontalPipeAnimation();		// Start horizontal pipe animation
		void endVineClimb();						// End vine climbing

	public:

		Mario(QPoint position);

		bool isSmall() { return marioStatus == SMALL ? true : false; }			// is mario small?
		bool isBig() { return big; }											// is mario big?
		bool isFire() { return fire; }											// is mario on fire?
		bool isInvincible() { return invincible; }								// is mario invincible?
		bool isTransforming(){ return transforming; }							// is mario on transormation?
        bool isBouncing() { return bouncing; }									// is mario bouncing?
		int getPosX() { return pos().x(); }										// get mario x coord
		int getPosY() { return pos().y(); }										// get mario t coord
		bool isOnPipe() { return on_pipe; }										// is mario on a pipe?
        QPointF getPos() { return pos(); }										// get mario coords
		void setRunning(bool _running);											// toggle running
		void setCrouch(bool value) { crouch = value; }							// toggle crouch status
		void setPipeAnimation(Direction dir, int next_active_sublevel);			// set pipe animation: direction and target sublevel
		void setExitPipePosX(qreal value) { exit_pipe_posx = value; }			// set x coord for pipe exit
		void setExitPipePosY(qreal value) { exit_pipe_posy = value; }			// set y coord for pipe exit
		int getLives() { return lives; }										// get mario lives
		void increaseLives();													// add a life
		void decreaseLives() { lives--; }										// remove a life
		void setLives(int value) { lives = value; }								// set mario lives

        virtual std::string name(){ return "Mario";}
        virtual void animate();
        virtual void hit(Object *what, Direction fromDir);
		virtual void die();

		void mushroomEat(bool red = true);			// mario eat a mushroom
        void starEat();								// mario eat a star
		void flowerEat();							// mario eat a flower
		void hurt();								// mario get hurt
        void jump();								// mario jump
		void bounce();								// mario bounce
		void startSlide();							// mario start sliding
		void endSlide();							// mario end sliding
		void startVineClimb(int xpos);				// mario start climb the vine
};
