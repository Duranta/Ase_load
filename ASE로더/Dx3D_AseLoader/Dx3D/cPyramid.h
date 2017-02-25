#pragma once
class cPyramid : public cObject
{
private:
	vector<ST_PC_VERTEX>	m_vecVertex;
	D3DXMATRIXA16			m_matWorld;

public:
	cPyramid(void);
	~cPyramid(void);

	void Setup(D3DCOLOR c, D3DXMATRIXA16& matWorld);
	void Render();
};

