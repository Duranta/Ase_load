#pragma once

class cPyramid;

class cGrid : public cObject
{
private:
	vector<ST_PC_VERTEX>	m_vecVertex;
	//vector<ST_PNT_VERTEX>	m_vecVertex;
	vector<cPyramid*>		m_vecPyramid;
	vector<ST_PC_VERTEX>	m_vecTri;

public:
	cGrid();
	~cGrid();

	void Setup();
	void Render();
	vector<ST_PC_VERTEX>& GetVectri() { return m_vecTri; }
};

