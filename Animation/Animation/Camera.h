#pragma once
#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "GameData.h"
#include <D3DX10math.h>
//#include "Player.h"
class Camera
{
public:
	Camera();
	Camera(const Camera&);
	~Camera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);
	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();
	void Render();
	void GetViewMatrix(D3DXMATRIX&);
	void Initialize();
	//void HandleMovementInput(InputClass*, float);
	void Tick();
	void SetFrameTime(float time);
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	//void SetFollowObject(Player* follow);

	void SetOffset(float, float, float);


private:
	float positionX;
	float positionY;
	float positionZ;
	float rotationX;
	float rotationY;
	float rotationZ;

	float offsetPosX;
	float offsetPosY;
	float offsetPosZ;

	float frameTime;

	float forwardSpeed = 0.0f;
	float backwardSpeed = 0.0f;
	float upwardSpeed = 0.0f;
	float downwardSpeed = 0.0f;
	float leftTurnSpeed = 0.0f;
	float rightTurnSpeed = 0.0f;
	float lookUpSpeed = 0.0f;
	float lookDownSpeed = 0.0f;
	D3DXMATRIX viewMatrix;
	GameData* gameData;
	//Player* player;
	
};
#endif // !_CAMERA_H_
