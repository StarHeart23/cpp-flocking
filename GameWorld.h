#ifndef _H_GAME_WORLD_H
#define _H_GAME_WORLD_H

#include <vector>
#include <set>
#include <map>
#include <string>
#include "GameEntity.h"
#include "GLFloor.h"
#include "GLPath.h"
#include "Vehicle.h"
#include "Obstacle.h"

typedef std::map<std::string, Vehicle*> MappedAgentGroup;
typedef std::map<std::string, Obstacle*> MappedObstacleGroup;
typedef std::vector<Vehicle*> AgentGroup;
typedef std::vector<Obstacle*> ObstacleGroup;

class GameWorld
{
public:
	GameWorld();
	virtual ~GameWorld();


public:
	void WorldWrap(GameEntity* pAgent);
	void WorldBound(GameEntity* pAgent);


protected:
	AgentGroup m_agents;
	MappedAgentGroup m_mapped_agents;
	ObstacleGroup m_obs;
	MappedObstacleGroup m_mapped_obstacles;


public:
	GLFloor& GetFloor() { return m_floor; }

public:
	const AgentGroup& GetConstAgents() { return m_agents; }
	AgentGroup& GetMutableAgents() { return m_agents; }
	const ObstacleGroup& GetConstObstacles() const { return m_obs; }
	void UpdateObstacles(const long& lElapsedTicks);
	void UpdateAgents(const long& lElapsedTicks);
	void GetNeighborObstacles(const GameEntity* pAgent, std::set<GameEntity*>& obs, double radius);
	void AddObstacle(Obstacle* pAgent);
	void AddAgent(Vehicle* pAgent);
	void RemoveAgents();
	void RemoveObstacles();
	void RegisterAgent(std::string agent_id, Vehicle* pAgent);
	void RegisterObstacle(std::string obs_id, Obstacle* pObs);
	Vehicle* GetRegisteredAgent(std::string agent_id);
	Obstacle* GetRegisteredObstacle(std::string obs_id);
	std::string GetRegisteredAgentGroupStatus() const;


protected:
	GLPath m_path;
public:
	GLPath& GetPath() { return m_path; }


public:
	double GetEnvHeight(double x, double z) const;
	double GetEnvWidth() const;
	double GetEnvLength() const;

protected:
	GLFloor m_floor;
};

#endif