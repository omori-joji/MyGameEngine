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
	rightModel_(0),          //右のモデル番号
	hModel_Right_(),
	hModel_Left_()
{

}

void Shadow::Initialize()
{
	hModel_[0][0] = Model::Load("Assets/Shadow/Shadow_Right.fbx");
	hModel_[0][1] = Model::Load("Assets/Shadow/ShadowRun_Right.fbx");


	hModel_[1][0] = Model::Load("Assets/Shadow/Shadow_Left.fbx");
	hModel_[1][1] = Model::Load("Assets/Shadow/ShadowRun_Left.fbx");
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
		recordDirection_.push_back(pPlayer_->GetDirection());

		recordModelNumber_.push_back(pPlayer_->GetModelNumber());

	}

	//再生中
	//動的配列のサイズ分影の位置を変える
	//プレイヤーのアニメーション情報(モデル番号)を影に反映する(右左)
	else if(frameCounter_<recordData_.size()-1 && isRecording_ == true)
	{

		//毎フレーム影のPositonをプレイヤーのPositionにしてあげる
		transform_.position_ = recordData_[frameCounter_];
		transform_.position_.z += 0.1f;


		shadowModelNumber_ = recordModelNumber_[frameCounter_];
		shadowDirection_ = recordDirection_[frameCounter_];


		//次のフレームへ
		frameCounter_++;
	}


	//再生し終わったら
	if (frameCounter_ >= recordData_.size() - 1 && isRecording_ == true)
	{
		for (int i = 0; i < 9; i++)
		{
			//ボタンのモデルを切り替える
			pStage_->CheckBlock(41 + i, false);

			//壁のモデルを切り替える
			pStage_->CheckBlock(61 + i, false);
		}

		//非表示
		isRecording_ = false;

		//フレーム数のリセット
		frameCounter_ = 0;
	}
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

//保存した動きを再生する関数
void Shadow::ShadowDisplayFlag()
{
	//再生開始
	isRecording_ = true;

	//最初のフレームへ
	frameCounter_ = 0;
}
