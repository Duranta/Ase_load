#include "stdafx.h"
#include "cCharacterController.h"


cCharacterController::cCharacterController()
	: m_vPosition(0, 0, 0)
	, m_fRotY(0)
	, m_fSpeed(0.5f)
{
}


cCharacterController::~cCharacterController()
{
}

void cCharacterController::Update(iMap* pMap)
{
	if (GetKeyState('A') & 0x8000)
	{
		m_fRotY -= 0.1f;
	}
	else if (GetKeyState('D') & 0x8000)
	{
		m_fRotY += 0.1f;
	}

	D3DXMATRIXA16 matRotY;
	D3DXMatrixRotationY(&matRotY, m_fRotY);

	D3DXVECTOR3 vDir(0.0f, 0.0f, 1.0f);
	D3DXVec3TransformNormal(&vDir, &vDir, &matRotY);

	D3DXVECTOR3 pos;

	if (GetKeyState('W') & 0x8000)
	{
		pos = m_vPosition + vDir * m_fSpeed;
	}
	else if (GetKeyState('S') & 0x8000)
	{
		pos = m_vPosition - vDir * m_fSpeed;
	}

	if (pMap)
	{
		if (pMap->GetHeight(pos.x, pos.y, pos.z))
		{
			m_vPosition = pos;
		}
	}

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matRotY * matT;

	D3DXVECTOR3 vPos = m_vPosition;
	vPos.y += 5.0f;

	D3DLIGHT9 light = InitSpotLight(&vPos, &vDir, &YELLOW);
	g_pD3DDevice->SetLight(3, &light);
	g_pD3DDevice->LightEnable(3, true);
}