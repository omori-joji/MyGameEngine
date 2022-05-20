#include "Input.h"

//名前空間
namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;			//DirectInputの用意
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;	//キーボードの情報を用意	
	BYTE keyState[256] = { 0 };					//キーの数(一応余分に用意しておく)
	BYTE prevKeyState[256];						//前フレームでの各キーの状態

	//初期化
	void Initialize(HWND hWnd)
	{
		//DirectInputの用意
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);

		//キーボードの情報を用意
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}

	//更新
	void Update()
	{
		memcpy(prevKeyState, keyState, sizeof(keyState));

		//何のキーが押されているかを調べる
		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
	}

	//引数でキーコードを受け取る
	//押されているかを調べるので戻り値はbool型にする
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
	//押した瞬間を調べるので戻り値はbool型にする
	bool IsKeyDown(int keyCode)
	{
		//今は押してて、前回は押してない
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	//離した瞬間を調べる
	//離れた瞬間を調べるので戻り値はbool型にする
	bool IsKeyUp(int keyCode)
	{
		//今は押しいない、前回は押していた
		if (!IsKey(keyCode) && (prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	//解放
	void Release()
	{
		SAFE_RELEASE(pKeyDevice);
		SAFE_RELEASE(pDInput);
	}
}
