#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cCube.h"
#include "cGrid.h"
#include "cCharacterController.h"
#include "cWall.h"
#include "cInterpolation.h"
#include "cGroup.h"
#include "cObjLoader.h"
#include "cObjMap.h"
#include "cFrame.h"
#include "cAseLoader.h"
cMainGame::cMainGame()
	: m_pCamera(NULL)
	, m_pCharacterController(NULL)
{
}


cMainGame::~cMainGame()
{
	g_pTextureManager->Destroy();
	g_pObjectManager->Destroy();
	g_pDeviceManager->Destory();
}

void cMainGame::Setup()
{
	srand(time(NULL));
	rand();

	D3DXMATRIXA16 mat;

	m_pCharacterController = new cCharacterController;
	g_pAutoReleasePool->AddObject(m_pCharacterController);

	m_pCamera = new cCamera;
	g_pAutoReleasePool->AddObject(m_pCamera);
	m_pCamera->Setup();

	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	//g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);

	D3DLIGHT9 light;

	light = InitDirectionalLight(&D3DXVECTOR3(1.0f, -1.0f, 0.0f), &WHITE);
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, true);

	// cObjLoader* objLoader = new cObjLoader;
	// objLoader->Load("obj/box.obj", NULL, m_vecBox);

	D3DXMATRIXA16 matS, matR, matWorld;
	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2);

	matWorld = matS * matR;

	// objLoader->Load("obj/map_surface.obj", &matWorld, m_vecMap);
	
	cAseLoader* aseLoader = new cAseLoader;
	m_pWoman = new cFrame;
	aseLoader->Load("ase/woman/woman_01_all_stand.ASE", &matWorld, *m_pWoman);
	
	int a = 0;
	//SAFE_RELEASE(objLoader);
}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	if (m_pCharacterController)
		m_pCharacterController->Update(NULL);

	if (m_pCamera)
		m_pCamera->Update(m_pCharacterController->GetPosition());
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);



	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);



	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

//	for each (auto p in m_vecBox)
//	 	p->Render();
	// 
	// for each (auto p in m_vecMap)
	// 	p->Render();

	if (m_pWoman)
		m_pWoman->Render();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(0, 0, 0, 0);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}