#pragma once
#include "Engine/SceneManager.h"
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"

//Titleシーンを管理するクラス
class Title : public GameObject
{
	const int BACK_GROUND_VERTICAL_;	//背景のY軸の値
	const int BACK_GROUND_BESIDE_;		//背景のX軸の値
	const float DEPTH_;					//背景の奥行
	const float STAGE_NUMBER_VERTICAL_;	//ステージ番号Y軸の値
	const float STAGE_NUMBER_BESIDE_;	//ステージ番号X軸の値
	const float SCALE_MAGNIFICATION_;	//ステージ番号の奥行
	int stageNum_;//移行したいステージのモデル番号
	int imageNum_;//背景のモデル番号

	enum
	{
		MODELE_NUMVER_1,
		MODELE_NUMVER_2,
		MODELE_NUMVER_3,
		MODELE_NUMVER_4,

		SE_NUMBER_1 = 0,
		SE_NUMBER_2,

		MAX_SE = 2,
		MAX_MODELE,
		MAX_STAGE_NUMBER,
	};
	int se_[MAX_SE];							//SEを格納する変数
	int hModel_[MAX_MODELE];					//モデルを格納する変数
	int stageNum_Modele_[MAX_STAGE_NUMBER];		//ステージ番号のモデルを格納する変数
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Title(GameObject* parent);
	void Initialize() override;		//初期化
	void Update() override;			//更新
	void Draw() override;			//描画
	void Release() override;		//開放
};

