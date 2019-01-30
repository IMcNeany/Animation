#include "Game.h"

Game::Game(ID3D11Device* _pd3dDevice, HWND _hWnd, HINSTANCE _hInstance)
{
	m_hWnd = _hWnd;
	gameData = new GameData;
	gameData->m_keyboardState = m_keyboardState;
	gameData->m_prevKeyboardState = m_prevKeyboardState;
	gameData->m_mouseState = &m_mouseState;
	m_pKeyboard = nullptr;
	m_pDirectInput = nullptr;
	m_mouse = nullptr;

	//ShowCursor(true);

	RECT rc;
	GetClientRect(_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	float AR = (float)width / (float)height;

	//Direct Input Stuff
	HRESULT hr = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&m_pDirectInput, NULL);
	hr = m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL);
	hr = m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);
	hr = m_pKeyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND |
		DISCL_NONEXCLUSIVE);

	//Direct Mouse input stuff
	hr = m_pDirectInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	hr = m_mouse->SetDataFormat(&c_dfDIMouse);
	hr = m_mouse->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND |
		DISCL_NONEXCLUSIVE);
	// Create the texture shader object.

	//set current frame time as otherwise won't be initilised for player
	DWORD currentTime = GetTickCount();
	float dt = min((float)(currentTime - playTime) / 1000.0f, 0.1f);
	gameData->frameTick = dt;
	playTime = currentTime;
	//camera->SetFrameTime((float)gameData->frameTick);


	camera = new Camera;
	//camera->SetPosition(10.0f, 10.0f, 10.0f);
	//camera->SetOffset(10.0f, 30.0f, -10.0f);
	camera->SetOffset(0.0f, 3.0f, -5.0f);

	

	/*grassBlades = new Grass();
	grassBlades->Initialize(_pd3dDevice, L"../Animation/data/grass.dds", _hWnd);
	grassBlades->SetPos(D3DXVECTOR3(1, -3, 0));
	grassBlades->SetStatic(true);
	grassBlades->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	grassBlades->SetWorldMatrix(worldMatrix);
	gameObjects.push_back(grassBlades);*/
	
	////loads in the environment assets
	////environment = new Environment(_pd3dDevice,_hWnd);

 // camera->SetFollowObject(player);
	/////////////////////
	/////Load in objects ////
	////////////////////
	////triangle = new Triangle();
	////triangle->Initialize(_pd3dDevice);

	//float a = 0;
	//float b = -4;
	//float c = 0;

	///* for (int i = 0; i < 3; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		cube = new Cube();
	//		cube->Initialize(_pd3dDevice, L"../Collision Engine/data//dots.dds", _hWnd);
	//		cube->SetPos((D3DXVECTOR3(a, b, c)));
	//		cube->SetStatic(true);
	//		cube->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//		gameObjects.push_back(cube);

	//		a += 1;
	//	}
	//	c += 1;
	//	a = 0;
	//}*/
	//sphere = new Sphere();
	//sphere->Initialize(_pd3dDevice, L"../Animation/data/dots.dds", _hWnd);
	//sphere->SetPos(D3DXVECTOR3(3, 5, 0));
	//sphere->SetStatic(false);
	//sphere->SetVelocity(D3DXVECTOR3(-1, 0, 0));
	//gameObjects.push_back(sphere);

	 //spawn spheres
	// srand(time(NULL));
	//	 random_integer = lowest + rand() % range

	/* for (int i = 0; i < 20; i++)
	 {
		 int posX = rand() % 30 + 0;
		 int posY = rand() % 30 + 0;
		 int posZ = rand() % 30 + 0;

		 int velX = rand() % 10 + -5;
		 int velY = rand() % 10 + -5;// -5 + rand() % 5 + 1;
		 int velZ = rand() % 10 + -5;// -5 + rand() % 5 + 1;
		 char  msg[300];

		 sprintf_s(msg, "X variable is %d\n ", velX);
		 OutputDebugStringA(msg);

		 grassBlades = new Grass();
		 grassBlades->Initialize(_pd3dDevice, L"../Animation/data/grass.dds", _hWnd);
		 grassBlades->SetPos(D3DXVECTOR3(posX, posY, posZ));
		 grassBlades->SetStatic(false);
		 grassBlades->SetVelocity(D3DXVECTOR3(velX, velY, velZ));
		 gameObjects.push_back(grassBlades);
	 }*/

