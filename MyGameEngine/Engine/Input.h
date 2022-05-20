#pragma once
#include <dInput.h>
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

//��������̃}�N��
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Input
{
	void Initialize(HWND hWnd);		//������
	void Update();					//�X�V
	void Release();					//���

	//�����ŃL�[�R�[�h���󂯎��
	bool IsKey(int keyCode);		//�L�[�������Ă����
	bool IsKeyDown(int keyCode);	//�L�[�������ꂽ�u��
	bool IsKeyUp(int keyCode);		//�L�[�𗣂����u��
};

