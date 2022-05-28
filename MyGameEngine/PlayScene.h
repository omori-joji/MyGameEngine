#pragma once
#include "Engine/GameObject.h"
//プレイシーンを管理するクラス
class PlayScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);
	void Initialize() override;		//初期化
	void Update() override;			//更新
	void Draw() override;			//描画
	void Release() override;		//開放
};

