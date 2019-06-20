#include "Terrain.h"
#include <QBrush>
#include <QPainter>

Terrain::Terrain(QRect rect, int terrain_type) : Inert()
{
    setPos(QPoint(rect.x(), rect.y()));

	// Select the correct terrain texture
	std::string wall_texture;
	if (terrain_type == 0)
		wall_texture = ":/graphics/scenary/wall.png";
	else if (terrain_type == 1)
		wall_texture = ":/graphics/scenary/wall-underground.png";
	else if (terrain_type == 2)
		wall_texture = ":/graphics/scenary/wall-water.png";
	else if (terrain_type == 3)
		wall_texture = ":/graphics/scenary/wall-cloud.png";

	QPixmap collage(loadTexture(wall_texture));
	collage = collage.scaled(rect.width(), rect.height());
	QPainter painter(&collage);
	QPixmap single_block(loadTexture(wall_texture));
	for (int y = 0; y < rect.height(); y += single_block.height())
		for (int x = 0; x < rect.width(); x += single_block.width())
			painter.drawPixmap(x, y, single_block);
	setPixmap(collage);

	setZValue(2);
}