#pragma once
#include <d3d11.h>
#include <assert.h>
#include "Common.h"
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}

//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace Direct3D
{
	//�錾
	extern ID3D11Device* pDevice;
	extern ID3D11DeviceContext* pContext;

	void Initialize(int winW, int winH, HWND hWnd);	//������
	void InitShader();								//�V�F�[�_�[����
	void BeginDraw();								//�`��J�n
	void EndDraw();									//�`��I��
	void Release();									//���
	void Preparation(int winW,int winH, HWND hWnd);
	void RenderTargetView();
	void BlendState();
	void ViewPort(int winW, int winH);
		
};
