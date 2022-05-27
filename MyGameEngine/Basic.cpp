#include "Basic.h"


void Basic::Initialize()
{
}

void Basic::Update()
{

}

void Basic::Draw()
{
}

void Basic::Release()
{
}

Basic::Basic(GameObject* parent, const std::string& name)
	:GameObject(parent, name),
	isPastMeanTimeButton_(false),
	pStage_(nullptr),
	meanTimeGimmickNumber_(0),
	no1DoubleGimmickNumber_(0),
	no2DoubleGimmickNumber_(0),
	isPastDoubleButton_()
{
}

void Basic::CommonMeanTimeButtonDown()
{
	if (pStage_ == nullptr) pStage_ = (Stage*)Find("Stage");

	bool nowMeanTimeButton;

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

void Basic::No1DoubleButtonDown()
{
	//変数宣言
	//1フレーム前は踏んでいるかどうか
	bool nowNo1DoubleButton;

	//踏んだらtrueが返されて、何もなければfalseが返される
	nowNo1DoubleButton = pStage_->OnDoubleButton((int)transform_.position_.x, (int)(transform_.position_.y) - 1);

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
			pStage_->SetOnDoubleStepNumberCountUp(no1DoubleGimmickNumber_);
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
			pStage_->SetOnDoubleStepNumberCountDown(no1DoubleGimmickNumber_);
		}
	}
	//フレームを１つ進める
	isPastDoubleButton_[0] = nowNo1DoubleButton;
}

void Basic::No2DoubleButtonDown()
{
	bool nowNo2DoubleButton;

	nowNo2DoubleButton = pStage_->OrDoubleButton((int)transform_.position_.x, (int)(transform_.position_.y) - 1);

	if (!isPastDoubleButton_[1])
	{
		if (nowNo2DoubleButton)
		{
			no2DoubleGimmickNumber_ = pStage_->CheckFootBlock((int)transform_.position_.x, (int)(transform_.position_.y) - 1);
			pStage_->SetOrDoubleStepNumberCountUp(no2DoubleGimmickNumber_);
		}
	}
	else if (isPastDoubleButton_[1])
	{
		if (!nowNo2DoubleButton)
		{
			pStage_->SetOrDoubleStepNumberCountDown(no2DoubleGimmickNumber_);
		}
	}
	isPastDoubleButton_[1] = nowNo2DoubleButton;
}
