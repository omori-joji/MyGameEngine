#pragma once
#include <d3d11.h>
#include <assert.h>
#include "Common.h"
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}

//リンカ
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace Direct3D
{
	//宣言
	extern ID3D11Device* pDevice;
	extern ID3D11DeviceContext* pContext;

	void Initialize(int winW, int winH, HWND hWnd);	//初期化
	void InitShader();								//シェーダー準備
	void BeginDraw();								//描画開始
	void EndDraw();									//描画終了
	void Release();									//解放
	void Preparation(int winW,int winH, HWND hWnd);
	void RenderTargetView();
	void BlendState();
	void ViewPort(int winW, int winH);
		
};
