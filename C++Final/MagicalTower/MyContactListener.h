#pragma once

#include <Box2D/Box2D.h>
#include "Arrow.h"
#include "Entity.h"
#include "Character.h"

class MyContactListener : public b2ContactListener
{
public:
	MyContactListener();
	~MyContactListener();


	void BeginContact(b2Contact* contact) {



		//check if fixture A was a ball
		void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

		if (bodyUserDataA && bodyUserDataB)
		{
			if (static_cast<Entity*>(bodyUserDataA)->getEntityType() == EntityEnum::CHARACTER && static_cast<Entity*>(bodyUserDataB)->getEntityType() == EntityEnum::PROJECTILE)
			{
				printf("yolo\n");
				static_cast<Character*>(bodyUserDataA)->kill();
				static_cast<Arrow*>(bodyUserDataB)->startContact();
			}
			
			if (static_cast<Entity*>(bodyUserDataA)->getEntityType() == EntityEnum::PROJECTILE && static_cast<Entity*>(bodyUserDataB)->getEntityType() == EntityEnum::CHARACTER)
			{
				printf("yolo\n");
				static_cast<Arrow*>(bodyUserDataA)->startContact();
				static_cast<Character*>(bodyUserDataB)->kill();
			}
		}

		if (bodyUserDataA && bodyUserDataB)
		{
			if (static_cast<Entity*>(bodyUserDataB)->getEntityType() == EntityEnum::PROJECTILE && static_cast<Entity*>(bodyUserDataB)->getEntityType() == EntityEnum::PROJECTILE);
			{
				return;
			}
		}

		
		
		if (bodyUserDataA)
		{
			if (static_cast<Entity*>(bodyUserDataA)->getEntityType() == EntityEnum::PROJECTILE);
			{
				static_cast<Arrow*>(bodyUserDataA)->startContact();
			}
		}
		if (bodyUserDataB)
		{
			if (static_cast<Entity*>(bodyUserDataB)->getEntityType() == EntityEnum::PROJECTILE);
			{
				static_cast<Arrow*>(bodyUserDataB)->startContact();
			}
		}
 }
// 	void EndContact(b2Contact* contact) {
// 
// 		//check if fixture A was a ball
// 		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
// 		if (bodyUserData)
// 			static_cast<Arrow*>(bodyUserData)->endContact();
// 
// 		//check if fixture B was a ball
// 		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
// 		if (bodyUserData)
// 			static_cast<Arrow*>(bodyUserData)->endContact();
// 
// 	}
};

