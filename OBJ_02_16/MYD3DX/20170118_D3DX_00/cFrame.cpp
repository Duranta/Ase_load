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
void cFrame::Update()
{
	vector<cFrame*>::iterator iter;
	vector<cFrame*>::iterator iterEnd = v_child.end();

	for (iter = v_child.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render();
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
