#pragma once

#ifndef _SYSTEM_H_
#define _SYSTEM_H_
#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "dxgi.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "assimp.lib")

#include <Windows.h>
#include <dxgi.h>
#include<d3d11.h>
#include <D3DX10.h>
#include "Game.h"

class System
{
public:
	System();
	~System();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);


	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(D3DXMATRIX&);
	void GetWorldMatrix(D3DXMATRIX&);
	void GetOrthoMatrix(D3DXMATRIX&);
private:
	bool Tick();
	void BeginScene(float red, float green, float blue, float alpha);
	void EndScene();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

	LPCSTR applicationName;
	HINSTANCE hinstance;
	HWND hwnd;

	const bool vsync = false;
	const float screenDepth = 1000.0f;
	const float screenNear = 0.1f;

	bool vsync_enabled;
	int videoCardMemory;
	char videoCardDescription[128];
	IDXGISwapChain* swapChain;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11RasterizerState* rasterState;
	D3DXMATRIX projectionMatrix;
	D3DXMATRIX worldMatrix;
	D3DXMATRIX orthoMatrix;
	Game* game;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static System* ApplicationHandle = 0;
#endif // !_SYSTEM_H_