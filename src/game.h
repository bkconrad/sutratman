#ifndef GAME_H_
#define GAME_H_

#include <irrlicht.h>

#include <tnl.h>
#include <tnlLog.h>
#include <tnlNetBase.h>

using namespace TNL;

class Entity;
class Game : LogConsumer
{
public:
    static const float HEIGHTMAP_SIZE; // size of one side of the (square) heightmap

    explicit Game(bool server);
    Game();
    virtual ~Game();
    Vector<SafePtr<Entity> > *getEntities();

    virtual void initialize();
    virtual void update(U32 t);
    virtual void addEntity(Entity *entity);

    // overrides
    void writeString(const char*);

    irr::video::IVideoDriver *mDriver;
    irr::scene::IAnimatedMesh *mMesh;
    irr::scene::ISceneManager *mSceneManager;
    irr::scene::ITerrainSceneNode *mTerrain;
    irr::IrrlichtDevice *mDevice;

private:
    bool mServer;
    Vector<SafePtr<Entity> > mEntities;
};

#endif /* GAME_H_ */