/*	

	//cube = new Cube();
	//cube->Initialize(_pd3dDevice, L"../Collision Engine/data/dots.dds", _hWnd);
	//cube->SetStatic(true);
	//cube->SetPos(D3DXVECTOR3(0, 0, 0));
	//cube->SetVelocity(D3DXVECTOR3(0.0f,0.0f,0.0f));
	////cubeObjects.push_back(cube);
	//gameObjects.push_back(cube);

	//cube = new Cube();
	//cube->Initialize(_pd3dDevice, L"../Collision Engine/data/companion_cube.dds", _hWnd);
	//cube->SetStatic(true);
	//cube->SetPos(D3DXVECTOR3(3, 0, 0));
	//cube->SetVelocity(D3DXVECTOR3 (-3.0f,0.0f,0.0f));
	//gameObjects.push_back(cube);

	//m_ColorShader = new ColorShaderClass;
	//m_ColorShader->Initialize(_pd3dDevice, _hWnd);


	/*cube = new Cube();
	cube->Initialize(_pd3dDevice, L"../Collision Engine/data/dots.dds", _hWnd);
	cube->SetStatic(true);
	cube->SetPos(D3DXVECTOR3(6, 0, 0));
	cube->SetVelocity(D3DXVECTOR3(0.0f,0.0f,0.0f));
	gameObjects.push_back(cube);*/


	//textureShader = new TextureShader;
	//textureShader->Initialize(_pd3dDevice, _hWnd);

	startTime = GetTickCount();

}

bool Game::ReadKeyboard()
{
	//copy over old keyboard state
	memcpy(m_prevKeyboardState, m_keyboardState, sizeof(unsigned char) * 256);
	//clear out previous state
	ZeroMemory(&m_keyboardState, sizeof(m_keyboardState));
	// Read the keyboard device.
	HRESULT hr = m_pKeyboard->GetDeviceState(sizeof(m_keyboardState),
		(LPVOID)&m_keyboardState);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			m_pKeyboard->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool Game::ReadMouse()
{
	//clear out previous state
	ZeroMemory(&m_mouseState, sizeof(m_mouseState));
	// Read the keyboard device.
	HRESULT hr = m_mouse->GetDeviceState(sizeof(m_mouseState),
		(LPVOID)&m_mouseState);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
};

Game::~Game()
{
	if (m_pKeyboard)
	{
		m_pKeyboard->Unacquire();
		m_pKeyboard->Release();
	}


	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
	}

	if (m_pDirectInput)
	{
		m_pDirectInput->Release();
	}
	delete gameData;
}

bool Game::Tick(ID3D11DeviceContext* _pd3dImmediateContext, D3DXMATRIX projectionMatrix, D3DXMATRIX worldMatrix)
{

	
	CheckBounds();
	CollisionCheck();
	//read input in
	ReadKeyboard();
	ReadMouse();

	//if esc pressed close application
	if (m_keyboardState[DIK_ESCAPE] & 0x80)
	{
		return false;
	}

	DWORD currentTime = GetTickCount();
	float dt = min((float)(currentTime - playTime) / 1000.0f, 0.1f);
	gameData->frameTick = dt;
	playTime = currentTime;
	camera->SetFrameTime((float)gameData->frameTick);
	//player->SetFrameTime((float)gameData->frameTick);
	CheckKeyPressed();

	//need to change for all objects
	for (list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		(*it)->Tick(gameData->frameTick, _pd3dImmediateContext);
	}

	//player->Tick(gameData->frameTick, _pd3dImmediateContext);
	camera->Tick();
	//environment->Tick(gameData->frameTick, _pd3dImmediateContext);
Draw(_pd3dImmediateContext, projectionMatrix, worldMatrix);
return true;
}


void Game::Draw(ID3D11DeviceContext* _pd3dImmediateContext, D3DXMATRIX projectionMatrix, D3DXMATRIX worldMatrix)
{
	bool result;

	camera->Render();

	camera->GetViewMatrix(viewMatrix);

	//textureShader->Render(_pd3dImmediateContext, player->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		//player->GetTexture());
	//rotation
	//D3DXMatrixRotationX(&worldMatrix, 1.0f);
	for (list<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		(*it)->Render(_pd3dImmediateContext, worldMatrix, viewMatrix, projectionMatrix);
	//	textureShader->Render(_pd3dImmediateContext, (*it)->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		//	(*it)->GetTexture());
	}


	//environment->Render(_pd3dImmediateContext, worldMatrix, viewMatrix, projectionMatrix);

//	textureShader->Render(_pd3dImmediateContext, cube->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//	cube->GetTexture());
}


void Game::SetProjectionMatrix(D3DXMATRIX projectMatrix)
{
	projectionMatrix* projectMatrix;
}

void Game::SetWorldMatrix(D3DXMATRIX wMatrix)
{
	worldMatrix = wMatrix;
}

