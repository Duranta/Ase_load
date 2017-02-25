#include "stdafx.h"
#include "cWall.h"
#include "cCube.h"

cWall::cWall()
	: m_pRoot(NULL)
	, m_vPosition(D3DXVECTOR3(0, 0, 0))
{
}


cWall::~cWall()
{
}

void cWall::Setup()
{
	D3DXMATRIXA16 matS, matT, matWorld;
	vector<D3DXCOLOR> vecColor;

	vecColor.resize(6);

	float fCubeSize = 0.25f;
	float fPosZ = 20.0f;

	for (int i = 0; i < 6; ++i)
		vecColor[i] = D3DXCOLOR(D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256));

	D3DXMatrixScaling(&matS, fCubeSize, fCubeSize, fCubeSize);
	D3DXMatrixTranslation(&matT, 0.0f, 0.0f, fPosZ);
	matWorld = matS * matT;
	m_pRoot = new cCube;
	g_pAutoReleasePool->AddObject(m_pRoot);
	m_pRoot->Setup(&matWorld, NULL);

	for (int i = 1; i < 25; ++i)
	{
		for (int j = 0; j < 6; ++j)
			vecColor[j] = D3DXCOLOR(D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256));

		D3DXMatrixScaling(&matS, fCubeSize, fCubeSize, fCubeSize);
		D3DXMatrixTranslation(&matT, 0.0f, fCubeSize * 2.0f * i, fPosZ);
		matWorld = matS * matT;
		cCube* pCube = new cCube;
		g_pAutoReleasePool->AddObject(pCube);
		pCube->Setup(&matWorld, NULL);
		m_pRoot->AddChild(pCube);

		for (int j = 0; j < 25; ++j)
		{
			for (int k = 0; k < 6; ++k)
				vecColor[k] = D3DXCOLOR(D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256));

			D3DXMatrixScaling(&matS, fCubeSize, fCubeSize, fCubeSize);
			D3DXMatrixTranslation(&matT, -fCubeSize * 2.0f * i, fCubeSize * 2.0f * j, fPosZ);
			matWorld = matS * matT;
			cCube* pCube = new cCube;
			g_pAutoReleasePool->AddObject(pCube);
			pCube->Setup(&matWorld, NULL);
			m_pRoot->AddChild(pCube);
		}

		for (int j = 0; j < 25; ++j)
		{
			for (int k = 0; k < 6; ++k)
				vecColor[k] = D3DXCOLOR(D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256));

			D3DXMatrixScaling(&matS, fCubeSize, fCubeSize, fCubeSize);
			D3DXMatrixTranslation(&matT, fCubeSize * 2.0f * i, fCubeSize * 2.0f * j, fPosZ);
			matWorld = matS * matT;
			cCube* pCube = new cCube;
			g_pAutoReleasePool->AddObject(pCube);
			pCube->Setup(&matWorld, NULL);
			m_pRoot->AddChild(pCube);
		}
	}
}

void cWall::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	if (m_pRoot)
		m_pRoot->Render();
}