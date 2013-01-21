#ifndef ENTITY_NODE_H
#define ENTITY_NODE_H

#include <irrlicht.h>
#include <tnl.h>

using namespace TNL;
/**
A container and mapping logic for a game entity and Irrlicht node
*/
class Entity;
class EntityNode
{
   public:
      EntityNode(Entity* entity, irr::scene::IAnimatedMeshSceneNode* node);
      ~EntityNode();
      void update();
   protected:
   private:
      Entity* mEntity;
      irr::scene::IAnimatedMeshSceneNode* mNode;
};

#endif // ENTITY_NODE_H
