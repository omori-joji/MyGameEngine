#include "Player.h"

Player::Player(GameObject* parent)
	: GameObject(parent, "Player"),
	SPEED_(0.1f),					//移動速度
	WIDTH_(0.3f),					//Playerの幅
	HEIGHT_(0.6f),					//Playerの高さ
	MARGIN_(0.11f),					//当たり判定の遊び
	BLOCK_SIZE_(1.0f),				//ブロックのサイズ
	MAX_JUMP_(3.0f),				//ジャンプの上限
	BACK_POSITION_LEFT_(1.3f),		//触れていたら位置を戻す値
	BACK_POSITION_RIGHT_(0.3f),		//触れていたら位置を戻す値
	BACK_POSITION_UP_(0.6f),		//触れていたら位置を戻す値
	BACK_POSITION_DOWN_(1.0f),		//触れていたら位置を戻す値
	RESET_VALU_(0),					//初期化用の定数
	PLAYER_FOOT_(1),				//Playerの足元を見るためにY軸を-1する定数
	GRAVITY_(0.01f),				//重力の値
	DROP_DOWN_(-0.2f),				//Playerの下に何もなければ下に落ちるための定数
	RUN_MODEL_(1),					//Playerの走っているモデル番号
	STANDING_MODEL_(0),				//Playerの立っているモデル番号
	move_(0.01f),					//Y軸の移動
	direction_(0),					//Playerの向きのモデル番号
	modelNumber_(0),				//Playerの走っているモデル番号
	isJump_(false),					//ジャンプ中か
	isPastButton(false),			//1フレーム前、ボタンを踏んでいるかどうかの情報
	pStage_(nullptr)				//ステージの情報を入れるポインタ
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	hModel_[DIR_RIGHT][STANDING_MODEL_] = Model::Load("Assets/Player/PlayerRightStanding.fbx");
	hModel_[DIR_RIGHT][RUN_MODEL_] = Model::Load("Assets/Player/PlayerRightRun.fbx");

	hModel_[DIR_LEFT][STANDING_MODEL_] = Model::Load("Assets/Player/PlayerLeftStanding.fbx");
	hModel_[DIR_LEFT][RUN_MODEL_] = Model::Load("Assets/Player/PlayerLeftRun.fbx");
}

void Player::Update()
{
	//Find処理をまとめる関数
	AllFind();

	//Playerの操作をまとめる関数
	PlayerRightMove();
	PlayerLeftMove();
	
	//Playerの当たり判定をまとめる関数
	PlayerCollision();

	//リセットボタンを押したら
	//記録した影をすべてまっさらな状態にしたら
	if (Input::IsKeyDown(DIK_1) || Input::IsKeyDown(DIK_2))
	{
		//初期位置に戻る
		transform_.position_ = pStage_->GetStartPosition();
	}

	//ボタンに触れたかどうかを判定してStageの変数の値を変える関数
	FootButtonCheck();

	//ゴールに触れたかどうかを判別する関数を呼ぶ
	pStage_->GoalCol((int)transform_.position_.x, (int)transform_.position_.y);

	//ワープブロックに触れたかを判別する関数を呼ぶ
	pStage_->WarpBlockCollision((int)transform_.position_.x, (int)(transform_.position_.y));
}

void Player::Draw()
{
	Model::SetTransform(hModel_[direction_][modelNumber_], transform_);
	Model::Draw(hModel_[direction_][modelNumber_]);
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

void Player::PlayerRightMove()
{
	//右移動
	//右矢印キーを押していたら
	if (Input::IsKey(DIK_RIGHT))
	{
		//右移動
		transform_.position_.x += SPEED_;

		//モデル番号を変更
		direction_ = DIR_RIGHT;
		modelNumber_ = RUN_MODEL_;
	}

	//右矢印キーを押した瞬間
	if (Input::IsKeyDown(DIK_RIGHT))
	{
		//モデル番号を変更
		direction_ = DIR_RIGHT;
		modelNumber_ = STANDING_MODEL_;
	}

	//右矢印キーを離した瞬間
	if (Input::IsKeyUp(DIK_RIGHT))
	{
		//モデル番号を変更
		modelNumber_ = STANDING_MODEL_;
	}
}

void Player::PlayerLeftMove()
{
	//左移動
	//左矢印キーを押していたら
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= SPEED_;

		//モデル番号を変更
		direction_ = DIR_LEFT;
		modelNumber_ = RUN_MODEL_;
	}

	//左矢印キーを押した瞬間
	if (Input::IsKeyDown(DIK_LEFT))
	{
		//モデル番号を変更
		direction_ = DIR_LEFT;
		modelNumber_ = STANDING_MODEL_;
	}

	//左矢印キーを離したら
	if (Input::IsKeyUp(DIK_LEFT))
	{
		//モデル番号を変更
		modelNumber_ = STANDING_MODEL_;
	}
}

