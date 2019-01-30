#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::SetVelocity(D3DXVECTOR3 velocity)
{
}


D3DXVECTOR3 GameObject::GetVelocity()
{
	return velocity;
}

ID3D11ShaderResourceView * GameObject::GetTexture()
{
	return nullptr;
}

void GameObject::Render(ID3D11DeviceContext *, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX)
{
}

void GameObject::Tick(float, ID3D11DeviceContext *)
{

}

int GameObject::GetIndexCount()
{
	return 0;
}

D3DXVECTOR2 GameObject::GetMaxMin(D3DXVECTOR3)
{
	return D3DXVECTOR2 (0.0f, 0.0f);
}

int GameObject::GetAxisNormalLength()
{
	return 0;
}

D3DXVECTOR3 GameObject::GetAxis(int)
{
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

D3DXVECTOR3 GameObject::GetPos()
{
	return D3DXVECTOR3();
}

D3DXVECTOR3 GameObject::GetMinAxis()
{
	return D3DXVECTOR3();
}
void GameObject::SetPreviousVelocity(D3DXVECTOR3 vel)
{
	prevVelocity = vel;
}

D3DXVECTOR3 GameObject::GetMaxAxis()
{
	return D3DXVECTOR3();
}

void GameObject::SetPos(D3DXVECTOR3)
{
}

void GameObject::SetColliding(bool)
{
}
