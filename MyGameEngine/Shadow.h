#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"



class Player;
class Stage;

//■■シーンを管理するクラス
class Shadow : public GameObject
{
	Player* pPlayer_;
	Stage* pStage_;

	int hModel_;
	bool isRecording_; //Playerの動きを記録しているか
	DWORD frameCounter_;
	std::vector<XMFLOAT3>   recordData_;//プレイヤーの位置を記録する可変長配列

public:


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

	void Collision();
};

