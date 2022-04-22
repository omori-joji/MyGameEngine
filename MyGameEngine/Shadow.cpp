#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Shadow.h"
#include "Stage.h"
#include "Player.h"


Shadow::Shadow(GameObject* parent)
	:GameObject(parent, "Shadow"),  //親情報
	pPlayer_(nullptr),       //プレイヤーの情報を入れる関数
	pStage_(nullptr),        //ステージの情報を入れる関数
	isRecording_(false),     //Playerの動きを記録しているか
	frameCounter_(0),        //毎フレーム動きを記録するためのカウンター
	sWIDTH(0.3f),            //影の幅
	sMARGIN(0.11f)           //当たり判定の遊び
{

}

void Shadow::Initialize()
{
	//右を向いているモデル
	hModel_Right[0] = Model::Load("Assets/Shadow_Right.fbx");
	hModel_Right[1] = Model::Load("Assets/ShadowRun_Right.fbx");

	//左を向いているモデル
	hModel_Left[0] = Model::Load("Assets/Shadow_Left.fbx");
	hModel_Left[1] = Model::Load("Assets/ShadowRun_Left.fbx");
}

void Shadow::Update()
{
	if (pPlayer_ == nullptr)
	{
		pPlayer_ = (Player*)Find("Player");
	}

	if (pStage_ == nullptr)
	{
		pStage_ = (Stage*)Find("Stage");
	}

	//記録中
	if (isRecording_ == false)
	{

		//動的配列に毎フレームプレイヤーの位置を記録する
		recordData_.push_back(pPlayer_->transform_.position_);


		//動的配列にプレイヤーの向いている方向を記録する
		recordCheck_.push_back(pPlayer_->isDirection);


		//動的配列に現在のプレイヤーのモデル番号を記録する
		recordLeftMove_.push_back(pPlayer_->plyerLeftMoveCount);


		//動的配列に現在のプレイヤーのモデル番号を記録する
		recordRightMove_.push_back(pPlayer_->plyerRightMoveCount);
	}
	//再生中
	else if(frameCounter_<recordData_.size()-1 && isRecording_ == true)
	{

		//毎フレーム影のPositonをプレイヤーのPositionにしてあげる
		transform_.position_ = recordData_[frameCounter_];


		//毎フレームプレイヤーの向いている方向を格納する
		isRecordCheck = recordCheck_[frameCounter_];


		//毎フレームプレイヤーのモデル番号を格納する
		leftModel = recordLeftMove_[frameCounter_];


		//毎フレームプレイヤーのモデル番号を格納する
		rightModel = recordRightMove_[frameCounter_];


		//次のフレームへ
		frameCounter_++;
	}



	//再生し終わったら
	if (frameCounter_ >= recordData_.size() - 1)
	{
		//ボタンを踏んでいる状態で影の再生が終了したときボタンを元に戻す
		pStage_->CheckBlock(31, false);

		//非表示
		isRecording_ = false;

		//フレーム数のリセット
		frameCounter_ = 0;
	}



	int checkX1, checkX2;
	int checkY1, checkY2;


	checkX1 = (int)(transform_.position_.x + (sWIDTH - sMARGIN));
	checkX2 = (int)(transform_.position_.x - (sWIDTH - sMARGIN));
	checkY1 = (int)(transform_.position_.y);
	checkY2 = (int)(transform_.position_.y);

	//下の当たり判定
	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		//足元にあるボタンを探す
		pStage_->DownButton(transform_.position_.x, transform_.position_.y);
	}
}

void Shadow::Draw()
{
	//表示・非表示
	if (isRecording_)
	{
		if (isRecordCheck)
		{
			Model::SetTransform(hModel_Right[rightModel], transform_);
			Model::Draw(hModel_Right[rightModel]);
		}
		else
		{
			Model::SetTransform(hModel_Left[leftModel], transform_);
			Model::Draw(hModel_Left[leftModel]);
		}



	}

}

void Shadow::Release()
{
}

void Shadow::Collision()
{

}

//保存した動きを再生する関数
void Shadow::Flag()
{
	//再生開始
	isRecording_ = true;

	//最初のフレームへ
	frameCounter_ = 0;
}
