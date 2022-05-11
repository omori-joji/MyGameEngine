#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"


//クラスの前方宣言
class Player;
class Stage;


//Shadowを管理するクラス
class Shadow : public GameObject
{
	const int RESET_VALU_;
	const int ALL_GIMICKS_;
	const float BACK_DRAW_;
	const int MEANTIME_BUTTON_DOWN_;
	const int MEANTIME_BLOCK_ALPHA_;
	const int MATCH_VALU_;
	const int SHADOW_FOOT_;

	
	int shadowDirection_;						//影の向き
	int shadowModelNumber_;						//走っているモデル番号

	bool isShadowPastButton;


	DWORD frameCounter_;						//フレーム数


	std::vector<XMFLOAT3> recordData_;			//プレイヤーの位置を記録する可変長配列
	std::vector<int> recordDirection_;			//Playerの向きを記録する動的配列
	std::vector<int> recordModelNumber_;		//走っているモデル番号を記録する動的配列
	bool isRecording_;							//記録中かどうか


	Player* pPlayer_;							//Playerの情報が入る変数
	Stage* pStage_;								//Stageの情報が入る変数

	enum ShadowDirection
	{
		SDIR_RIGHT,
		SDIR_LEFT,
		SDIR_MAX,

		STANDING_MODEL = 0,
		RUN_MODEL,
	};
	int hModel_[SDIR_MAX][SDIR_MAX];							//影のモデルを格納する多次元配列

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

	//Find処理をまとめる関数
	void AllFind();

	//Playerの動きを記録と再生する関数
	void RecordingandPlayBack();


	//影の表示非表示を管理する関数
	//そのほかにも再生中か記録中かを判断する処理も行う
	void ShadowDisplayFlag();

	void ShadowFootButtonCheck();
};

