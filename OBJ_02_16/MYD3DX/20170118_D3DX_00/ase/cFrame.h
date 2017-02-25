#pragma once
#include "cMtlTex.h"

class cFrame : public cObject
{
private:
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorldTM, WorldTM);
	SYNTHESIZE_PASS_BY_REF(vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
	SYNTHESIZE_ADD_REF(cMtlTex*, m_pMtlTex, MtlTex);
	
	vector<cFrame*>		m_vecChild;

public:
	cFrame();
	~cFrame();

	void Render();
	void AddChild(cFrame* pChild);
};