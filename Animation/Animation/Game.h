#pragma once

#ifndef GAME_H_
#define GAME_H_

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <windows.h>
#include <list>
#include <dinput.h>
#include<d3d11.h>
#include "GameData.h"
#include "Model.h"
#include "Shaders.h"
//#include "Cube.h"
//#include "grass.h"
//#include "Sphere.h"
//#include "TextureShader.h"
#include "Camera.h"
//#include "triangle.h"
//#include "colorshaderclass.h"
//#include "Environment.h"
//#include "Player.h"
//#include "SAT.h"
#include <string.h>
#include <time.h>
//#include "System.h"
#include "GameObject.h"
#include<vector>
#include "TextureShader.h"
using std::list;
using namespace std;
//using std::unique_ptr;

class Game
{
public:
	Game(ID3D11Device* _pd3dDevice, HWND _hWnd, HINSTANCE _hInstance, D3DXMATRIX, ID3D11DeviceContext*);
	~Game();
	list<GameObject *> gameObjects;
	bool Tick(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX);

	void Draw(ID3D11DeviceContext* _pd3dImmediateContext, D3DXMATRIX, D3DXMATRIX); //render the current game state

	bool ReadKeyboard();
	bool ReadMouse();
	void SetProjectionMatrix(D3DXMATRIX projectMatrix);
	void SetWorldMatrix(D3DXMATRIX wMatrix);



	Texture* texture;
	TextureShader* textureShader;
	//Triangle* triangle;
	//ColorShaderClass* m_ColorShader;
	
protected:
	HWND m_hWnd;
	//input stuff
	IDirectInput8* m_pDirectInput;
	IDirectInputDevice8* m_pKeyboard;
	IDirectInputDevice8* m_mouse;
	unsigned char m_keyboardState[256];
	unsigned char m_prevKeyboardState[256];
	DIMOUSESTATE  m_mouseState;
	GameData* gameData;
	double startTime;
	double currentTime;
	DWORD playTime;
	//TextureShader* textureShader;
	//Cube* cube;
	//Sphere* sphere;
	Camera* camera;
	//Grass* grassBlades;
	//System* system;
	Model* model;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11DepthStencilView* depthStencilView;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;
	D3DXMATRIX worldMatrix;
	IDXGISwapChain* swapChain;
	//list<Cube*> cubeObjects;
	//list<Sphere*> sphereObjects;
	//Environment* environment;
	//Player* player;

	VertexShader vertexshader;
	PixelShader pixelshader;
	ConstantBuffer<CB_VS_vertexshader> cb_vs_vertexshader;
	ConstantBuffer<CB_PS_pixelshader> cb_ps_pixelshader;

	void CheckKeyPressed();
	void CollisionCheck();
	bool SATCheck(GameObject*, GameObject*);
	void AABBCheck();
	float overlap;
	bool doesOverlap(D3DXVECTOR2, D3DXVECTOR2, D3DXVECTOR3);
	//double getOverlap(SAT other);
	void CheckBounds();
	D3DXVECTOR3 collisionAxis;
	bool firstRun = true;
	bool maxA;
};


#endif // !GAME_H_