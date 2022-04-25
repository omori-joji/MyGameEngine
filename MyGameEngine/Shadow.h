#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"



class Player;
class Stage;

//■■シーンを管理するクラス
class Shadow : public GameObject
{
	Player* pPlayer_;//Playerの情報が入る変数
	Stage* pStage_;//Stageの情報が入る変数



	int hModel_Right_[2]; //右を向いているモデル
	int hModel_Left_[2];  //左を向いているモデル
	int leftModel_;       //左のモデル番号
	int rightModel_;      //右のモデル番号

	
	bool isRecordCheck_;  //プレイヤーが右を向いているか左を向いているか

	const float sWIDTH;//影の幅
	const float sMARGIN;//当たり判定の遊び


	DWORD frameCounter_;//フレーム数
	std::vector<XMFLOAT3> recordData_;//プレイヤーの位置を記録する可変長配列
	std::vector<bool> recordCheck_;   //記録されているフレーム数の時プレイヤーはどっちに向いているか
	std::vector<int> recordRightMove_;//右のモデル番号を記録する
	std::vector<int> recordLeftMove_;//左のモデル番号を記録する



public:
	bool isRecording_; //Playerの動きを記録しているか

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

	void Flag();
};

