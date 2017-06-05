#ifndef _H_OBSTACLE_H
#define _H_OBSTACLE_H

#include "GameEntity.h"

class Obstacle : public GameEntity
{
public:
	Obstacle(GameWorld* pWorld);
	virtual ~Obstacle() { }

public:
	virtual void Update(const long& lElapsedTicks) { }
};

#endif 