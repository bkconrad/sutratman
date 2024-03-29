#ifndef ENTITY_H_
#define ENTITY_H_

#include <irrlicht.h>

#include <tnl.h>
#include <tnlGhostConnection.h>
#include <tnlNetObject.h>

#include <gtest/gtest_prod.h>

using namespace TNL;
using irr::core::vector3df;

class Game;
class ClientGame;

class Entity : public NetObject
{
public:
    TNL_DECLARE_CLASS(Entity);
    TNL_DECLARE_RPC(c2sRotate, (F32 angle));

    // TODO should be replaced with stats or something
    static const float MOVESPEED;
    static const int FLOATSIZE;    

    Entity(Game *game = NULL);
    virtual ~Entity();

    // entity-specific things
    virtual bool isConsistentWith(const Entity &entity);
    virtual void update();

    // overrides
    virtual void onGhostAddBeforeUpdate(GhostConnection *connection);
    virtual U32 packUpdate(GhostConnection *connection, U32 updateMask, BitStream *bitStream);
    virtual void performScopeQuery(GhostConnection *connection);
    virtual void unpackUpdate(GhostConnection *connection, BitStream *bitStream);

    const vector3df &getPos() const;
    const vector3df &getRot() const;
    bool isControlled();
    void modPos(const vector3df &pos);
    void modRot(const vector3df &rot);
    void setControlled(bool controlled);
    void setPos(const vector3df &pos);
    void setRot(const vector3df &rot);

    void setNode(irr::scene::IAnimatedMeshSceneNode *node);
    irr::scene::IAnimatedMeshSceneNode *getNode();

    enum MaskBits
    {
        InitialMask = 1 << 0,
        PositionMask = 1 << 1,
        RotationMask = 1 << 2,
        VelocityMask = 1 << 3
    };

protected:
    static int IdIndex;

    ClientGame *mClientGame;
    Game *mGame;
    U32 mId;
    bool mIsControlled;
   vector3df mLastKnownPosition;
    irr::scene::IAnimatedMeshSceneNode *mNode;

private:

    FRIEND_TEST(entity, packing);
};

#endif /* ENTITY_H_ */
