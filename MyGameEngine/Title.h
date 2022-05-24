#pragma once
#include "Engine/SceneManager.h"
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"


//Titleシーンを管理するクラス
class Title : public GameObject
{
	int hModel_[3];
	int stageNumModel_[4];
	int se_[2];
	int stageNum_;
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

