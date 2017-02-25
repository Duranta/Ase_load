#include "stdafx.h"
#include "cObjectManager.h"


cObjectManager::cObjectManager()
{
}


cObjectManager::~cObjectManager()
{
}

void cObjectManager::AddObject(cObject* pObject)
{
	m_setObject.insert(pObject);
}

void cObjectManager::RemoveObject(cObject* pObject)
{
	m_setObject.erase(pObject);
}

void cObjectManager::Destroy()
{
	g_pAutoReleasePool->Drain();
	assert(m_setObject.empty() && "오브젝트 매니져왈 : 삭제 안된 객체 있다.");
}
