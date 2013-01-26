#include "entity.h"
#include "game.h"
#include "game_interface.h"
#include "log.h"
#include "mathutil.h"

#include <tnlBitStream.h>

using namespace mathutil;
using namespace TNL;

int Entity::IdIndex = 1;
const float Entity::MOVESPEED = 0.001;

TNL_IMPLEMENT_NETOBJECT(Entity);

TNL_IMPLEMENT_NETOBJECT_RPC(Entity, c2sMove, (F32 angle), (angle),
                            NetClassGroupAllMask,  RPCGuaranteedOrdered, RPCToGhostParent, 0)
{
    // TODO check client's ownership
    vec3 delta = vec3();
    // TODO check to see if these trig functions are inverted
    delta = vec3(-sin(angle * RADIANS), 0.0, -cos(angle * RADIANS));
    delta *= Entity::MOVESPEED;
    mPos += delta;
    setMaskBits(PositionMask);
}

TNL_IMPLEMENT_NETOBJECT_RPC(Entity, c2sRotate, (F32 angle), (angle),
                            NetClassGroupAllMask,  RPCGuaranteedOrdered, RPCToGhostParent, 0)
{
    // TODO check client's ownership
    mRot.y = angle;
    mod(mRot, TAU);
    setMaskBits(RotationMask);
}

Entity::Entity(Game *game)
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

void Entity::setPos(const vec3 &pos)
{
    mPos = pos;
}

void Entity::setPos(float x, float y, float z)
{
    mPos = vec3(x, y, z);
}

/**
 * @brief modify this entity's position by delta
 */
void Entity::modPos(const vec3 &delta)
{
    mPos += delta;
}

/**
 * @brief modify this entity's rotation by delta
 */
void Entity::modRot(const vec3 &rot)
{
    mRot += rot;
    mod(mRot, TAU);
}

/**
 * @brief remember that *all* floats are normalized to some range, and it is
 * up to the client code to convert from normalized scalers to the relevant
 * units. In the case of positions, and all distances (or any 0th derivative in
 * general) in the engine
 */
const vec3 &Entity::getPos()
{
    return mPos;
}

/**
 * @brief returns true if the other entity accurately reflects this entity's
 * state
 */
bool Entity::isConsistentWith(const Entity &entity)
{
    return length(distance(mPos, entity.mPos)) < EPSILON
           && length(distance(mRot, entity.mRot)) < EPSILON;
}

U32 Entity::packUpdate(GhostConnection *connection, U32 updateMask, BitStream *bitStream)
{
    // TODO assert that this is never called from the server side
    if(bitStream->writeFlag(updateMask & PositionMask))
    {
        bitStream->writeFloat(mPos.x, 16);
        bitStream->writeFloat(mPos.y, 16);
        bitStream->writeFloat(mPos.z, 16);
    }

    if(bitStream->writeFlag(updateMask & RotationMask))
    {
        bitStream->writeFloat(mRot.x, 16);
        bitStream->writeFloat(mRot.y, 16);
        bitStream->writeFloat(mRot.z, 16);
    }
}

void Entity::unpackUpdate(GhostConnection *connection, BitStream *bitStream)
{
    // position update
    if(bitStream->readFlag())
    {
        mPos.x = bitStream->readFloat(16);
        mPos.y = bitStream->readFloat(16);
        mPos.z = bitStream->readFloat(16);
    }

    // rotation update. Convert to radians from normalized float
    if(bitStream->readFlag())
    {
        mRot.x = bitStream->readFloat(16);
        mRot.y = bitStream->readFloat(16);
        mRot.z = bitStream->readFloat(16);
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
 * @brief set the rotation vector (radians)
 */
void Entity::setRot(const vec3 &rot)
{
    mRot = rot;
    mod(mRot, TAU);
}

/**
 * @brief rotation vector in radians
 */
const vec3 &Entity::getRot()
{
    return mRot;
}

