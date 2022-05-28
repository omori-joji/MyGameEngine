#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
//Resultシーンを管理するクラス
class Result : public GameObject
{
	int hModel_;						//モデル番号を格納する変数
	const int BACK_GROUND_VERTICAL_;	//背景のY軸の高さ
	const int BACK_GROUND_BESIDE_;		//背景のX軸の高さ
	const float BACK_GROUND_DEPTH_;		//背景の奥行
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Result(GameObject* parent);
	void Initialize() override;		//初期化
	void Update() override;			//更新
	void Draw() override;			//描画
	void Release() override;		//開放
};

