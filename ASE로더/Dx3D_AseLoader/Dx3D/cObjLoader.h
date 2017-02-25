#pragma once

class cMtlTex;
class cGroup;

class cObjLoader : public cObject
{
private:
	map<std::string, cMtlTex*> m_mapMtlTex;

	void LoadMtlLib(char* szFilePath);

public:
	cObjLoader();
	~cObjLoader();

	void Load(IN char* szFilePath, IN D3DXMATRIXA16* pmat, OUT vector<cGroup*>& vecGroup);
};