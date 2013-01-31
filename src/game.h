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

    explicit Game(bool server = false);
    virtual ~Game();
    
    int getLastFrameTime();
    irr::scene::ISceneManager *getSceneManager();
    
    Vector<SafePtr<Entity> > *getEntities();

    virtual void draw();
    virtual void initialize();
    virtual void update();
    virtual void addEntity(Entity *entity);

    // overrides
    void writeString(const char*);
    
protected:
    irr::video::IVideoDriver *mDriver;
    irr::scene::IAnimatedMesh *mMesh;
    irr::scene::ISceneManager *mSceneManager;
    irr::scene::ITerrainSceneNode *mTerrain;
    irr::IrrlichtDevice *mDevice;
    irr::video::E_DRIVER_TYPE mDriverType;
    
    int mLastFrameTime;

private:
    bool mServer;
    Vector<SafePtr<Entity> > mEntities;
};

#endif /* GAME_H_ */
