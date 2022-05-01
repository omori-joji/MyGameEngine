#pragma once
#include "Engine/GameObject.h"

class Title;

//■■シーンを管理するクラス
class Setumei : public GameObject
{

	int hModel_;
	int sceneMoveTime_;

	Title* pTitle;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Setumei(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

