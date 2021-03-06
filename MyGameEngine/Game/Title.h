#pragma once
#include "../Engine/SceneManager.h"
#include "../Engine/GameObject.h"

//Titleシーンを管理するクラス
class Title : public GameObject
{
	const float BACK_GROUND_VERTICAL_;	//背景のY軸の値
	const float BACK_GROUND_BESIDE_;	//背景のX軸の値
	const float DEPTH_;					//背景の奥行
	const float STAGE_NUMBER_VERTICAL_;	//ステージ番号Y軸の値
	const float STAGE_NUMBER_BESIDE_;	//ステージ番号X軸の値
	const float SCALE_MAGNIFICATION_;	//ステージ番号の奥行
	const float DEPTH_DIFFERRENCE_;		//背景との奥行の差
	int stageNum_;						//移行したいステージのモデル番号
	int imageNum_;						//背景のモデル番号
	const string FILE_PAS_;				//Titleのモデルデータのファイルパス

	//ステージ番号
	enum
	{
		STAGE_NUMVER_1,	//ステージ番号1
		STAGE_NUMVER_2,	//ステージ番号2
		STAGE_NUMVER_3,	//ステージ番号3
		MODELE_NUMVER_4,	//ステージ番号4
		STAGE_NUMBER_MAX,
	};
	//背景のモデル番号
	enum
	{
		BACKGROUND,
		BACKGROUND_NOWLOADING,
		MODELE_MAX,
	};
	//サウンド番号
	enum
	{
		SE_ARROW,			//矢印キーを押したときのSE
		SE_DECISION,		//決定ボタンのSE
		SOUND_BGM,
		SE_MAX,
	};

	int se_[SE_MAX];							//SEを格納する変数
	int hModel_[MODELE_MAX];					//モデルを格納する変数
	int stageNum_Modele_[STAGE_NUMBER_MAX];		//ステージ番号のモデルを格納する変数
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Title(GameObject* parent);
	void Initialize() override;		//初期化
	void Update() override;			//更新
	void Draw() override;			//描画
	void Release() override;		//開放
};

