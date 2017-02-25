#pragma once

#define VK_1 '1'
#define VK_2 '2'
#define VK_3 '3'

class cCube : public cGameObject
{
private:
	vector<ST_PC_VERTEX>	m_vecPCVertex;
	vector<ST_PN_VERTEX>	m_vecPNVertex;
	vector<ST_PT_VERTEX>	m_vecPTVertex;
	vector<ST_PNT_VERTEX>	m_vecPNTVertex;
	vector<cCube*>			m_vecChild;

public:
	cCube();
	~cCube();

	void Setup(D3DXMATRIXA16* pMat, vector<D3DXVECTOR2>* vecTVertex = NULL);
	void Update(D3DXMATRIXA16* pParentWorldTM);
	void Render();
	void AddChild(cCube* pChild);
};