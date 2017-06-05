#ifndef _H_GL_PREDATOR_ROLE_H
#define _H_GL_PREDATOR_ROLE_H

#include "GLVector.h"
#include "GLRole.h"
#include "GLSteering_Pursuit.h"
#include <set>

class GameEntity;

class GLRole_Predator : public GLRole
{
public:
	GLRole_Predator(GameEntity* pAgent);
	virtual ~GLRole_Predator();

public:
	virtual void Update(const long& lElapsedTicks);
	virtual bool IsPenetratable(int TypeId) const;

public:
	void AddPreyId(int id) { m_prey_ids.insert(id); }
	void SetPursuitSteeringHandler(GLSteering_Pursuit* pPursuitSteeringHandler) { m_pPursuitSteeringHandler=pPursuitSteeringHandler; }

protected:
	std::set<int> m_prey_ids;
	GLSteering_Pursuit* m_pPursuitSteeringHandler;
};
#endif