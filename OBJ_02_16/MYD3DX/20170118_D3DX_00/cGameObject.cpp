#include "stdafx.h"
#include "cGameObject.h"


cGameObject::cGameObject()
	: m_vLocalTranslation(0, 0, 0)
	, m_fRotXAngle(0)
	, m_fRotXAngleSpeed(0)
	, m_fRotYAngle(0)
	, m_fRotYAngleSpeed(0)
	, m_fRotZAngle(0)
	, m_fRotZAngleSpeed(0)
	, m_bAnimation(false)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cGameObject::~cGameObject()
{
}

void cGameObject::Update(D3DXMATRIXA16* pParentWorldTM /*= NULL*/)
{
	D3DXMATRIXA16 matT, matRotX, matRotY, matRotZ, matTI;

	if (m_bAnimation)
	{
		m_fRotXAngle += m_fRotXAngleSpeed;
		m_fRotYAngle += m_fRotYAngleSpeed;
		m_fRotZAngle += m_fRotZAngleSpeed;
	}
	else
	{
		m_fRotXAngle = 0;
		m_fRotYAngle = 0;
		m_fRotZAngle = 0;
	}

	if (m_fRotXAngle < -D3DX_PI * 0.25f)
	{
		m_fRotXAngleSpeed *= -1;
		m_fRotXAngle = -D3DX_PI * 0.25f;
	}
	else if (m_fRotXAngle > D3DX_PI * 0.25f)
	{
		m_fRotXAngleSpeed *= -1;
		m_fRotXAngle = D3DX_PI * 0.25f;
	}

	if (m_fRotYAngle < -D3DX_PI * 0.25f)
	{
		m_fRotYAngleSpeed *= -1;
		m_fRotYAngle = -D3DX_PI * 0.25f;
	}
	else if (m_fRotYAngle > D3DX_PI * 0.25f)
	{
		m_fRotYAngleSpeed *= -1;
		m_fRotYAngle = D3DX_PI * 0.25f;
	}

	if (m_fRotZAngle < -D3DX_PI * 0.25f)
	{
		m_fRotZAngleSpeed *= -1;
		m_fRotZAngle = -D3DX_PI * 0.25f;
	}
	else if (m_fRotZAngle > D3DX_PI * 0.25f)
	{
		m_fRotZAngleSpeed *= -1;
		m_fRotZAngle = D3DX_PI * 0.25f;
	}

	D3DXMatrixTranslation(&matT, m_vLocalTranslation.x,
		m_vLocalTranslation.y, m_vLocalTranslation.z);
	D3DXMatrixRotationX(&matRotX, m_fRotXAngle);
	D3DXMatrixRotationY(&matRotY, m_fRotYAngle);
	D3DXMatrixRotationZ(&matRotZ, m_fRotZAngle);
	D3DXMatrixTranslation(&matTI, -m_vLocalTranslation.x,
		-m_vLocalTranslation.y, -m_vLocalTranslation.z);

	m_matWorld = matT * matRotX * matRotY * matRotZ * matTI;

	if (pParentWorldTM)
		m_matWorld *= *pParentWorldTM;
}

void cGameObject::Render()
{

}
