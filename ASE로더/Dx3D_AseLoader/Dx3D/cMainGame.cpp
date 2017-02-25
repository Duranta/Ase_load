#include "StdAfx.h"
#include "cMainGame.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cCube.h"
#include "cCharactorController.h"
#include "cWall.h"
#include "cInterpolation.h"
#include "cGroup.h"
#include "cObjLoader.h"
#include "cObjMap.h"
#include "cAseCharacter.h"

cMainGame::cMainGame(void)
	: m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_pRoot(NULL)
	, m_pCharactorContoller(NULL)
	, m_pInterpolation(NULL)
	, m_pWall(NULL)
	, m_pAseCharacter(NULL)
{
}

cMainGame::~cMainGame(void)
{
	g_pAutoReleasePool->Drain();
	g_pObjectManager->Destroy();
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	m_pGrid = new cGrid;
	g_pAutoReleasePool->AddObject(m_pGrid);
	m_pGrid->Setup();

	m_pWall = new cWall;
	g_pAutoReleasePool->AddObject(m_pWall);
	m_pWall->Setup();

	D3DXMATRIXA16 matS, matR, matT, matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2);
	D3DXMatrixTranslation(&matT, 0, 0, 10.0f);
	matWorld = matS * matR * matT;

	cObjLoader* objLoader = new cObjLoader;
	objLoader->Load("obj/Map.obj", &matWorld, m_vecMap);
	SAFE_RELEASE(objLoader);

	objLoader = new cObjLoader;
	objLoader->Load("obj/map_surface.obj", &matWorld, m_vecIMap);
	SAFE_RELEASE(objLoader);

	cObjMap* objMap = new cObjMap;
	g_pAutoReleasePool->AddObject(objMap);
	objMap->Load("obj/map_surface.obj", &matWorld);
	m_pMap = objMap;

	m_pInterpolation = new cInterpolation;
	g_pAutoReleasePool->AddObject(m_pInterpolation);
	m_pInterpolation->Setup();
	m_pInterpolation->SetActionTime(3);

	m_pCamera = new cCamera;
	g_pAutoReleasePool->AddObject(m_pCamera);
	m_pCamera->Setup();

	m_pCharactorContoller = new cCharactorController;
	g_pAutoReleasePool->AddObject(m_pCharactorContoller);

	SetupCubeMan();

	m_pAseCharacter = new cAseCharacter;
	g_pAutoReleasePool->AddObject(m_pAseCharacter);
	m_pAseCharacter->Load("./woman/woman_01_all.ASE");

	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	//g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);

	D3DLIGHT9	light;
	D3DXVECTOR3 direction = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	D3DXVec3Normalize(&direction, &direction);
	D3DXCOLOR	color = WHITE;
	light = InitDirectionalLight(&direction, &color);
	g_pD3DDevice->SetLight(0, &light);
	g_pD3DDevice->LightEnable(0, true);

	light = InitPointLight(&D3DXVECTOR3(2, 1, 2), &BLUE);
	g_pD3DDevice->SetLight(1, &light);
	g_pD3DDevice->LightEnable(1, true);
}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	if (m_pCharactorContoller)
		m_pCharactorContoller->Update(m_pMap);

	if (m_pInterpolation)
		m_pInterpolation->Update();

	//if (m_pRoot)
	//	m_pRoot->Update(&m_pCharactorContoller->GetWorldTM());

	if (m_pAseCharacter)
		m_pAseCharacter->Update(&m_pCharactorContoller->GetWorldTM());

	if (m_pCamera)
		m_pCamera->Update(&m_pCharactorContoller->GetPosition());
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL,	D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,	D3DCOLOR_XRGB(47, 121, 112), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	// ±×¸²À» ±×¸°´Ù.
	if (m_pGrid)
		m_pGrid->Render();

	if (m_pWall)
		m_pWall->Render();

	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	for each(auto p in m_vecMap)
	{
		p->Render();
	}

	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	for each(auto p in m_vecIMap)
	{
		p->Render();
	}

	if (m_pInterpolation)
		m_pInterpolation->Render();

	//if (m_pRoot)
	//	m_pRoot->Render();

	if (m_pAseCharacter)
		m_pAseCharacter->Render();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cMainGame::SetupCubeMan()
{
	g_pTextureManager->AddTexture("batman", "batman.png");

	D3DXMATRIXA16 matS, matT, mat;
	vector<D3DXVECTOR2> vecVertex;

	// ¸öÅë Á¤¸é
	vecVertex.push_back(D3DXVECTOR2(5.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(5.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(7.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(5.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(7.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(7.0f / 16.0f, 8.0f / 8.0f));
	// ¸öÅë ÈÄ¸é
	vecVertex.push_back(D3DXVECTOR2(10.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(8.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(10.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(10.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(8.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(8.0f / 16.0f, 5.0f / 8.0f));
	// ¸öÅë ¿ÞÂÊ
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(5.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(5.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(5.0f / 16.0f, 8.0f / 8.0f));
	// ¸öÅë ¿À¸¥ÂÊ
	vecVertex.push_back(D3DXVECTOR2(7.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(7.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(8.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(7.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(8.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(8.0f / 16.0f, 8.0f / 8.0f));
	// ¸öÅë À§ÂÊ
	vecVertex.push_back(D3DXVECTOR2(5.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(5.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(7.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(5.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(7.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(7.0f / 16.0f, 5.0f / 8.0f));
	// ¸öÅë ¾Æ·¡ÂÊ
	vecVertex.push_back(D3DXVECTOR2(7.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(7.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(9.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(7.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(9.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(9.0f / 16.0f, 5.0f / 8.0f));

	// ¸öÅë
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 0.5f);
	D3DXMatrixTranslation(&matT, 0.0f, 3.0f, 0.0f);
	mat = matS * matT;
	m_pRoot = new cCube;
	g_pAutoReleasePool->AddObject(m_pRoot);
	m_pRoot->Setup(&mat, &vecVertex);
	vecVertex.clear();

	// ¸Ó¸® ¾Õ¸é
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 2.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 2.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 2.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 4.0f / 8.0f));
	// ¸Ó¸® ÈÄ¸é
	vecVertex.push_back(D3DXVECTOR2(8.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(6.0f / 16.0f, 2.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(8.0f / 16.0f, 2.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(8.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(6.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(6.0f / 16.0f, 2.0f / 8.0f));
	// ¸Ó¸® ¿ÞÂÊ
	vecVertex.push_back(D3DXVECTOR2(0.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(0.0f / 16.0f, 2.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 2.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(0.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 2.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 4.0f / 8.0f));
	// ¸Ó¸® ¿À¸¥ÂÊ
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 2.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(6.0f / 16.0f, 2.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(6.0f / 16.0f, 2.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(6.0f / 16.0f, 4.0f / 8.0f));
	// ¸Ó¸® À­¸é
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 2.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 0.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 0.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 2.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 0.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 2.0f / 8.0f));
	// ¸Ó¸® ¾Æ·§¸é
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 2.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 0.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(6.0f / 16.0f, 0.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 2.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(6.0f / 16.0f, 0.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(6.0f / 16.0f, 2.0f / 8.0f));

	// ¸Ó¸®
	D3DXMatrixScaling(&matS, 0.7f, 0.7f, 0.7f);
	D3DXMatrixTranslation(&matT, 0.0f, 4.7f, 0.0f);
	mat = matS * matT;
	cCube* pHead = new cCube;
	g_pAutoReleasePool->AddObject(pHead);
	pHead->Setup(&mat, &vecVertex);
	vecVertex.clear();
	m_pRoot->AddChild(pHead);

	// ¿ÞÆÈ ¾Õ¸é
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 8.0f / 8.0f));
	// ¿ÞÆÈ ÈÄ¸é
	vecVertex.push_back(D3DXVECTOR2(14.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(14.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(14.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 5.0f / 8.0f));
	// ¿ÞÆÈ ¿ÞÂÊ
	vecVertex.push_back(D3DXVECTOR2(10.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(10.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(10.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 8.0f / 8.0f));
	// ¿ÞÆÈ ¿À¸¥ÂÊ
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 8.0f / 8.0f));
	// ¿ÞÆÈ À§ÂÊ
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 5.0f / 8.0f));
	// ¿ÞÆÈ ¾Æ·¡ÂÊ
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 5.0f / 8.0f));

	// ¿ÞÆÈ
	D3DXMatrixScaling(&matS, 0.5f, 1.0f, 0.5f);
	D3DXMatrixTranslation(&matT, -1.5f, 3.0f, 0.0f);
	mat = matS * matT;
	cCube* pLArm = new cCube;
	g_pAutoReleasePool->AddObject(pLArm);
	pLArm->Setup(&mat, &vecVertex);
	vecVertex.clear();
	pLArm->SetXAngleSpeed(0.1f);
	pLArm->SetLocalTranslation(D3DXVECTOR3(0.0f, -4.0f, 0.0f));
	m_pRoot->AddChild(pLArm);

	// ¿À¸¥ÆÈ ¾Õ¸é
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(14.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(14.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(14.0f / 16.0f, 8.0f / 8.0f));
	// ¿À¸¥ÆÈ ÈÄ¸é
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 5.0f / 8.0f));
	// ¿À¸¥ÆÈ ¿ÞÂÊ
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 8.0f / 8.0f));
	// ¿À¸¥ÆÈ ¿À¸¥ÂÊ
	vecVertex.push_back(D3DXVECTOR2(10.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(10.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(10.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 8.0f / 8.0f));
	// ¿À¸¥ÆÈ À§ÂÊ
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(11.0f / 16.0f, 4.0f / 8.0f));
	// ¿À¸¥ÆÈ ¾Æ·¡ÂÊ
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(13.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(12.0f / 16.0f, 4.0f / 8.0f));

	// ¿À¸¥ÆÈ
	D3DXMatrixScaling(&matS, 0.5f, 1.0f, 0.5f);
	D3DXMatrixTranslation(&matT, 1.5f, 3.0f, 0.0f);
	mat = matS * matT;
	cCube* pRArm = new cCube;
	g_pAutoReleasePool->AddObject(pRArm);
	pRArm->Setup(&mat, &vecVertex);
	vecVertex.clear();
	pRArm->SetXAngleSpeed(-0.1f);
	pRArm->SetLocalTranslation(D3DXVECTOR3(0.0f, -4.0f, 0.0f));
	m_pRoot->AddChild(pRArm);

	// ¿ÞÂÊ ´Ù¸® ¾Õ¸é
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 8.0f / 8.0f));
	// ¿ÞÂÊ ´Ù¸® ÈÄ¸é
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 5.0f / 8.0f));
	// ¿ÞÂÊ ´Ù¸® ¿ÞÂÊ
	vecVertex.push_back(D3DXVECTOR2(0.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(0.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(0.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 8.0f / 8.0f));
	// ¿ÞÂÊ ´Ù¸® ¿À¸¥ÂÊ
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 8.0f / 8.0f));
	// ¿ÞÂÊ ´Ù¸® À§ÂÊ
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 5.0f / 8.0f));
	// ¿ÞÂÊ ´Ù¸® ¾Æ·¡ÂÊ
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 5.0f / 8.0f));

	// ¿Þ´Ù¸®
	D3DXMatrixScaling(&matS, 0.5f, 1.0f, 0.5f);
	D3DXMatrixTranslation(&matT, -0.5f, 1.0f, 0);
	mat = matS * matT;
	cCube* pLLeg = new cCube;
	g_pAutoReleasePool->AddObject(pLLeg);
	pLLeg->Setup(&mat, &vecVertex);
	vecVertex.clear();
	pLLeg->SetXAngleSpeed(-0.1f);
	pLLeg->SetLocalTranslation(D3DXVECTOR3(0.0f, -2.0f, 0.0f));
	m_pRoot->AddChild(pLLeg);

	// ¿À¸¥ÂÊ ´Ù¸® ¾Õ¸é
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 8.0f / 8.0f));
	// ¿À¸¥ÂÊ ´Ù¸® ÈÄ¸é
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(4.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 5.0f / 8.0f));
	// ¿À¸¥ÂÊ ´Ù¸® ¿ÞÂÊ
	vecVertex.push_back(D3DXVECTOR2(0.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(0.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(0.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 8.0f / 8.0f));
	// ¿À¸¥ÂÊ ´Ù¸® ¿À¸¥ÂÊ
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 8.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 8.0f / 8.0f));
	// ¿À¸¥ÂÊ ´Ù¸® À§ÂÊ
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(1.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 5.0f / 8.0f));
	// ¿À¸¥ÂÊ ´Ù¸® ¾Æ·¡ÂÊ
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(2.0f / 16.0f, 5.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 4.0f / 8.0f));
	vecVertex.push_back(D3DXVECTOR2(3.0f / 16.0f, 5.0f / 8.0f));

	// ¿À¸¥´Ù¸®
	D3DXMatrixScaling(&matS, 0.5f, 1.0f, 0.5f);
	D3DXMatrixTranslation(&matT, 0.5f, 1.0f, 0);
	mat = matS * matT;
	cCube* pRLeg = new cCube;
	g_pAutoReleasePool->AddObject(pRLeg);
	pRLeg->Setup(&mat, &vecVertex);
	vecVertex.clear();
	pRLeg->SetXAngleSpeed(0.1f);
	pRLeg->SetLocalTranslation(D3DXVECTOR3(0.0f, -2.0f, 0.0f));
	m_pRoot->AddChild(pRLeg);
}