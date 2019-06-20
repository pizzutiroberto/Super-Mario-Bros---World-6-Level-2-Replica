#pragma once

#include <QPoint>
#include <QPixmap>
#include <QBitmap>
#include <QColor>
#include <string>

enum Direction {UNKNOWN, RIGHT, LEFT, UP, DOWN};

static Direction inverse(Direction dir)
{
    if(dir == RIGHT)
        return LEFT;
    else if(dir == LEFT)
        return RIGHT;
    else if(dir == UP)
        return DOWN;
    else if(dir == DOWN)
        return UP;
    else
        return UNKNOWN;
}

static bool strends (std::string const &str, std::string const &end)
{
	if (str.length() >= end.length()) 
		return (0 == str.compare (str.length() - end.length(), end.length(), end));
	else
		return false;
}

static QPixmap loadTextureTransparent(const std::string & file, QColor mask_color = Qt::magenta)
{
	QPixmap pixmap(file.c_str());
	pixmap.setMask(pixmap.createMaskFromColor(mask_color));
	return pixmap;
}

static QPixmap loadTexture(const std::string file, QColor mask_color = Qt::magenta)
{
	if(strends(file, ".bmp"))
		return loadTextureTransparent(file, mask_color);
	else
		return QPixmap(file.c_str());
}
