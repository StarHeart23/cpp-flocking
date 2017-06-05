#include "GameWorld.h"
#include "GLMath.h"
#include <io.h>
#include <sstream>
#include <algorithm>
#include <cfloat>

GameWorld::GameWorld()
{
	
}

GameWorld::~GameWorld()
{
	RemoveAgents();
	RemoveObstacles();
}

double GameWorld::GetEnvHeight(double x, double z) const
{
	if(m_bShowFloor)
	{
		return 0;
	}
	else if(m_bShowTerrain)
	{
		return m_terrain.GetHeight(static_cast<int>(x), static_cast<int>(z));
	}
	else
	{
		return 0;
	}
}

double GameWorld::GetEnvWidth() const
{
	if(m_bShowFloor)
	{
		return m_floor.GetLength();
	}
	else if(m_bShowTerrain)
	{
		return m_terrain.GetWidth();
	}

	return 0;
}

double GameWorld::GetEnvLength() const
{
	if(m_bShowFloor)
	{
		return m_floor.GetLength();
	}
	else if(m_bShowTerrain)
	{
		return m_terrain.GetLength();
	}

	return 0;
}

void GameWorld::RemoveAgents()
{
	AgentGroup::iterator pos_agent;
	for(pos_agent=m_agents.begin(); pos_agent != m_agents.end(); ++pos_agent)
	{
		delete *pos_agent;
	}
	m_agents.clear();
	m_mapped_agents.clear();
}

void GameWorld::AddObstacle(Obstacle* pAgent)
{
	if(pAgent == NULL)
	{
		return;
	}
	ObstacleGroup::iterator pos_obs=std::find(m_obs.begin(), m_obs.end(), pAgent);
	if(pos_obs != m_obs.end())
	{
		return;
	}
	m_obs.push_back(pAgent);
	if(m_bShowFloor)
	{
		m_floor.GetObstacleQuadTree().AddAgent(pAgent);
	}
	if(m_bShowTerrain)
	{
		m_terrain.GetObstacleQuadTree().AddAgent(pAgent);
	}
}

void GameWorld::AddAgent(Vehicle* pAgent)
{
	if(pAgent == NULL)
	{
		return;
	}
	AgentGroup::iterator pos_agent=std::find(m_agents.begin(), m_agents.end(), pAgent);
	if(pos_agent != m_agents.end())
	{
		return;
	}
	m_agents.push_back(pAgent);
}

void GameWorld::UpdateObstacles(const long& lElapsedTicks)
{
	ObstacleGroup::iterator pos_obs;
	for(pos_obs=m_obs.begin(); pos_obs != m_obs.end(); ++pos_obs)
	{
		(*pos_obs)->Update(lElapsedTicks);
	}
}

void GameWorld::UpdateAgents(const long& lElapsedTicks)
{
	AgentGroup::iterator pos_agent;
	for(pos_agent=m_agents.begin(); pos_agent != m_agents.end(); ++pos_agent)
	{
		(*pos_agent)->Update(lElapsedTicks);
		//GLVector agent_position=(*pos_agent)->get_position();
	}
}

void GameWorld::GetNeighborObstacles(const GameEntity* pAgent, std::set<GameEntity*>& obs, double radius)
{
	m_floor.GetObstacleQuadTree().GetNeighbors(pAgent, obs, radius);
}

void GameWorld::RemoveObstacles()
{
	ObstacleGroup::iterator pos_obs;
	for(pos_obs=m_obs.begin(); pos_obs != m_obs.end(); ++pos_obs)
	{
		delete *pos_obs;
	}
	m_obs.clear();
	m_mapped_obstacles.clear();

	m_floor.ResetQuadTree();
}

void GameWorld::WorldBound(GameEntity* pAgent)
{
	GLVector pos=pAgent->get_position();
	double x=pos.x;
	double z=pos.z;

	double full_length=m_floor.GetLength();
	double half_length=full_length / 2.0;
	if(x < -half_length)
	{
		double dx=-half_length - x;
		x+=dx * 2;
	}
	else if(x > half_length)
	{
		double dx=half_length - x;
		x+=dx * 2;
	}
	if(z < -half_length)
	{
		double dz=-half_length - z;
		z+=dz * 2;
	}
	else if(z > half_length)
	{
		double dz=half_length - z;
		z+=dz * 2;
	}

	pos.x=x;
	pos.z=z;
	//pos.y=this->GetEnvHeight(x, z);
	pAgent->set_position(pos);
}

