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
   const vec2 pos = mEntity->getPos();
   const vec2 rot = mEntity->getRot();
   mNode->setPosition(irr::core::vector3df(pos.x * Video::VIDEOSCALE, pos.y * Video::VIDEOSCALE, 0.0));
   mNode->setRotation(irr::core::vector3df(radiansToDegrees(rot.x), radiansToDegrees(rot.y), 0.0));
}
