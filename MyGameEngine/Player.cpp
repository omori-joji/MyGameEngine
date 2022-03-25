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

	gravity_(0.01),//重力

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
}

void Player::Update()
{
	//Stageクラスを探す
	//pStage_に探した情報が入る
	if (pStage_ == nullptr)
	{
		pStage_ = (Stage*)Find("Stage");
	}


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
			gravity_ = -0.2f;
			transform_.position_.y += gravity_;
		}
	}


	//下
	checkX1 = (int)(transform_.position_.x + (WIDTH - MARGIN));
	checkX2 = (int)(transform_.position_.x - (WIDTH - MARGIN));
	checkY1 = (int)(transform_.position_.y);
	checkY2 = (int)(transform_.position_.y);

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		isJump = false;
		transform_.position_.y = (float)checkY1 + 1.0f;
	}
	//重力
	//下に何もなかったらどんどん下がる
	else
	{

		transform_.position_.y -= gravity_;
		//ブロックの直径より値が大きくなるとすり抜けてしまうので
		//ブロックの直系よりは大きくならないようにする
		//gravityの値は0.01
		if (gravity_ < BLOCK_SIZE)
		{
			gravity_ += 0.01f;
		}
	}



	//上か下に何かが当たっていれば、ｙ座標だけ戻す
	//上
	if (pStage_->isCrash((int)transform_.position_.x, (int)(transform_.position_.y + 0.6f)) == true)
	{
		transform_.position_.y = prevPos_.y;
	}

	//下にブロックがあるかどうか
	if (pStage_->isCrash((int)transform_.position_.x, (int)(transform_.position_.y)) == true)
	{
		gravity_ = 0;
		isJump = false;
		transform_.position_.y = prevPos_.y;
	}



	//下にボタンがあるかどうか
	pStage_->Button((int)transform_.position_.x, (int)(transform_.position_.y)-1);




	//右か左に何かが当たっていれば、x座標だけ戻す
	if (pStage_->isCrash((int)transform_.position_.x +0.3f, (int)(transform_.position_.y + 0.3f)) == true)
	{
		transform_.position_.x = prevPos_.x;
	}

	if (pStage_->isCrash((int)transform_.position_.x - 0.3f, (int)(transform_.position_.y + 0.3f)) == true)
	{
		transform_.position_.x = prevPos_.x;
	}

	prevPos_ = transform_.position_;
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}


//そのマスに障害物があるかどうか
//戻り値、何かあるtrue,何もないfalse
//bool Player::isCrash(int x, int y)
//{
//	//配列に1が入っていれば通れない
//	if (map_[x][y] == 0)
//	{
//		return false;
//	}
//	else
//	{
//		return true;
//	}
//}
