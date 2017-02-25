#include "StdAfx.h"
#include "cPyramid.h"


cPyramid::cPyramid(void)
{
}


cPyramid::~cPyramid(void)
{
}

void cPyramid::Setup(D3DCOLOR c, D3DXMATRIXA16& matWorld)
{
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 0, 0, 0), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 1,-1,-1), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-1,-1,-1), c));

	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 0, 0, 0), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 1,-1, 1), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 1,-1,-1), c));

	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 0, 0, 0), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-1,-1, 1), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 1,-1, 1), c));

	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 0, 0, 0), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-1,-1,-1), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-1,-1, 1), c));

	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 1,-1,-1), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-1,-1, 1), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-1,-1,-1), c));

	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 1,-1,-1), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 1,-1, 1), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-1,-1, 1), c));
	
	//D3DXMatrixIdentity(&m_matWorld);
	m_matWorld = matWorld;
}

void cPyramid::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}
