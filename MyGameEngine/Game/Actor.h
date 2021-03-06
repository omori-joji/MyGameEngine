#pragma once
#include "../Engine/GameObject.h"
#include "Stage.h"
#include <string>

//クラスの前方宣言
class Stage;

class Actor : public GameObject
{
	char meanTimeGimmickNumber_;		//押している間発動するボタンの1の位
	char no1DoubleGimmickNumber_;		//片方の同時押しボタンの1の位
	char no2DoubleGimmickNumber_;		//もう片方の同時押しボタンの1の位
	bool isPastMeanTimeButton_;			//1フレーム前に同時ボタンを踏んでいるかいないか
	bool isPastDoubleButton_[2];		//1フレーム前に踏んでいる間発動するボタンを踏んでいるかいないか
	int buttonSE_;						//SEを格納する変数
	Stage* pStage_;						//Stageクラスを格納するポインタ
public:
	void Initialize() override;		//初期化
	void Update() override;			//更新
	void Draw() override;			//描画
	void Release() override;		//開放
	Actor(GameObject* parent, const std::string& name);//コンストラクタ

	//踏んでいる間発動するボタンを踏んだ瞬間の処理
	//引数：なし
	//戻り値：なし
	void CommonMeanTimeButtonDown();

	//同時押しボタンの片方を踏んだ瞬間の処理
	//引数：なし
	//戻り値：なし
	void No1DoubleButtonDown();	

	//もう片方の同時押しボタンを踏んだ瞬間の処理
	//引数：なし
	//戻り値：なし
	void No2DoubleButtonDown();
};

