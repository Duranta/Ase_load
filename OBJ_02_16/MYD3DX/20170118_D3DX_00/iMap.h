#pragma once
#include "stdafx.h"

interface iMap
{
public:
	virtual void Load(char* szFullPath, D3DXMATRIXA16* pMat) PURE;
	virtual bool GetHeight(IN const float& x, OUT float& y, IN const float& z) PURE;
};