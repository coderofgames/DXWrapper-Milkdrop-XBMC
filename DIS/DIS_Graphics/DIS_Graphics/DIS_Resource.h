#ifndef DIS_RESOURCE_H
#define DIS_RESOURCE_H

class BaseResource
{
public:

	BaseResource()
	{
		m_resourceType = 0;
		m_pool = 0;
		m_ok = false;
	}
	~BaseResource()
	{
	}

	bool	IsOk() { return m_ok; }
	int		GetPool() { return m_pool; }
	int		GetResourceType() { return m_resourceType; }

	int		m_resourceType;
	int		m_pool;
	bool	m_ok;
};

#endif