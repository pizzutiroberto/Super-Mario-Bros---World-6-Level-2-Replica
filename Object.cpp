#include "Object.h"
#include "Game.h"

Object::Object() : QGraphicsPixmapItem(0)
{
	collidable = true;
	walkable   = false;

	setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

	Game::instance()->getScene()->addItem(this);
}

Direction Object::touchingDirection(Object* item)
{
    QRectF curr_rect = sceneBoundingRect();
    QRectF item_rect = item->sceneBoundingRect();

    int xi0 = std::max(curr_rect.x(), item_rect.x());
    int yi0 = std::max(curr_rect.y(), item_rect.y());
    int xi1 = std::min(curr_rect.x() + curr_rect.width(), item_rect.x() + item_rect.width());
    int yi1 = std::min(curr_rect.y() + curr_rect.height(), item_rect.y() + item_rect.height());

    if(xi0 == xi1 && yi1 > yi0)
    {
        if(xi0 == curr_rect.x())
            return LEFT;
        else
            return RIGHT;
    }
    else if(yi0 == yi1 && xi1 > xi0)
    {
        if(yi0 == curr_rect.y())
            return UP;
        else
            return DOWN;
    }

    return UNKNOWN;
}

Direction Object::collisionDirection(Object* item)
{
    QRectF curr_rect =  sceneBoundingRect();
    QRectF item_rect =  item->sceneBoundingRect();

    if(!curr_rect.intersects(item_rect))
        return UNKNOWN;

    QRectF interRect = curr_rect.intersected(item_rect);

    if(interRect.width() < interRect.height())
    {
        if(interRect.left() == curr_rect.x())
            return LEFT;
        else
            return RIGHT;
    }
    else
    {
        if(interRect.top() == curr_rect.y())
            return UP;
        else
            return DOWN;
    }
}