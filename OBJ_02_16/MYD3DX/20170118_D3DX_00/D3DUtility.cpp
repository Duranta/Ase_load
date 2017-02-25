#include "stdafx.h"
#include "D3DUtility.h"

namespace D3DUTILITY
{
	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
	{
		D3DMATERIAL9 mtrl;
		mtrl.Ambient = a;
		mtrl.Diffuse = d;
		mtrl.Specular = s;
		mtrl.Emissive = e;
		mtrl.Power = p;

		return mtrl;
	}

	void ComputeNormal(D3DXVECTOR3* out, D3DXVECTOR3* p0, D3DXVECTOR3* p1, D3DXVECTOR3* p2)
	{
		D3DXVECTOR3 u = *p1 - *p0;
		D3DXVECTOR3 v = *p2 - *p0;

		D3DXVec3Cross(out, &u, &v);
		D3DXVec3Normalize(out, out);
	}

	D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3* dir, D3DXCOLOR* c)
	{
		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(D3DLIGHT9));

		D3DXVec3Normalize(dir, dir);

		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Ambient = *c * 0.4f;
		light.Diffuse = *c;
		light.Specular = *c * 0.6f;
		light.Direction = *dir;

		return light;
	}

	D3DLIGHT9 InitPointLight(D3DXVECTOR3* pos, D3DXCOLOR* c)
	{
		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(D3DLIGHT9));

		light.Type = D3DLIGHT_POINT;
		light.Ambient = *c * 0.4f;
		light.Diffuse = *c;
		light.Specular = *c * 0.6f;
		light.Position = *pos;
		light.Range = 20.0f;
		light.Falloff = 1.0f;
		light.Attenuation0 = 0.005f;
		light.Attenuation1 = 0.005f;
		light.Attenuation2 = 0.005f;

		return light;
	}

	D3DLIGHT9 D3DUTILITY::InitSpotLight(D3DXVECTOR3* pos, D3DXVECTOR3* dir, D3DXCOLOR* c)
	{
		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(D3DLIGHT9));

		D3DXVec3Normalize(dir, dir);

		light.Type = D3DLIGHT_SPOT;
		light.Ambient = *c * 0.4f;
		light.Diffuse = *c;
		light.Specular = *c * 0.6f;
		light.Position = *pos;
		light.Direction = *dir;
		light.Range = 50.0f;
		light.Falloff = 1.0f;
		light.Theta = 0.0f;
		light.Phi = D3DX_PI / 6;
		light.Attenuation0 = 0.005f;
		light.Attenuation1 = 0.005f;
		light.Attenuation2 = 0.005f;

		return light;
	}
}

