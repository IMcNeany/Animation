#include "Texture.h"

Texture::Texture()
{
	texture = 0;
}

Texture::~Texture()
{

}

bool Texture::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;


	// Load the texture in.
	result = D3DX11CreateShaderResourceViewFromFile(device, (LPCSTR)filename, NULL, NULL, &texture, NULL);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void Texture::Shutdown()
{
	// delete texture
	if (texture)
	{
		texture->Release();
		texture = 0;
	}
}

ID3D11ShaderResourceView* Texture::GetTexture()
{
	return texture;
}
