#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::Initialize(std::string filePath, ID3D11Device * device, WCHAR * textureFilename, HWND)
{
	device = device;
	deviceContext = deviceContext;
	texture = texture;
	cb_vs_vertexshader = cb_vs_vertexshader;

	if (!LoadModel(filePath))
	{
		//return false;
		//error
	}


	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	UpdateWorldMatrix();

}

void Model::SetTexture(ID3D11ShaderResourceView * texture)
{
	texture = texture;
}

void Model::Render(ID3D11DeviceContext*, D3DXMATRIX viewProjectionMatrix)
{
	//Update Constant buffer with WVP Matrix
	D3DXMATRIX worldViewProjection;
	D3DXMatrixMultiply(&worldViewProjection, worldMatrix, &viewProjectionMatrix);
	cb_vs_vertexshader->data.mat = worldViewProjection; //viewProjectionMatrix; //Calculate World-View-Projection Matrix
	D3DXMatrixTranspose(&cb_vs_vertexshader->data.mat, &cb_vs_vertexshader->data.mat); //XMMatrixTranspose(cb_vs_vertexshader->data.mat);
	cb_vs_vertexshader->ApplyChanges();
	deviceContext->VSSetConstantBuffers(0, 1, cb_vs_vertexshader->GetAddressOf());

	deviceContext->PSSetShaderResources(0, 1, &texture); //Set Texture

	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Render();
	}
}

bool Model::LoadModel(const std::string & filePath)
{
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(filePath,
		aiProcess_Triangulate |
		aiProcess_ConvertToLeftHanded);

	if (pScene == nullptr)
		return false;

	ProcessNode(pScene->mRootNode, pScene);
	return true;
}

void Model::ProcessNode(aiNode * node, const aiScene * scene)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{
	// Data to fill
	std::vector<Mesh::Vertex> vertices;
	std::vector<DWORD> indices;

	//Get vertices
	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		Mesh::Vertex vertex;
		vertex.pos.x = mesh->mVertices[i].x;
		vertex.pos.y = mesh->mVertices[i].y;
		vertex.pos.z = mesh->mVertices[i].z;

		if (mesh->mTextureCoords[0])
		{
			vertex.texCoord.x = (float)mesh->mTextureCoords[0][i].x;
			vertex.texCoord.y = (float)mesh->mTextureCoords[0][i].y;
		}

		vertices.push_back(vertex);
	}

	//Get indices
	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	return Mesh(device, deviceContext, vertices, indices);
}

void Model::UpdateWorldMatrix()
{
	D3DXMatrixRotationYawPitchRoll(worldMatrix, rotation.y, rotation.x, rotation.z); 
	D3DXMatrixTranslation(worldMatrix, position.x, position.y, position.z);
	//this->worldMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z) * XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, 0.0f, 0.0f, rotation.y);
	//XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
	D3DXVec3TransformCoord(&vec_forward, &DEFAULT_FORWARD_VECTOR, &rotationMatrix);
	D3DXVec3TransformCoord(&vec_backward, &DEFAULT_BACKWARD_VECTOR, &rotationMatrix);
	D3DXVec3TransformCoord(&vec_left, &DEFAULT_LEFT_VECTOR, &rotationMatrix);
	D3DXVec3TransformCoord(&vec_right, &DEFAULT_RIGHT_VECTOR, &rotationMatrix);
	//this->vec_forward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
	//this->vec_backward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecRotationMatrix);
	//this->vec_left = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix);
	//this->vec_right = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatrix);
}

void Model::SetPosition(D3DXVECTOR3 pos)
{
	position = pos;
	posVector = position;
	UpdateWorldMatrix();
}


void Model::AdjustPosition(D3DXVECTOR3 pos)
{
	position.x += pos.y;
	position.y += pos.y;
	position.z += pos.z;
	posVector =position;
	this->UpdateWorldMatrix();
}


void Model::SetRotation(D3DXVECTOR3 rot)
{
	rotation = rot;
	rotVector = rotation;
	UpdateWorldMatrix();
}


void Model::AdjustRotation(D3DXVECTOR3 rot)
{
	rotVector += rot;
	rotVector = rotation;
	this->UpdateWorldMatrix();
}

void Model::SetLookAtPos(D3DXVECTOR3 lookAtPos)
{
	//Verify that look at pos is not the same as cam pos. They cannot be the same as that wouldn't make sense and would result in undefined behavior.
	if (lookAtPos.x == position.x && lookAtPos.y == position.y && lookAtPos.z == this->position.z)
		return;

	lookAtPos.x = position.x - lookAtPos.x;
	lookAtPos.y = position.y - lookAtPos.y;
	lookAtPos.z = position.z - lookAtPos.z;

	float pitch = 0.0f;
	if (lookAtPos.y != 0.0f)
	{
		const float distance = sqrt(lookAtPos.x * lookAtPos.x + lookAtPos.z * lookAtPos.z);
		pitch = atan(lookAtPos.y / distance);
	}

	float yaw = 0.0f;
	if (lookAtPos.x != 0.0f)
	{
		yaw = atan(lookAtPos.x / lookAtPos.z);
	}
	if (lookAtPos.z > 0)
		yaw += D3DX_PI;

	SetRotation(D3DXVECTOR3(pitch, yaw, 0.0f));
}


