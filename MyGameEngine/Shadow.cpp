#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Shadow.h"
#include "Stage.h"
#include "Player.h"


Shadow::Shadow(GameObject* parent)
	:GameObject(parent, "Shadow"),

	frameCounter_(0),					//毎フレーム動きを記録するためのカウンター
	shadowDirection_(0),				//Playerの向きを記録する動的配列
	shadowModelNumber_(0),				//走っているモデル番号を記録する動的配列

	hModel_(),							//影のモデルを格納する多次元配列

	isRecording_(false),				//Playerの動きを記録しているか

	pPlayer_(nullptr),					//プレイヤーの情報を入れる関数
	pStage_(nullptr),					//ステージの情報を入れる関数
	RESET_VALU_(0),
	BACK_DRAW_(0.1f),
	ALL_GIMICKS_(9),
	MEANTIME_BLOCK_ALPHA_(61),
	MEANTIME_BUTTON_DOWN_(41),
	MATCH_VALU_(1),
	isShadowPastButton(false),
	SHADOW_FOOT_(1)
{
}

void Shadow::Initialize()
{
	hModel_[SDIR_RIGHT][STANDING_MODEL] = Model::Load("Assets/Shadow/Shadow_Right.fbx");
	hModel_[SDIR_RIGHT][RUN_MODEL] = Model::Load("Assets/Shadow/ShadowRun_Right.fbx");

	hModel_[SDIR_LEFT][STANDING_MODEL] = Model::Load("Assets/Shadow/Shadow_Left.fbx");
	hModel_[SDIR_LEFT][RUN_MODEL] = Model::Load("Assets/Shadow/ShadowRun_Left.fbx");
}

void Shadow::Update()
{
	AllFind();

	RecordingandPlayBack();

	
}

void Shadow::Draw()
{
	//表示・非表示
	//再生中であれば処理を行う
	if (isRecording_)
	{
		Model::SetTransform(hModel_[shadowDirection_][shadowModelNumber_], transform_);
		Model::Draw(hModel_[shadowDirection_][shadowModelNumber_]);
	}
}

void Shadow::Release()
{
}

void Shadow::AllFind()
{
	//Playerの情報を格納
	if (pPlayer_ == nullptr)
	{
		pPlayer_ = (Player*)Find("Player");
	}

	//ステージの情報を格納
	if (pStage_ == nullptr)
	{
		pStage_ = (Stage*)Find("Stage");
	}
}

void Shadow::RecordingandPlayBack()
{
	//記録中
	if (isRecording_ == false)
	{
		//動的配列に毎フレームプレイヤーの位置を記録する
		recordData_.push_back(pPlayer_->transform_.position_);

		//動的配列にプレイヤーの向いている方向を記録する
		recordDirection_.push_back(pPlayer_->GetDirection());

		//動的配列にモデル番号を記録する
		recordModelNumber_.push_back(pPlayer_->GetModelNumber());
	}

	//再生中
	//動的配列のサイズ分影の位置を変える
	//プレイヤーのアニメーション情報(モデル番号)を影に反映する(右左)
	else if (frameCounter_ < recordData_.size() - MATCH_VALU_ && isRecording_ == true)
	{

		//毎フレーム影のPositonに記録したPlayeyの位置を反映する
		transform_.position_ = recordData_[frameCounter_];

		//Playeｒ
		transform_.position_.z += BACK_DRAW_;

		shadowModelNumber_ = recordModelNumber_[frameCounter_];

		shadowDirection_ = recordDirection_[frameCounter_];

		//次のフレームへ
		frameCounter_++;

		ShadowFootButtonCheck();
	}

	//再生し終わったら
	if (frameCounter_ >= recordData_.size() - MATCH_VALU_ && isRecording_ == true)
	{
		for (int i = RESET_VALU_; i < ALL_GIMICKS_; i++)
		{
			//ボタンのモデルを切り替える
			pStage_->CheckBlock(MEANTIME_BUTTON_DOWN_ + i, false);

			//壁のモデルを切り替える
			pStage_->CheckBlock(MEANTIME_BLOCK_ALPHA_ + i, false);
		}

		//非表示
		isRecording_ = false;

		//フレーム数のリセット
		frameCounter_ = RESET_VALU_;
	}
}

//保存した動きを再生する関数
void Shadow::ShadowDisplayFlag()
{
	//再生開始
	isRecording_ = true;

	//最初のフレームへ
	frameCounter_ = RESET_VALU_;
}

void Shadow::ShadowFootButtonCheck()
{
	//変数を作成
	bool nowButton;

	//ボタンを踏んでいればtrue踏んでいなければfalseが返される
	nowButton = pStage_->DownButton((int)transform_.position_.x, (int)(transform_.position_.y) - SHADOW_FOOT_);

	//1フレーム前は踏んでいない
	if (!isShadowPastButton)
	{
		//今は踏んでいる
		if (nowButton)
		{
			//カウントアップ
			pStage_->StepNumberCountUp();
		}
	}
	//1フレーム前は踏んでいる
	else if (isShadowPastButton)
	{
		//今は踏んでいない
		if (!nowButton)
		{
			//カウントダウン
			pStage_->StepNumberCountDown();
		}
	}
	//今踏んでいるかどうかの情報を1フレーム前の情報に格納する
	isShadowPastButton = nowButton;
}
