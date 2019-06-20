#include "LevelManager.h"
#include "Background.h"
#include "Block.h"
#include "Box.h"
#include "Brick.h"
#include "Goomba.h"
#include "Pipe.h"
#include "Terrain.h"
#include "Pole.h"
#include "Coin.h"
#include "Troopa.h"
#include "Beetle.h"
#include "Paratroopa.h"
#include "PiranhaPlant.h"
#include "Game.h"
#include "Platform.h"
#include "CheepCheep.h"
#include "Blooper.h"
#include "HUD.h"
#include <iostream>
#include <QSoundEffect>

void LevelManager::load(std::string level_name, QGraphicsScene * scene)
{
	int scale = 16;
	int terrain_level = 200;

	new HUD();

	if (level_name == "World-6-2")
	{
        /*---------------------- 6-2 OVERWORLD ---------------------------*/

		scene->setBackgroundBrush(QBrush(QColor(99, 133, 251)));

		new Terrain(QRect(	0		 , terrain_level, 123 * scale, 2 * scale), 0);
		new Terrain(QRect(129 * scale, terrain_level,  12 * scale, 2 * scale), 0);
		new Terrain(QRect(142 * scale, terrain_level,       scale, 2 * scale), 0);
		new Terrain(QRect(144 * scale, terrain_level,   8 * scale, 2 * scale), 0);
		new Terrain(QRect(153 * scale, terrain_level,  86 * scale, 2 * scale), 0);

		new Background(QPoint( 	  0		   , terrain_level),			  ":/graphics/scenary/castle.png");
		new Background(QPoint( 11.5 * scale, terrain_level),			  ":/graphics/scenary/bush-big.png");
		new Background(QPoint(   16 * scale, terrain_level),			  ":/graphics/scenary/hill-small.png");
		new Background(QPoint( 23.5 * scale, terrain_level),			  ":/graphics/scenary/bush-small.png");
		new Background(QPoint( 41.5 * scale, terrain_level),			  ":/graphics/scenary/bush-med.png");
		new Background(QPoint( 	  9 * scale, terrain_level -  9 * scale), ":/graphics/scenary/cloud-small.png");
		new Background(QPoint(   20 * scale, terrain_level - 10 * scale), ":/graphics/scenary/cloud-small.png");
		new Background(QPoint(   27 * scale, terrain_level -  9 * scale), ":/graphics/scenary/cloud-big.png");
		new Background(QPoint(   37 * scale, terrain_level - 10 * scale), ":/graphics/scenary/cloud-med.png");
		new Background(QPoint(   48 * scale, terrain_level),			  ":/graphics/scenary/hill-big.png");
		new Background(QPoint( 59.5 * scale, terrain_level),			  ":/graphics/scenary/bush-big.png");
		new Background(QPoint(   64 * scale, terrain_level),			  ":/graphics/scenary/hill-small.png");
		new Background(QPoint(   57 * scale, terrain_level -  9 * scale), ":/graphics/scenary/cloud-small.png");
		new Background(QPoint(   68 * scale, terrain_level - 10 * scale), ":/graphics/scenary/cloud-small.png");
		new Background(QPoint( 71.5 * scale, terrain_level),			  ":/graphics/scenary/bush-small.png");
		new Background(QPoint(   76 * scale, terrain_level -  9 * scale), ":/graphics/scenary/cloud-big.png");
		new Background(QPoint(   85 * scale, terrain_level - 10 * scale), ":/graphics/scenary/cloud-med.png");
		new Background(QPoint( 89.5 * scale, terrain_level),			  ":/graphics/scenary/bush-med.png");
		new Background(QPoint(   96 * scale, terrain_level),			  ":/graphics/scenary/hill-big.png");
		new Background(QPoint(104.5 * scale, terrain_level -  9 * scale), ":/graphics/scenary/cloud-small.png");
		new Background(QPoint(107.5 * scale, terrain_level),			  ":/graphics/scenary/bush-big.png");
		new Background(QPoint(  112 * scale, terrain_level),			  ":/graphics/scenary/hill-small.png");
		new Background(QPoint(115.5 * scale, terrain_level - 10 * scale), ":/graphics/scenary/cloud-small.png");
		new Background(QPoint(119.5 * scale, terrain_level),			  ":/graphics/scenary/bush-small.png");
		new Background(QPoint(123.5 * scale, terrain_level -  9 * scale), ":/graphics/scenary/cloud-big.png");
		new Background(QPoint(132.5 * scale, terrain_level - 10 * scale), ":/graphics/scenary/cloud-med.png");
		new Background(QPoint(137.5 * scale, terrain_level),			  ":/graphics/scenary/bush-med.png");
		new Background(QPoint(  144 * scale, terrain_level),			  ":/graphics/scenary/hill-big.png");
		new Background(QPoint(152.5 * scale, terrain_level -  9 * scale), ":/graphics/scenary/cloud-small.png");
		new Background(QPoint(155.5 * scale, terrain_level),			  ":/graphics/scenary/bush-big.png");
		new Background(QPoint(  160 * scale, terrain_level),			  ":/graphics/scenary/hill-small.png");
		new Background(QPoint(163.5 * scale, terrain_level - 10 * scale), ":/graphics/scenary/cloud-small.png");
		new Background(QPoint(167.5 * scale, terrain_level),			  ":/graphics/scenary/bush-small.png");
		new Background(QPoint(171.5 * scale, terrain_level -  9 * scale), ":/graphics/scenary/cloud-big.png");
		new Background(QPoint(180.5 * scale, terrain_level - 10 * scale), ":/graphics/scenary/cloud-med.png");
		new Background(QPoint(185.5 * scale, terrain_level),			  ":/graphics/scenary/bush-med.png");
		new Background(QPoint(  192 * scale, terrain_level),			  ":/graphics/scenary/hill-big.png");
		new Background(QPoint(200.5 * scale, terrain_level -  9 * scale), ":/graphics/scenary/cloud-small.png");
		new Background(QPoint(  208 * scale, terrain_level),			  ":/graphics/scenary/hill-small.png");
		new Background(QPoint(211.5 * scale, terrain_level - 8 * scale), ":/graphics/scenary/cloud-small.png");
		new Background(QPoint(215.5 * scale, terrain_level),			  ":/graphics/scenary/bush-small.png");
		new Background(QPoint(219.5 * scale, terrain_level -  9 * scale), ":/graphics/scenary/cloud-big.png");
		new Background(QPoint(  220 * scale, terrain_level),			  ":/graphics/scenary/castle.png");
		new Background(QPoint(228.5 * scale, terrain_level - 8 * scale), ":/graphics/scenary/cloud-med.png");
		new Background(QPoint(232.5 * scale, terrain_level),			  ":/graphics/scenary/bush-med.png");

		new Brick(QPoint( 10 * scale, terrain_level - 4 * scale), 0);
		new Brick(QPoint( 11 * scale, terrain_level - 4 * scale), 0);
		new Brick(QPoint( 12 * scale, terrain_level - 4 * scale), 0);
		new Brick(QPoint( 23 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint( 25 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint( 51 * scale, terrain_level - 4 * scale), 0);
		new Brick(QPoint( 67 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint( 68 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint( 69 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint( 70 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint( 71 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint( 77 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint( 78 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint( 79 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint( 80 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint(110 * scale, terrain_level - 4 * scale), 0);
		new Brick(QPoint(113 * scale, terrain_level - 4 * scale), 0);
		new Brick(QPoint(115 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint(119 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint(120 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint(121 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint(122 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint(123 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint(124 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint(125 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint(126 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint(138 * scale, terrain_level - 5 * scale), 0);
		new Brick(QPoint(139 * scale, terrain_level - 5 * scale), 0);
		new Brick(QPoint(141 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint(144 * scale, terrain_level - 4 * scale), 0);
		new Brick(QPoint(145 * scale, terrain_level - 4 * scale), 0);
		new Brick(QPoint(146 * scale, terrain_level - 4 * scale), 0);
		new Brick(QPoint(145 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint(146 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint(160 * scale, terrain_level - 4 * scale), 0);
		new Brick(QPoint(161 * scale, terrain_level - 4 * scale), 0);
		new Brick(QPoint(162 * scale, terrain_level - 4 * scale), 0);
		new Brick(QPoint(160 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint(161 * scale, terrain_level - 8 * scale), 0);
		new Brick(QPoint(162 * scale, terrain_level - 8 * scale), 0);

		new Box(QPoint( 24 * scale, terrain_level - 4 * scale), INVISIBLE, COIN);
		new Box(QPoint( 24 * scale, terrain_level - 8 * scale), BRICKED, MULTICOIN);
		new Box(QPoint( 52 * scale, terrain_level - 4 * scale), BRICKED, POWERUP);
		new Box(QPoint( 81 * scale, terrain_level - 8 * scale), BRICKED, VINE);
		new Box(QPoint( 82 * scale, terrain_level - 4 * scale), INVISIBLE, COIN);
		new Box(QPoint(140 * scale, terrain_level - 8 * scale), BRICKED, STAR);

		new Block(QPoint( 32 * scale, terrain_level - 5 * scale));
		new Block(QPoint( 33 * scale, terrain_level - 5 * scale));
		new Block(QPoint( 62 * scale, terrain_level - 4 * scale));
		new Block(QPoint( 63 * scale, terrain_level - 4 * scale));
		new Block(QPoint(111 * scale, terrain_level - 4 * scale));
		new Block(QPoint(112 * scale, terrain_level - 4 * scale));
		new Block(QPoint(149 * scale, terrain_level -     scale));
		new Block(QPoint(150 * scale, terrain_level -     scale));
		new Block(QPoint(150 * scale, terrain_level - 2 * scale));
		new Block(QPoint(151 * scale, terrain_level -     scale));
		new Block(QPoint(151 * scale, terrain_level - 2 * scale));
		new Block(QPoint(151 * scale, terrain_level - 3 * scale));
		new Block(QPoint(156 * scale, terrain_level -     scale));
		new Block(QPoint(156 * scale, terrain_level - 2 * scale));
		new Block(QPoint(156 * scale, terrain_level - 3 * scale));
		new Block(QPoint(156 * scale, terrain_level - 4 * scale));
		new Block(QPoint(157 * scale, terrain_level -     scale));
		new Block(QPoint(157 * scale, terrain_level - 2 * scale));
		new Block(QPoint(167 * scale, terrain_level - 4 * scale));
		new Block(QPoint(168 * scale, terrain_level - 4 * scale));
		new Block(QPoint(199 * scale, terrain_level -     scale));
		new Block(QPoint(200 * scale, terrain_level -     scale));
		new Block(QPoint(200 * scale, terrain_level - 2 * scale));
		new Block(QPoint(203 * scale, terrain_level -     scale));
		new Block(QPoint(203 * scale, terrain_level - 2 * scale));
		new Block(QPoint(203 * scale, terrain_level - 3 * scale));
		new Block(QPoint(203 * scale, terrain_level - 4 * scale));
		new Block(QPoint(203 * scale, terrain_level - 5 * scale));
		new Block(QPoint(204 * scale, terrain_level -     scale));
		new Block(QPoint(204 * scale, terrain_level - 2 * scale));
		new Block(QPoint(204 * scale, terrain_level - 3 * scale));
		new Block(QPoint(204 * scale, terrain_level - 4 * scale));
		new Block(QPoint(204 * scale, terrain_level - 5 * scale));
		new Block(QPoint(204 * scale, terrain_level - 6 * scale));
		new Block(QPoint(205 * scale, terrain_level -     scale));
		new Block(QPoint(205 * scale, terrain_level - 2 * scale));
		new Block(QPoint(205 * scale, terrain_level - 3 * scale));
		new Block(QPoint(205 * scale, terrain_level - 4 * scale));
		new Block(QPoint(205 * scale, terrain_level - 5 * scale));
		new Block(QPoint(205 * scale, terrain_level - 6 * scale));
		new Block(QPoint(205 * scale, terrain_level - 7 * scale));
		new Block(QPoint(206 * scale, terrain_level -     scale));
		new Block(QPoint(206 * scale, terrain_level - 2 * scale));
		new Block(QPoint(206 * scale, terrain_level - 3 * scale));
		new Block(QPoint(206 * scale, terrain_level - 4 * scale));
		new Block(QPoint(206 * scale, terrain_level - 5 * scale));
		new Block(QPoint(206 * scale, terrain_level - 6 * scale));
		new Block(QPoint(206 * scale, terrain_level - 7 * scale));
		new Block(QPoint(206 * scale, terrain_level - 8 * scale));
		new Block(QPoint(207 * scale, terrain_level -     scale));
		new Block(QPoint(207 * scale, terrain_level - 2 * scale));
		new Block(QPoint(207 * scale, terrain_level - 3 * scale));
		new Block(QPoint(207 * scale, terrain_level - 4 * scale));
		new Block(QPoint(207 * scale, terrain_level - 5 * scale));
		new Block(QPoint(207 * scale, terrain_level - 6 * scale));
		new Block(QPoint(207 * scale, terrain_level - 7 * scale));
		new Block(QPoint(207 * scale, terrain_level - 8 * scale));
		new Block(QPoint(216 * scale, terrain_level -     scale));

		new Pipe(QPoint( 19 * scale, terrain_level),			 4);
		new Pipe(QPoint( 28 * scale, terrain_level),			 4);
		new Pipe(QPoint( 35 * scale, terrain_level),			 2);
		new Pipe(QPoint( 37 * scale, terrain_level),			 2);
		new Pipe(QPoint( 46 * scale, terrain_level),			 4);
		new Pipe(QPoint( 32 * scale, terrain_level - 5 * scale), 2);
		new Pipe(QPoint( 56 * scale, terrain_level),			 5);
		new Pipe(QPoint( 62 * scale, terrain_level - 4 * scale), 2);
		new Pipe(QPoint( 67 * scale, terrain_level),			 2);
		new Pipe(QPoint( 74 * scale, terrain_level),			 2);
		new Pipe(QPoint( 80 * scale, terrain_level),			 3);
		new Pipe(QPoint( 84 * scale, terrain_level),			 2);
		new Pipe(QPoint( 87 * scale, terrain_level),			 6);
		new Pipe(QPoint( 94 * scale, terrain_level),			 3);
		new Pipe(QPoint(102 * scale, terrain_level),			 4);
		new Pipe(QPoint(105 * scale, terrain_level),			 2);
		new Pipe(QPoint(111 * scale, terrain_level - 4 * scale), 3);
		new Pipe(QPoint(115 * scale, terrain_level),			 2);
		new Pipe(QPoint(131 * scale, terrain_level),			 2);
		new Pipe(QPoint(135 * scale, terrain_level),			 2);
		new Pipe(QPoint(153 * scale, terrain_level),			 3);
		new Pipe(QPoint(167 * scale, terrain_level - 4 * scale), 3);
		new Pipe(QPoint(174 * scale, terrain_level),			 4);
		new Pipe(QPoint(179 * scale, terrain_level),			 2);
		new Pipe(QPoint(181 * scale, terrain_level),			 3);
		new Pipe(QPoint(183 * scale, terrain_level),			 4);
		new Pipe(QPoint(189 * scale, terrain_level),			 3);
		new Pipe(QPoint(201 * scale, terrain_level),			 4);

		new Pole(QPoint(216 * scale, terrain_level));

		new Goomba(QPoint( 67 * scale, terrain_level - 8 * scale), LEFT);
		new Goomba(QPoint(169 * scale, terrain_level),			   LEFT);

		new Troopa(QPoint(26 * scale, terrain_level), LEFT);

		new Paratroopa(QPoint( 43 * scale, terrain_level - 3.5 * scale), LEFT);
		new Paratroopa(QPoint(206 * scale, terrain_level - 9.5 * scale), LEFT);

		new Beetle(QPoint( 54 * scale, terrain_level),			   LEFT);
		new Beetle(QPoint( 92 * scale, terrain_level),			   LEFT);
		new Beetle(QPoint(120 * scale, terrain_level - 8 * scale), LEFT);
		new Beetle(QPoint(163 * scale, terrain_level),			   LEFT);

		new PiranhaPlant(QPoint( 19.5 * scale, terrain_level - 4 * scale));
		new PiranhaPlant(QPoint( 28.5 * scale, terrain_level - 4 * scale));
		new PiranhaPlant(QPoint( 32.5 * scale, terrain_level - 7 * scale));
		new PiranhaPlant(QPoint( 35.5 * scale, terrain_level - 2 * scale));
		new PiranhaPlant(QPoint( 37.5 * scale, terrain_level - 2 * scale));
		new PiranhaPlant(QPoint( 46.5 * scale, terrain_level - 4 * scale));
		new PiranhaPlant(QPoint( 56.5 * scale, terrain_level - 5 * scale));
		new PiranhaPlant(QPoint( 62.5 * scale, terrain_level - 6 * scale));
		new PiranhaPlant(QPoint( 67.5 * scale, terrain_level - 2 * scale));
        new PiranhaPlant(QPoint( 80.5 * scale, terrain_level - 3 * scale));
		new PiranhaPlant(QPoint( 84.5 * scale, terrain_level - 2 * scale));
		new PiranhaPlant(QPoint( 87.5 * scale, terrain_level - 6 * scale));
		new PiranhaPlant(QPoint( 94.5 * scale, terrain_level - 3 * scale));
		new PiranhaPlant(QPoint(105.5 * scale, terrain_level - 2 * scale));
		new PiranhaPlant(QPoint(111.5 * scale, terrain_level - 7 * scale));
		new PiranhaPlant(QPoint(115.5 * scale, terrain_level - 2 * scale));
		new PiranhaPlant(QPoint(131.5 * scale, terrain_level - 2 * scale));
		new PiranhaPlant(QPoint(135.5 * scale, terrain_level - 2 * scale));
		new PiranhaPlant(QPoint(153.5 * scale, terrain_level - 3 * scale));
		new PiranhaPlant(QPoint(105.5 * scale, terrain_level - 2 * scale));
		new PiranhaPlant(QPoint(167.5 * scale, terrain_level - 7 * scale));
		new PiranhaPlant(QPoint(174.5 * scale, terrain_level - 4 * scale));
		new PiranhaPlant(QPoint(179.5 * scale, terrain_level - 2 * scale));
		new PiranhaPlant(QPoint(181.5 * scale, terrain_level - 3 * scale));
		new PiranhaPlant(QPoint(183.5 * scale, terrain_level - 4 * scale));
		new PiranhaPlant(QPoint(189.5 * scale, terrain_level - 3 * scale));
		new PiranhaPlant(QPoint(201.5 * scale, terrain_level - 4 * scale));

        /*-------------------- END 6-2 OVERWORLD ---------------------------*/

        /*-------------------- 6-2 UNDERGROUND 1 ---------------------------*/

        terrain_level = 200 + 300;

        new Terrain(QRect(0, terrain_level, 17 * scale, 2 * scale), 1);

        new Brick(QPoint( 0,		 terrain_level -      scale), 1);
        new Brick(QPoint( 0,		 terrain_level -  2 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level -  3 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level -  4 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level -  5 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level -  6 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level -  7 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level -  8 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level -  9 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level - 10 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level - 11 * scale), 1);
        new Brick(QPoint( 4 * scale, terrain_level -  6 * scale), 1);
        new Brick(QPoint( 4 * scale, terrain_level -  7 * scale), 1);
        new Brick(QPoint( 4 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint( 5 * scale, terrain_level -  6 * scale), 1);
        new Brick(QPoint( 5 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint( 6 * scale, terrain_level -  6 * scale), 1);
        new Brick(QPoint( 6 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint( 7 * scale, terrain_level -  6 * scale), 1);
        new Brick(QPoint( 7 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint( 8 * scale, terrain_level -  6 * scale), 1);
        new Brick(QPoint( 8 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint( 9 * scale, terrain_level -  6 * scale), 1);
        new Brick(QPoint( 9 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint(10 * scale, terrain_level -  6 * scale), 1);
        new Brick(QPoint(10 * scale, terrain_level -  7 * scale), 1);
        new Brick(QPoint(10 * scale, terrain_level -  8 * scale), 1);
        new Brick(QPoint(10 * scale, terrain_level -  9 * scale), 1);
        new Brick(QPoint(10 * scale, terrain_level - 10 * scale), 1);
        new Brick(QPoint(10 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint(11 * scale, terrain_level -  7 * scale), 1);
        new Brick(QPoint(12 * scale, terrain_level -  7 * scale), 1);

        new Box(QPoint(14 * scale, terrain_level - 6 * scale), BRICKEDUND, MULTICOIN);

        new Pipe(QPoint(13 * scale, terrain_level), 14);
        for (int i = 2; i < 11; i++)
            new Pipe(QPoint(15 * scale, terrain_level - i * scale), 0);

        new Coin(QPoint(5 * scale, terrain_level - 7 * scale));
        new Coin(QPoint(5 * scale, terrain_level - 8 * scale));
        new Coin(QPoint(6 * scale, terrain_level - 7 * scale));
        new Coin(QPoint(6 * scale, terrain_level - 8 * scale));
        new Coin(QPoint(7 * scale, terrain_level - 7 * scale));
        new Coin(QPoint(7 * scale, terrain_level - 8 * scale));
        new Coin(QPoint(8 * scale, terrain_level - 7 * scale));
        new Coin(QPoint(8 * scale, terrain_level - 8 * scale));
        new Coin(QPoint(9 * scale, terrain_level - 7 * scale));
        new Coin(QPoint(9 * scale, terrain_level - 8 * scale));

        /*------------------ END 6-2 UNDERGROUND 1 --------------------------*/

        /*-------------------- 6-2 UNDERGROUND 2 ---------------------------*/

        terrain_level = 200 + 300 + 300;

        new Terrain(QRect(0, terrain_level, 17 * scale, 2 * scale), 1);

        new Brick(QPoint( 0,		 terrain_level -	  scale), 1);
        new Brick(QPoint( 0,		 terrain_level -  2 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level -  3 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level -  4 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level -  5 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level -  6 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level -  7 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level -  8 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level -  9 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level - 10 * scale), 1);
        new Brick(QPoint( 0,		 terrain_level - 11 * scale), 1);
        new Brick(QPoint( 3 * scale, terrain_level -  2 * scale), 1);
        new Brick(QPoint( 3 * scale, terrain_level -  3 * scale), 1);
        new Brick(QPoint( 3 * scale, terrain_level -  4 * scale), 1);
        new Brick(QPoint( 3 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint( 4 * scale, terrain_level -  4 * scale), 1);
        new Brick(QPoint( 4 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint( 5 * scale, terrain_level -  4 * scale), 1);
        new Brick(QPoint( 5 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint( 6 * scale, terrain_level -  4 * scale), 1);
        new Brick(QPoint( 6 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint( 7 * scale, terrain_level -  4 * scale), 1);
        new Brick(QPoint( 7 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint( 8 * scale, terrain_level -  4 * scale), 1);
        new Brick(QPoint( 8 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint( 9 * scale, terrain_level -  4 * scale), 1);
        new Brick(QPoint( 9 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint(10 * scale, terrain_level -  2 * scale), 1);
        new Brick(QPoint(10 * scale, terrain_level -  3 * scale), 1);
        new Brick(QPoint(10 * scale, terrain_level -  4 * scale), 1);
        new Brick(QPoint(10 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint(11 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint(12 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint(13 * scale, terrain_level - 11 * scale), 1);
        new Brick(QPoint(14 * scale, terrain_level - 11 * scale), 1);

        new Box(QPoint(13 * scale, terrain_level - 4 * scale), BRICKEDUND, POWERUP);

        new Coin(QPoint( 3 * scale, terrain_level -		scale));
        new Coin(QPoint( 4 * scale, terrain_level -		scale));
        new Coin(QPoint( 5 * scale, terrain_level -		scale));
        new Coin(QPoint( 6 * scale, terrain_level -		scale));
        new Coin(QPoint( 7 * scale, terrain_level -		scale));
        new Coin(QPoint( 8 * scale, terrain_level -		scale));
        new Coin(QPoint( 9 * scale, terrain_level -		scale));
        new Coin(QPoint(10 * scale, terrain_level -		scale));
        new Coin(QPoint(11 * scale, terrain_level -		scale));
        new Coin(QPoint(12 * scale, terrain_level -		scale));
        new Coin(QPoint( 3 * scale, terrain_level - 5 * scale));
        new Coin(QPoint( 4 * scale, terrain_level - 5 * scale));
        new Coin(QPoint( 5 * scale, terrain_level - 5 * scale));
        new Coin(QPoint( 6 * scale, terrain_level - 5 * scale));
        new Coin(QPoint( 7 * scale, terrain_level - 5 * scale));
        new Coin(QPoint( 8 * scale, terrain_level - 5 * scale));
        new Coin(QPoint( 9 * scale, terrain_level - 5 * scale));
        new Coin(QPoint(10 * scale, terrain_level - 5 * scale));

        new Pipe(QPoint(13 * scale, terrain_level), 14);
        for (int i = 2; i < 11; i++)
            new Pipe(QPoint(15 * scale, terrain_level - i * scale), 0);

        /*------------------ END 6-2 UNDERGROUND 2 --------------------------*/

        /*------------------------ 6-2 WATER --------------------------------*/

		terrain_level = 200 + 300 + 300 + 300;

        new Terrain(QRect( 0,		  terrain_level,			  22 * scale, 2 * scale), 2);
        new Terrain(QRect(11 * scale, terrain_level -  7 * scale,  5 * scale,	  scale), 2);
        new Terrain(QRect(26 * scale, terrain_level -  3 * scale,  2 * scale, 5 * scale), 2);
        new Terrain(QRect(26 * scale, terrain_level - 11 * scale,  2 * scale, 3 * scale), 2);
        new Terrain(QRect(32 * scale, terrain_level -  3 * scale,  2 * scale, 5 * scale), 2);
        new Terrain(QRect(32 * scale, terrain_level - 11 * scale,  2 * scale, 3 * scale), 2);
        new Terrain(QRect(34 * scale, terrain_level,			   4 * scale, 2 * scale), 2);
        new Terrain(QRect(38 * scale, terrain_level -  9 * scale,  6 * scale,	  scale), 2);
        new Terrain(QRect(40 * scale, terrain_level,			   2 * scale, 2 * scale), 2);
        new Terrain(QRect(44 * scale, terrain_level,			  21 * scale, 2 * scale), 2);
        new Terrain(QRect(50 * scale, terrain_level -  4 * scale,  4 * scale,	  scale), 2);
        new Terrain(QRect(54 * scale, terrain_level -  7 * scale,  4 * scale,	  scale), 2);
        new Terrain(QRect(59 * scale, terrain_level -	   scale,  6 * scale,	  scale), 2);
        new Terrain(QRect(60 * scale, terrain_level -  2 * scale,  5 * scale,	  scale), 2);
        new Terrain(QRect(61 * scale, terrain_level -  4 * scale,  4 * scale, 2 * scale), 2);
        new Terrain(QRect(61 * scale, terrain_level - 11 * scale,  4 * scale, 4 * scale), 2);
        new Terrain(QRect(63 * scale, terrain_level -  7 * scale,  2 * scale, 3 * scale), 2);

        for (int i = 0; i < 65; i++) {
            new Background(QPoint(i * scale, terrain_level - 10 * scale), ":/graphics/scenary/water.png");
            new Background(QPoint(i * scale, terrain_level - 11 * scale), ":/graphics/scenary/water-sky.png");
			new Background(QPoint(i * scale, terrain_level - 12 * scale), ":/graphics/scenary/water-sky.png");
			new Background(QPoint(i * scale, terrain_level - 13 * scale), ":/graphics/scenary/water-sky.png");
        }

        new Brick(QPoint(12 * scale, terrain_level -	 scale), 2);
        new Brick(QPoint(12 * scale, terrain_level - 2 * scale), 2);
        new Brick(QPoint(12 * scale, terrain_level - 3 * scale), 2);
        new Brick(QPoint(15 * scale, terrain_level - 8 * scale), 2);
        new Brick(QPoint(15 * scale, terrain_level - 9 * scale), 2);
        new Brick(QPoint(20 * scale, terrain_level -	 scale), 2);
        new Brick(QPoint(20 * scale, terrain_level - 2 * scale), 2);
        new Brick(QPoint(20 * scale, terrain_level - 3 * scale), 2);
        new Brick(QPoint(20 * scale, terrain_level - 4 * scale), 2);
        new Brick(QPoint(38 * scale, terrain_level - 5 * scale), 2);
        new Brick(QPoint(38 * scale, terrain_level - 6 * scale), 2);
        new Brick(QPoint(38 * scale, terrain_level - 7 * scale), 2);
        new Brick(QPoint(38 * scale, terrain_level - 8 * scale), 2);
        new Brick(QPoint(43 * scale, terrain_level - 5 * scale), 2);
        new Brick(QPoint(43 * scale, terrain_level - 6 * scale), 2);
        new Brick(QPoint(43 * scale, terrain_level - 7 * scale), 2);
        new Brick(QPoint(43 * scale, terrain_level - 8 * scale), 2);
        new Brick(QPoint(46 * scale, terrain_level -	 scale), 2);
        new Brick(QPoint(46 * scale, terrain_level - 2 * scale), 2);

        new Pipe(QPoint(62 * scale, terrain_level - 4 * scale), 13);

		new Platform(QPoint(22.5 * scale, terrain_level - 4.2 * scale), 9, 1, RIGHT);
		new Platform(QPoint(  29 * scale, terrain_level -   7 * scale), 9, 1, LEFT);

		new Coin(QPoint(22 * scale, terrain_level - 6 * scale));
		new Coin(QPoint(23 * scale, terrain_level - 6 * scale));
		new Coin(QPoint(24 * scale, terrain_level - 6 * scale));
		new Coin(QPoint(25 * scale, terrain_level - 6 * scale));
		new Coin(QPoint(26 * scale, terrain_level - 6 * scale));
		new Coin(QPoint(27 * scale, terrain_level - 6 * scale));
		new Coin(QPoint(28 * scale, terrain_level - 6 * scale));
		new Coin(QPoint(29 * scale, terrain_level - 6 * scale));
		new Coin(QPoint(30 * scale, terrain_level - 6 * scale));
		new Coin(QPoint(31 * scale, terrain_level - 6 * scale));
		new Coin(QPoint(40 * scale, terrain_level - 1 * scale));
		new Coin(QPoint(41 * scale, terrain_level - 1 * scale));
		new Coin(QPoint(50 * scale, terrain_level - 5 * scale));
		new Coin(QPoint(51 * scale, terrain_level - 5 * scale));
		new Coin(QPoint(52 * scale, terrain_level - 5 * scale));
		new Coin(QPoint(53 * scale, terrain_level - 5 * scale));
		new Coin(QPoint(54 * scale, terrain_level - 8 * scale));
		new Coin(QPoint(55 * scale, terrain_level - 8 * scale));
		new Coin(QPoint(56 * scale, terrain_level - 8 * scale));
		new Coin(QPoint(57 * scale, terrain_level - 8 * scale));

        /*---------------------- END 6-2 WATER ------------------------------*/

        /*------------------------- 6-2 SKY ---------------------------------*/

        scene->setBackgroundBrush(QBrush(QColor(99, 133, 251)));

        terrain_level = 200 - 250;

        new Terrain(QRect((77 +  0) * scale, terrain_level,			  4 * scale,	 scale), 3);
        new Terrain(QRect((77 +  5) * scale, terrain_level,			 78 * scale,	 scale), 3);
        new Terrain(QRect((77 + 32) * scale, terrain_level - 5 * scale,	  scale,	 scale), 3);
        new Terrain(QRect((77 + 51) * scale, terrain_level - 6 * scale,	  scale, 2 * scale), 3);
        new Terrain(QRect((77 + 61) * scale, terrain_level - 6 * scale,	  scale, 2 * scale), 3);
        new Terrain(QRect((77 + 67) * scale, terrain_level - 7 * scale,  2 * scale,	 scale), 3);
        new Terrain(QRect((77 + 71) * scale, terrain_level - 7 * scale,	  scale,	 scale), 3);
        new Terrain(QRect((77 + 73) * scale, terrain_level - 7 * scale,	  scale,	 scale), 3);
        new Terrain(QRect((77 + 75) * scale, terrain_level - 7 * scale,	  scale,	 scale), 3);
        new Terrain(QRect((77 + 77) * scale, terrain_level - 7 * scale,	  scale,	 scale), 3);
        new Terrain(QRect((77 + 79) * scale, terrain_level - 7 * scale,	  scale,	 scale), 3);

		new Platform(QPoint((77 + 16) * scale, terrain_level - 3 * scale), 70, 0, RIGHT);

        for (int i = 15; i < 31; i++) {
            new Coin(QPoint((77 + i) * scale, terrain_level - 7 * scale));
            new Coin(QPoint((77 + (i + 19)) * scale, terrain_level - 7 * scale));
        }
        for (int i = 53; i < 60; i++)
            new Coin(QPoint((77 + i) * scale, terrain_level - 8 * scale));
        for (int i = 71; i < 81; i++)
            new Coin(QPoint((77 + i) * scale, terrain_level - 8 * scale));
        new Coin(QPoint((77 + 86) * scale, terrain_level - 2 * scale));
        new Coin(QPoint((77 + 87) * scale, terrain_level - 2 * scale));
        new Coin(QPoint((77 + 88) * scale, terrain_level - 2 * scale));

        /*----------------------- END 6-2 SKY -------------------------------*/
	}
	else
		std::cerr << "Level not implemented";
}