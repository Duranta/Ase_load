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
	bool				m_bAnimation;

public:
	cGameObject();
	~cGameObject();

	virtual void Update(D3DXMATRIXA16* pParentWorldTM = NULL);
	virtual void Render();

	void SetLocalTranslation(D3DXVECTOR3& v) { m_vLocalTranslation = v; }
	void SetXAngleSpeed(float f) { m_fRotXAngleSpeed = f; }
	void SetYAngleSpeed(float f) { m_fRotYAngleSpeed = f; }
	void SetZAngleSpeed(float f) { m_fRotZAngleSpeed = f; }
	void SetAnimation(bool b) { m_bAnimation = b; }
};

