#pragma once
#include "cFrame.h"

class cMtlTex;

class cAseLoader : public cObject
{
protected:
	FILE*							m_fp;
	char							m_szToken[1024];
	vector<cMtlTex*>				m_vecMtlTex;
	map<std::string, cFrame*>		m_mapFrame;
	cFrame*							m_pRoot;

public:
	cAseLoader(void);
	virtual ~cAseLoader(void);

	char*	GetToken();
	int		GetInteger();
	float	GetFloat();
	bool	IsWhiteSpace(char c);
	bool	IsEqual(char* str1, char* str2);

	cFrame* Load(IN char* szFullPath, OUT ST_ASE_SCENE* pScene);

	void	ProcessMATERIAL_LIST();
	void	ProcessMATERIAL(OUT cMtlTex* pMtlTex);
	void	ProcessMAP_DIFFUSE(OUT cMtlTex* pMtlTex);

	cFrame*	ProcessGEOMOBJECT();
	void	ProcessNODE_TM(OUT cFrame* pFrame);
	void	ProcessMESH(OUT cFrame* pFrame);
	void	ProcessMESH_VERTEX_LIST(OUT std::vector<D3DXVECTOR3>& vecV);
	void	ProcessMESH_FACE_LIST(IN std::vector<D3DXVECTOR3>& vecV, OUT std::vector<ST_PNT_VERTEX>& vecVertex);
	void	ProcessMESH_TVERTLIST(OUT std::vector<D3DXVECTOR2>& vecVT);
	void	ProcessMESH_TFACELIST(IN std::vector<D3DXVECTOR2>& vecVT, OUT std::vector<ST_PNT_VERTEX>& vecVertex);
	void	ProcessMESH_NORMALS(OUT std::vector<ST_PNT_VERTEX>&	vecVertex);
	
	void	ProcessSCENE(OUT ST_ASE_SCENE* pScene);
	void	ProcessTM_ANIMATION(OUT cFrame* pFrame);
	void	ProcessPOS_TRACK(OUT cFrame* pFrame);
	void	ProcessROT_TRACK(OUT cFrame* pFrame);
};