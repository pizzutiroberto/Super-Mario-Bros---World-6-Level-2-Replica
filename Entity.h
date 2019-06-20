#pragma once

#include "Object.h"

class Entity : public Object
{
    protected:

        int moving_speed;
		int moving_speed_div;
		int jumping_speed;
		int jumping_duration;

		Direction dir;
        bool moving;
        bool jumping;
        bool falling;
		bool swimming;
		bool underwater;
		bool phantom;
		bool dying;
		bool dead;
		bool freezed;
		bool slow;
		bool onAnimation;
        bool invincible_bounce;

        int jump_counter;
		int death_counter;
		int walk_counter;
		int phantom_counter;
		int freeze_counter;

		int falling_speed;
		int death_duration;
		int phantom_duration;
		int freeze_duration;

        QPointF prevPos;
        Object *walkable_object;

        virtual void startJumping();		// Start a jump
        virtual void endJumping();			// End a jump
		virtual void startPhantom();		// Go in phantom mode
		virtual void endPhantom();			// End the phantom mode

    public:

        Entity();

		bool isDead(){ return dead; }												// Return dead status
		bool isDying(){ return dying; }												// Return dying status
		bool isPhantom(){ return phantom; }											// Return phantom status
		bool isFalling() { return falling; }										// Return falling status
		bool isFreezed() { return freezed; }										// Return freezed status
		bool isMoving() { return moving; }											// Return moving status
		bool isOnAnimation() { return onAnimation; }								// Return locked animation status
        Direction getDirection() { return dir; }									// Get the actual direction
        virtual void bounceOnInvincible();											// Enemy flip when dies
		virtual void setDirection(Direction _dir) { dir = _dir; }					// Set direction
		virtual void setMoving(bool _moving) { if(!dying) moving = _moving; }		// Set moving status

        virtual std::string name() = 0;
        virtual void animate() = 0;
        virtual void advance();
		virtual void freeze() { freezed = true; }									// Set freezed status
        virtual void solveCollisions();
        virtual void hit(Object *what, Direction fromDir) = 0;
		virtual void die();
};
