#pragma once

#define WHITE	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
#define BLACK	D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f)
#define RED		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)
#define GREEN	D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)
#define BLUE	D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)
#define YELLOW	D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f)

namespace D3DUTILITY
{
	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);

	const D3DMATERIAL9 WHITE_MTRL = InitMtrl(WHITE, WHITE, WHITE, BLACK, 8.0f);
	const D3DMATERIAL9 RED_MTRL = InitMtrl(RED, RED, RED, BLACK, 8.0f);
	const D3DMATERIAL9 GREEN_MTRL = InitMtrl(GREEN, GREEN, GREEN, BLACK, 8.0f);
	const D3DMATERIAL9 BLUE_MTRL = InitMtrl(BLUE, BLUE, BLUE, BLACK, 8.0f);
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 8.0f);

	void ComputeNormal(D3DXVECTOR3* out, D3DXVECTOR3* p0, D3DXVECTOR3* p1, D3DXVECTOR3* p2);

	D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3* dir, D3DXCOLOR* c);
	D3DLIGHT9 InitPointLight(D3DXVECTOR3* pos, D3DXCOLOR* c);
	D3DLIGHT9 InitSpotLight(D3DXVECTOR3* pos, D3DXVECTOR3* dir, D3DXCOLOR* c);
}

//	1. Position 정점의 좌표 x,y,z(float)				: D3DFVF_XYZ
// 	2. RHW (float)                                  : D3DFVF_XYZRHW (D3DFVF_XYZ 또는 D3DFVF_NORMAL과 같이 사용불가)
// 	3. Blending Weight Data 결합 가중치 (float)		: D3DFVF_XYZB1 ~ D3DFVF_XYZB5
// 	4. Vertex Normal 정점의 법선 벡터 x,y,z(float)	: D3DFVF_NORMAL
// 	5. Vertex Point Size 정점의 점 크기 (float)		: D3DFVF_PSIZE
// 	6. Diffuse Color (DWORD)						: D3DFVF_DIFFUSE
// 	7. Specular Color (DWORD)						: D3DFVF_SPECULAR
// 	8. Texture Coordinate Set 1 (float)             : D3DFVF_TEX0 - D3DFVF_TEX8

struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;

	static const int FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

	ST_PC_VERTEX() {}

	ST_PC_VERTEX(D3DXVECTOR3 _p, D3DCOLOR _c)
	{
		p = _p;
		c = _c;
	}
};

struct ST_PN_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3	n;

	static const int FVF = D3DFVF_XYZ | D3DFVF_NORMAL;

	ST_PN_VERTEX() {}

	ST_PN_VERTEX(D3DXVECTOR3 _p, D3DXVECTOR3 _n)
	{
		p = _p;
		n = _n;
	}
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2	t;

	static const int FVF = D3DFVF_XYZ | D3DFVF_TEX1;

	ST_PT_VERTEX() {}

	ST_PT_VERTEX(D3DXVECTOR3 _p, D3DXVECTOR2 _t)
	{
		p = _p;
		t = _t;
	}
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2	t;

	static const int FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

	ST_PNT_VERTEX() {}

	ST_PNT_VERTEX(D3DXVECTOR3 _p, D3DXVECTOR3 _n, D3DXVECTOR2 _t)
	{
		p = _p;
		n = _n;
		t = _t;
	}
};