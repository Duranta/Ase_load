#pragma once
#include "iMap.h"

class cGrid;
class cCamera;
class cCube;
class cCharactorController;
class cInterpolation;
class cWall;
class cGroup;
class cAseCharacter;

class cMainGame
{
private:
	cGrid*					m_pGrid;
	cCamera*				m_pCamera;
	cCube*					m_pRoot;
	cCharactorController*	m_pCharactorContoller;
	cWall*					m_pWall;
	cInterpolation*			m_pInterpolation;

	vector<cGroup*>			m_vecMap;
	vector<cGroup*>			m_vecIMap;
	iMap*					m_pMap;

	cAseCharacter*			m_pAseCharacter;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void SetupCubeMan();
};