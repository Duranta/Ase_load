#pragma once

#define g_pTextureManager cTextureManager::GetInstance()

class cTextureManager
{
private:
	map<string, LPDIRECT3DTEXTURE9> m_mapTexture;

public:
	cTextureManager();
	~cTextureManager();

	static cTextureManager* GetInstance()
	{
		static cTextureManager instance;
		return &instance;
	}

	void AddTexture(string key, string fileName);
	

	void Destroy();
	LPDIRECT3DTEXTURE9& GetTexture(string key) { return m_mapTexture[key]; }
};

