#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"




Player::Player(GameObject* parent)
	: GameObject(parent, "Player"),

	//移動速度
	SPEED(0.1f),

	WIDTH(0.3f),//Playerの幅
	HEIGHT(0.6f),//Playerの高さ
	MARGIN(0.11f),//当たり判定の遊び
	BLOCK_SIZE(1.0f),//ブロックのサイズ
	MAX_JUMP(3.0f),//ジャンプの上限
	isJump(false),//ジャンプ中か

	move_(0.01),//Y軸の移動
	gravity_(0.01),

	frameCounter_(0),
	isRecording_(true),

	hModel_(-1), 
	pStage_(nullptr)
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	hModel_ = Model::Load("Assets/Player.fbx");

	stertPos_ = transform_.position_; //初期スポーン地点を記録
}

void Player::Update()
{
	//Stageクラスを探す
	//pStage_に探した情報が入る
	if (pStage_ == nullptr)
	{
		pStage_ = (Stage*)Find("Stage");
	}

	//記録中
	if (isRecording_ == true)
	{
		//右移動
		if (Input::IsKey(DIK_RIGHT))
		{
			transform_.position_.x += SPEED;
		}

		//左移動
		if (Input::IsKey(DIK_LEFT))
		{
			transform_.position_.x -= SPEED;
		}

		//現在地を記録（可変長配列に今の位置を追加）
		recordData_.push_back(transform_.position_);
	}

	//再生中
	else
	{
		//frameCounter_フレーム目に保存された位置へ
		transform_.position_ = recordData_[frameCounter_];

		//保存された最後のフレームまで行ってなかったら
		if (frameCounter_ < recordData_.size() - 1)
		{
			//次のフレームへ
			frameCounter_++;
		}
	}

	//再生スタート
	if (Input::IsKeyDown(DIK_LSHIFT)|| Input::IsKeyDown(DIK_RSHIFT))
	{
		frameCounter_ = 0;      //最初のフレームから
		isRecording_ = false;   //フラグを変更して再生モードへ

		transform_.position_ = stertPos_; //初期位置に戻る

		isRecording_ = true;
	}




	//プレイヤーの原点は上下で見ると下。左右で見ると真ん中
	//当たったかどうか

	//
	int checkX1 , checkX2;
	int checkY1 , checkY2;


	//左
	checkX1 = (int)(transform_.position_.x - WIDTH);
	checkX2 = (int)(transform_.position_.x - WIDTH);
	checkY1 = (int)(transform_.position_.y + (HEIGHT- MARGIN));
	checkY2 = (int)(transform_.position_.y + MARGIN);

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		transform_.position_.x = (float)checkX1 + 1.3f;
	}

	//右
	checkX1 = (int)(transform_.position_.x + WIDTH);
	checkX2 = (int)(transform_.position_.x + WIDTH);
	checkY1 = (int)(transform_.position_.y + (HEIGHT - MARGIN));
	checkY2 = (int)(transform_.position_.y + MARGIN);

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		transform_.position_.x = (float)checkX1 - 0.3f;
	}


	//上
	checkX1 = (int)(transform_.position_.x + (WIDTH- MARGIN));
	checkX2 = (int)(transform_.position_.x - (WIDTH - MARGIN));
	checkY1 = (int)(transform_.position_.y + HEIGHT);
	checkY2 = (int)(transform_.position_.y + HEIGHT);

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		transform_.position_.y = (float)checkY1 - 0.6f;
	}
	else
	{
		//ジャンプ
		if (Input::IsKeyDown(DIK_SPACE) && isJump == false)
		{
			isJump = true;//ジャンプしている

			//gravityの値をマイナスにすることによって今度は上方向に重力がかかるようになる
			transform_.position_.y += move_;
			move_ = -0.2f;
		}
	}


	//下
	checkX1 = (int)(transform_.position_.x + (WIDTH - MARGIN));
	checkX2 = (int)(transform_.position_.x - (WIDTH - MARGIN));
	checkY1 = (int)(transform_.position_.y);
	checkY2 = (int)(transform_.position_.y);

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		isJump = false;//下にブロックがあったら今はジャンプしていない
		move_ = 0;
		transform_.position_.y = (float)checkY1 + 1.0f;
	}
	//重力
	//下に何もなかったらどんどん下がる
	else
	{

		transform_.position_.y -= move_;
		//ブロックの直径より値が大きくなるとすり抜けてしまうので
		//ブロックの直系よりは大きくならないようにする
		//gravityの値は0.01
		if (move_ < BLOCK_SIZE)
		{
			move_ += gravity_;
		}
	}

	pStage_->DownButton((int)transform_.position_.x, (int)(transform_.position_.y) - 1);
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{

}
