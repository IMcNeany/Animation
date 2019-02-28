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
#include <list>

class Mesh
{
public:
	Mesh();
	~Mesh();

	struct Vertex
	{
		Vertex() {}
		Vertex(float x, float y, float z, float u, float v, int id, float weight)
			: pos(x, y, z), texCoord(u, v), boneID(id,weight) {}

		D3DXVECTOR3 pos;
		D3DXVECTOR2 texCoord;
		D3DXVECTOR2 boneID;
	};

	struct VertexBoneData
	{
		int IDs;
		float Weights;
		std::string boneName;
		aiMatrix4x4 offset;
	};

	Mesh(ID3D11Device * device, ID3D11DeviceContext * deviceContext, std::vector<Vertex> & vertices, std::vector<DWORD> & indices);
	void LoadBones(int MeshIndex, const aiMesh* pMesh);
	int GetListSize();
	Mesh(const Mesh & mesh);
	void Render();
	D3DXVECTOR2 GetVertexInfo(int i);
	std::vector<VertexBoneData>boneList;
	D3DXMATRIX TransformBones(aiScene* pScene, float);
	void ReadNodeHierarchy(float animationTime, aiNode * pNode, D3DXMATRIX parentTransform, aiScene* pScene);
	aiBone CreateNodeTree(aiNode node, aiBone parent);
private:

	float boneWeight;
	int boneID;
	int numBones;
	VertexBuffer<Vertex> vertexbuffer;
	IndexBuffer indexbuffer;
	ID3D11DeviceContext * deviceContext;
};


