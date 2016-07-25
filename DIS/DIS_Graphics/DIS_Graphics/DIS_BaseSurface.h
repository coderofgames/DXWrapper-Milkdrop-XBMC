#ifndef DIS_BASESURFACE_H
#define DIS_BASESURFACE_H

#include "DIS_Resource.h"

class BaseSurface : public BaseResource
{
public:

	BaseSurface()
	{
		m_format = 0;
	}
	
	~BaseSurface()
	{
	}

	int		GetFormat() { return m_format; }

	int		m_format;
};

#endif