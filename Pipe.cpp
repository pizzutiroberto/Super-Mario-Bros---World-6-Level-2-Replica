#include "Pipe.h"

Pipe::Pipe(QPoint position, int size) : Inert()
{
	// Select the correct texture
	if (size == 0)
		setPixmap(QPixmap(loadTexture(":/graphics/scenary/pipe-blank.png")));
	else if(size == 2)
		setPixmap(QPixmap(loadTexture(":/graphics/scenary/pipe-2.png")));
	else if(size == 3)
		setPixmap(QPixmap(loadTexture(":/graphics/scenary/pipe-3.png")));
	else if (size == 4)
		setPixmap(QPixmap(loadTexture(":/graphics/scenary/pipe-4.png")));
	else if (size == 5)
		setPixmap(QPixmap(loadTexture(":/graphics/scenary/pipe-5.png")));
	else if (size == 6)
		setPixmap(QPixmap(loadTexture(":/graphics/scenary/pipe-6.png")));
	else if (size == 13)
		setPixmap(QPixmap(loadTexture(":/graphics/scenary/pipe-h3.png")));
	else if (size == 14)
		setPixmap(QPixmap(loadTexture(":/graphics/scenary/pipe-h4.png")));

	setPos(position-QPoint(0, pixmap().height()));
	setZValue(3);
}