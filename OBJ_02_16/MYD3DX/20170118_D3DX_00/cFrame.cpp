#include "stdafx.h"
#include "cFrame.h"


cFrame::cFrame()
	: m_parentName("NULL")
	, m_pMtlTex(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cFrame::~cFrame()
{
}

void cFrame::SetMtlTex(cMtlTex* pTex)
{
	if (m_pMtlTex != pTex)
	{
		SAFE_ADDREF(pTex);
		m_pMtlTex = pTex;
	//
	}
}
void cFrame::AddChild(cFrame* pChild)
{
	if (this != pChild)
	{
		SAFE_ADDREF(pChild);
		v_child.push_back(pChild);
	}
	//			materName[strlen(materName) - 1] = '\0';

}
void cFrame::MainUpate()
{/*
	int nFirstTick = m_stScene.nFirstFrame * m_stScene.nTicksPerFrame;
	int nLastTick = m_stScene.nLastFrame * m_stScene.nTicksPerFrame;
	int nTickSpeed = m_stScene.nFrameSpeed * m_stScene.nTicksPerFrame;
	int nKeyFrame = (nTickSpeed * GetTickCount() / 1000) % (nLastTick - nFirstTick) + nFirstTick;

	D3DXMATRIXA16 matS, matR, matW;
	D3DXMatrixScaling(&matS, 5.f, 5.f, 5.f);
	D3DXMatrixRotationY(&matR, D3DX_PI);

	matW = matS * matR * *matWorld;*/

	vector<cFrame*>::iterator iter;
	vector<cFrame*>::iterator iterEnd = v_child.end();

	for (iter = v_child.begin(); iter != iterEnd; ++iter)
	{
		// (*iter)->Update(keyFrame, * pParent);
	}
}
void cFrame::Update(int keyFrame, D3DXMATRIXA16* pParent)
{
	vector<cFrame*>::iterator iter;
	vector<cFrame*>::iterator iterEnd = v_child.end();

	for (iter = v_child.begin(); iter != iterEnd; ++iter)
	{
		// (*iter)->Render(keyFrame, * pParent);
	}
}

void cFrame::Render()
{
	if (m_pMtlTex)
	{
		DWORD dwFillMode;
		g_pD3DDevice->GetRenderState(D3DRS_FILLMODE, &dwFillMode);
		if (dwFillMode == D3DFILL_WIREFRAME)
			g_pD3DDevice->SetTexture(0, NULL);
		else
		{
		//	g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("woman/hair_woman_01.jpg"));
			g_pD3DDevice->SetTexture(0, m_pMtlTex->GetTexture());

		}
		D3DXMATRIXA16 iden;
		D3DXMatrixIdentity(&iden);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &iden);

		g_pD3DDevice->SetMaterial(&m_pMtlTex->GetMtl());
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3,
			&m_vecVertex[0], sizeof(ST_PNT_VERTEX));
		int a = 0;
	}

	vector<cFrame*>::iterator iter;
	vector<cFrame*>::iterator iterEnd = v_child.end();

	for (iter = v_child.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render();
	}
}
