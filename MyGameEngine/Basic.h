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
	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
	Basic(GameObject* parent, const std::string& name);
	void CommonMeanTimeButtonDown();
};

