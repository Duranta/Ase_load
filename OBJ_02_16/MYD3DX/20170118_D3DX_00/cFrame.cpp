#include "stdafx.h"
#include "cFrame.h"


cFrame::cFrame()
	: m_parentName("NULL")
	, m_pMtlTex(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cFrame::~cFrame()
{
}

void cFrame::SetMtlTex(cMtlTex* pTex)
{
	if (m_pMtlTex != pTex)
	{
		SAFE_ADDREF(pTex);
		m_pMtlTex = pTex;
	//
	}
}
void cFrame::AddChild(cFrame* pChild)
{
	if (this != pChild)
	{
		SAFE_ADDREF(pChild);
		v_child.push_back(pChild);
	}
	//			materName[strlen(materName) - 1] = '\0';

}
void cFrame::MainUpate()
{
	int nFirstTick = m_stTickData.nFirstFrame * m_stTickData.nTicksPerFrame;
	int nLastTick = m_stTickData.nLastFrame * m_stTickData.nTicksPerFrame;
	int nTickSpeed = m_stTickData.nFrameSpeed * m_stTickData.nTicksPerFrame;
	int nKeyFrame = (nTickSpeed * GetTickCount() / 1000) % (nLastTick - nFirstTick) + nFirstTick;

	D3DXMATRIXA16 matS, matR, matW;
	D3DXMatrixScaling(&matS, 5.f, 5.f, 5.f);
	D3DXMatrixRotationY(&matR, D3DX_PI);

	//matW = matS * matR * matWorld;

	vector<cFrame*>::iterator iter;
	vector<cFrame*>::iterator iterEnd = v_child.end();

	for (iter = v_child.begin(); iter != iterEnd; ++iter)
	{
		 (*iter)->Update(nKeyFrame, &m_matLocalTM);
	}
}
void cFrame::Update(int keyFrame, D3DXMATRIXA16* pParent)
{
	D3DXMATRIXA16 matLocalT, matLocalR;
	CalLocalPosMatrix(keyFrame, matLocalT);
	CalLocalRotMatrix(keyFrame, matLocalR);
	
	m_matWorld = matLocalR*matLocalT;

    m_matWorld *= (*pParent);
	
	vector<cFrame*>::iterator iter;
	vector<cFrame*>::iterator iterEnd = v_child.end();

	for (iter = v_child.begin(); iter != iterEnd; ++iter)
	{
	
		(*iter)->Update(keyFrame, &m_matWorld);
	}
}

void cFrame::CalLocalPosMatrix(int nKeyFrame, D3DXMATRIXA16 & posMat)
{
	D3DXMatrixIdentity(&posMat);

	if (m_vecPosTrack.empty())
	{
		posMat._41 = m_matLocalTM._41;
		posMat._42 = m_matLocalTM._42;
		posMat._43 = m_matLocalTM._43;
	}
	else if (nKeyFrame <= m_vecPosTrack.front().n)
	{
		posMat._41 = m_vecPosTrack.front().v.x;
		posMat._42 = m_vecPosTrack.front().v.y;
		posMat._43 = m_vecPosTrack.front().v.z;
	}
	else if (nKeyFrame >= m_vecPosTrack.back().n)
	{
		posMat._41 = m_vecPosTrack.back().v.x;
		posMat._42 = m_vecPosTrack.back().v.y;
		posMat._43 = m_vecPosTrack.back().v.z;
	}
	else
	{
		int iNext = 0;
		for (unsigned int i = 0; i < m_vecPosTrack.size(); ++i)
		{
			if (m_vecPosTrack[i].n > nKeyFrame)
			{
				iNext = i;
				break;
			}
		}
		if (iNext == 0)return;
		int iPrev = iNext - 1;

		float t = (nKeyFrame - m_vecPosTrack[iPrev].n) / (float)(m_vecPosTrack[iNext].n - m_vecPosTrack[iPrev].n);


		D3DXVECTOR3 v;
		D3DXVec3Lerp(&v, &m_vecPosTrack[iPrev].v, &m_vecPosTrack[iNext].v, t);
		posMat._41 = v.x;
		posMat._42 = v.y;
		posMat._43 = v.z;

		// else �κ� ����
		// Frame 1200 ���� , 0��Ʈ�� frame =500   1��Ʈ�� frame =1000 2��Ʈ�� frame =1500
		// ���� ���ƾ� �Ǵ� Ʈ���� 1�� Ʈ���� �Ǿ� �� .n ������(tick) �� 1200 �� 1���� 2�� ���̸� ���ƾ� ��
		// ���� �ִ� �ִϸ��̼��� 1�� Ʈ���� ���ƾ� �Ѵ�.  1200 ���� n ���� Ŭ�� ���� ���� -1 �ϸ� ���� Ʈ��
		// ���� ���� �ϱ� ���� t ���� ���ؾ� �ȴ�.
		// ���� Ʈ���� tick ���� 1000, ���� �ִϸ��̼� tick = 1200 , 200 tick �帧 
		// ���� Ʈ���� ���� Ʈ���� tick ��ü�� 500 , 
		// �̸� ���� �󸶳� �������� ������ ���´�. 
	}
	
}

void cFrame::CalLocalRotMatrix(int nKeyFrame, D3DXMATRIXA16 & rotMat)
{
	D3DXMatrixIdentity(&rotMat);
	if (m_vecRotTrack.empty())
	{
		rotMat = m_matLocalTM;
		rotMat._41 = 0.0f;
		rotMat._42 = 0.0f;
		rotMat._43 = 0.0f;
	}
	else if (nKeyFrame <= m_vecRotTrack.front().n)
	{
		D3DXMatrixRotationQuaternion(&rotMat, &m_vecRotTrack.front().q);
	}
	else if (nKeyFrame >= m_vecRotTrack.back().n)
	{
		D3DXMatrixRotationQuaternion(&rotMat, &m_vecRotTrack.back().q);
	}
	else
	{
		int iNext = 0;
		for (unsigned int i = 0; i < m_vecPosTrack.size(); ++i)
		{
			if (m_vecPosTrack[i].n > nKeyFrame)
			{
				iNext = i;
				break;
			}
		}
		if (iNext == 0)return;

		int iPrev = iNext - 1;

		float t = (nKeyFrame - m_vecRotTrack[iPrev].n) / (float)(m_vecRotTrack[iNext].n - m_vecRotTrack[iPrev].n);

		D3DXQUATERNION q;
		D3DXQuaternionSlerp(&q, &m_vecRotTrack[iPrev].q, &m_vecRotTrack[iNext].q, t);
		D3DXMatrixRotationQuaternion(&rotMat, &q);
	}
}

void cFrame::Render()
{
	if (m_pMtlTex)
	{
		DWORD dwFillMode;
		g_pD3DDevice->GetRenderState(D3DRS_FILLMODE, &dwFillMode);
		if (dwFillMode == D3DFILL_WIREFRAME)
			g_pD3DDevice->SetTexture(0, NULL);
		else
		{
		//	g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("woman/hair_woman_01.jpg"));
			g_pD3DDevice->SetTexture(0, m_pMtlTex->GetTexture());

		}
		D3DXMATRIXA16 iden;
		D3DXMatrixIdentity(&iden);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matLocalTM);

	//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &iden);

		g_pD3DDevice->SetMaterial(&m_pMtlTex->GetMtl());
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3,
			&m_vecVertex[0], sizeof(ST_PNT_VERTEX));
		int a = 0;
	}

	vector<cFrame*>::iterator iter;
	vector<cFrame*>::iterator iterEnd = v_child.end();

	for (iter = v_child.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render();
	}
}
