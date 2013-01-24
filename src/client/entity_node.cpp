#include "video.h"
#include "entity_node.h"
#include "entity.h"
#include "mathutil.h"

using namespace mathutil;

EntityNode::EntityNode(Entity* entity, irr::scene::IAnimatedMeshSceneNode* node)
   : mEntity(entity), mNode(node)
{
}

EntityNode::~EntityNode()
{
   mNode->drop();
}

/** @brief configure the node from this entity's data
  */
void EntityNode::update()
{
   const vec3 pos = mEntity->getPos();
   const vec3 rot = mEntity->getRot() * RADIANS;
   mNode->setPosition(irr::core::vector3df(pos.x * Video::VIDEOSCALE, pos.y * Video::VIDEOSCALE, pos.z * Video::VIDEOSCALE));
   mNode->setRotation(irr::core::vector3df(radiansToDegrees(rot.x), radiansToDegrees(rot.y), radiansToDegrees(rot.z)));
}
