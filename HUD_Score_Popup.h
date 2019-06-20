#pragma once

#include "Entity.h"

enum scoreValue {
	SCORE50, 
	SCORE100, 
	SCORE200, 
	SCORE400, 
	SCORE500, 
	SCORE1000,
	SCORE1500,
	SCORE2000,
	SCORE2500,
	SCORE3000,
	SCORE3500,
	SCORE4000,
	SCORE4500,
	SCORE5000
};

class HUD_Score_Popup : public Entity
{
	protected:

		QPixmap texture_score_50   = QPixmap(loadTexture(":/graphics/HUD/score-50.png"));
		QPixmap texture_score_100  = QPixmap(loadTexture(":/graphics/HUD/score-100.png"));
		QPixmap texture_score_200  = QPixmap(loadTexture(":/graphics/HUD/score-200.png"));
		QPixmap texture_score_400  = QPixmap(loadTexture(":/graphics/HUD/score-400.png"));
		QPixmap texture_score_500  = QPixmap(loadTexture(":/graphics/HUD/score-500.png"));
		QPixmap texture_score_1000 = QPixmap(loadTexture(":/graphics/HUD/score-1000.png"));
		QPixmap texture_score_1500 = QPixmap(loadTexture(":/graphics/HUD/score-1500.png"));
		QPixmap texture_score_2000 = QPixmap(loadTexture(":/graphics/HUD/score-2000.png"));
		QPixmap texture_score_2500 = QPixmap(loadTexture(":/graphics/HUD/score-2500.png"));
		QPixmap texture_score_3000 = QPixmap(loadTexture(":/graphics/HUD/score-3000.png"));
		QPixmap texture_score_3500 = QPixmap(loadTexture(":/graphics/HUD/score-3500.png"));
		QPixmap texture_score_4000 = QPixmap(loadTexture(":/graphics/HUD/score-4000.png"));
		QPixmap texture_score_4500 = QPixmap(loadTexture(":/graphics/HUD/score-4500.png"));
		QPixmap texture_score_5000 = QPixmap(loadTexture(":/graphics/HUD/score-5000.png"));

		QPixmap texture_score;
		QPoint spawned_position;

		scoreValue value;

    public:

		HUD_Score_Popup(QPoint position, scoreValue _value);

        virtual std::string name() { return "HUD Score Popup"; }
		virtual void animate();
        virtual void hit(Object *what, Direction fromDir) { }
};