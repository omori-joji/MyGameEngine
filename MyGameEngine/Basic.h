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
	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;
	Basic(GameObject* parent, const std::string& name);
	void CommonMeanTimeButtonDown();
	void No1DoubleButtonDown();
	void No2DoubleButtonDown();
};

