#pragma once

#include "Entity.h"

class HUD_Life_Popup : public Entity
{
protected:

	QPixmap texture_1up = QPixmap(loadTexture(":/graphics/HUD/life-1up.png"));;
	QPoint spawned_position;

public:

	HUD_Life_Popup(QPoint position);

	virtual std::string name() { return "HUD Life Popup"; }
	virtual void animate();
	virtual void hit(Object *what, Direction fromDir) { }
};