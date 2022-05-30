#pragma once
#include <xaudio2.h>
#include <vector>
#include <vector>
#include <string>
#include "Common.h"
//#include "Sound.h"


//-----------------------------------------------------------
//効果音を管理する
//-----------------------------------------------------------
namespace Audio
{
	//初期化
	//引数：hWnd	ウィンドウハンドル
	void Initialize();


	//サウンドファイルをロード
	//すでに同じ名前のファイルをロード済みの場合は、既存のデータの番号を返す
	//引数：fileName　ファイル名
	//戻値：そのサウンドデータに割り当てられた番号
	int Load(std::string fileName, int svNuM);

	//再生
	//引数：handle	再生したいサウンドの番号
	void Play(int handle);

	//停止
	//引数：handle	止めたいサウンドの番号
	void Stop(int handle);

	//任意のサウンドを開放
	//引数：handle	開放したいサウンドの番号
	void Release();
}