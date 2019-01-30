#pragma once

#include "Texture.h"
#include<vector>
#include <D3DX10math.h>
using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();
	virtual void SetVelocity(D3DXVECTOR3);
	virtual D3DXVECTOR3 GetVelocity();
	virtual float GetPosX() { return positionX; }
	virtual float GetPosY() { return positionY; }
	virtual float GetPosZ() { return positionZ; }
	virtual D3DXVECTOR3 GetPrevVelocity() { return prevVelocity; }
	virtual ID3D11ShaderResourceView* GetTexture();
	virtual void Render(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
	virtual void Tick(float, ID3D11DeviceContext*);
	virtual int GetIndexCount();
	virtual D3DXVECTOR2 GetMaxMin(D3DXVECTOR3);
	virtual int GetAxisNormalLength();
	virtual D3DXVECTOR3 GetAxis(int);
	virtual bool GetStatic() { return staticObj; }
	virtual D3DXVECTOR3 GetPos();
	virtual D3DXVECTOR3 GetMinAxis();
	virtual void SetPreviousVelocity(D3DXVECTOR3);
	virtual D3DXVECTOR3 GetMaxAxis();
	virtual void SetPos (D3DXVECTOR3);
	virtual void SetColliding(bool);
private:
	D3DXVECTOR3 velocity = D3DXVECTOR3(0.0f,0.0f,0.0f);

	float positionX;
	float positionY;
	float positionZ;
	float rotationX;
	float rotationY;
	float rotationZ;
	bool staticObj = false;
	D3DXVECTOR3 prevVelocity;
	bool colliding;
};
