#include "entity.h"
#include "game.h"
#include "game_interface.h"
#include "log.h"
#include "mathutil.h"

#include <tnlBitStream.h>

using namespace mathutil;
using namespace TNL;

int Entity::IdIndex = 1;
const float Entity::MOVESPEED = 0.05;

TNL_IMPLEMENT_NETOBJECT(Entity);

TNL_IMPLEMENT_NETOBJECT_RPC(Entity, c2sRotate, (F32 angle), (angle),
                            NetClassGroupAllMask,  RPCGuaranteedOrdered, RPCToGhostParent, 0)
{
    // TODO check client's ownership
    setRot(vector3df(0.0f, angle * DEGREES, 0.0f));
    setMaskBits(RotationMask);
}

Entity::Entity(Game *game)
    : mNode(NULL), mLastKnownPosition(0)
{
    mGame = game;
    mNetFlags.set(Ghostable);
}

Entity::~Entity()
{
    //dtor
}

void Entity::performScopeQuery(GhostConnection *connection)
{
    int i;

    for(i = 0; i < mGame->getEntities()->size(); i++)
    {
        connection->objectInScope((NetObject*)(mGame->getEntities()->operator[](i)));
    }
}

/**
 * @brief set whether this is the locally controlled entity
 */
void Entity::setControlled(bool controlled)
{
    mIsControlled = controlled;
}

/**
 * @brief return true if this is the locally controlled entity
 */
bool Entity::isControlled()
{
    return mIsControlled;
}

void Entity::setPos(const vector3df &pos)
{
    mNode->setPosition(pos);
    mLastKnownPosition = pos;
}

/**
 * @brief modify this entity's position by delta
 */
void Entity::modPos(const vector3df &delta)
{
    mNode->setPosition(mNode->getPosition() + delta);
}

/**
 * @brief modify this entity's rotation by delta
 */
void Entity::modRot(const vector3df &delta)
{
    mNode->setRotation(mNode->getRotation() + delta);
}

/**
 * @brief remember that *all* floats are normalized to some range, and it is
 * up to the client code to convert from normalized scalers to the relevant
 * units. In the case of positions, and all distances (or any 0th derivative in
 * general) in the engine
 */
const vector3df &Entity::getPos() const
{
    return mNode->getPosition();
}

/**
 * @brief returns true if the other entity accurately reflects this entity's
 * state
 */
bool Entity::isConsistentWith(const Entity &entity)
{
    return (getPos() - entity.getPos()).getLength() < EPSILON
         && (getRot() - entity.getRot()).getLength() < EPSILON;
}

U32 Entity::packUpdate(GhostConnection *connection, U32 updateMask, BitStream *bitStream)
{
    // TODO assert that this is never called from the server side
    if(bitStream->writeFlag(updateMask & PositionMask))
    {
        vector3df pos = mLastKnownPosition;
        bitStream->writeFloat(pos.X, 16);
        bitStream->writeFloat(pos.Y, 16);
        bitStream->writeFloat(pos.Z, 16);
    }

    if(bitStream->writeFlag(updateMask & RotationMask))
    {
        vector3df rot = getRot() / DEGREES;
        bitStream->writeFloat(rot.X, 16);
        bitStream->writeFloat(rot.Y, 16);
        bitStream->writeFloat(rot.Z, 16);
    }
	return 0;
}

void Entity::unpackUpdate(GhostConnection *connection, BitStream *bitStream)
{
    // position update
    if(bitStream->readFlag())
    {
        vector3df pos;
        pos.X = bitStream->readFloat(16);
        pos.Y = bitStream->readFloat(16);
        pos.Z = bitStream->readFloat(16);
        if (mNode) {
            setPos(pos);
        }
    }

    // rotation update. Convert to radians from normalized float
    if(bitStream->readFlag())
    {
        vector3df rot;
        rot.X = bitStream->readFloat(16);
        rot.Y = bitStream->readFloat(16);
        rot.Z = bitStream->readFloat(16);
        if (mNode) {
            setRot(rot * DEGREES);
        }
    }
}

bool Entity::onGhostAdd(GhostConnection *connection)
{
    // set our game pointer. we can safely cast to GameConnection inside of Entities
    mGame = static_cast<GameInterface*>(connection->getInterface())->getGame();
    mGame->addEntity(this);
    return true;
}

/**
 * @brief set the rotation vector (degrees)
 */
void Entity::setRot(const vector3df &rot)
{
    mNode->setRotation(rot);
}

/**
 * @brief rotation vector in degrees
 */
const vector3df &Entity::getRot() const
{
    return mNode->getRotation();
}

/** @brief setNode
  *
  * @todo: document this function
  */
void Entity::setNode(irr::scene::IAnimatedMeshSceneNode *node)
{
    mNode = node;
}

/** @brief getNode
  *
  * @todo: document this function
  */
irr::scene::IAnimatedMeshSceneNode* Entity::getNode()
{
    return mNode;
}

void Entity::update()
{
   //setPos(mLastKnownPosition);
}
