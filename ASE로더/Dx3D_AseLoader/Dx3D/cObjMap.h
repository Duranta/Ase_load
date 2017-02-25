#pragma once
#include "iMap.h"

class cObjMap :	public iMap, public cObject
{
protected:
	vector<D3DXVECTOR3> m_vecVertex;

public:
	cObjMap(void);
	~cObjMap(void);

	virtual void Load(char* szFullPath, D3DXMATRIXA16* pmat) override;
	virtual bool GetHeight(IN const float& x, OUT float& y, IN const float& z) override;
};