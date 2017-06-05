#ifndef _H_VEHICLE_H
#define _H_VEHICLE_H

#include "MovingEntity.h"
#include "GLSteering_Composite.h"
#include <string>

class Vehicle : public MovingEntity
{
public:
	Vehicle(GameWorld* pWorld);
	virtual ~Vehicle();

public:
	virtual void Update(const long& lElapsedTicks);

public:
	GLSteering* GetSteering(std::string sname);
	void AddSteering(const char* sname, GLSteering* pSteering);
	void RemoveSteering(const char* sname);

public:
	GLVector LocalToWorldCoordinate(const GLVector& vLocalTarget) const;
	GLVector WorldToLocalCoordinate(const GLVector& vWorldTarget) const;
	GLVector LocalToWorldVector(const GLVector& vLocalTarget) const;

protected:
	GLSteering_Composite* m_pSteering;
public:
	GLSteering_Composite* GetSteering() { return m_pSteering; }
	
public:
	virtual bool IsPenetratable(GameEntity* pAgent) const;

protected:
	double m_dVisibleDistance;
public:
	double GetVisibleDistance() const { return m_dVisibleDistance; }
	void SetVisibleDistance(double distance) { m_dVisibleDistance=distance; }

public:
	void tag_neighbors(double r);
	void tag_obstacles(double scan_radius);

};
#endif