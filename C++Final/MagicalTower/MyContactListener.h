#pragma once

#include <Box2D/Box2D.h>
#include "Arrow.h"
#include "Entity.h"
#include "Character.h"
#include <iostream>
#include "Item.h"
#include "ManaOrb.h"
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
			//arrow arrow collision do nothing
			if (static_cast<Entity*>(bodyUserDataA)->getEntityType() == EntityEnum::PROJECTILE && static_cast<Entity*>(bodyUserDataB)->getEntityType() == EntityEnum::PROJECTILE)
			{
				return;
			}
			//arrow character collision
			if (static_cast<Entity*>(bodyUserDataA)->getEntityType() == EntityEnum::PROJECTILE && static_cast<Entity*>(bodyUserDataB)->getEntityType() == EntityEnum::CHARACTER)
			{
				static_cast<Arrow*>(bodyUserDataA)->startContact();
				if (!static_cast<Character*>(bodyUserDataB)->getManaShield())
				{
					static_cast<Character*>(bodyUserDataB)->kill();
				}
				
			}
			//character arrow collision
			if (static_cast<Entity*>(bodyUserDataA)->getEntityType() == EntityEnum::CHARACTER && static_cast<Entity*>(bodyUserDataB)->getEntityType() == EntityEnum::PROJECTILE)
			{
				if (!static_cast<Character*>(bodyUserDataA)->getManaShield())
				{
					static_cast<Character*>(bodyUserDataA)->kill();
				}
				static_cast<Arrow*>(bodyUserDataB)->startContact();
			}
			//character Item collision
			if (static_cast<Entity*>(bodyUserDataA)->getEntityType() == EntityEnum::ITEM && static_cast<Entity*>(bodyUserDataB)->getEntityType() == EntityEnum::CHARACTER)
			{
				if (static_cast<Item*>(bodyUserDataA)->getItemType() == ItemEnum::MANA_ORB)
				{
					static_cast<ManaOrb*>(bodyUserDataA)->kill();
					static_cast<Character*>(bodyUserDataB)->_mana += static_cast<ManaOrb*>(bodyUserDataA)->getMana();

				}
			}//Item Character collision

			if (static_cast<Entity*>(bodyUserDataA)->getEntityType() == EntityEnum::CHARACTER && static_cast<Entity*>(bodyUserDataB)->getEntityType() == EntityEnum::ITEM)
			{
				if (static_cast<Item*>(bodyUserDataB)->getItemType() == ItemEnum::MANA_ORB)
				{
					static_cast<ManaOrb*>(bodyUserDataB)->kill();
					static_cast<Character*>(bodyUserDataA)->_mana += static_cast<ManaOrb*>(bodyUserDataB)->getMana();
				}
			}
		}
		if (bodyUserDataA)
		{
			if (static_cast<Entity*>(bodyUserDataA)->getEntityType() == EntityEnum::PROJECTILE)
			{
				static_cast<Arrow*>(bodyUserDataA)->startContact();
			}
		}
		if (bodyUserDataB)
		{
			if (static_cast<Entity*>(bodyUserDataB)->getEntityType() == EntityEnum::PROJECTILE)
			{
				static_cast<Arrow*>(bodyUserDataB)->startContact();
			}
		}
		//check if fixture A was the foot sensor
		void* fixtureUserData = contact->GetFixtureA()->GetUserData();

		if (fixtureUserData)
			if (static_cast<Entity*>(fixtureUserData)->getEntityType() == EntityEnum::CHARACTER)
			{
				static_cast<Character*>(fixtureUserData)->numFootContact++;
			}
		//check if fixture B was the foot sensor
		
		fixtureUserData = contact->GetFixtureB()->GetUserData();
		if (fixtureUserData)
			if (static_cast<Entity*>(fixtureUserData)->getEntityType() == EntityEnum::CHARACTER)
			{
				static_cast<Character*>(fixtureUserData)->numFootContact++;
			}
	}
	void EndContact(b2Contact* contact) {

		//check if fixture A was the foot sensor
		void* fixtureUserData = contact->GetFixtureA()->GetUserData();
		if (fixtureUserData)
			if (static_cast<Entity*>(fixtureUserData)->getEntityType() == EntityEnum::CHARACTER)
			{
				static_cast<Character*>(fixtureUserData)->numFootContact--;
			}
		//check if fixture B was the foot sensor
		
		fixtureUserData = contact->GetFixtureB()->GetUserData();
		if (fixtureUserData)
		if (static_cast<Entity*>(fixtureUserData)->getEntityType() == EntityEnum::CHARACTER)
		{
			static_cast<Character*>(fixtureUserData)->numFootContact--;
		}
	}
};

