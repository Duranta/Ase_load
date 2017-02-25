#include "stdafx.h"
#include "cAseCharacter.h"
#include "cAseLoader.h"

cAseCharacter::cAseCharacter(void)
	: m_pRoot(NULL)
{
}

cAseCharacter::~cAseCharacter(void)
{
}

void cAseCharacter::Load(char* szFullPath)
{
	cAseLoader* pAseLoader = new cAseLoader;
	m_pRoot = pAseLoader->Load(szFullPath, &m_stScene);
	SAFE_RELEASE(pAseLoader);
}

void cAseCharacter::Update(D3DXMATRIXA16* matWorld)
{
	int nFirstTick = m_stScene.nFirstFrame * m_stScene.nTicksPerFrame;
	int nLastTick = m_stScene.nLastFrame * m_stScene.nTicksPerFrame;
	int nTickSpeed = m_stScene.nFrameSpeed * m_stScene.nTicksPerFrame;
	int nKeyFrame = (nTickSpeed * GetTickCount() / 1000) % (nLastTick - nFirstTick) + nFirstTick;

	D3DXMATRIXA16 matS, matR, matW;
	D3DXMatrixScaling(&matS, 5.f, 5.f, 5.f);
	D3DXMatrixRotationY(&matR, D3DX_PI);

	matW = matS * matR * *matWorld;

	if (m_pRoot)
		m_pRoot->Update(nKeyFrame, &matW);
}

void cAseCharacter::Render()
{
	if (m_pRoot)
		m_pRoot->Render();
}