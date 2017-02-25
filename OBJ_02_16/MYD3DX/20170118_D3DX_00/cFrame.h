#pragma once
#include "cObject.h"

#include "cMtlTex.h"

struct ST_POS_SAMPLE
{
	int				n;
	D3DXVECTOR3		v;
};

struct ST_ROT_SAMPLE
{
	int				n;
	D3DXQUATERNION	q;
};

struct ST_FRAMFE_DATA
{
	int nFirstFrame;
	int nLastFrame;
	int nFrameSpeed;
	int nTicksPerFrame;
};

class cFrame :
	public cObject
{
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorld, MatWorld);
	SYNTHESIZE_PASS_BY_REF(vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
	//SYNTHESIZE_ADD_REF(cMtlTex*, m_pMtlTex, MtlTex);

	cMtlTex* m_pMtlTex;

	vector<cFrame*> v_child;

	string m_nodeName;
	string m_parentName;
	//=====================  animation value
	D3DXMATRIXA16			m_matLocalTM;
	vector<ST_POS_SAMPLE>	m_vecPosTrack;
	vector<ST_ROT_SAMPLE>	m_vecRotTrack;

public:
	cFrame();
	~cFrame();

	cMtlTex* GetMtlTex(){ return m_pMtlTex; };
	void SetMtlTex(cMtlTex* pTex);

	void Render();
	void AddChild(cFrame* pChild);
	void SetMyNodeName(string nodeName)   { m_nodeName = nodeName; }
	void SetParentNodeName(string parentName){ m_parentName = parentName; }
	void Update();
	string GetNodeName(){ return m_nodeName; }
	string GetParentName(){ return m_parentName; }

	vector<cFrame*> GetChild(){ return v_child; }
	// 애니메이션 추가. 
	//void Update(int iKeyFrame , D3DXMATRIXA16* pMatParent);
};