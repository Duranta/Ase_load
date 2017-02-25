#include "StdAfx.h"
#include "cCube.h"

cCube::cCube()
{
}

cCube::~cCube()
{
}

void cCube::Setup(D3DXMATRIXA16* pMat, vector<D3DXVECTOR2>* vecTexture /*= NULL*/)
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

	D3DXMATRIXA16 matWorld, matR;
	if (vecTexture)
		D3DXMatrixRotationY(&matR, D3DX_PI);
	else
		D3DXMatrixIdentity(&matR);

	if (pMat)
		matWorld = *pMat;
	else
		D3DXMatrixIdentity(&matWorld);

	for (int i = 0; i < vecVertex.size(); ++i)
		D3DXVec3TransformCoord(&vecVertex[i], &vecVertex[i], &(matWorld * matR));

	D3DXVECTOR3 vNormal;

	if (vecTexture != NULL)
	{
		ComputeNormal(&vNormal, &vecVertex[0], &vecVertex[1], &vecVertex[2]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[0], vNormal, (*vecTexture)[0]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[1], vNormal, (*vecTexture)[1]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[2], vNormal, (*vecTexture)[2]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[0], vNormal, (*vecTexture)[3]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[2], vNormal, (*vecTexture)[4]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[3], vNormal, (*vecTexture)[5]));
		ComputeNormal(&vNormal, &vecVertex[4], &vecVertex[6], &vecVertex[5]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTexture)[6]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[6], vNormal, (*vecTexture)[7]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[5], vNormal, (*vecTexture)[8]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTexture)[9]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[7], vNormal, (*vecTexture)[10]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[6], vNormal, (*vecTexture)[11]));
		ComputeNormal(&vNormal, &vecVertex[4], &vecVertex[5], &vecVertex[1]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTexture)[12]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[5], vNormal, (*vecTexture)[13]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[1], vNormal, (*vecTexture)[14]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTexture)[15]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[1], vNormal, (*vecTexture)[16]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[0], vNormal, (*vecTexture)[17]));
		ComputeNormal(&vNormal, &vecVertex[3], &vecVertex[2], &vecVertex[6]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[3], vNormal, (*vecTexture)[18]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[2], vNormal, (*vecTexture)[19]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[6], vNormal, (*vecTexture)[20]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[3], vNormal, (*vecTexture)[21]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[6], vNormal, (*vecTexture)[22]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[7], vNormal, (*vecTexture)[23]));
		ComputeNormal(&vNormal, &vecVertex[1], &vecVertex[5], &vecVertex[6]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[1], vNormal, (*vecTexture)[24]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[5], vNormal, (*vecTexture)[25]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[6], vNormal, (*vecTexture)[26]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[1], vNormal, (*vecTexture)[27]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[6], vNormal, (*vecTexture)[28]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[2], vNormal, (*vecTexture)[29]));
		ComputeNormal(&vNormal, &vecVertex[4], &vecVertex[0], &vecVertex[3]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTexture)[30]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[0], vNormal, (*vecTexture)[31]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[3], vNormal, (*vecTexture)[32]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTexture)[33]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[3], vNormal, (*vecTexture)[34]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[7], vNormal, (*vecTexture)[35]));
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
		ComputeNormal(&vNormal, &vecVertex[4], &vecVertex[5], &vecVertex[1]);
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[4], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[5], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[1], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[4], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[1], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[0], vNormal));
		ComputeNormal(&vNormal, &vecVertex[3], &vecVertex[2], &vecVertex[6]);
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[3], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[2], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[6], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[3], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[6], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[7], vNormal));
		ComputeNormal(&vNormal, &vecVertex[1], &vecVertex[5], &vecVertex[6]);
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[1], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[5], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[6], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[1], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[6], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[2], vNormal));
		ComputeNormal(&vNormal, &vecVertex[4], &vecVertex[0], &vecVertex[3]);
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[4], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[0], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[3], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[4], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[3], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[7], vNormal));
	}
}

void cCube::Update(D3DXMATRIXA16* pParentWorldTM /*= NULL*/)
{
	cGameObject::Update(pParentWorldTM);

	for each(auto p in m_vecChild)
	{
		p->Update(&m_matWorld);
	}
}

void cCube::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	if (!m_vecPNTVertex.empty())
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("batman"));
		g_pD3DDevice->SetMaterial(&WHITE_MTRL);
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPNTVertex.size() / 3, &m_vecPNTVertex[0], sizeof(ST_PNT_VERTEX));
	}
	else if (!m_vecPNVertex.empty())
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		g_pD3DDevice->SetTexture(0, NULL);
		g_pD3DDevice->SetMaterial(&WHITE_MTRL);
		g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPNVertex.size() / 3, &m_vecPNVertex[0], sizeof(ST_PN_VERTEX));
	}

	for each(auto p in m_vecChild)
	{
		p->Render();
	}
}

void cCube::AddChild( cCube* pChild )
{
	m_vecChild.push_back(pChild);
}