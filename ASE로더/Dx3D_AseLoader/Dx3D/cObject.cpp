#include "stdafx.h"
#include "cObject.h"


cObject::cObject()
	: m_nRefCount(1)
{
	g_pObjectManager->AddObject(this);
}


cObject::~cObject()
{
	if (m_nRefCount <= 0)
		g_pObjectManager->RemoveObject(this);
	else
		assert(false && "Release를 이용해서 객체를 해제하세요.");
}

void cObject::AddRef()
{
	++m_nRefCount;
	g_pAutoReleasePool->AddObject(this);
}

void cObject::Release()
{
	--m_nRefCount;

	if (m_nRefCount <= 0)
	{
		delete this;
	}
}