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
	if (m_mapTextures[key])
		SAFE_RELEASE(m_mapTextures[key]);

	D3DXCreateTextureFromFile(g_pD3DDevice, fileName.c_str(), &m_mapTextures[key]);
}

void cTextureManager::Destroy()
{
	map<string, LPDIRECT3DTEXTURE9>::iterator iter;

	for (iter = m_mapTextures.begin(); iter != m_mapTextures.end(); ++iter)
		SAFE_RELEASE(iter->second);

	m_mapTextures.clear();
}