#include "stdafx.h"
#include "cCube.h"


cCube::cCube()
{
}


cCube::~cCube()
{
}

void cCube::Setup(D3DXMATRIXA16* pMat, vector<D3DXVECTOR2>* vecTVertex /*= NULL*/)
{
	vector<D3DXVECTOR3> vecVertex;
	vecVertex.push_back(D3DXVECTOR3(-1.0f,-1.0f,-1.0f));
	vecVertex.push_back(D3DXVECTOR3(-1.0f, 1.0f,-1.0f));
	vecVertex.push_back(D3DXVECTOR3( 1.0f, 1.0f,-1.0f));
	vecVertex.push_back(D3DXVECTOR3( 1.0f,-1.0f,-1.0f));
	vecVertex.push_back(D3DXVECTOR3(-1.0f,-1.0f, 1.0f));
	vecVertex.push_back(D3DXVECTOR3(-1.0f, 1.0f, 1.0f));
	vecVertex.push_back(D3DXVECTOR3( 1.0f, 1.0f, 1.0f));
	vecVertex.push_back(D3DXVECTOR3( 1.0f,-1.0f, 1.0f));

	D3DXMATRIXA16 matWorld;

	if (pMat)
		matWorld = *pMat;
	else
		D3DXMatrixIdentity(&matWorld);

	for (int i = 0; i < vecVertex.size(); ++i)
		D3DXVec3TransformCoord(&vecVertex[i], &vecVertex[i], &matWorld);

	D3DXVECTOR3 vNormal;

	if (vecTVertex != NULL)
	{
		ComputeNormal(&vNormal, &vecVertex[0], &vecVertex[1], &vecVertex[2]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[0], vNormal, (*vecTVertex)[0]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[1], vNormal, (*vecTVertex)[1]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[2], vNormal, (*vecTVertex)[2]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[0], vNormal, (*vecTVertex)[3]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[2], vNormal, (*vecTVertex)[4]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[3], vNormal, (*vecTVertex)[5]));
		ComputeNormal(&vNormal, &vecVertex[4], &vecVertex[6], &vecVertex[5]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTVertex)[6]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[6], vNormal, (*vecTVertex)[7]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[5], vNormal, (*vecTVertex)[8]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTVertex)[9]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[7], vNormal, (*vecTVertex)[10]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[6], vNormal, (*vecTVertex)[11]));
		ComputeNormal(&vNormal, &vecVertex[0], &vecVertex[4], &vecVertex[1]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[0], vNormal, (*vecTVertex)[12]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTVertex)[13]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[1], vNormal, (*vecTVertex)[14]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[1], vNormal, (*vecTVertex)[15]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTVertex)[16]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[5], vNormal, (*vecTVertex)[17]));
		ComputeNormal(&vNormal, &vecVertex[2], &vecVertex[6], &vecVertex[3]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[2], vNormal, (*vecTVertex)[18]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[6], vNormal, (*vecTVertex)[19]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[3], vNormal, (*vecTVertex)[20]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[3], vNormal, (*vecTVertex)[21]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[6], vNormal, (*vecTVertex)[22]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[7], vNormal, (*vecTVertex)[23]));
		ComputeNormal(&vNormal, &vecVertex[0], &vecVertex[3], &vecVertex[4]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[0], vNormal, (*vecTVertex)[24]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[3], vNormal, (*vecTVertex)[25]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTVertex)[26]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[3], vNormal, (*vecTVertex)[27]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[7], vNormal, (*vecTVertex)[28]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTVertex)[29]));
		ComputeNormal(&vNormal, &vecVertex[1], &vecVertex[5], &vecVertex[2]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[1], vNormal, (*vecTVertex)[30]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[5], vNormal, (*vecTVertex)[31]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[2], vNormal, (*vecTVertex)[32]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[2], vNormal, (*vecTVertex)[33]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[5], vNormal, (*vecTVertex)[34]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[6], vNormal, (*vecTVertex)[35]));
	}
	else
	{
		ComputeNormal(&vNormal, &vecVertex[0], &vecVertex[1], &vecVertex[2]);
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[0], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[1], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[2], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[0], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[2], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[3], vNormal));
		ComputeNormal(&vNormal, &vecVertex[4], &vecVertex[6], &vecVertex[5]);
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[4], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[6], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[5], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[4], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[7], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[6], vNormal));
		ComputeNormal(&vNormal, &vecVertex[0], &vecVertex[4], &vecVertex[1]);
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[0], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[4], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[1], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[1], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[4], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[5], vNormal));
		ComputeNormal(&vNormal, &vecVertex[2], &vecVertex[6], &vecVertex[3]);
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[2], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[6], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[3], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[3], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[6], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[7], vNormal));
		ComputeNormal(&vNormal, &vecVertex[0], &vecVertex[3], &vecVertex[4]);
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[0], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[3], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[4], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[3], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[7], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[4], vNormal));
		ComputeNormal(&vNormal, &vecVertex[1], &vecVertex[5], &vecVertex[2]);
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[1], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[5], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[2], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[2], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[5], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[6], vNormal));
	}
}

void cCube::Update(D3DXMATRIXA16* pParentWorldTM)
{
	cGameObject::Update(pParentWorldTM);

	for each (auto p in m_vecChild)
	{
		p->SetAnimation(m_bAnimation);
		p->Update(&m_matWorld);
	}
}

void cCube::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	if (!m_vecPNTVertex.empty())
	{
		g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("bat"));
		g_pD3DDevice->SetMaterial(&WHITE_MTRL);
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPNTVertex.size() / 3,
			&m_vecPNTVertex[0], sizeof(ST_PNT_VERTEX));
	}
	else if (!m_vecPNVertex.empty())
	{
		g_pD3DDevice->SetTexture(0, NULL);
		g_pD3DDevice->SetMaterial(&WHITE_MTRL);
		g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPNVertex.size() / 3,
			&m_vecPNVertex[0], sizeof(ST_PN_VERTEX));
	}

	for each (auto p in m_vecChild)
	{
		p->Render();
	}
}

void cCube::AddChild(cCube* pChild)
{
	m_vecChild.push_back(pChild);
}