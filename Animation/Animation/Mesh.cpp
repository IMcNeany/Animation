#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{

}

Mesh::Mesh(ID3D11Device * device, ID3D11DeviceContext * deviceContext, std::vector<Vertex>& vertices, std::vector<DWORD>& indices)
{
	this->deviceContext = deviceContext;

	HRESULT hr = vertexbuffer.Initialize(device, vertices.data(), vertices.size());
	

	hr = indexbuffer.Initialize(device, indices.data(), indices.size());

}

Mesh::Mesh(const Mesh & mesh)
{
	this->deviceContext = mesh.deviceContext;
	this->indexbuffer = mesh.indexbuffer;
	this->vertexbuffer = mesh.vertexbuffer;
}

void Mesh::Render()
{
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, vertexbuffer.GetAddressOf(), vertexbuffer.StridePtr(), &offset);
	deviceContext->IASetIndexBuffer(indexbuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	deviceContext->DrawIndexed(indexbuffer.BufferSize(), 0, 0);
}