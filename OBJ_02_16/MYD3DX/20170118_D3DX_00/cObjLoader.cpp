#include "stdafx.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "cMtlTex.h"


cObjLoader::cObjLoader()
{
}


cObjLoader::~cObjLoader()
{
}

void cObjLoader::Load(IN char* szFilePath, IN D3DXMATRIXA16* pMat, OUT vector<cGroup*>& vecGroup)
{

	vector<D3DXVECTOR3> vecPos;
	vector<D3DXVECTOR2> vecTexture;
	vector<D3DXVECTOR3> vecNor;
	vector<ST_PNT_VERTEX> vecVertex;

	char sMtrlName[CHAR_MAX];

	FILE* file = NULL;
	fopen_s(&file, szFilePath, "r");

	if (file == NULL)return;
	while (1){

		char lineHeader[MAXCHAR];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		ST_PNT_VERTEX tmpSPV;

		if (strcmp(lineHeader, "mtllib")==0)
		{
			char szMtlPath[1024];
			char szFullPath[1024];
			fscanf(file, " ./%s", &szMtlPath);
			//sMtrlName = szMtlPath;
			sprintf(szFullPath, "obj/%s", szMtlPath);
			
			LoadMtlLib(szFullPath);
		}
		else if (strcmp(lineHeader,"usemtl") == 0)
		{
			fscanf(file, "%s", &sMtrlName);
		}
		else if (strcmp(lineHeader, "g") == 0)
		{
			if (vecVertex.empty())continue;

			cGroup* pGroup = new cGroup;
			g_pAutoReleasePool->AddObject(pGroup);

			pGroup->SetVertex(vecVertex);
			pGroup->SetMtlTex(m_mapMtlTex[sMtrlName]);
			vecGroup.push_back(pGroup);
			vecVertex.clear();

		}
		else if (strcmp(lineHeader, "v") == 0)
		{
			fscanf(file, "%f %f %f\n", &tmpSPV.p.x, &tmpSPV.p.y, &tmpSPV.p.z);
			vecPos.push_back(tmpSPV.p);
		}
		else if (strcmp(lineHeader, "vt") == 0){
			fscanf(file, "%f %f\n", &tmpSPV.t.x, &tmpSPV.t.y);
			vecTexture.push_back(tmpSPV.t);
		}
		else if (strcmp(lineHeader, "vn") == 0){
			fscanf(file, "%f %f %f\n", &tmpSPV.n.x, &tmpSPV.n.y, &tmpSPV.n.z);
			vecNor.push_back(tmpSPV.n);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			int index[3][3];
			fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d"
				, &index[0][0], &index[0][1], &index[0][2],
				&index[1][0], &index[1][1], &index[1][2],
				&index[2][0], &index[2][1], &index[2][2], sizeof(index));

			for (int i = 0; i < 3; i++)
			{
				ST_PNT_VERTEX pnt;
				pnt.p = vecPos[index[i][0]-1];
				pnt.t = vecTexture[index[i][1]-1];
				pnt.n = vecNor[index[i][2]-1];

				if (pMat)
				{
					D3DXVec3TransformCoord(&pnt.p, &pnt.p, pMat);
					//D3DXVec3TransformNormal(&pnt.n, &pnt.n, pMat);
				}
				vecVertex.push_back(pnt);
			}
		};

		// v , vr , vn 을 이용 하여 인덱스 조합 해서 넣어야댐
		// 지금 프레임 워크에서 인덱스포합 Group 에 넣는 방법을 모르겠음. 

	}


	fclose(file);

}

void cObjLoader::LoadMtlLib(char* szFilePath)
{
	FILE* file = NULL;
	fopen_s(&file, szFilePath, "r");

	D3DMATERIAL9* tmpMaterial;

    char fileMtl[MAXCHAR];

	if (file == NULL)return;

	while (1)
	{
		char lineHeader[MAXCHAR];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));

		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.


		if (strcmp(lineHeader, "newmtl") == 0)
		{
			fscanf_s(file, "%s", &fileMtl, sizeof(fileMtl));

			m_mapMtlTex[fileMtl] = new cMtlTex;
 			g_pAutoReleasePool->AddObject(m_mapMtlTex[fileMtl]);
			tmpMaterial = &m_mapMtlTex[fileMtl]->GetMtl();
		}
		else if (strcmp(lineHeader, "Ka") == 0)
		{
			fscanf_s(file, "%f %f %f\n", &tmpMaterial->Ambient.r, &tmpMaterial->Ambient.g, &tmpMaterial->Ambient.b, sizeof(D3DMATERIAL9));
		}
		else if (strcmp(lineHeader, "Kd") == 0)
		{
			fscanf_s(file, "%f %f %f\n", &tmpMaterial->Diffuse.r, &tmpMaterial->Diffuse.g, &tmpMaterial->Diffuse.b, sizeof(D3DMATERIAL9));

		}
		else if (strcmp(lineHeader, "Ks") == 0)
		{
			fscanf_s(file, "%f %f %f\n", &tmpMaterial->Specular.r, &tmpMaterial->Specular.g, &tmpMaterial->Specular.b, sizeof(D3DMATERIAL9));

		}
		else if (strcmp(lineHeader, "d") == 0)
		{
			float tmpAlpha;
			fscanf_s(file, "%f\n", &tmpAlpha, sizeof(float));
			tmpMaterial->Ambient.a = tmpAlpha;
			tmpMaterial->Diffuse.a = tmpAlpha;
			tmpMaterial->Specular.a = tmpAlpha;
		}
		else if (strcmp(lineHeader, "Ns") == 0)
		{
			float test;
			fscanf(file, "%f\n", &test);
		}
		else if (strcmp(lineHeader, "map_Kd") == 0)
		{
			char strName[MAXCHAR];
			char szFullPath[MAXCHAR];
			fscanf_s(file, "%s\n", &strName, sizeof(strName));
			//D3DXCreateTextureFromFile(g_pD3DDevice, strName,"생성 & 주소 "  );
			//sprintf_s(szFullPath, sizeof(szFullPath), "obj/%s", strName);
 			sprintf(szFullPath, "obj/%s", strName);

			g_pTextureManager->AddTexture(strName, szFullPath);
			m_mapMtlTex[fileMtl]->SetTexture(g_pTextureManager->GetTexture(strName));

		}


	}

	fclose(file);

}