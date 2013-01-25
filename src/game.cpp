#include "entity.h"
#include "game.h"
#include "log.h"

using namespace TNL;

Game::Game(bool server)
{
    mServer = server;
    Game();
    setMsgTypes(LogNetConnection | LogFatalError | LogError | LogWarning);
}

Game::Game()
{
}

Game::~Game()
{
    for(int i; i < mEntities.size(); i++)
    {
        delete mEntities[i];
    }
}

void Game::addEntity(Entity *entity)
{
    mEntities.push_back(entity);
}

Vector<SafePtr<Entity> >* Game::getEntities()
{
    return &mEntities;
}

void Game::writeString(const char *s)
{
    Log::p(s);
}
