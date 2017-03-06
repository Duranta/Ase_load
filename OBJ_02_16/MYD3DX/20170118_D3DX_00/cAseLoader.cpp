#include "stdafx.h"
#include "cAseLoader.h"
#include "cFrame.h"
#include "cMtlTex.h"


cAseLoader::cAseLoader()
{
}

cAseLoader::~cAseLoader()
{
}

void cAseLoader::Load(IN char* szFilePath, IN D3DXMATRIXA16* pMat,
	OUT cFrame& Frame)
{
	LoadMtlLib(szFilePath);
	// 파일 오픈
	FILE* fp = NULL;
	fopen_s(&fp, szFilePath, "r");

	// 파일 파싱에 필요한 데이터 공간
	char nodeName[MAXCHAR]; //현재 노드 이름 저장
	int texNum = -1;
	D3DXMATRIXA16 mat;
	cFrame* pFrame = NULL;

	vector<ST_PNT_VERTEX> vecSPV;
	vector<D3DXVECTOR3> vecPos;  // v
	vector<D3DXVECTOR2> vecTexture;// vt
	vector<D3DXVECTOR3> vecNor;    // vn
	vector<int> vecVIndex;
	vector<int> vecVTIndex;
	string mtlName;
	int vCount = 0;
	int iTextureCount = 1;
	// 애니메이션 rot 값
	ST_ROT_SAMPLE tackRot;
	tackRot.n = 0;
	tackRot.q = { 0,0,0,0 };

	while (true)
	{
		char lineHeader[1024] = { 0, };
		// read the first word of the line
		int res = fscanf(fp, "%s", lineHeader);
		if (res == EOF)
		{
			break;
		}


		if (strcmp(lineHeader, "*GEOMOBJECT") == 0)
		{
			if (vCount != 0)
			{
				ST_PNT_VERTEX SPV;
				bool isPos = false;
				bool isTexture = false;
				bool isNormal = false;

				if (vecPos.size() != 0)
				{
					isPos = true;
				}
				if (vecTexture.size() != 0)
				{
					isTexture = true;
				}
				if (vecNor.size() != 0)
				{
					isNormal = true;
				}
				for (int i = 0; i < vCount * 3; i++)
				{
					if (isPos == true)
						SPV.p = vecPos[vecVIndex[i]];
					if (isTexture == true)
						SPV.t = vecTexture[vecVTIndex[i]];
					if (isNormal == true)
						SPV.n = vecNor[i];

					vecSPV.push_back(SPV);
				}

				pFrame->SetVertex(vecSPV);
				if (texNum != -1)
				{
					//pFrame->SetMtlTex(m_mapMtlTex[mtlName]);
					//cMtlTex * test = m_mapMtlTex.find(mtlName)->second;

					//pFrame->m_pMtlTex 
					if (pFrame != NULL)
						pFrame->SetMtlTex(m_mapMtlTex[mtlName]);
					//m_Frame[pFrame->GetNodeName()]->SetMtlTex(m_mapMtlTex[mtlName]);

					iTextureCount++;
					texNum = -1;
				}

				//============ 멀리 떨어져 있는 경우 여기 때문
				pFrame->SetMatWorld(mat);

				vCount = 0;
				vecPos.clear();
				vecVIndex.clear();
				vecTexture.clear();
				vecVTIndex.clear();
				vecNor.clear();
				vecSPV.clear();

				isPos = false;
				isTexture = false;
				isNormal = false;
			}

		}
		else if (strcmp(lineHeader, "*NODE_NAME") == 0)
		{
			fgets(nodeName, MAXCHAR, fp);
			nodeName[strlen(nodeName) - 1] = '\0';

			if (m_Frame.find(nodeName) != m_Frame.end())
				continue;

			pFrame = new cFrame;	//임시 저장
			g_pAutoReleasePool->AddObject(pFrame);

			D3DXMATRIXA16 matIden;
			D3DXMatrixIdentity(&matIden);
			pFrame->SetMyNodeName(nodeName);
			pFrame->SetMatWorld(matIden);

			m_Frame.insert(pair<string, cFrame*>(nodeName, pFrame));

			// currentFrame = FineFrame(vecGroup, nodeName); // 현재 지오 매트리 지오메트리 정보 담을  Frame
		}
		else if (strcmp(lineHeader, "*NODE_PARENT") == 0)
		{
			char parentName[MAXCHAR];
			fgets(parentName, MAXCHAR, fp);
			parentName[strlen(parentName) - 1] = '\0';

			pFrame->SetParentNodeName(parentName);
		}
		else if (strcmp(lineHeader, "*TM_ROW0") == 0)
		{
			//fscanf(fp, "%f %f %f", &mat._11, &mat._13, &mat._12); // z y 순서 바꿈.
			//mat._14 = 0;
			// =========== 수정     ================
			char oneLine[MAXCHAR] = {};
			char temp[MAXCHAR] = {};

			fgets(oneLine, MAXCHAR, fp);
			sscanf(oneLine, "%f %f %f", &mat._11, &mat._13, &mat._12);
			mat._14 = 0;

			fgets(oneLine, MAXCHAR, fp);
			sscanf(oneLine, " %*s  %f %f %f", &mat._31, &mat._33, &mat._32);
			mat._34 = 0;

			fgets(oneLine, MAXCHAR, fp);
			sscanf(oneLine, " %*s  %f %f %f", &mat._21, &mat._23, &mat._22);
			mat._24 = 0;

			fgets(oneLine, MAXCHAR, fp);
			sscanf(oneLine, " %*s  %f %f %f", &mat._41, &mat._43, &mat._42);
			mat._44 = 1;

		}
		//else if (strcmp(lineHeader, "*TM_ROW1") == 0)
		//{
		//	fscanf(fp, "%f %f %f", &mat._31, &mat._33, &mat._32); // z y 순서 바꿈.
		//	mat._34 = 0;
		//}
		//else if (strcmp(lineHeader, "*TM_ROW2") == 0)
		//{
		//	fscanf(fp, "%f %f %f", &mat._21, &mat._23, &mat._22); // z y 순서 바꿈.
		//	mat._24 = 0;
		//}
		//else if (strcmp(lineHeader, "*TM_ROW3") == 0)
		//{
		//	// 0 0 0 1 초기화 확인
		//	fscanf(fp, "%f %f %f", &mat._41, &mat._43, &mat._42);
		//	mat._44 = 1;
		//}
		// 정점 숫자. 
		else if (strcmp(lineHeader, "*MESH_NUMFACES") == 0)
		{
			fscanf(fp, "%d", &vCount); // 페이스 숫자. 
		}
		// 정점 포지션 정보
		else if (strcmp(lineHeader, "*MESH_VERTEX") == 0)
		{
			D3DXVECTOR3 pos;
			fscanf(fp, "%*d %f %f %f", &pos.x, &pos.z, &pos.y);
			vecPos.push_back(pos);
		}
		//정점 포지션 인덱스.
		else if (strcmp(lineHeader, "*MESH_FACE") == 0)
		{
			// 메쉬 인덱스
			int idx[3];
			fscanf(fp, "%*s %*s %d %*s %d %*s %d", &idx[0], &idx[2], &idx[1]);
			for (int i = 0; i < 3; ++i)
			{
				vecVIndex.push_back(idx[i]);
			}
		}
		// 정점 UV
		else if (strcmp(lineHeader, "*MESH_TVERT") == 0)
		{
			D3DXVECTOR2 uv;
			fscanf(fp, "%*d %f %f %*f", &uv.x, &uv.y);
			uv.y = 1.f - uv.y;
			vecTexture.push_back(uv);
		}
		// UV 텍스쳐 인덱스
		else if (strcmp(lineHeader, "*MESH_TFACE") == 0)
		{
			int idx[3];
			fscanf(fp, "%*d %d %d %d", &idx[0], &idx[2], &idx[1]);
			for (int i = 0; i < 3; ++i)
			{
				vecVTIndex.push_back(idx[i]);
			}
		}
		// 노말정보 , +index 포함
		else if (strcmp(lineHeader, "*MESH_FACENORMAL") == 0)
		{
			char oneLine[MAXCHAR] = {};

			D3DXVECTOR3 nor[3];
			int index[3] = { 0, 2, 1 };

			fgets(oneLine, MAXCHAR, fp);

			for (int i = 0; i < 3; i++)
			{
				fgets(oneLine, MAXCHAR, fp);
				sscanf(oneLine, " %*s %*d %f %f %f"
					, &nor[index[i]].x, &nor[index[i]].z, &nor[index[i]].y);
			}
			for (int i = 0; i < 3; i++)
			{
				vecNor.push_back(nor[i]);
			}

			//	fread(oneLine, 1, 1024, fp);

			//fscanf(fp, "%*d %f %f %f/n %*s %*d %f %f %f/n %*s %*d %f %f %f/n"

			//	, &nor2.x, &nor2.z, &nor2.y
			//	, &nor3.x, &nor3.z, &nor3.y);
			//fscanf(fp, "%s", &oneLine);


			//vecNor.push_back(nor2);
			//vecNor.push_back(nor3);


		}
		else if (strcmp(lineHeader, "*CONTROL_POS_SAMPLE") == 0)
		{
			ST_POS_SAMPLE pos;
			fscanf(fp, "%d %f %f %f", &pos.n, &pos.v.x, &pos.v.z, &pos.v.y);
			pFrame->m_vecPosTrack.push_back(pos);
		}
		else if (strcmp(lineHeader, "*CONTROL_ROT_SAMPLE") == 0)
		{
			ST_ROT_SAMPLE rot;

			fscanf(fp, "%d %f %f %f %f", &rot.n, &rot.q.x, &rot.q.z, &rot.q.y, &rot.q.w);

			// 처음 들어왔다면 tackRot 에 = rot 대입
			if (pFrame->m_vecRotTrack.empty())
			{
				rot.q.x *= sinf(rot.q.w / 2);
				rot.q.y *= sinf(rot.q.w / 2);
				rot.q.z *= cosf(rot.q.w / 2);
				tackRot = rot;
			}
			else
			{
				tackRot.n = rot.n;
				rot.q.x *= sinf(rot.q.w / 2);
				rot.q.y *= sinf(rot.q.w / 2);
				rot.q.z *= cosf(rot.q.w / 2);

				tackRot.q *= rot.q;

			}
			pFrame->m_vecRotTrack.push_back(tackRot);
		}
		else if (strcmp(lineHeader, "*MATERIAL_REF") == 0)
		{
			fscanf(fp, "%d", &texNum);
			map<string, cMtlTex*>::iterator iter;
			map<string, cMtlTex*>::iterator iterEnd = m_mapMtlTex.end();

			for (iter = m_mapMtlTex.begin(); iter != iterEnd; ++iter)
			{
				if (iter->second->GetmtlNum() == texNum)
				{
					mtlName = iter->first;
					break;
				}
			}
		}

	}

	//==============================================
	ST_PNT_VERTEX SPV;
	bool isPos = false;
	bool isTexture = false;
	bool isNormal = false;

	if (vecPos.size() != 0)
	{
		isPos = true;
	}
	if (vecTexture.size() != 0)
	{
		isTexture = true;
	}
	if (vecNor.size() != 0)
	{
		isNormal = true;
	}
	for (int i = 0; i < vCount * 3; i++)
	{
		if (isPos == true)
			SPV.p = vecPos[vecVIndex[i]];
		if (isTexture == true)
			SPV.t = vecTexture[vecVTIndex[i]];
		if (isNormal == true)
			SPV.n = vecNor[i];

		vecSPV.push_back(SPV);
	}

	pFrame->SetVertex(vecSPV);
	if (texNum != -1)
	{
		//pFrame->SetMtlTex(m_mapMtlTex[mtlName]);
		//cMtlTex * test = m_mapMtlTex.find(mtlName)->second;

		//pFrame->m_pMtlTex 
		if (pFrame != NULL)
			pFrame->SetMtlTex(m_mapMtlTex[mtlName]);
		//m_Frame[pFrame->GetNodeName()]->SetMtlTex(m_mapMtlTex[mtlName]);

		iTextureCount++;
		texNum = -1;
	}

	pFrame->SetMatWorld(mat);

	vCount = 0;
	vecPos.clear();
	vecVIndex.clear();
	vecTexture.clear();
	vecVTIndex.clear();
	vecNor.clear();
	vecSPV.clear();

	isPos = false;
	isTexture = false;
	isNormal = false;

	makeNode(Frame);
	//makeTM(Frame);
	InvLocalPos(Frame);
	//Frame.MainCalLocalTM();
}

