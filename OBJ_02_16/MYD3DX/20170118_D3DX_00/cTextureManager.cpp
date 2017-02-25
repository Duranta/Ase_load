#include "stdafx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager()
{
}


cTextureManager::~cTextureManager()
{
}

void cTextureManager::AddTexture(string key, string fileName)
{
	if (!m_mapTexture[key])
		D3DXCreateTextureFromFile(g_pD3DDevice, fileName.c_str(), &m_mapTexture[key]);
}

void cTextureManager::Destroy()
{
	map<string, LPDIRECT3DTEXTURE9>::iterator iter;

	for (iter = m_mapTexture.begin(); iter != m_mapTexture.end(); ++iter)
		SAFE_RELEASE(iter->second);

	m_mapTexture.clear();
}
