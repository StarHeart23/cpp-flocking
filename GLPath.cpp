#include "GLPath.h"
#include <iostream>
#include "GLMath.h"
#include <cmath>


GLPathNode::GLPathNode()
: m_prev(NULL)
, m_next(NULL)
{
	
}

GLPathNode::~GLPathNode()
{
	if(m_next !=NULL)
	{
		delete m_next;
	}
	m_next=NULL;
	m_prev=NULL;
}

GLPath::GLPath()
: m_pHead(NULL)
, m_pTail(NULL)
, m_pCurrent(NULL)
, m_bLoop(false)
{
	
}

GLPath::~GLPath()
{
	DeletePath();
}

void GLPath::DeletePath()
{
	if(m_pHead != NULL)
	{
		delete  m_pHead;
	}
	m_pHead=NULL;
	m_pTail=NULL;
	m_pCurrent=NULL;
}

void GLPath::RandomCreate(int number_points, const GLVector &min_point, const GLVector &max_point)
{
	DeletePath();

	GLVector mid_point=(min_point + max_point) / 2;

	GLVector pt1=mid_point - min_point; 
	GLVector pt2=max_point - mid_point;

	pt1.x=std::abs(pt1.x);
	pt1.z=std::abs(pt1.z);
	pt2.x=std::abs(pt2.x);
	pt2.z=std::abs(pt2.z);

	double minx=pt1.x > pt2.x ? pt2.x : pt1.x;
	double minz=pt1.z > pt2.z ? pt2.z : pt1.z;

	double minr = minx > minz ? minz : minx;

	double sector=glMath.PI() * 2.0 / number_points;

	GLPathNode* pPrevNode=NULL;
	GLPathNode* pCurrentNode=NULL;

	for(int i=0; i<number_points; i++)
	{
		pCurrentNode=new GLPathNode;
		if(i==0)
		{
			m_pHead=pCurrentNode;
		}
		double radius=glMath.nextDouble(minr * 0.6, minr * 1.2);
		pCurrentNode->m_position=GLVector(radius * cos(i * sector), 0, radius * sin(i * sector)) + mid_point;
		pCurrentNode->m_prev=pPrevNode;
		pCurrentNode->m_next=NULL;

		if(pPrevNode != NULL)
		{
			pPrevNode->m_next=pCurrentNode;
		}
		pPrevNode=pCurrentNode;
	}
	m_pTail=pCurrentNode;
	m_pCurrent=m_pHead;
}

void GLPath::AddPoint(const GLVector& position)
{
	GLPathNode* pCurrentNode=new GLPathNode;
	pCurrentNode->m_position=position;
	pCurrentNode->m_prev=m_pTail;
	pCurrentNode->m_next=NULL;
	if(m_pHead==NULL)
	{
		m_pHead=pCurrentNode;
	}
	if(m_pTail != NULL)
	{
		m_pTail->m_next=pCurrentNode;
	}

	m_pTail=pCurrentNode;
}

bool GLPath::IsEnded() const
{
	if(m_pCurrent==m_pTail && m_bLoop==false)
	{
		return true;
	}
	return false;
}

GLVector GLPath::GetCurrent() const
{
	return m_pCurrent->m_position;
}

void GLPath::Next()
{
	if(m_pCurrent->m_next != NULL)
	{
		m_pCurrent=m_pCurrent->m_next;
	}
	else
	{
		if(m_bLoop)
		{
			m_pCurrent=m_pHead;
		}
	}
}
