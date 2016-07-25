#include "DIS_ResourceTypes.h"

#include <vector>
using std::vector;

class ResourceManagerImpl : public DIS_ResourceManager
{
public:

	ResourceManagerImpl();
	~ResourceManagerImpl();

	void AddResource(LPRESOURCE resource);
	void ReleaseResource(int resID);
	
	vector< LPRESOURCE > m_resources;
};



DIS_ResourceManager* CreateResourceManager( DIS_ResourceManager* resourceManager )
{
	if( resourceManager )
	{
		delete resourceManager;
		resourceManager = NULL;
	}

	resourceManager = new ResourceManagerImpl();

	return resourceManager;
}


ResourceManagerImpl::ResourceManagerImpl()
{
}

ResourceManagerImpl ::~ResourceManagerImpl () 
{
	for( int i = 0; i < m_resources.size(); i++ )
	{
		// this forces the object to release all 
		// its resources
		delete m_resources[i];
		m_resources[i] = NULL;
	}
	m_resources.clear();
}

void ResourceManagerImpl::AddResource(LPRESOURCE resource)
{
	resource->id = m_resources.size();
	m_resources.push_back(resource);
}

void ResourceManagerImpl::ReleaseResource(int resID)
{
	// if the user calls Release() on an object, 
	// this function will remove this instance
	// from the resource manager
	if( (resID < 0) || (resID > m_resources.size()) )
		return;

	if( m_resources[resID] )
	{
		//m_resources[resID]->Release();
		delete m_resources[resID];
		m_resources[resID] = NULL;
	}

	m_resources.erase( m_resources.begin() + resID );
}

