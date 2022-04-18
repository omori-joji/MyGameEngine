#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Shadow.h"
#include "Stage.h"
#include "Player.h"


Shadow::Shadow(GameObject* parent)
	:GameObject(parent, "Shadow"),  //親情報
	pPlayer_(nullptr),       //プレイヤーの情報を入れる関数
	pStage_(nullptr),        //ステージの情報を入れる関数
    hModel_(-1),             //モデル番号
	isRecording_(false),     //Playerの動きを記録しているか
	frameCounter_(0),         //毎フレーム動きを記録するためのカウンター
	sWIDTH(0.3f),
	sMARGIN(0.11f)
{

}

void Shadow::Initialize()
{
	//何のFBXファイルをロードするか
	hModel_ = Model::Load("Assets/Player_0.fbx");
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
		//可変長配列に毎フレームプレイヤーの位置を記録する
		recordData_.push_back(pPlayer_->transform_.position_);
	}
	//再生中
	else if(frameCounter_<recordData_.size()-1 && isRecording_ == true)
	{

		//毎フレーム影のPositonをプレイヤーのPositionにしてあげる
		transform_.position_ = recordData_[frameCounter_];

		//次のフレームへ
		frameCounter_++;
	}



	//再生し終わったら
	if (frameCounter_ >= recordData_.size() - 1)
	{

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

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		pStage_->DownButton(transform_.position_.x, transform_.position_.y);
	}
}

void Shadow::Draw()
{
	//表示・非表示
	if (isRecording_)
	{
		Model::SetTransform(hModel_, transform_);
		Model::Draw(hModel_);
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
	isRecording_ = true;
	frameCounter_ = 0;
}
