#pragma once
#include "cObject.h"

class cGameObject :	public cObject
{
protected:
	D3DXMATRIXA16		m_matWorld;
	D3DXVECTOR3			m_vLocalTranslation;
	float				m_fRotXAngle;
	float				m_fRotXAngleSpeed;
	float				m_fRotYAngle;
	float				m_fRotYAngleSpeed;
	float				m_fRotZAngle;
	float				m_fRotZAngleSpeed;

	//D3DXVECTOR3			m_vPrevPosition;
	//SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vDirection, Direction);
	//SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vPosition, Position);

public:
	cGameObject();
	virtual ~cGameObject();

	virtual void Update(D3DXMATRIXA16* pParentWorldTM = NULL);
	virtual void Render();

	void SetXAngleSpeed(float fRotAngleSpeed);
	void SetYAngleSpeed(float fRotAngleSpeed);
	void SetZAngleSpeed(float fRotAngleSpeed);
	void SetLocalTranslation(D3DXVECTOR3& v);
};