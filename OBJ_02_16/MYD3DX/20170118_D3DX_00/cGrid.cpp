#include "stdafx.h"
#include "cGrid.h"
#include "cPyramid.h"

cGrid::cGrid()
{
}


cGrid::~cGrid()
{
}

void cGrid::Setup()
{
	int nNumLine = 5;
	float fInterval = 1.0f;
	float fMax = nNumLine * fInterval;
	
	D3DCOLOR c = D3DCOLOR_XRGB(255, 255, 255);
	for (int i = 1; i <= fMax; ++i)
	{
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-fMax, 0.0f,  i), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( fMax, 0.0f,  i), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-fMax, 0.0f, -i), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( fMax, 0.0f, -i), c));

		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( i, 0.0f, -fMax), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( i, 0.0f,  fMax), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-i, 0.0f, -fMax), c));
		m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-i, 0.0f,  fMax), c));
	}

	cPyramid* pyramid;
	D3DXMATRIXA16 matS, matR, matWorld;
	D3DXMatrixScaling(&matS, 0.2f, 0.2f, 3.0f);

	c = D3DCOLOR_XRGB(255, 0, 0);
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-fMax, 0.0f, 0.0f), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( fMax, 0.0f, 0.0f), c));

	pyramid = new cPyramid;
	g_pAutoReleasePool->AddObject(pyramid);
	D3DXMatrixRotationY(&matR, D3DX_PI / 2.0f);
	matWorld = matS * matR;
	pyramid->Setup(c, matWorld);
	m_vecPyramid.push_back(pyramid);

	c = D3DCOLOR_XRGB(0, 255, 0);
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(0.0f, 0.0f, -fMax), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(0.0f, 0.0f,  fMax), c));

	pyramid = new cPyramid;
	g_pAutoReleasePool->AddObject(pyramid);
	D3DXMatrixIdentity(&matR);
	matWorld = matS * matR;
	pyramid->Setup(c, matWorld);
	m_vecPyramid.push_back(pyramid);

	c = D3DCOLOR_XRGB(0, 0, 255);
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(0.0f,-fMax, 0.0f), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(0.0f, fMax, 0.0f), c));

	pyramid = new cPyramid;
	g_pAutoReleasePool->AddObject(pyramid);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	matWorld = matS * matR;
	pyramid->Setup(c, matWorld);
	m_vecPyramid.push_back(pyramid);

	ST_PC_VERTEX stVertex;
	stVertex.c = D3DCOLOR_XRGB(0, 255, 0);

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			stVertex.p = D3DXVECTOR3(i * 5, (i + j) * 5, j * 5);
			m_vecTri.push_back(stVertex);
			stVertex.p = D3DXVECTOR3(i * 5 + 5, (i + j) * 5, j * 5);
			m_vecTri.push_back(stVertex);
			stVertex.p = D3DXVECTOR3(i * 5 + 5, (i + j) * 5, j * 5 - 5);
			m_vecTri.push_back(stVertex);
		}
	}
}

void cGrid::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecVertex.size() / 2,
		&m_vecVertex[0], sizeof(ST_PC_VERTEX));

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecTri.size() / 3,
		&m_vecTri[0], sizeof(ST_PC_VERTEX));

	for (int i = 0; i < m_vecPyramid.size(); ++i)
	{
		m_vecPyramid[i]->Render();
	}
}
