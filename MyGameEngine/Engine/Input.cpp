#include "Input.h"

namespace Input
{
	//DirectInputDirectInputの用意
	LPDIRECTINPUT8   pDInput = nullptr;

	//キーボードの情報を用意
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;

	//キーの数(一応余分に用意しておく)
	BYTE keyState[256] = { 0 };

	//前フレームでの各キーの状態
	BYTE prevKeyState[256];

	void Initialize(HWND hWnd)
	{
		//DirectInputの用意
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);

		//キーボードの情報を用意
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}

	void Update()
	{
		memcpy(prevKeyState, keyState, sizeof(keyState));

		//何のキーが押されているかを調べる
		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
	}

	//引数で渡されたキーの番号を調べる
	bool IsKey(int keyCode)
	{
		//渡されたキー番号の配列に1が入り、trueが返される
		if (keyState[keyCode] & 0x80) //0x80 != 0の省略
		{
			return true;
		}
		return false;
	}

	//上で作った関数を使い、押した瞬間を取得する
	bool IsKeyDown(int keyCode)
	{
		//今は押してて、前回は押してない
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	//離した瞬間
	bool IsKeyUp(int keyCode)
	{
		//今は押しいない、前回は押していた
		if (!IsKey(keyCode) && (prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	void Release()
	{
		SAFE_RELEASE(pKeyDevice);
		SAFE_RELEASE(pDInput);
	}
}
