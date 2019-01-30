#include "Camera.h"

Camera::Camera()
{
	positionX = 0.0f;
	positionY = 0.0f;
	positionZ = 0.0f;

	rotationX = 0.0f;
	rotationY = 0.0f;
	rotationZ = 0.0f;

	frameTime = 0.0f;

	forwardSpeed = 0.0f;
	backwardSpeed = 0.0f;
	upwardSpeed = 0.0f;
	downwardSpeed = 0.0f;
	leftTurnSpeed = 0.0f;
	rightTurnSpeed = 0.0f;
	lookUpSpeed = 0.0f;
	lookDownSpeed = 0.0f;
	
}



Camera::Camera(const Camera& other)
{

}

Camera::~Camera()
{

}

void Camera::Initialize()
{
	positionX = 0.0f;
	positionY = 0.0f;
	positionZ = 0.0f;

	rotationX = 0.0f;
	rotationY = 0.0f;
	rotationZ = 0.0f;
	//frameTime = gameData->frameTick;
}

void Camera::SetPosition(float x, float y, float z)
{
	positionX = x;
	positionY = y;
	positionZ = z;
	
}

void Camera::SetOffset(float x, float y , float z)
{
	offsetPosX = x;
	offsetPosY = y;
	offsetPosZ = z;
	SetPosition(x, y, z);
}

void Camera::SetRotation(float x, float y, float z)
{
	rotationX = x;
	rotationY = y;
	rotationZ = z;
}

D3DXVECTOR3 Camera::GetPosition()
{
	return D3DXVECTOR3(positionX, positionY, positionZ);
}

D3DXVECTOR3 Camera::GetRotation()
{
	return D3DXVECTOR3(rotationX, rotationY, rotationZ);
}

void Camera::SetFrameTime(float time)
{
	frameTime = time;
	return;
}
//void Camera::SetFollowObject(Player* follow)
//{
//	player = follow;
//}
void Camera::Tick()
{
//	frameTime = gameData->frameTick;
	bool result;
	float posX, posY, posZ, rotX, rotY, rotZ;

	//positionX = player->GetPos().x + offsetPosX;
	//positionY = player->GetPos().y + offsetPosY;
	//positionZ = player->GetPos().z + offsetPosZ;
	// Do the frame input processing.

	// Get the view point position/rotation.
	//GetPosition(posX, posY, posZ);
	//GetRotation(rotX, rotY, rotZ);

}

void Camera::Render()
{
	D3DXVECTOR3 up, position, lookAt;
	D3DXMATRIX rotationMatrix;
	float yaw;
	float pitch;
	float roll;
	float radians = 0.01745f;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	position.x = positionX;
	position.y = positionY;
	position.z = positionZ;

	lookAt.x = 0.0f;
	lookAt.y = -1.0f;
	lookAt.z = 1.0f;

	pitch = rotationX * radians;
	yaw = rotationY * radians;
	roll = rotationZ * radians;

	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);
	lookAt = position + lookAt;
	D3DXMatrixLookAtLH(&viewMatrix, &position, &lookAt, &up);
}

void Camera::GetViewMatrix(D3DXMATRIX& vMatrix)
{
	vMatrix = viewMatrix;
}


void Camera::MoveForward()
{
	
	float radians;

		forwardSpeed += frameTime * 1.0f;
		if (forwardSpeed > (frameTime * 100.0f))
		{
			forwardSpeed = frameTime * 100.0f;
		}

	radians = rotationY * 0.0174532925f;

	// Update the position.
	positionX += sinf(radians) * forwardSpeed;
	positionZ += cosf(radians) * forwardSpeed;

}

void Camera::MoveBackward()
{
	float radians;

		backwardSpeed += frameTime * 1.0f;

		if (backwardSpeed > (frameTime * 100.0f))
		{
			backwardSpeed = frameTime * 100.0f;
		}

	// Convert degrees to radians.
	radians = rotationY * 0.0174532925f;

	// Update the position.
	positionX -= sinf(radians) * backwardSpeed;
	positionZ -= cosf(radians) * backwardSpeed;

}

void Camera::MoveLeft() {
	float radians;

	forwardSpeed += frameTime * 1.0f;
	if (forwardSpeed > (frameTime * 100.0f))
	{
		forwardSpeed = frameTime * 100.0f;
	}

	radians = rotationY * 0.0174532925f;

	// Update the position.
	positionX -= cosf(radians) * forwardSpeed;
	positionZ += sinf(radians) * forwardSpeed;
}

void Camera::MoveRight() {
	float radians;

	forwardSpeed += frameTime * 1.0f;
	if (forwardSpeed > (frameTime * 100.0f))
	{
		forwardSpeed = frameTime * 100.0f;
	}

	radians = rotationY * 0.0174532925f;

	// Update the position.
	positionX += cosf(radians) * forwardSpeed;
	positionZ -= sinf(radians) * forwardSpeed;
}