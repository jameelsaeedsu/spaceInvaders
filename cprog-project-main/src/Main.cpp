#include "Session.h"
#include "Player.h"
#include "Enemy.h"
#include <SDL2/SDL.h>
#include <string>

using namespace SPACEINVASION;

std::string resPath = "../../resources/";

int main(int argc, char** argv)
{
    Session session;
    session.setIcon((resPath + "images/logo.png").c_str());
    session.setBackground((resPath + "images/bg.jpeg").c_str());
    Player* player = Player::getInstance(session);
    session.add(player);
    session.run();
    return 0;
}