void Game::CheckKeyPressed() {

	if (m_keyboardState[DIK_W] & 0x80)
	{
		//player->MoveForward();
		camera->MoveForward();
	}
	if (m_keyboardState[DIK_S] & 0x80)
	{
		//player->MoveBackward();
		camera->MoveBackward();
	}
	if (m_keyboardState[DIK_A] & 0x80)
	{
		//player->MoveLeft();
		camera->MoveLeft();
	}
	if (m_keyboardState[DIK_D] & 0x80)
	{
		//player->MoveRight();
		camera->MoveRight();
	}
}

void Game::CheckBounds() 
{

	for (list<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); i++)
	{
		if ((*i)->GetPosX() < -20 || (*i)->GetPosX() > 50 
			|| (*i)->GetPosY() < -20 || (*i)->GetPosY() > 50
			|| (*i)->GetPosZ() < -20 || (*i)->GetPosZ() > 50)
		{
			int posX = rand() % 20 + 1;
			int posY = rand() % 20 + 1;
			int posZ = rand() % 20 + 1;

			(*i)->SetPos(D3DXVECTOR3(posX, posY, posZ));
		}
	}
}

void Game::CollisionCheck()
{

	//AABBCheck();


	for (list<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); i++)
	{

		for (list<GameObject*>::iterator j = gameObjects.begin(); j != gameObjects.end(); j++)
		{
			(*i)->SetPreviousVelocity((*i)->GetVelocity());
			(*j)->SetPreviousVelocity((*j)->GetVelocity());
			if (i == j)
			{

			}
			else
			{

				if ((*i)->GetPosX() >= ((*j)->GetPosX() - 2.0f) && ((*i)->GetPosX() <= (*j)->GetPosX() + 2.0f)
					&& ((*i)->GetPosZ() >= (*j)->GetPosZ() - 2.0f) && ((*i)->GetPosZ() <= (*j)->GetPosZ() + 2.0f))
				{ 
					if (SATCheck((*i), (*j)))
					{
						(*i)->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						(*j)->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						(*i)->SetColliding(true);
						(*j)->SetColliding(true);
						if (!(*i)->GetStatic() && (*j)->GetStatic())
						{

							D3DXVECTOR3 pos = (*i)->GetPos() - (*j)->GetPos();
							OutputDebugStringA("COLLIDES J still\n");
							float dir = D3DXVec3Dot(&collisionAxis, &pos);
							
							if (dir > 0)
							{
								(*i)->SetPos((*i)->GetPos() + (collisionAxis* (0.1)));
							}
							else
							{
								(*i)->SetPos((*i)->GetPos() - (collisionAxis* (0.1)));
							}
							//(*j)->SetVelocity(D3DXVECTOR3((*j)->GetVelocity().x * -1, (*j)->GetVelocity().y * -1, (*j)->GetVelocity().z * -1));
							(*i)->SetVelocity(D3DXVECTOR3((*i)->GetPrevVelocity().x * -1, (*i)->GetPrevVelocity().y * -1, (*i)->GetPrevVelocity().z * -1));
						}
						if (!(*j)->GetStatic() && (*i)->GetStatic())
						{
							D3DXVECTOR3 pos = (*j)->GetPos() - (*i)->GetPos();
							OutputDebugStringA("COLLIDES I still\n");
							float dir = D3DXVec3Dot(&collisionAxis, &pos);

							if (dir > 0)
							{
								(*j)->SetPos((*j)->GetPos() + (collisionAxis* (0.1)));
							}
							else
							{
								(*j)->SetPos((*j)->GetPos() - (collisionAxis* (0.1)));
							}
							(*j)->SetVelocity(D3DXVECTOR3((*j)->GetPrevVelocity().x * -1, (*j)->GetPrevVelocity().y * -1, (*j)->GetPrevVelocity().z * -1));
							//(*i)->SetVelocity(D3DXVECTOR3((*i)->GetVelocity().x * -1, (*i)->GetVelocity().y * -1, (*i)->GetVelocity().z * -1));

						}
						else if (!(*j)->GetStatic() && !(*i)->GetStatic())
						{
							D3DXVECTOR3 pos = (*j)->GetPos() - (*i)->GetPos();

							float dir = D3DXVec3Dot(&collisionAxis, &pos);
							
							
							if (dir > 0)
							{
								//(*j)->SetPos((*j)->GetPos() + (collisionAxis* (0.1)));
								//(*i)->SetPos((*i)->GetPos() + (collisionAxis* (0.1)));
								(*j)->SetVelocity(D3DXVECTOR3((*j)->GetPrevVelocity().x * -1, (*j)->GetPrevVelocity().y * -1, (*j)->GetPrevVelocity().z * -1));
								(*i)->SetVelocity(D3DXVECTOR3((*i)->GetPrevVelocity().x * -1, (*i)->GetPrevVelocity().y * -1, (*i)->GetPrevVelocity().z * -1));
							}
							else
							{
								//(*j)->SetPos((*j)->GetPos() - (collisionAxis* (0.1)));
								//(*i)->SetPos((*i)->GetPos() - (collisionAxis* (0.1)));
								(*j)->SetVelocity(D3DXVECTOR3((*j)->GetPrevVelocity().x * -1, (*j)->GetPrevVelocity().y * -1, (*j)->GetPrevVelocity().z * -1));
								(*i)->SetVelocity(D3DXVECTOR3((*i)->GetPrevVelocity().x * -1, (*i)->GetPrevVelocity().y * -1, (*i)->GetPrevVelocity().z * -1));
							}

						}
					}

				}
				else
				{
					(*i)->SetColliding(false);
					(*j)->SetColliding(false);

					//(*i)->SetVelocity(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
					//(*j)->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
			
					
			}
		}
	}


}