void GameWorld::WorldWrap(GameEntity* pAgent)
{
	GLVector pos=pAgent->get_position();
	double x=pos.x;
	double z=pos.z;

	double full_length=m_floor.GetLength();
	double half_length=full_length / 2.0;
	if(x < -half_length)
	{
		x+=full_length;
	}
	else if(x > half_length)
	{
		x-=full_length;
	}
	if(z < -half_length)
	{
		z+=full_length;
	}
	else if(z > half_length)
	{
		z-=full_length;
	}

	pos.x=x;
	pos.z=z;
	//pos.y=this->GetEnvHeight(x, z);
	pAgent->set_position(pos);
}

void GameWorld::RegisterAgent(std::string agent_id, Vehicle* pAgent)
{
	MappedAgentGroup::iterator pos_agent=m_mapped_agents.find(agent_id);
	if(pos_agent != m_mapped_agents.end())
	{
		AgentGroup::iterator pos=std::find(m_agents.begin(), m_agents.end(), pos_agent->second);
		if(pos != m_agents.end())
		{
			delete (*pos);
			m_agents.erase(pos);
		}
	}
	m_mapped_agents[agent_id]=pAgent;
	m_agents.push_back(pAgent);
}

void GameWorld::RegisterObstacle(std::string obstacle_id, Obstacle* pObs)
{
	MappedObstacleGroup::iterator pos_obstacle=m_mapped_obstacles.find(obstacle_id);
	if(pos_obstacle != m_mapped_obstacles.end())
	{
		ObstacleGroup::iterator pos=std::find(m_obs.begin(), m_obs.end(), pos_obstacle->second);
		if(pos != m_obs.end())
		{
			delete (*pos);
			m_obs.erase(pos);
		}
	}
	m_mapped_obstacles[obstacle_id]=pObs;
	m_obs.push_back(pObs);
}

Vehicle* GameWorld::GetRegisteredAgent(std::string agent_id)
{
	std::map<std::string, Vehicle*>::iterator pos_mapped_agent=m_mapped_agents.find(agent_id);
	if(pos_mapped_agent != m_mapped_agents.end())
	{
		return pos_mapped_agent->second;
	}

	return NULL;
}

Obstacle* GameWorld::GetRegisteredObstacle(std::string obs_id)
{
	std::map<std::string, Obstacle*>::iterator pos_mapped_obstacle=m_mapped_obstacles.find(obs_id);
	if(pos_mapped_obstacle != m_mapped_obstacles.end())
	{
		return pos_mapped_obstacle->second;
	}

	return NULL;
}

std::string GameWorld::GetRegisteredAgentGroupStatus() const
{
	std::ostringstream oss;
	oss << "<?xml version=\"1.0\"?>\n";
	oss << "<root>\n";

	MappedAgentGroup::const_iterator pos_mapped_agent;
	for(pos_mapped_agent=m_mapped_agents.begin(); pos_mapped_agent != m_mapped_agents.end(); ++pos_mapped_agent)
	{
		std::string agent_id=pos_mapped_agent->first;
		Vehicle* pAgent=pos_mapped_agent->second;
		const GLVector& position=pAgent->get_position();
		oss << "<agent_status agent_id=\"" << agent_id << "\" p_x=\"" << position.x << "\" p_y=\"" << position.y << "\" p_z=\"" << position.z 
			<< "\" />\n";
	}
	MappedObstacleGroup::const_iterator pos_mapped_obstacle;
	for(pos_mapped_obstacle=m_mapped_obstacles.begin(); pos_mapped_obstacle != m_mapped_obstacles.end(); ++pos_mapped_obstacle)
	{
		std::string obstacle_id=pos_mapped_obstacle->first;
		Obstacle* pObs=pos_mapped_obstacle->second;
		const GLVector& position=pObs->get_position();
		oss << "<agent_status agent_id=\"" << obstacle_id << "\" p_x=\"" << position.x << "\" p_y=\"" << position.y << "\" p_z=\"" << position.z 
			<< "\" />\n";
	}
	oss << "<current_state name=\"" << m_pState->GetStateName() << "\" />\n";

	oss << "</root>\n";
	return oss.str();
}