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
	int meanTimeGimmickNumber_;
	Stage* pStage_;
	bool isPastMeanTimeButton_;

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
};

