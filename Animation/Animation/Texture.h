#pragma once
#ifndef _TEXTURECLASS_H_
#define _TEXTURECLASS_H_

#include <d3d11.h>
#include <d3dx11tex.h>
#include <string>

class Texture
{
public:
	Texture();
	~Texture();
	bool Initialize(ID3D11Device*, std::string);
	void Shutdown();
	ID3D11ShaderResourceView* GetTexture();

private:
	ID3D11ShaderResourceView* texture;
};

#endif