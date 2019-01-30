#pragma once
#include "Texture.h"
#include <fstream>
#include <iostream>
#include "Mesh.h"

using namespace std;

class Model
{
public:
	Model();
	~Model();
	void Initialize(std::string filePath, ID3D11Device* device, WCHAR* textureFilename, HWND);
	void Render(ID3D11DeviceContext*, D3DXMATRIX);
	void SetTexture(ID3D11ShaderResourceView * texture);

	D3DXVECTOR3 GetPosition() { return position; };
	D3DXVECTOR3  GetRotation() { return rotation; };
	void SetPosition(D3DXVECTOR3);
	void AdjustPosition(D3DXVECTOR3);
	void SetRotation(D3DXVECTOR3);
	void AdjustRotation(D3DXVECTOR3);
	void SetLookAtPos(D3DXVECTOR3 lookAtPos);
	D3DXVECTOR3  GetForwardVector() {return vec_forward;};
	D3DXVECTOR3  GetRightVector() { return vec_right; };
	D3DXVECTOR3  GetBackwardVector() { return vec_backward; };
	D3DXVECTOR3  GetLeftVector() { return vec_left;};

private:
	std::vector<Mesh> meshes;
	bool LoadModel(const std::string & filePath);
	void ProcessNode(aiNode * node, const aiScene * scene);
	Mesh ProcessMesh(aiMesh * mesh, const aiScene * scene);
	void UpdateWorldMatrix();

	ID3D11Device * device = nullptr;
	ID3D11DeviceContext * deviceContext = nullptr;
	ConstantBuffer<CB_VS_vertexshader> * cb_vs_vertexshader = nullptr;
	ID3D11ShaderResourceView * texture = nullptr;

	D3DXMATRIX* worldMatrix = D3DXMatrixIdentity(worldMatrix);

	
	D3DXVECTOR3 posVector;
	D3DXVECTOR3 rotVector;
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;


	D3DXVECTOR3 DEFAULT_FORWARD_VECTOR = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 DEFAULT_UP_VECTOR = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 DEFAULT_BACKWARD_VECTOR = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	D3DXVECTOR3 DEFAULT_LEFT_VECTOR = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	D3DXVECTOR3 DEFAULT_RIGHT_VECTOR = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	D3DXVECTOR3 vec_forward;
	D3DXVECTOR3 vec_left;
	D3DXVECTOR3 vec_right;
	D3DXVECTOR3 vec_backward;
};

