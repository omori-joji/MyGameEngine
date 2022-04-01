#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"


//■■シーンを管理するクラス
class Shadow : public GameObject
{
	Player* pPlayer_;

	int hModel_;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Shadow(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

