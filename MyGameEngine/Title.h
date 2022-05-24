#pragma once
#include "Engine/SceneManager.h"
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"


//Titleシーンを管理するクラス
class Title : public GameObject
{
	const int BACK_GROUND_VERTICAL_;
	const int BACK_GROUND_BESIDE_;
	const float DEPTH_;
	const float STAGE_NUMBER_VERTICAL_;
	const float STAGE_NUMBER_BESIDE_;
	const float SCALE_MAGNIFICATION_;

	int stageNum_;
	int imageNum_;
	int chengeCount;
	enum
	{
		MAX_SE = 2,
		MAX_MODELE,
		MAX_STAGE_NUMBER,

	};
	int se_[MAX_SE];
	int hModel_[MAX_MODELE];
	int stageNum_Modele_[MAX_STAGE_NUMBER];

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

