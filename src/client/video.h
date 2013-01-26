#ifndef VIDEO_H_
#define VIDEO_H_

#include <irrlicht.h>
#include <tnl.h>
#include <tnlNetBase.h>

using namespace TNL;

class EntityNode;
class Entity;

class Video
{
public:
    static const float CAMERA_ACCELERATION; // acceleration of camera movement
    static const float CAMERA_MAX_SPEED; // max speed of camera movement
    static const float VIDEOSCALE; // scale from normalized simulation positions to irrlich positions
    static const float HEIGHTMAP_SIZE; // size of one side of the (square) heightmap

    static Video *get();

    bool run();
    void addEntity(Entity *entity);

private:
    static Video *mInstance;

    Video();
    virtual ~Video();

    irr::scene::ICameraSceneNode *mCamera;
    float mCameraRotation; // camera's rotation around the y axis
    float mCameraVelocity; // camera's current angular velocity

    irr::IrrlichtDevice *mDevice;
    irr::video::IVideoDriver *mDriver;
    irr::IEventReceiver *mEventReceiver;
    irr::scene::IAnimatedMesh *mMesh;
    irr::scene::ISceneManager *mSceneManager;
    irr::scene::ITerrainSceneNode *mTerrain;

    SafePtr<Entity> mFocusEntity;
    Vector<EntityNode*> mEntityNodes;
};

#endif /* VIDEO_H_ */
