#ifndef GAME_H_
#define GAME_H_

#include <tnl.h>
#include <tnlLog.h>
#include <tnlNetBase.h>

using namespace TNL;

class Entity;
class Game : LogConsumer
{
public:
    explicit Game(bool server);
    Game();
    virtual ~Game();
    virtual void addEntity(Entity *entity);
    Vector<SafePtr<Entity> >* getEntities();

    // overrides
    void writeString(const char*);

private:
    bool mServer;
    Vector<SafePtr<Entity> > mEntities;
};

#endif /* GAME_H_ */