void Player::PlayerCollision()
{
	//プレイヤーの原点は上下で見ると下。左右で見ると真ん中
	//当たったかどうか
	//当たり判定の変数宣言
	int checkX1, checkX2;
	int checkY1, checkY2;

	//左の当たり判定
	//4点に当たり判定を作成
	checkX1 = (int)(transform_.position_.x - WIDTH_);
	checkX2 = (int)(transform_.position_.x - WIDTH_);
	checkY1 = (int)(transform_.position_.y + (HEIGHT_ - MARGIN_));
	checkY2 = (int)(transform_.position_.y + MARGIN_);

	//移動した先にブロックがあったらがtrueが返ってきて、何もなければfalseが返される
	//もし移動先にブロックがあったら
	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		//位置を戻す
		transform_.position_.x = (float)checkX1 + BACK_POSITION_LEFT_;
	}

	//右の当たり判定
	//4点に当たり判定を作成
	checkX1 = (int)(transform_.position_.x + WIDTH_);
	checkX2 = (int)(transform_.position_.x + WIDTH_);
	checkY1 = (int)(transform_.position_.y + (HEIGHT_ - MARGIN_));
	checkY2 = (int)(transform_.position_.y + MARGIN_);

	//移動した先にブロックがあったらがtrueが返ってきて、何もなければfalseが返される
	//もし移動先にブロックがあったら
	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		//位置を戻す
		transform_.position_.x = (float)checkX1 - BACK_POSITION_RIGHT_;
	}

	//上の当たり判定
	//4点に当たり判定を作成
	checkX1 = (int)(transform_.position_.x + (WIDTH_ - MARGIN_));
	checkX2 = (int)(transform_.position_.x - (WIDTH_ - MARGIN_));
	checkY1 = (int)(transform_.position_.y + HEIGHT_);
	checkY2 = (int)(transform_.position_.y + HEIGHT_);

	//移動した先にブロックがあったらがtrueが返ってきて、何もなければfalseが返される
	//もし移動先にブロックがあったら
	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		//位置を戻す
		transform_.position_.y = (float)checkY1 - BACK_POSITION_UP_;
	}
	//ブロックがなかったら
	else
	{
		//ジャンプ
		if (Input::IsKeyDown(DIK_SPACE) && isJump_ == false)
		{
			//ジャンプしている
			isJump_ = true;

			//Y軸の移動
			transform_.position_.y += move_;

			//gravityの値をマイナスの値にして、今度は上方向に重力がかかるようになる
			move_ = DROP_DOWN_;
		}
	}

	//下の当たり判定
	checkX1 = (int)(transform_.position_.x + (WIDTH_ - MARGIN_));
	checkX2 = (int)(transform_.position_.x - (WIDTH_ - MARGIN_));
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
		if (move_ < BLOCK_SIZE_)
		{
			move_ += GRAVITY_;
		}
	}
}

void Player::FootButtonCheck()
{
	//変数を作成
	bool nowButton;

	//ボタンを踏んでいればtrue踏んでいなければfalseが返される
	nowButton = pStage_->DownButton((int)transform_.position_.x, (int)(transform_.position_.y) - PLAYER_FOOT_);

	//1フレーム前は踏んでいない
	if (!isPastButton)
	{
		//今は踏んでいる
		if (nowButton)
		{
			//カウントアップ
			pStage_->StepNumberCountUp();
		}
	}
	//1フレーム前は踏んでいる
	else if (isPastButton)
	{
		//今は踏んでいない
		if (!nowButton)
		{
			//カウントダウン
			pStage_->StepNumberCountDown();
		}
	}
	//今踏んでいるかどうかの情報を1フレーム前の情報に格納する
	isPastButton = nowButton;
}

int Player::GetModelNumber()
{
	return modelNumber_;
}

int Player::GetDirection()
{
	return direction_;
}
