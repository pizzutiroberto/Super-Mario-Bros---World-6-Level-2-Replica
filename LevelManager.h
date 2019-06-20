#pragma once

#include <QGraphicsScene>
#include <string>

class LevelManager
{
    public:       

		static void load(std::string level_name, QGraphicsScene * scene);
};
