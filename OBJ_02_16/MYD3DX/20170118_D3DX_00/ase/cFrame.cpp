#include "stdafx.h"
#include "cFrame.h"


cFrame::cFrame()
	: m_pMtlTex(NULL)
{
	D3DXMatrixIdentity(&m_matWorldTM);
}


cFrame::~cFrame()
{
}

void cFrame::Render()
{
	if (m_pMtlTex && !m_vecVertex.empty())
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
		g_pD3DDevice->SetTexture(0, m_pMtlTex->GetTexture());
		g_pD3DDevice->SetMaterial(&m_pMtlTex->GetMtl());
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PNT_VERTEX));
	}

	for each(auto p in m_vecChild)
	{
		p->Render();
	}
}

void cFrame::AddChild(cFrame* pChild)
{
	if (pChild == NULL)
		return;

	SAFE_ADDREF(pChild);

	m_vecChild.push_back(pChild);
}
