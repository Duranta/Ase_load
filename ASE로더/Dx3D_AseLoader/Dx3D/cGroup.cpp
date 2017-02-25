#include "StdAfx.h"
#include "cGroup.h"
#include "cMtlTex.h"

cGroup::cGroup()
	: m_pMtlTex(NULL)
{
}


cGroup::~cGroup()
{
}

void cGroup::Render()
{	
	DWORD dwFillMode;
	g_pD3DDevice->GetRenderState(D3DRS_FILLMODE, &dwFillMode);
	if (dwFillMode == D3DFILL_WIREFRAME)
	{
		g_pD3DDevice->SetTexture(0, NULL);
	}
	else
	{
		g_pD3DDevice->SetTexture(0, m_pMtlTex->GetTexture());
	}
	
	g_pD3DDevice->SetMaterial(&m_pMtlTex->GetMtl());
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PNT_VERTEX));
}