#pragma once
#include "iMap.h"

class cCamera;
class cCharacterController;
class cGroup;
class cFrame;
class cMainGame
{
private:
	cCamera*				m_pCamera;
	cCharacterController*	m_pCharacterController;
	// vector<cGroup*>			m_vecMap;
	// vector<cGroup*>			m_vecSurface;
	 vector<cGroup*>			m_vecBox;
	cFrame*						m_pWoman;
	
	iMap*					m_pMap;

public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

