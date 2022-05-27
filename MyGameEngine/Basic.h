#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"
#include "Engine/Fbx.h"
#include "Basic.h"
#include "Stage.h"
#include <string>

class Stage;

class Basic : public GameObject
{
	char meanTimeGimmickNumber_;
	char no1DoubleGimmickNumber_;
	char no2DoubleGimmickNumber_;
	Stage* pStage_;
	bool isPastMeanTimeButton_;
	bool isPastDoubleButton_[2];

public:
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	Basic(GameObject* parent, const std::string& name);
	void CommonMeanTimeButtonDown();
	void No1DoubleButtonDown();
	void No2DoubleButtonDown();
};

