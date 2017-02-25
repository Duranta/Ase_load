#include "stdafx.h"
#include "cInterpolation.h"


cInterpolation::cInterpolation()
	: m_vFrom(0, 0, 0)
	, m_vMid(0, 0, 0)
	, m_vTo(0, 0, 0)
	, m_fActionTime(0)
	, m_fPassedActionTime(0)
	, m_nNextIndex(0)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cInterpolation::~cInterpolation()
{
}

void cInterpolation::Setup()
{
	ST_PC_VERTEX stVertex;
	stVertex.c = D3DCOLOR_XRGB(255, 0, 0);

	m_vecTarget.push_back(D3DXVECTOR3(10.0f, 0.0f, 0.0f));
	m_vecTarget.push_back(D3DXVECTOR3(5.0f, 0.0f, sqrtf(75.0f)));
	m_vecTarget.push_back(D3DXVECTOR3(-5.0f, 0.0f, sqrtf(75.0f)));
	m_vecTarget.push_back(D3DXVECTOR3(-10.0f, 0.0f, 0.0f));
	m_vecTarget.push_back(D3DXVECTOR3(-5.0f, 0.0f, -sqrtf(75.0f)));
	m_vecTarget.push_back(D3DXVECTOR3(5.0f, 0.0f, -sqrtf(75.0f)));

	for (int i = 0; i < 6; ++i)
	{
		stVertex.p = m_vecTarget[i];
		m_vecVertex.push_back(stVertex);
		stVertex.p = m_vecTarget[(i + 1) % 6];
		m_vecVertex.push_back(stVertex);
	}

	m_vTo = m_vecTarget[m_nNextIndex];
}

void cInterpolation::Update()
{
	//LinearInterpolation();
	BezierInterpolation();
}

void cInterpolation::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecVertex.size() / 2, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}

void cInterpolation::LinearInterpolation()
{
	D3DXMATRIXA16 matR, matT;
	D3DXVECTOR3 vPos, vDir;

	vDir = m_vTo - m_vFrom;
	m_fPassedActionTime += g_pTimeManager->GetDeltaTime();
	float t = m_fPassedActionTime / m_fActionTime;

	vPos = m_vFrom * (1.0f - t) + m_vTo * t;
	//D3DXVec3Lerp(&vPos, &m_vFrom, &m_vTo, t);
	//vPos = m_vFrom + t * vDir;
	D3DXMatrixTranslation(&matT, vPos.x, vPos.y, vPos.z);

	D3DXVec3Normalize(&vDir, &vDir);
	D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &vDir, &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&matR, &matR);

	m_matWorld = matR * matT;

	if (m_fPassedActionTime >= m_fActionTime)
	{
		m_fPassedActionTime = 0.0f;
		m_vFrom = vPos;
		m_nNextIndex = (m_nNextIndex + 1) % m_vecTarget.size();
		m_vTo = m_vecTarget[m_nNextIndex];
	}
}

void cInterpolation::BezierInterpolation()
{
	D3DXMATRIXA16 matR, matT;
	D3DXVECTOR3 vPos, vP1, vP2, vDir;

	m_fPassedActionTime += g_pTimeManager->GetDeltaTime();
	float t = m_fPassedActionTime / m_fActionTime;

	D3DXVec3Lerp(&vP1, &m_vFrom, &m_vMid, t);
	D3DXVec3Lerp(&vP2, &m_vMid, &m_vTo, t);

	vDir = vP2 - vP1;
	D3DXVec3Lerp(&vPos, &vP1, &vP2, t);
	D3DXMatrixTranslation(&matT, vPos.x, vPos.y, vPos.z);

	D3DXVec3Normalize(&vDir, &vDir);
	D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &vDir, &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&matR, &matR);

	m_matWorld = matR * matT;

	if (m_fPassedActionTime >= m_fActionTime)
	{
		m_fPassedActionTime = 0.0f;
		m_vFrom = vPos;
		m_nNextIndex = (m_nNextIndex + 1) % m_vecTarget.size();
		m_vMid = m_vecTarget[m_nNextIndex];
		m_nNextIndex = (m_nNextIndex + 1) % m_vecTarget.size();
		m_vTo = m_vecTarget[m_nNextIndex];
	}
}