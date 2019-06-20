#include "Background.h"
#include <QBitmap>

Background::Background(QPoint position, std::string _texture_path)
{
	collidable = false;

	texture_path = _texture_path;
	setPixmap(loadTexture(texture_path));

	setPos(position-QPoint(0, pixmap().height()));
}