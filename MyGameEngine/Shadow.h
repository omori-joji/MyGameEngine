#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include <string>
#include "Player.h"
#include "Stage.h"

//クラスの前方宣言
class Player;
class Stage;


//Shadowを管理するクラス
class Shadow : public GameObject
{
	const int RESET_VALU_;						//初期化用
	const int ALL_GIMICKS_;						//同じ種類のギミックすべてを探すための値
	const int MEANTIME_BUTTON_DOWN_;			//踏んでいる間発動するボタンのモデル番号
	const int MEANTIME_BLOCK_ALPHA_;			//開いている壁のモデル番号
	const int MATCH_VALU_;						//配列の要素数を合わせるための値
	const int SHADOW_FOOT_;						//影の足元を見るための値
	const float BACK_DRAW_;						//Playerに重ならないように少し奥に描画する
	const string filePas_;

	int shadowDirection_;						//影の向き
	int shadowModelNumber_;						//走っているモデル番号
	DWORD frameCounter_;						//フレーム数

	bool isRecording_;							//記録中かどうか
	bool isShadowPastButton_;					//ボタンを踏んでいるか

	std::vector<int> recordDirection_;			//Playerの向きを記録する動的配列
	std::vector<int> recordModelNumber_;		//走っているモデル番号を記録する動的配列
	std::vector<XMFLOAT3> recordData_;			//プレイヤーの位置を記録する可変長配列

	Player* pPlayer_;							//Playerの情報が入る変数
	Stage* pStage_;								//Stageの情報が入る変数

	enum ShadowDirection
	{
		SDIR_RIGHT,								//右向き
		SDIR_LEFT,								//左向き
		SDIR_MAX,								//配列の最大要素数

		STANDING_MODEL = 0,						//立っているモデル番号
		RUN_MODEL,								//走っているモデル番号
	};
	int hModel_[SDIR_MAX][SDIR_MAX];			//影のモデルを格納する多次元配列

public:
	Shadow(GameObject* parent);					//コンストラクタ
	void Initialize() override;					//初期化
	void Update() override;						//更新
	void Draw() override;						//描画
	void Release() override;					//開放
	void ShadowIsPlayFlag();					//影の表示非表示、再生中か記録中かをを管理する関数
	bool GetIsRecording();						//isRecording_を返すためのゲッター

private:
	void AllFind();								//Find処理をまとめる関数
	void RecordingandPlayBack();				//Playerの動きを記録と再生する関数
	void ShadowFootButtonCheck();				//足元を見てボタンを踏んだ瞬間、離れた瞬間の処理をする関数
};

