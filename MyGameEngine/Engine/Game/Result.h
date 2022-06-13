#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"
//Resultシーンを管理するクラス
class Result : public GameObject
{
	int hModel_;						//モデル番号を格納する変数
	const float BACK_GROUND_VERTICAL_;	//背景のY軸の高さ
	const float BACK_GROUND_BESIDE_;	//背景のX軸の高さ
	const float BACK_GROUND_DEPTH_;		//背景の奥行
	int resultBGM_;						//BGMを格納する変数
	const string FILE_PAS_;				//リザルト画面のモデルのファイルパス
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Result(GameObject* parent);
	void Initialize() override;		//初期化
	void Update() override;			//更新
	void Draw() override;			//描画
	void Release() override;		//開放
};

