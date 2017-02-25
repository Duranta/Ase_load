#pragma once
#include "iMap.h"

class cCharacterController : public cObject
{
private:
	D3DXMATRIXA16	m_matWorld;
	D3DXVECTOR3		m_vPosition;
	float			m_fRotY;
	float			m_fSpeed;

public:
	cCharacterController();
	~cCharacterController();

	void Update(iMap* pMap);
	D3DXMATRIXA16* GetWorldTM() { return &m_matWorld; }
	D3DXVECTOR3* GetPosition() { return &m_vPosition; }
};