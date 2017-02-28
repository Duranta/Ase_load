#pragma once
#include "cObject.h"
#include "cFrame.h"

class cMtlTex;
//class cFrame;

class cAseLoader :
	public cObject
{
	map<string, cMtlTex*> m_mapMtlTex;
	
	map<int, cMtlTex*> m_mapMtlTexInt;


	void LoadMtlLib(char* szFilePath);

	map<string, cFrame*> m_Frame;
	
	ST_FRAMFE_DATA m_stTickData;

public:
	cAseLoader();
	~cAseLoader();

	
	void Load(IN char* szFilePath, IN D3DXMATRIXA16* pMat,
		OUT cFrame& Frame);

	void makeNode(cFrame& Frame);
	void makeTM(cFrame& Frame);
	cFrame* FineFrame(map<string, cFrame*>& mapFrame, const char* cName);
	void InvLocalPos(cFrame& pFrame);
};

