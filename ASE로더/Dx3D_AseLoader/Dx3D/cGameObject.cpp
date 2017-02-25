#include "stdafx.h"
#include "cGameObject.h"


cGameObject::cGameObject()
	: m_vLocalTranslation(0, 0, 0)
	, m_fRotXAngle(0)
	, m_fRotXAngleSpeed(0)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cGameObject::~cGameObject()
{
}

void cGameObject::Update(D3DXMATRIXA16* pParentWorldTM /*= NULL*/)
{
	D3DXMATRIXA16 matT, matR, matTT;

	m_fRotXAngle += m_fRotXAngleSpeed;
	if (m_fRotXAngle < -D3DX_PI / 4.0f)
	{
		m_fRotXAngleSpeed *= -1;
		m_fRotXAngle = -D3DX_PI / 4.0f;
	}

	if (m_fRotXAngle > D3DX_PI / 4.0f)
	{
		m_fRotXAngleSpeed *= -1;
		m_fRotXAngle = D3DX_PI / 4.0f;
	}

	D3DXMatrixTranslation(&matT, m_vLocalTranslation.x, m_vLocalTranslation.y, m_vLocalTranslation.z);
	D3DXMatrixRotationX(&matR, m_fRotXAngle);
	D3DXMatrixTranslation(&matTT, -m_vLocalTranslation.x, -m_vLocalTranslation.y, -m_vLocalTranslation.z);

	m_matWorld = matT * matR * matTT;

	if (pParentWorldTM)
	{
		m_matWorld *= *pParentWorldTM;
	}
}

void cGameObject::Render()
{

}

void cGameObject::SetXAngleSpeed(float fRotAngleSpeed)
{
	m_fRotXAngleSpeed = fRotAngleSpeed;
}

void cGameObject::SetYAngleSpeed(float fRotAngleSpeed)
{
	m_fRotYAngleSpeed = fRotAngleSpeed;
}

void cGameObject::SetZAngleSpeed(float fRotAngleSpeed)
{
	m_fRotZAngleSpeed = fRotAngleSpeed;
}

void cGameObject::SetLocalTranslation(D3DXVECTOR3& v)
{
	m_vLocalTranslation = v;
}