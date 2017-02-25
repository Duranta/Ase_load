#pragma once
#include "cObject.h"
class cMtlTex :	public cObject
{
private:
	SYNTHESIZE_PASS_BY_REF(D3DMATERIAL9, m_stMtl, Mtl);
	SYNTHESIZE_ADD_REF(LPDIRECT3DTEXTURE9, m_pTexture, Texture);
	SYNTHESIZE_PASS_BY_REF(int, m_mtlNum, mtlNum);
	//SYNTHESIZE(string, m_tName, TName);


public:
	string m_tName;
	cMtlTex();
	~cMtlTex();
};

