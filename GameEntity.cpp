#include "GameEntity.h"
#include "GameWorld.h"
#include "GLMath.h"
#include <cassert>
#include <cmath>

//#define GAME_ENTITY_SHOW_FIELD_SPHERE

#ifdef GAME_ENTITY_SHOW_FIELD_SPHERE
#include <glut.h>
#endif

GameEntity::GameEntity(GameWorld* pWorld)
: m_bounding_radius(1.8)
, m_is_tagged(false)
, m_pWorld(pWorld)
, m_typeId(0)
, m_iZoneId(ZONE_LAND)
, m_bMarkedForDestruction(false)
, m_Height2WidthRatio(1)
{
	if(m_iZoneId==ZONE_LAND)
	{
		m_position.y=m_pWorld->GetEnvHeight(m_position.x, m_position.z);
	}
}


GameEntity::~GameEntity()
{
	AgentRoleGroup::iterator pos_role;
	for(pos_role=m_roles.begin(); pos_role != m_roles.end(); ++pos_role)
	{
		if(pos_role->second != NULL)
		{
			delete pos_role->second;
		}
	}
	m_roles.clear();
}

void GameEntity::set_position(const GLVector& position)
{
	if(m_iZoneId==ZONE_LAND)
	{
		m_position=position;
		double new_y=m_pWorld->GetEnvHeight(position.x, position.z);
		m_position.y=new_y;
	}
	else
	{
		m_position=position; 
	}
}

bool GameEntity::CollideWith(const GameEntity* rhs, double offset) const
{
	double center_distance=(rhs->get_position() - this->get_position()).length();
	double radius_sum= rhs->get_bounding_radius() + this->get_bounding_radius();

	if(center_distance < radius_sum - offset)
	{
		return true;
	}

	return false;
}

void GameEntity::Update(const long &lElapsedTicks)
{

}

bool GameEntity::IsPenetratable(GameEntity* pAgent) const
{
	return false;
}

void GameEntity::EnforceNonPenetration(GameEntity* pAgent)
{
	assert(pAgent != this);

	if(this->IsPenetratable(pAgent))
	{
		return;
	}

	GLVector vTo=pAgent->get_position() - this->get_position();
	double distance=vTo.length();
	double overlapping_distance=pAgent->get_bounding_radius() + m_bounding_radius - distance;
	if(overlapping_distance > 0)
	{
		if(distance==0)
		{
			distance=glMath.Epsilon();
		}
		pAgent->set_position(pAgent->get_position()+vTo * overlapping_distance / distance);
	}
}

void GameEntity::UpdateRoleAction(const long& lElapsedTicks)
{
	AgentRoleGroup::iterator pos_role;
	for(pos_role=m_roles.begin(); pos_role != m_roles.end(); ++pos_role)
	{
		if(pos_role->second != NULL)
		{
			pos_role->second->Update(lElapsedTicks);
		}
	}
}

void GameEntity::RemoveRole(std::string role_name)
{
	AgentRoleGroup::iterator pos_role=m_roles.find(role_name);
	if(pos_role!=m_roles.end())
	{
		if(pos_role->second != NULL)
		{
			delete pos_role->second;
			m_roles.erase(pos_role);
		}
	}
}

void GameEntity::AddRole(std::string role_name, GLRole* pRole)
{
	AgentRoleGroup::iterator pos_role=m_roles.find(role_name);
	if(pos_role != m_roles.end())
	{
		delete pos_role->second;
		pos_role->second=pRole;
	}
	else
	{
		m_roles[role_name]=pRole;
	}
}