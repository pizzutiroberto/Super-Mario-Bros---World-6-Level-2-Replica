#include <QApplication>
#include "Game.h"

//int WinMain(int argc, char *argv[])
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	Game::instance()->show();

    return app.exec();
}
