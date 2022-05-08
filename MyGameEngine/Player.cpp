#include "Player.h"
#include "Shadow.h"
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
	BACK_POSITION_LEFT_(1.3f),
	BACK_POSITION_RIGHT_(0.3f),
	BACK_POSITION_UP_(0.6f),
	BACK_POSITION_DOWN_(1.0f),
	RESET_VALU_(0),
	PLAYER_FOOT_(1),
	GRAVITY_(0.01f),
	DROP_DOWN_(-0.2f),
	isJump_(false),//ジャンプ中か

	move_(0.01f),//Y軸の移動
 
	pStage_(nullptr),//ステージの情報を入れるポインタ
	plyerRightMoveCount(0),
	isDirection(true),
	plyerLeftMoveCount(0),
	hModel_Left(),
	hModel_Right()
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	hModel_Right[0] = Model::Load("Assets/Player/PlayerRightStanding.fbx");
	hModel_Right[1] = Model::Load("Assets/Player/PlayerRightRun.fbx");

	hModel_Left[0] = Model::Load("Assets/Player/PlayerLeftStanding.fbx");
	hModel_Left[1] = Model::Load("Assets/Player/PlayerLeftRun.fbx");
}

void Player::Update()
{
	//Find処理をまとめる関数
	AllFind();

	//Playerの操作をまとめる関数
	PlayerMove();
	
	//Playerの当たり判定をまとめる関数
	PlayerCollision();



	//リセットボタンを押したら
	//記録した影をすべてまっさらな状態にしたら
	if (Input::IsKeyDown(DIK_1) || Input::IsKeyDown(DIK_2))
	{
		//初期位置に戻る
		transform_.position_ = pStage_->GetStartPosition();
	}



	//足元にボタンがあるかないかを判別する関数を呼ぶ
	pStage_->DownButton((int)transform_.position_.x, (int)(transform_.position_.y)- PLAYER_FOOT_);


	//ゴールに触れたかどうかを判別する関数を呼ぶ
	pStage_->GoalCol((int)transform_.position_.x, (int)transform_.position_.y);


	//ワープブロックに触れたかを判別する関数を呼ぶ
	pStage_->WarpBlockExit((int)transform_.position_.x, (int)(transform_.position_.y));
}

void Player::Draw()
{
	if (isDirection)
	{
		Model::SetTransform(hModel_Right[plyerRightMoveCount], transform_);
		Model::Draw(hModel_Right[plyerRightMoveCount]);
	}
	else if(!isDirection)
	{
		Model::SetTransform(hModel_Left[plyerLeftMoveCount], transform_);
		Model::Draw(hModel_Left[plyerLeftMoveCount]);
	}

}

void Player::Release()
{

}

void Player::AllFind()
{
	//Stageクラスを探す
//pStage_に探した情報が入る
	if (pStage_ == nullptr)
	{
		pStage_ = (Stage*)Find("Stage");
	}
}

void Player::PlayerMove()
{
	//左移動
//左矢印キーを押していたら
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= SPEED;
	}

	//左矢印キーを押した瞬間
	if (Input::IsKeyDown(DIK_LEFT))
	{
		//左を向いているフラグ
		isDirection = false;

		//モデル番号を変更
		plyerLeftMoveCount++;
	}

	//左矢印キーを離したら
	if (Input::IsKeyUp(DIK_LEFT))
	{
		//モデル番号を変更
		plyerLeftMoveCount--;
	}



	//右移動
	//右矢印キーを押していたら
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.position_.x += SPEED;
	}

	//右矢印キーを押した瞬間
	if (Input::IsKeyDown(DIK_RIGHT))
	{
		//右を向いているフラグ
		isDirection = true;

		plyerRightMoveCount++;
	}

	//右矢印キーを離した瞬間
	if (Input::IsKeyUp(DIK_RIGHT))
	{
		//モデル番号を変更
		plyerRightMoveCount--;
	}
}

void Player::PlayerCollision()
{
	//プレイヤーの原点は上下で見ると下。左右で見ると真ん中
	//当たったかどうか

	//当たり判定の変数宣言
	int checkX1, checkX2;
	int checkY1, checkY2;


	//左
	checkX1 = (int)(transform_.position_.x - WIDTH);
	checkX2 = (int)(transform_.position_.x - WIDTH);
	checkY1 = (int)(transform_.position_.y + (HEIGHT - MARGIN));
	checkY2 = (int)(transform_.position_.y + MARGIN);

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		transform_.position_.x = (float)checkX1 + BACK_POSITION_LEFT_;
	}

	//右
	checkX1 = (int)(transform_.position_.x + WIDTH);
	checkX2 = (int)(transform_.position_.x + WIDTH);
	checkY1 = (int)(transform_.position_.y + (HEIGHT - MARGIN));
	checkY2 = (int)(transform_.position_.y + MARGIN);

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		transform_.position_.x = (float)checkX1 - BACK_POSITION_RIGHT_;
	}


	//上
	checkX1 = (int)(transform_.position_.x + (WIDTH - MARGIN));
	checkX2 = (int)(transform_.position_.x - (WIDTH - MARGIN));
	checkY1 = (int)(transform_.position_.y + HEIGHT);
	checkY2 = (int)(transform_.position_.y + HEIGHT);

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		transform_.position_.y = (float)checkY1 - BACK_POSITION_UP_;
	}
	else
	{
		//ジャンプ
		if (Input::IsKeyDown(DIK_SPACE) && isJump_ == false)
		{
			isJump_ = true;//ジャンプしている

			//gravityの値をマイナスにすることによって今度は上方向に重力がかかるようになる
			transform_.position_.y += move_;
			move_ = DROP_DOWN_;
		}
	}


	//下
	checkX1 = (int)(transform_.position_.x + (WIDTH - MARGIN));
	checkX2 = (int)(transform_.position_.x - (WIDTH - MARGIN));
	checkY1 = (int)(transform_.position_.y);
	checkY2 = (int)(transform_.position_.y);

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		isJump_ = false;//下にブロックがあったら今はジャンプしていない

		move_ = RESET_VALU_;

		transform_.position_.y = (float)checkY1 + BACK_POSITION_DOWN_;
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
			move_ += GRAVITY_;
		}
	}
}
