#include "GLRole_Predator.h"
#include "GameEntity.h"
#include "GameWorld.h"
#include <cfloat>

GLRole_Predator::GLRole_Predator(GameEntity* pAgent)
: GLRole(pAgent)
, m_pPursuitSteeringHandler(NULL)
{

}

GLRole_Predator::~GLRole_Predator()
{

}
bool GLRole_Predator::IsPenetratable(int TypeId) const
{
	std::set<int>::const_iterator pos=m_prey_ids.find(TypeId);
	if(pos != m_prey_ids.end())
	{
		return true;
	}
	return false;
}

void GLRole_Predator::Update(const long& lElapsedTicks)
{
	AgentGroup& agents=m_pAgent->GetWorld()->GetMutableAgents();
	AgentGroup::iterator pos_agent;
	Vehicle* pAgent=NULL;

	double closest_distance=DBL_MAX;
	Vehicle* current_prey=NULL;
	GLVector predator_position=m_pAgent->get_position();

	for(pos_agent=agents.begin(); pos_agent!=agents.end(); ++pos_agent)
	{
		pAgent=(*pos_agent);

		if(m_pAgent == pAgent)
		{
			continue;
		}

		if(!pAgent->InTheSameZone(m_pAgent))
		{
			continue;
		}

		if(m_prey_ids.find(pAgent->GetTypeId())!=m_prey_ids.end())
		{
			if(m_pPursuitSteeringHandler != NULL)
			{
				double distance=(pAgent->get_position() - predator_position).length();
				if(current_prey == NULL)
				{
					current_prey=pAgent;	
					closest_distance=distance;
				}
				else if(closest_distance > distance)
				{
					current_prey=pAgent;
					closest_distance=distance;
				}
			}
		}
	}

	if(m_pPursuitSteeringHandler != NULL)
	{
		m_pPursuitSteeringHandler->SetTarget(current_prey);
	}
}
