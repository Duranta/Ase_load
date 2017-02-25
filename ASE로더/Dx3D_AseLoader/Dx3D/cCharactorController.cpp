#include "StdAfx.h"
#include "cCharactorController.h"


cCharactorController::cCharactorController(void)
	: m_vPosition(0, 0, 10)
	, m_fRotX(0.0f)
	, m_fRotY(0.0f)
	, m_fRotZ(0.0f)
	, m_fSpeed(0.5f)
{
}


cCharactorController::~cCharactorController(void)
{
}

void cCharactorController::Update(iMap* pMap)
{
	if (GetKeyState('A') & 0x8000)
	{
		m_fRotY -= 0.1f;
	}
	else if (GetKeyState('D') & 0x8000)
	{
		m_fRotY += 0.1f;
	}

	if (GetKeyState(VK_UP) & 0x8000)
	{
		m_fRotX -= 0.1f;
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		m_fRotX += 0.1f;
	}

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_fRotZ -= 0.1f;
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_fRotZ += 0.1f;
	}

	D3DXVECTOR3 vDir(0, 0, 1);
	D3DXMATRIXA16 matRotX, matRotY, matRotZ;
	D3DXMatrixRotationX(&matRotX, m_fRotX);
	D3DXVec3TransformNormal(&vDir, &vDir, &matRotX);
	D3DXMatrixRotationY(&matRotY, m_fRotY);
	D3DXVec3TransformNormal(&vDir, &vDir, &matRotY);
	D3DXMatrixRotationZ(&matRotZ, m_fRotZ);
	D3DXVec3TransformNormal(&vDir, &vDir, &matRotZ);

	D3DXVECTOR3 p = m_vPosition;

	if (GetKeyState('W') & 0x8000)
	{
		p = p + vDir * m_fSpeed;
	}
	else if (GetKeyState('S') & 0x8000)
	{
		p = m_vPosition - vDir * m_fSpeed;
	}

	if (pMap)
	{
		if (pMap->GetHeight(p.x, p.y, p.z))
		{
			m_vPosition = p;
		}
	}

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matRotX * matRotY * matRotZ * matT;

	D3DXVECTOR3 lightPos = m_vPosition;
	lightPos.y += 5.0f;
	D3DLIGHT9 light = InitSpotLight(&lightPos, &vDir, &WHITE);
	g_pD3DDevice->SetLight(3, &light);
	g_pD3DDevice->LightEnable(3, true);
}