#include "video.h"
#include "entity_node.h"
#include "entity.h"
#include "vec2.h"

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
   const Vec2 pos = mEntity->getPos();
   mNode->setPosition(irr::core::vector3df(pos.x * Video::VIDEOSCALE, pos.y * Video::VIDEOSCALE, 0.0));
}
