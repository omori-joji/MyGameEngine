#pragma once
#include "Engine/GameObject.h"
#include "Actor.h"

//クラスの前方宣言
class Player;
class Stage;

//Shadowを管理するクラス
class Shadow : public Actor
{
	const int MATCH_VALU_;						//配列の要素数を合わせるための値
	const char RESET_VALU_;						//初期化用
	const float BACK_DRAW_;						//Playerに重ならないように少し奥に描画する
	const string file_Pas_;						//モデルが保存されているファイルパス
	int double_Speed_;							//二倍速にするための変数
	char shadow_Direction_;						//影の向き
	char shadow_Model_Number_;					//走っているモデル番号
	bool isRecording_;							//記録中かどうか
	DWORD frame_Counter_;						//フレーム数
	Player* pPlayer_;							//Playerの情報が入る変数
	Stage* pStage_;								//Stageの情報が入る変数

	//可変長配列
	std::vector<int> record_Direction_;			//Playerの向きを記録する動的配列
	std::vector<int> record_Model_Number_;		//走っているモデル番号を記録する動的配列
	std::vector<XMFLOAT3> record_Data_;			//プレイヤーの位置を記録する可変長配列

	//影のモデル番号
	enum S_Model
	{
		S_DIR_RIGHT,							//右向き
		S_DIR_LEFT,								//左向き
		S_DIRMAX,								//配列の最大要素数

		STANDING_MODEL = 0,						//立っているモデル番号
		RUN_MODEL,								//走っているモデル番号
	}s_Modele;
	int hModel_[S_DIRMAX][S_DIRMAX];			//影のモデルを格納する多次元配列
public:
	Shadow(GameObject* parent);					//コンストラクタ
	void Initialize() override;					//初期化
	void Update() override;						//更新
	void Draw() override;						//描画
	void Release() override;					//開放

	//影の表示非表示、再生中か記録中かをを管理する関数
	//引数：なし
	//戻り値：なし
	void ShadowIsPlayFlag();
private:
	//Find処理をまとめる関数
	//引数：なし
	//戻り値：なし
	void AllFind();

	//Playerの動きを記録と再生する関数
	//引数：なし
	//戻り値：なし
	void RecordingandPlayBack();
};

