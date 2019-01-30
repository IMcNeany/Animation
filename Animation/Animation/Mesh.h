#pragma once
//#include "Vertex.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
//#include<D3DX10.h>
//#include <D3DX11.h>
#include <scene.h>
#include<Importer.hpp>
#include <postprocess.h>


class Mesh
{
public:
	Mesh();
	~Mesh();

	struct Vertex
	{
		Vertex() {}
		Vertex(float x, float y, float z, float u, float v)
			: pos(x, y, z), texCoord(u, v) {}

		D3DXVECTOR3 pos;
		D3DXVECTOR2 texCoord;
	};

	Mesh(ID3D11Device * device, ID3D11DeviceContext * deviceContext, std::vector<Vertex> & vertices, std::vector<DWORD> & indices);
	Mesh(const Mesh & mesh);
	void Render();
private:



	VertexBuffer<Vertex> vertexbuffer;
	IndexBuffer indexbuffer;
	ID3D11DeviceContext * deviceContext;
};


