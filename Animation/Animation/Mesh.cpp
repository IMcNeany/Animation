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

void Mesh::LoadBones(int MeshIndex, const aiMesh* pMesh)
{
	/*a) Create a map or a similar container to store which nodes are necessary for the skeleton.Pre - initialise it for all nodes with a "no".
	b) For each bone in the mesh :
	b1) Find the corresponding node in the scene's hierarchy by comparing their names. 
	b2) Mark this node as "yes" in the necessityMap.
	b3) Mark all of its parents the same way until you 1) find the mesh's node or 2) the parent of the mesh's node.
	c) Recursively iterate over the node hierarchy
	c1) If the node is marked as necessary, copy it into the skeleton and check its children
	c2) If the node is marked as not necessary, skip it and do not iterate over its children.
	*/

	for (int i = 0; i < pMesh->mNumBones; i++) {

		int boneIndex = 0;
		std::string boneName(pMesh->mBones[i]->mName.data);
		pMesh->mBones[i]->mOffsetMatrix;

		for (int j = 0; j < pMesh->mBones[i]->mNumWeights; j++)
		{
			
			VertexBoneData bones;
			//check vertex against vertex id
			bones.IDs= pMesh->mBones[i]->mWeights[j].mVertexId;
			bones.Weights = pMesh->mBones[i]->mWeights[j].mWeight;
			bones.boneName = boneName;
			bones.offset = pMesh->mBones[i]->mOffsetMatrix;
			//bone ID needs to be the position on info in bone list..
			boneList.push_back(bones);
		}

	}
}

int Mesh::GetListSize()
{
	return boneList.size();
}

D3DXVECTOR2 Mesh::GetVertexInfo(int i) {

	D3DXVECTOR2 boneInfo;
	for (int j = 0; j < boneList.size; j++)
	{
		if (i == boneList[j].IDs) 
		{
			boneInfo = D3DXVECTOR2(j, boneList[j].Weights);
			return boneInfo;
		}
	}

	return boneInfo;
}

D3DXMATRIX Mesh::TransformBones(aiScene* pScene, float time) {
	
	D3DXMATRIX identity;
	
	float TicksPerSecond = pScene->mAnimations[0]->mTicksPerSecond != 0 ?
		pScene->mAnimations[0]->mTicksPerSecond : 25.0f;
	float tick = time * TicksPerSecond;
	float AnimationTime = fmod(tick, pScene->mAnimations[0]->mDuration);
	ReadNodeHierarchy(AnimationTime, pScene->mRootNode, identity, pScene);

	//Transforms.resize(m_NumBones);

	//for (int i = 0; i < m_NumBones; i++) {
	//	Transforms[i] = m_BoneInfo[i].FinalTransformation;
	//}
}

void Mesh::ReadNodeHierarchy(float animationTime, aiNode * pNode, D3DXMATRIX parentTransform, aiScene* pScene)
{
	std::string nodeName = pNode->mName.data;

	const aiAnimation* pAnimation = pScene->mAnimations[0];
	//D3DXMATRIX NodeTransformation(pNode->mTransformation);
	const aiNodeAnim* pNodeAnim;// = FindNodeAnim(pAnimation, nodeName);


}

aiBone Mesh::CreateNodeTree(aiNode node, aiBone parent) 
{
	//for (int i = 0; i < boneList.size; i++)
	//{
		//if(boneList[i].IDs)

	//}

}
Mesh::Mesh(const Mesh & mesh)
{
	this->deviceContext = mesh.deviceContext;
	this->indexbuffer = mesh.indexbuffer;
	this->vertexbuffer = mesh.vertexbuffer;
}

void Mesh::Render()
{

	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(Vertex);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, vertexbuffer.GetAddressOf(), &stride, &offset);
	deviceContext->IASetIndexBuffer(indexbuffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}



