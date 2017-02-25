#pragma once
#include "cObject.h"

class cMtlTex;
class cFrame;

class cAseLoader :
	public cObject
{
	map<string, cMtlTex*> m_mapMtlTex;
	
	map<int, cMtlTex*> m_mapMtlTexInt;


	void LoadMtlLib(char* szFilePath);
	void LoadMtlLibInt(char* szFilePath);

	map<string, cFrame*> m_Frame;

public:
	cAseLoader();
	~cAseLoader();

	//void Load(IN char* szFilePath, IN D3DXMATRIXA16* pMat,
	//	OUT vector<cFrame*>& vecGroup);
	void Load(IN char* szFilePath, IN D3DXMATRIXA16* pMat,
		OUT cFrame& Frame);

	void makeNode(cFrame& Frame);
	cFrame* FineFrame(map<string, cFrame*>& mapFrame, const char* cName);
	
	cFrame* FindParent(cFrame& Frame, char* cName);
	void Correct();
};

