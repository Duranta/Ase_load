#include "stdafx.h"
#include "cPyramid.h"


cPyramid::cPyramid()
{
}


cPyramid::~cPyramid()
{
}

void cPyramid::Setup(D3DCOLOR c, D3DXMATRIXA16& matWorld)
{
	//À­¸é
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 0, 0, 0), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-1, 1, 1), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 1, 1, 1), c));
	//¾Æ·§¸é
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 0, 0, 0), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 1,-1, 1), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-1,-1, 1), c));
	//¿À¸¥ÂÊ¸é
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 0, 0, 0), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 1, 1, 1), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 1,-1, 1), c));
	//¿ÞÂÊ¸é
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 0, 0, 0), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-1,-1, 1), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-1, 1, 1), c));

	//¶Ñ±î¸®
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-1,-1, 1), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 1,-1, 1), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-1, 1, 1), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 1,-1, 1), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3( 1, 1, 1), c));
	m_vecVertex.push_back(ST_PC_VERTEX(D3DXVECTOR3(-1, 1, 1), c));

	m_matWorld = matWorld;
}

void cPyramid::Render()
{
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3,
		&m_vecVertex[0], sizeof(ST_PC_VERTEX));
}