bool Game::SATCheck(GameObject* i, GameObject* j)
{
	vector<D3DXVECTOR3> obj1Axis;
	vector<D3DXVECTOR3> obj2Axis;
	obj1Axis.clear();
	for (int k = 0; k < (i)->GetAxisNormalLength(); k++)
	{
		obj1Axis.push_back((i)->GetAxis(k));
	}

	obj2Axis.clear();
	for (int k = 0; k < (j)->GetAxisNormalLength(); k++)
	{
		obj2Axis.push_back((j)->GetAxis(k));
	}

	for (int k = 0; k < obj1Axis.size(); k++)
	{
		D3DXVECTOR3 axis = obj1Axis.at(k);
		D3DXVECTOR2 projection1 = (i)->GetMaxMin(axis);
		D3DXVECTOR2 projection2 = (j)->GetMaxMin(axis);
	
		if (doesOverlap(projection1, projection2, axis))
		{
			//shapes don't overlap
			return false;
		}
		
	}

	for (int k = 0; k < obj2Axis.size(); k++)
		{
		D3DXVECTOR3 axis = obj2Axis.at(k);

		D3DXVECTOR2 projection1 = (i)->GetMaxMin(axis);
		D3DXVECTOR2 projection2 = (j)->GetMaxMin(axis);

		if (doesOverlap(projection1,projection2,axis))
		{
		//shapes don't overlap
			return false;
		}
	}

	return true;
}

bool Game::doesOverlap(D3DXVECTOR2 projection1, D3DXVECTOR2 projection2, D3DXVECTOR3 axis)
{
	float max = projection1.x;
	float min = projection1.y;

	float maxB = projection2.x;
	float minB = projection2.y;

	//get min axis and max axis
	if (max < minB || min > maxB) {

		if (max < minB)
		{
			overlap = max - minB;
			collisionAxis = axis;

			return true;
		}
		else if (min > maxB)
		{
			overlap = min - maxB;
			collisionAxis = axis;
			return true;
		}
		
		return true;
	}
	return false;
}

void Game::AABBCheck() {
	//this is AABB
	for (list<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); i++)
	{
		for (list<GameObject*>::iterator j = gameObjects.begin(); j != gameObjects.end(); j++)
		{
			if (i == j)
			{
			}
			else
			{
				if ((*i)->GetPosX() >= ((*j)->GetPosX() - 1.0f) && ((*i)->GetPosX() <= (*j)->GetPosX() + 1.0f)
				&& ((*i)->GetPosZ() >= (*j)->GetPosZ() - 1.0f) && ((*i)->GetPosZ() <= (*j)->GetPosZ() + 1.0f))
				{
					//need to make different just to reverse velocity..
					if ((*i)->GetVelocity() == D3DXVECTOR3(3.0f,0.0f,0.0f))
					{
						(*i)->SetVelocity(D3DXVECTOR3(-3.0f, 0.0f, 0.0f));
						(*j)->SetVelocity(D3DXVECTOR3(3.0f, 0.0f, 0.0f));
					}
					else if ((*i)->GetVelocity() == D3DXVECTOR3(-3.0f, 0.0f, 0.0f))
					{
						(*i)->SetVelocity(D3DXVECTOR3(3.0f, 0.0f, 0.0f));
						(*j)->SetVelocity(D3DXVECTOR3(-3.0f, 0.0f, 0.0f));
					}

				}
			}
		}
	}
}