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
	meanTimeGimmickNumber_(0)
{

}

void Basic::CommonMeanTimeButtonDown()
{
	int a = 0;
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