void cAseLoader::LoadMtlLib(char* szFilePath)
{
	FILE* fp = NULL;
	fopen_s(&fp, szFilePath, "r");
	D3DMATERIAL9* pD3mater;
	int materialCount = 0;
	int materialCountTemp = 0;
	int materialNum = 0;
	char materName[MAXCHAR];


	while (true)
	{
		char lineHeader[1024] = { 0, };
		// read the first word of the line
		int res = fscanf(fp, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		if (strcmp(lineHeader, "*MATERIAL_COUNT") == 0)
		{
			fscanf(fp, "%d", &materialCount);
		}
		else if (strcmp(lineHeader, "*MATERIAL") == 0)
		{
			fscanf(fp, "%d", &materialNum);
		}
		else if (strcmp(lineHeader, "*MATERIAL_NAME") == 0)
		{
			//fscanf(fp, "%s", &materName);

			char oneLine[MAXCHAR];
			//fgets(oneLine, MAXCHAR, fp);
			fgets(oneLine, MAXCHAR, fp);

			//materName[strlen(materName) - 1] = '\0';

			int idx = 0;
			while (idx < MAXCHAR)
			{
				if (oneLine[idx] == '\"')
				{
					int idx2 = 0;
					while (true)
					{
						materName[idx2] = oneLine[idx + 1 + idx2];
						if (materName[idx2] == '\"')
						{
							materName[idx2] = 0;
							break;
						}
						++idx2;

					}
					break;
				}
				++idx;
			}


			m_mapMtlTex[materName] = new cMtlTex;
			g_pAutoReleasePool->AddObject(m_mapMtlTex[materName]);
			pD3mater = &m_mapMtlTex[materName]->GetMtl();

			m_mapMtlTex[materName]->SetmtlNum(materialNum);
		}
		else if (strcmp(lineHeader, "*MATERIAL_AMBIENT") == 0)
		{
			fscanf_s(fp, "%f %f %f\n", &pD3mater->Ambient.r, &pD3mater->Ambient.g, &pD3mater->Ambient.b, sizeof(D3DMATERIAL9));
			pD3mater->Ambient.a = 1.0f;
		}
		else if (strcmp(lineHeader, "*MATERIAL_DIFFUSE") == 0)
		{
			fscanf_s(fp, "%f %f %f\n", &pD3mater->Diffuse.r, &pD3mater->Diffuse.g, &pD3mater->Diffuse.b, sizeof(D3DMATERIAL9));
			pD3mater->Diffuse.a = 1.0f;
		}
		else if (strcmp(lineHeader, "*MATERIAL_SPECULAR") == 0)
		{
			fscanf_s(fp, "%f %f %f\n", &pD3mater->Specular.r, &pD3mater->Specular.g, &pD3mater->Specular.b, sizeof(D3DMATERIAL9));
			pD3mater->Specular.a = 1.0f;
		}
		else if (strcmp(lineHeader, "*BITMAP") == 0)
		{
			char filePath[MAXCHAR] = { 0, };
			char filePullPath[MAXCHAR] = { 0, };
			char oneLine[MAXCHAR] = { 0, };
			//	fscanf_s(fp, "./%s", &filePath,sizeof(filePath));

			fgets(oneLine, MAXCHAR, fp);
			int idx = 0;
			while (idx < MAXCHAR)
			{
				if (oneLine[idx] == '\"')
				{
					int idx2 = 0;
					while (true)
					{
						filePath[idx2] = oneLine[idx + 3 + idx2];
						if (filePath[idx2] == '\"')
						{
							filePath[idx2] = 0;
							break;
						}
						++idx2;

					}
					break;
				}
				++idx;
			}


			sprintf(filePullPath, "ase/%s", filePath);

			g_pTextureManager->AddTexture(filePath, filePullPath);
			m_mapMtlTex[materName]->SetTexture(g_pTextureManager->GetTexture(filePath));
			string tName = filePath;
			m_mapMtlTex[materName]->m_tName = tName;
			++materialCountTemp;

			if (materialCountTemp == materialCount)
			{
				break;
			}
		}
		else if (strcmp(lineHeader, "*SCENE_FIRSTFRAME") == 0)
		{
			int iTick = 0;
			fscanf_s(fp, "%d\n", &iTick, sizeof(int));
			m_stTickData.nFirstFrame = iTick;
		}
		else if (strcmp(lineHeader, "*SCENE_LASTFRAME") == 0)
		{
			int iTick = 0;
			fscanf_s(fp, "%d\n", &iTick, sizeof(int));
			m_stTickData.nLastFrame = iTick;
		}
		else if (strcmp(lineHeader, "*SCENE_FRAMESPEED") == 0)
		{
			int iTick = 0;
			fscanf_s(fp, "%d\n", &iTick, sizeof(int));
			m_stTickData.nFrameSpeed = iTick;
		}
		else if (strcmp(lineHeader, "*SCENE_TICKSPERFRAME") == 0)
		{
			int iTick = 0;
			fscanf_s(fp, "%d\n", &iTick, sizeof(int));
			m_stTickData.nTicksPerFrame = iTick;
		}

	}

	//fclose(fp);

}

cFrame* cAseLoader::FineFrame(map<string, cFrame*>& mapFrame, const char* cName)
{
	map<string, cFrame*>::iterator iter;
	map<string, cFrame*>::iterator iterEnd = mapFrame.end();

	for (iter = mapFrame.begin(); iter != iterEnd; ++iter)
	{
		if (strcmp(cName, iter->second->GetNodeName().c_str()) == 0)
		{
			return (iter)->second;
		}
	}
	return NULL;
}

void cAseLoader::InvLocalPos(cFrame & pFrame)
{
	map<string, cFrame*>::iterator iter;
	map<string, cFrame*>::iterator iterEnd = m_Frame.end();

	//string debug;
	char* cName[MAXCHAR];

	for (iter = m_Frame.begin(); iter != iterEnd; ++iter)
	{
		// 노말 , 정점 
		for (int i = 0; i < iter->second->GetVertex().size(); ++i)
		{
			D3DXMATRIXA16 matInvWorld;
			if (strcmp(iter->second->GetParentName().c_str(), "NULL") == 0)
			{
				D3DXMatrixIdentity(&matInvWorld);
			}
			else
			{
				D3DXMatrixInverse(&matInvWorld, 0, &m_Frame[iter->second->GetParentName()]->GetMatWorld());
			}
			D3DXVec3TransformCoord(&iter->second->GetVertex()[i].p,
				&iter->second->GetVertex()[i].p, &matInvWorld);
			//D3DXVec3TransformCoord(&iter->second->GetVertex()[i].p,
			//	&iter->second->GetVertex()[i].p, &matInvWorld);
		}
	}
}




void cAseLoader::makeNode(cFrame& Frame)
{
	map<string, cFrame*>::iterator iter;
	map<string, cFrame*>::iterator iterEnd = m_Frame.end();
	//string debug;
	char* cName[MAXCHAR];
	D3DXMATRIXA16 matInvParent;

	for (iter = m_Frame.begin(); iter != iterEnd; ++iter)
	{
		// 부모일때 
		if (strcmp(iter->second->GetParentName().c_str(), "NULL") == 0)
		{
			// 첫번째 값 집어 넣는다. 
			//Frame = *iter->second;
			D3DXMATRIXA16 matIden;

			D3DXMatrixIdentity(&matIden);
			Frame.m_matLocalTM = matIden; //FrameTM 을 단위행렬로 초기화
			Frame.SetTickData(m_stTickData);

			iter->second->SetTM(iter->second->GetMatWorld());

			Frame.AddChild(iter->second);
		}
		else
		{
			m_Frame[iter->second->GetParentName()]->AddChild(iter->second);
			D3DXMatrixInverse(&matInvParent, 0, &m_Frame[iter->second->GetParentName()]->GetMatWorld());
			//iter->second->m_matLocalTM *= matInvParent;
			iter->second->SetTM(iter->second->GetMatWorld()*matInvParent);
		}
	}
}

void cAseLoader::makeTM(cFrame & Frame)
{
	map<string, cFrame*>::iterator iter;
	map<string, cFrame*>::iterator iterEnd = m_Frame.end();
	//string debug;
	char* cName[MAXCHAR];
	D3DXMATRIXA16 matInvParent;

	for (iter = m_Frame.begin(); iter != iterEnd; ++iter)
	{
		// 부모일때 
		if (strcmp(iter->second->GetParentName().c_str(), "NULL") == 0)
		{
			Frame.m_matLocalTM = Frame.GetMatWorld();
		}
		else
		{
			D3DXMatrixInverse(&matInvParent, 0, &m_Frame[iter->second->GetParentName()]->GetMatWorld());
			//iter->second->m_matLocalTM *= matInvParent;
			// world  = local*pWorld;
			// local = world *pWorld(-1)

			iter->second->SetTM(iter->second->GetMatWorld()*matInvParent);
		}
	}
}
