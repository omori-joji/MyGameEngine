#include "Shadow.h"

Shadow::Shadow(GameObject* parent)
	:GameObject(parent, "Shadow"),

	frameCounter_(0),					//毎フレーム動きを記録するためのカウンター
	shadowDirection_(0),				//Playerの向きを記録する動的配列
	shadowModelNumber_(0),				//走っているモデル番号を記録する動的配列
	RESET_VALU_(0),						//初期化用
	BACK_DRAW_(0.1f),					//Playerに重ならないように少し奥に描画する
	ALL_GIMICKS_(9),					//同じ種類のギミックすべてを探すための値
	MEANTIME_BLOCK_ALPHA_(61),			//開いている壁のモデル番号
	MEANTIME_BUTTON_DOWN_(41),			//踏んでいる間発動するボタンのモデル番号
	MATCH_VALU_(1),						//配列の要素数を合わせるための値
	SHADOW_FOOT_(1),					//影の足元を見るための値
	hModel_(),							//影のモデルを格納する多次元配列
	filePas_("Assets/Shadow/"),			//Shadowのファイルパス
	isRecording_(false),				//Playerの動きを記録しているか
	isShadowPastButton_(),				//ボタンを踏んでいるか
	pPlayer_(nullptr),					//プレイヤーの情報を入れる関数
	pStage_(nullptr)					//ステージの情報を入れる関数
{
}

void Shadow::Initialize()
{
	//右方向を向いているモデルのロード
	hModel_[SDIR_RIGHT][STANDING_MODEL] = Model::Load(filePas_  + "Shadow_Right.fbx");
	hModel_[SDIR_RIGHT][RUN_MODEL] = Model::Load(filePas_ + "ShadowRun_Right.fbx");

	//左方向を向いているモデルのロード
	hModel_[SDIR_LEFT][STANDING_MODEL] = Model::Load(filePas_ + "Shadow_Left.fbx");
	hModel_[SDIR_LEFT][RUN_MODEL] = Model::Load(filePas_ +"ShadowRun_Left.fbx");
}

void Shadow::Update()
{
	//Find処理をまとめる関数
	AllFind();

	//Playerの動きを記録、再生する関数
	RecordingandPlayBack();

	//ボタンを踏んだか離れたかを処理する関数
	ShadowFootButtonCheck();
	ShadowOnDoubleButtonCheck();
	ShadowOrDoubleButtonCheck();

	//ボタンと壁のモデルを切り替える関数
	//引数に足元のブロックの情報を渡してあげる
	pStage_->ChengeButtonAndWall((int)transform_.position_.x, (int)transform_.position_.y - SHADOW_FOOT_);
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

		//Playerより奥に描画する
		transform_.position_.z += BACK_DRAW_;

		//走っているモデル番号の情報を取得
		shadowModelNumber_ = recordModelNumber_[frameCounter_];

		//立っているモデル番号の情報を取得
		shadowDirection_ = recordDirection_[frameCounter_];

		//次のフレームへ
		frameCounter_++;
	}
	//再生し終わったら
	if (frameCounter_ >= recordData_.size() - MATCH_VALU_ && isRecording_ == true)
	{
		//非表示
		isRecording_ = false;

		//フレーム数のリセット
		frameCounter_ = RESET_VALU_;

		//位置がそのままだとボタンから離れる時の処理が行われないので影の位置を初期位置に戻す
		transform_.position_ = pStage_->GetStartPosition();
	}
}

//描画、再生の合図を出す関数
void Shadow::ShadowIsPlayFlag()
{
	//再生開始
	isRecording_ = true;

	//最初のフレームへ
	frameCounter_ = RESET_VALU_;
}

bool Shadow::GetIsRecording()
{
	return isRecording_;
}

void Shadow::ShadowFootButtonCheck()
{
	//変数を作成
	bool nowButton;

	//ボタンを踏んでいればtrue踏んでいなければfalseが返される
	nowButton = pStage_->MeanTimeButton((int)transform_.position_.x, (int)(transform_.position_.y) - SHADOW_FOOT_);

	//1フレーム前は踏んでいない
	if (!isShadowPastButton_[0])
	{
		//今は踏んでいる
		if (nowButton)
		{
			//カウントアップ
			pStage_->SetMeanTimeStepNumberCountUp();
		}
	}
	//1フレーム前は踏んでいる
	else if (isShadowPastButton_[0])
	{
		//今は踏んでいない
		if (!nowButton)
		{
			//カウントダウン
			pStage_->SetMeanTimeStepNumberCountDown();
		}
	}
	//今踏んでいるかどうかの情報を1フレーム前の情報に格納する
	isShadowPastButton_[0] = nowButton;
}

void Shadow::ShadowOnDoubleButtonCheck()
{
	bool onDoubleButton;

	onDoubleButton = pStage_->DoubleButton((int)transform_.position_.x, (int)(transform_.position_.y) - SHADOW_FOOT_);

	if (!isShadowPastButton_[1])
	{
		if (onDoubleButton)
		{
			pStage_->SetOnDoubleStepNumberCountUp();
		}
	}
	else if (isShadowPastButton_[1])
	{
		if (!onDoubleButton)
		{
			pStage_->SetOnDoubleStepNumberCountDown();
		}
	}
	isShadowPastButton_[1] = onDoubleButton;
}

void Shadow::ShadowOrDoubleButtonCheck()
{
	bool orDoubleButton;

	orDoubleButton = pStage_->DoubleButton((int)transform_.position_.x, (int)(transform_.position_.y) - SHADOW_FOOT_);

	if (!isShadowPastButton_[2])
	{
		if (orDoubleButton)
		{
			pStage_->SetOrDoubleStepNumberCountUp();
		}
	}
	else if (isShadowPastButton_[2])
	{
		if (!orDoubleButton)
		{
			pStage_->SetOrDoubleStepNumberCountDown();
		}
	}
	isShadowPastButton_[2] = orDoubleButton;
}
