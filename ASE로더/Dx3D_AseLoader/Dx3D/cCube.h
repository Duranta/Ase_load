#pragma once

class cCube : public cGameObject
{
private:
	std::vector<ST_PC_VERTEX>	m_vecPCVertex;
	std::vector<ST_PN_VERTEX>	m_vecPNVertex;
	std::vector<ST_PT_VERTEX>	m_vecPTVertex;
	std::vector<ST_PNT_VERTEX>	m_vecPNTVertex;
	vector<cCube*>				m_vecChild;

public:
	cCube();
	~cCube();

	void Setup(D3DXMATRIXA16* pmat, vector<D3DXVECTOR2>* vecTexture = NULL);
	virtual void Update(D3DXMATRIXA16* pParentWorldTM = NULL) override;
	virtual void Render() override;

	void AddChild(cCube* pChild);
};

