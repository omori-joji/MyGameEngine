#pragma once
#include "Engine/GameObject.h"


//Titleシーンを管理するクラス
class Title : public GameObject
{
	int hModel_[5];
	int imageNum_;
	int chengeCount;

	bool iskeyDown_;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Title(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

