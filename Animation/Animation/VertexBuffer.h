#pragma once
#ifndef VertexBuffer_h__
#define VertexBuffer_h__
#include <d3d11.h>
#include <wrl/client.h>
#include <memory>

template<class T>
class VertexBuffer
{
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	std::shared_ptr<UINT> stride;
	int bufferSize = 0;

public:
	VertexBuffer() {}


	VertexBuffer(const VertexBuffer<T>& rhs)
	{
		buffer = rhs.buffer;
		bufferSize = rhs.bufferSize;
		stride = rhs.stride;
	}

	VertexBuffer<T> & operator=(const VertexBuffer<T>& a)
	{
		buffer = a.buffer;
		bufferSize = a.bufferSize;
		stride = a.stride;
		return *this;
	}

	ID3D11Buffer* Get()const
	{
		return buffer.Get();
	}

	ID3D11Buffer* const* GetAddressOf()const
	{
		return buffer.GetAddressOf();
	}

	int BufferSize() const
	{
		return bufferSize;
	}

	const int Stride() const
	{
		return *stride.get();
	}

	const UINT * StridePtr() const
	{
		return stride.get();
	}

	HRESULT Initialize(ID3D11Device *device, T * data, int numVertices)
	{
		if (buffer.Get() != nullptr)
			buffer.Reset();

		bufferSize = numVertices;
		if (stride.get() == nullptr)
			stride = std::make_shared<UINT>(sizeof(T));

		D3D11_BUFFER_DESC vertexBufferDesc;
		ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(T) * numVertices;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA vertexBufferData;
		ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
		vertexBufferData.pSysMem = data;

		HRESULT hr = device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, buffer.GetAddressOf());
		return hr;
	}
};
#endif