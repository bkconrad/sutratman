#ifndef MOBILE_ENTITY_ANIMATOR_H_
#define MOBILE_ENTITY_ANIMATOR_H_

#include <irrlicht.h>

using namespace irr;
using namespace video;
using namespace scene;

class MobileEntityAnimator : public irr::scene::ISceneNodeAnimatorCollisionResponse
{
public:
		//! constructor
		MobileEntityAnimator(ISceneManager* scenemanager,
			ITriangleSelector* world, ISceneNode* object,
			const core::vector3df& ellipsoidRadius = core::vector3df(30,60,30),
			const core::vector3df& gravityPerSecond = core::vector3df(0,-100.0f,0),
			const core::vector3df& ellipsoidTranslation = core::vector3df(0,0,0),
			f32 slidingSpeed = 0.0005f);

		//! destructor
		virtual ~MobileEntityAnimator();

		//! Returns if the attached scene node is falling, which means that
		//! there is no blocking wall from the scene node in the direction of
		//! the gravity.
		virtual bool isFalling() const;

		//! Sets the radius of the ellipsoid with which collision detection and
		//! response is done.
		virtual void setEllipsoidRadius(const core::vector3df& radius);

		//! Returns the radius of the ellipsoid with which the collision detection and
		//! response is done.
		virtual core::vector3df getEllipsoidRadius() const;

		//! Sets the gravity of the environment.
		virtual void setGravity(const core::vector3df& gravity);

		//! 'Jump' the animator, by adding a jump speed opposite to its gravity
		virtual void jump(f32 jumpSpeed);

		//! Should the Target react on collision ( default = true )
		virtual void setAnimateTarget ( bool enable );
		virtual bool getAnimateTarget () const;

		//! Returns current vector of gravity.
		virtual core::vector3df getGravity() const;

		//! Sets the translation of the ellipsoid for collision detection.
		virtual void setEllipsoidTranslation(const core::vector3df &translation);

		//! Returns the translation of the ellipsoid for collision detection.
		virtual core::vector3df getEllipsoidTranslation() const;

		//! Sets a triangle selector holding all triangles of the world with which
		//! the scene node may collide.
		virtual void setWorld(ITriangleSelector* newWorld);

		//! Returns the current triangle selector containing all triangles for
		//! collision detection.
		virtual ITriangleSelector* getWorld() const;

		//! animates a scene node
		virtual void animateNode(ISceneNode* node, u32 timeMs);

		//! Writes attributes of the scene node animator.
		virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;

		//! Reads attributes of the scene node animator.
		virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);

		//! Returns type of the scene node animator
		virtual ESCENE_NODE_ANIMATOR_TYPE getType() const { return ESNAT_COLLISION_RESPONSE; }

		//! Creates a clone of this animator.
		/** Please note that you will have to drop
		(IReferenceCounted::drop()) the returned pointer after calling
		this. */
		virtual ISceneNodeAnimator* createClone(ISceneNode* node, ISceneManager* newManager=0);

		//! Set the single node that this animator will act on.
		virtual void setTargetNode(ISceneNode * node) { setNode(node); }

		//! Gets the single node that this animator is acting on.
		virtual ISceneNode* getTargetNode(void) const { return Object; }

		//! Returns true if a collision occurred during the last animateNode()
		virtual bool collisionOccurred() const { return CollisionOccurred; }

		//! Returns the last point of collision.
		virtual const core::vector3df & getCollisionPoint() const { return CollisionPoint; }

		//! Returns the last triangle that caused a collision.
		virtual const core::triangle3df & getCollisionTriangle() const { return CollisionTriangle; }

		virtual const core::vector3df & getCollisionResultPosition(void) const { return CollisionResultPosition; }

		virtual ISceneNode* getCollisionNode(void) const { return CollisionNode; }

      void setVelocity(const core::vector3df& v);
      const core::vector3df getActualVelocity() const;
      void setActualVelocity(const core::vector3df& v);

		//! Sets a callback interface which will be called if a collision occurs.
		/** \param callback: collision callback handler that will be called when a collision
		occurs. Set this to 0 to disable the callback.
		*/
		virtual void setCollisionCallback(ICollisionCallback* callback);

	private:
		bool AnimateCameraTarget;
		ICollisionCallback* CollisionCallback;
		ISceneNode * CollisionNode;
		bool CollisionOccurred;
		core::vector3df CollisionPoint;
		core::vector3df CollisionResultPosition;
		core::triangle3df CollisionTriangle;
		bool Falling;
		core::vector3df FallingVelocity; // In the direction of Gravity.
		bool FirstUpdate;
		core::vector3df Gravity;
		bool IsCamera;
		core::vector3df LastPosition;
		u32 LastTime;
      core::vector3df MovementVelocity;
		ISceneNode* Object;
		core::vector3df Radius;
		core::triangle3df RefTriangle;
		ISceneManager* SceneManager;
		void setNode(ISceneNode* node);
		f32 SlidingSpeed;
		core::vector3df Translation;
		ITriangleSelector* World;
};

#endif /* MOBILE_ENTITY_ANIMATOR_H_ */
