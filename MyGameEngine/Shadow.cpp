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
	sMARGIN(0.11f),          //当たり判定の遊び
	isRecordCheck_(true),    //プレイヤーが右を向いているか左を向いているか
	leftModel_(0),           //左のモデル番号
	rightModel_(0)           //右のモデル番号
{

}

void Shadow::Initialize()
{
	//右を向いているモデル
	hModel_Right_[0] = Model::Load("Assets/Shadow_Right.fbx");
	hModel_Right_[1] = Model::Load("Assets/ShadowRun_Right.fbx");

	//左を向いているモデル
	hModel_Left_[0] = Model::Load("Assets/Shadow_Left.fbx");
	hModel_Left_[1] = Model::Load("Assets/ShadowRun_Left.fbx");
}

void Shadow::Update()
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
	//動的配列のサイズ分影の位置を変える
	//プレイヤーのアニメーション情報(モデル番号)を影に反映する(右左)
	else if(frameCounter_<recordData_.size()-1 && isRecording_ == true)
	{

		//毎フレーム影のPositonをプレイヤーのPositionにしてあげる
		transform_.position_ = recordData_[frameCounter_];
		transform_.position_.z += 0.1f;


		//毎フレームプレイヤーの向いている方向を格納する
		isRecordCheck_ = recordCheck_[frameCounter_];


		//毎フレームプレイヤーのモデル番号を格納する
		leftModel_ = recordLeftMove_[frameCounter_];


		//毎フレームプレイヤーのモデル番号を格納する
		rightModel_ = recordRightMove_[frameCounter_];


		//次のフレームへ
		frameCounter_++;
	}



	//再生し終わったら
	if (frameCounter_ >= recordData_.size() - 1)
	{
		//ボタンを踏んでいる状態で影の再生が終了したときボタンを元に戻す
		pStage_->CheckBlock(41, false);

		//非表示
		isRecording_ = false;

		//フレーム数のリセット
		frameCounter_ = 0;
	}



	//下の当たり判定
	int checkX1, checkX2;
	int checkY1, checkY2;

	//当たり判定の位置設定
	checkX1 = (int)(transform_.position_.x + (sWIDTH - sMARGIN));
	checkX2 = (int)(transform_.position_.x - (sWIDTH - sMARGIN));
	checkY1 = (int)(transform_.position_.y);
	checkY2 = (int)(transform_.position_.y);

	//上の行で設定した位置にブロックが配置された配列があるならfalseが返される
	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		//足元にあるボタンを探す
		pStage_->DownButton((int)transform_.position_.x, ((int)transform_.position_.y)-1);
	}
}

void Shadow::Draw()
{
	//表示・非表示
	//再生中であれば処理を行う
	if (isRecording_)
	{
		//右を向いていたらこっちを実行
		if (isRecordCheck_)
		{
			Model::SetTransform(hModel_Right_[rightModel_], transform_);
			Model::Draw(hModel_Right_[rightModel_]);
		}
		//左を向いていたらこっちを実行
		else
		{
			Model::SetTransform(hModel_Left_[leftModel_], transform_);
			Model::Draw(hModel_Left_[leftModel_]);
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
