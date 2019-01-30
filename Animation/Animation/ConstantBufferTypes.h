#pragma once
#include <D3DX10math.h>

struct CB_VS_vertexshader
{
	D3DXMATRIX mat;
};

struct CB_PS_pixelshader
{
	float alpha = 1.0f;
};