#pragma once

// 뷰 매트릭스 변형을 카메라 클래스가 한다.
class cCamera : public cObject
{
private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;

	D3DXMATRIXA16	m_matView;
	D3DXMATRIXA16	m_matProj;

	float			m_fDistance;
	float			m_fRotY;
	float			m_fRotX;

	bool			m_isRButtonDown;
	POINT			m_ptPrevMouse;

public:
	cCamera();
	~cCamera();

	void Setup();
	void Update(D3DXVECTOR3* pTarget);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	D3DXMATRIXA16 GetViewMatrix() { return m_matView; }
	D3DXMATRIXA16 GetProjMatrix() { return m_matProj; }
};

