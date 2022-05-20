#pragma once
#include <dInput.h>
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

//解放処理のマクロ
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Input
{
	void Initialize(HWND hWnd);		//初期化
	void Update();					//更新
	void Release();					//解放

	//引数でキーコードを受け取る
	bool IsKey(int keyCode);		//キーを押している間
	bool IsKeyDown(int keyCode);	//キーが押された瞬間
	bool IsKeyUp(int keyCode);		//キーを離した瞬間
};

