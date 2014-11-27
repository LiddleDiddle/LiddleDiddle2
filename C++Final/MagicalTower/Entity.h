#pragma once


enum EntityEnum
{
	PROJECTILE,
	ITEM,
	CHARACTER
};

class Entity
{
public:
	virtual int getEntityType() = 0;
protected:
	int entityType;
};