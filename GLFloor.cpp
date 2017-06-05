#include "GLFloor.h"
#include "GameWorld.h"
#include <iostream>

GLFloor::GLFloor()
: m_pWorld(NULL)
{
	
}

GLFloor::~GLFloor()
{
	
}

double GLFloor::GetLength() const
{
	GLVector disp=p1 - p2;
	return disp.length();
}

void GLFloor::CreateHorizontalPlane(double length)
{
	int half_length=static_cast<int>(length / 2);
	p1=GLVector(-half_length, 0, half_length);
	p2=GLVector(half_length, 0, half_length);
	p3=GLVector(half_length, 0, -half_length);
	p4=GLVector(-half_length, 0, -half_length);
	calculate_normal();

	m_obsQuadTree.MakeQuadTree(5, -half_length, -half_length, half_length, half_length);
}

void GLFloor::calculate_normal()
{
	GLVector v1=p2 - p1;
	GLVector v2=p3 - p1;

	GLVector n=v1.cross(v2);
	m_normal=n.normalize();

	m_distance_to_origin=p1.dot(m_normal);
}
