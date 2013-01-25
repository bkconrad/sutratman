#ifndef ENTITY_NODE_H_
#define ENTITY_NODE_H_

#include <irrlicht.h>
#include <tnl.h>

using namespace TNL;

class Entity;

/**
 *A container and mapping logic for a game entity and Irrlicht node
 */
class EntityNode
{
public:
    EntityNode(Entity *entity, irr::scene::IAnimatedMeshSceneNode *node);
    ~EntityNode();
    void update();
private:
    Entity *mEntity;
    irr::scene::IAnimatedMeshSceneNode *mNode;
};

#endif /* ENTITY_NODE_H_ */
