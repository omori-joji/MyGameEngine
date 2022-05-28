#include "Basic.h"

//初期化
void Basic::Initialize()
{
}

//更新
void Basic::Update()
{
}

//描画
void Basic::Draw()
{
}

//解放
void Basic::Release()
{
}

//コンストラクタ
Basic::Basic(GameObject* parent, const std::string& name)
	:GameObject(parent, name),
	meanTimeGimmickNumber_(0),			//押している間発動するボタンの1の位
	no1DoubleGimmickNumber_(0),			//片方の同時押しボタンの1の位
	no2DoubleGimmickNumber_(0),			//もう片方の同時押しボタンの1の位
	isPastDoubleButton_(),				//1フレーム前に同時ボタンを踏んでいるかいないか
	isPastMeanTimeButton_(false),		//1フレーム前に踏んでいる間発動するボタンを踏んでいるかいないか
	pStage_(nullptr)					//Stageクラスを格納するポインタ
{
}

//踏んでいる間発動するボタンを踏んだ瞬間の処理
void Basic::CommonMeanTimeButtonDown()
{
	//Stageクラスを格納
	if (pStage_ == nullptr) pStage_ = (Stage*)Find("Stage");

	//変数宣言
	//今ボタンを踏んでいるかいないかを判断する
	bool nowMeanTimeButton;

	//踏んでいる間発動するボタンを踏んでいたらtrue。踏んでいなかったらfalseが返される
	nowMeanTimeButton = pStage_->MeanTimeButton((int)transform_.position_.x, (int)(transform_.position_.y) - 1);

	//1フレーム前は踏んでいない
	if (!isPastMeanTimeButton_)
	{
		//今は踏んでいる
		if (nowMeanTimeButton)
		{
			//踏んだ瞬間の処理
			//ギミックのモデル番号を調べる
			//踏んだボタンのモデル番号の1の位が返される
			meanTimeGimmickNumber_ = pStage_->CheckFootBlock((int)transform_.position_.x, (int)(transform_.position_.y) - 1);

			//踏んだボタンに対応する変数をカウントアップ
			//引数には踏んだモデル番号の1の位を渡す
			pStage_->SetMeanTimeStepNumberCountUp(meanTimeGimmickNumber_);
		}
	}
	//1フレーム前は踏んでいる
	else if (isPastMeanTimeButton_)
	{
		//今は踏んでいない
		if (!nowMeanTimeButton)
		{
			//離れた瞬間の処理
			//離れたボタンに対応する変数をカウントダウン
			//引数には離れたモデル番号の1の位を渡す
			pStage_->SetMeanTimeStepNumberCountDown(meanTimeGimmickNumber_);
		}
	}
	//フレームを１つ進める
	isPastMeanTimeButton_ = nowMeanTimeButton;
}


//同時押しボタンの片方を踏んだ瞬間の処理
void Basic::No1DoubleButtonDown()
{
	//変数宣言
	//1フレーム前は踏んでいるかどうか
	bool nowNo1DoubleButton;

	//踏んだらtrueが返されて、何もなければfalseが返される
	nowNo1DoubleButton = pStage_->No1DoubleButton((int)transform_.position_.x, (int)(transform_.position_.y) - 1);

	//1フレーム前は踏んでいない
	if (!isPastDoubleButton_[0])
	{
		//今は踏んでいる
		if (nowNo1DoubleButton)
		{
			//踏んだ瞬間の処理
			//ギミックのモデル番号を調べる
			//踏んだボタンのモデル番号の1の位が返される
			no1DoubleGimmickNumber_ = pStage_->CheckFootBlock((int)transform_.position_.x, (int)(transform_.position_.y) - 1);

			//踏んだボタンに対応する変数をカウントアップ
			//引数には踏んだモデル番号の1の位を渡す
			pStage_->SetNo1DoubleStepNumberCountUp(no1DoubleGimmickNumber_);
		}
	}
	//1フレーム前は踏んでいる
	else if (isPastDoubleButton_[0])
	{
		//今は踏んでいない
		if (!nowNo1DoubleButton)
		{
			//離れた瞬間の処理
			//離れたボタンに対応する変数をカウントダウン
			//引数には離れたモデル番号の1の位を渡す
			pStage_->SetNo1DoubleStepNumberCountDown(no1DoubleGimmickNumber_);
		}
	}
	//フレームを１つ進める
	isPastDoubleButton_[0] = nowNo1DoubleButton;
}


//もう片方の同時押しボタンを踏んだ瞬間の処理
//上記と同じ処理なのでコメントは省略
void Basic::No2DoubleButtonDown()
{
	bool nowNo2DoubleButton;

	nowNo2DoubleButton = pStage_->No2DoubleButton((int)transform_.position_.x, (int)(transform_.position_.y) - 1);

	if (!isPastDoubleButton_[1])
	{
		if (nowNo2DoubleButton)
		{
			no2DoubleGimmickNumber_ = pStage_->CheckFootBlock((int)transform_.position_.x, (int)(transform_.position_.y) - 1);
			pStage_->SetNo2DoubleStepNumberCountUp(no2DoubleGimmickNumber_);
		}
	}
	else if (isPastDoubleButton_[1])
	{
		if (!nowNo2DoubleButton)
		{
			pStage_->SetNo2DoubleStepNumberCountDown(no2DoubleGimmickNumber_);
		}
	}
	isPastDoubleButton_[1] = nowNo2DoubleButton;
}
