#pragma once
#include "iMap.h"

class cCharactorController : public cObject
{
private:
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3,	m_vPosition, Position);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorld, WorldTM);
	float			m_fRotX;
	float			m_fRotY;
	float			m_fRotZ;
	float			m_fSpeed;

public:
	cCharactorController(void);
	~cCharactorController(void);

	void Update(iMap* pMap);
};