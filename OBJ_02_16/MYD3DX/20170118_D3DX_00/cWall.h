#pragma once

class cCube;

class cWall : public cObject
{
private:
	cCube*			m_pRoot;
	D3DXVECTOR3		m_vPosition;

public:
	cWall();
	~cWall();

	void Setup();
	void Render();
};

