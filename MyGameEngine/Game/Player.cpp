#include "Player.h"
#include "Stage.h"

//コンストラクタ
Player::Player(GameObject* parent)
	: Actor(parent, "Player"),
	SPEED_(0.1f),					//移動速度
	WIDTH_(0.3f),					//Playerの幅
	HEIGHT_(0.6f),					//Playerの高さ
	MARGIN_(0.11f),					//当たり判定の遊び
	BLOCK_SIZE_(1.0f),				//ブロックのサイズ
	MAX_JUMP_(3.0f),				//ジャンプの上限
	GRAVITY_(0.01f),				//重力の値
	RESET_VALU_(0),					//初期化用の定数
	PLAYER_FOOT_(1),				//Playerの足元を見るためにY軸を-1する定数
	BACK_POSITION_LEFT_(1.3f),		//触れていたら位置を戻す値
	BACK_POSITION_RIGHT_(0.3f),		//触れていたら位置を戻す値
	BACK_POSITION_UP_(0.6f),		//触れていたら位置を戻す値
	BACK_POSITION_DOWN_(1.0f),		//触れていたら位置を戻す値
	DROP_DOWN_(-0.2f),				//Playerの下に何もなければ下に落ちるための定数
	yMove_(0.02f),					//Y軸の移動
	Model_Number_(0),				//Playerの走っているモデル番号
	hModel_(),						//モデルをロードするための多次元配列
	MODEL_FILE_PAS_("Assets/Player/"),//Playerのモデルが保存されているファイルパス
	SE_FILE_PAS_("Assets/Sound/"),	//サウンドファイルのファイルパス
	isJump_(false),					//ジャンプ中か
	pStage_(nullptr),				//ステージの情報を入れるポインタ
	hSe_()							//SEをロードするための配列
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
	//サウンドファイルのロード
	hSe_[JUMP] = Audio::Load(SE_FILE_PAS_ + "Jump.wav", 2);
	hSe_[RESET] = Audio::Load(SE_FILE_PAS_ + "Reset.wav", 2);

	//右方向を向いているモデルのロード
	hModel_[DIR_RIGHT][STANDING_MODEL] = Model::Load(MODEL_FILE_PAS_ + "PlayerRightStanding.fbx");
	hModel_[DIR_RIGHT][RUN_MODEL] = Model::Load(MODEL_FILE_PAS_ + "PlayerRightRun.fbx");

	//左方向を向いているモデルのロード
	hModel_[DIR_LEFT][STANDING_MODEL] = Model::Load(MODEL_FILE_PAS_ + "PlayerLeftStanding.fbx");
	hModel_[DIR_LEFT][RUN_MODEL] = Model::Load(MODEL_FILE_PAS_ + "PlayerLeftRun.fbx");
}

//更新
void Player::Update()
{
	AllFind();

	PlayerRightMove();

	PlayerLeftMove();
	
	Jump();

	Collision();

	Reset();

	CommonMeanTimeButtonDown();

	//Actorクラスから継承
	No1DoubleButtonDown();
	No2DoubleButtonDown();

	pStage_->ChengeButtonAndWall();

	pStage_->GoalCol((int)transform_.position_.x, (int)transform_.position_.y);

	pStage_->WarpBlockCollision((int)transform_.position_.x, (int)(transform_.position_.y));
}

//Playyerの当たり判定をまとめる関数
//引数：なし
//戻り値：なし
void Player::Collision()
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

	//下の当たり判定
	//4点に当たり判定を作成
	checkX1 = (int)(transform_.position_.x + (WIDTH_ - MARGIN_));
	checkX2 = (int)(transform_.position_.x - (WIDTH_ - MARGIN_));
	checkY1 = (int)(transform_.position_.y);
	checkY2 = (int)(transform_.position_.y);

	//移動した先にブロックがあったらがtrueが返ってきて、何もなければfalseが返される
	//もし移動先にブロックがあったら
	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		isJump_ = false;

		//Y軸の移動を初期化する
		yMove_ = 0;

		//位置を戻す
		transform_.position_.y = (float)checkY1 + BACK_POSITION_DOWN_;
	}
	else
	{
		//ジャンプしている
		isJump_ = true;
	}
}

//初期位置に戻る処理をまとめた関数
//引数：なし
//戻り値：なし
void Player::Reset()
{
	//リセットボタンを押したら
	//記録した影をすべてまっさらな状態にしたら
	if (Input::IsKeyDown(DIK_1))
	{
		//初期位置に戻る
		transform_.position_ = pStage_->GetStartPosition();
		Audio::Play(hSe_[1]);
	}
}

//ジャンプの処理をまとめた関数
//引数：なし
//戻り値：なし
void Player::Jump()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		//足元にブロックがなかったら
		if (!pStage_->isCrash((int)transform_.position_.x, transform_.position_.y-0.1))
		{
			return;
		}

		//SEを鳴らす
		Audio::Play(hSe_[0]);

		//Y軸の移動
		transform_.position_.y += yMove_;

		//gravityの値をマイナスの値にして、今度は上方向に重力がかかるようになる
		yMove_ = DROP_DOWN_;
	}

	if (isJump_)
	{
		//下に落ちる
		transform_.position_.y -= yMove_;

		//ブロックの直径より値が大きくなるとすり抜けてしまうので
		//ブロックの直系よりは大きくならないようにする
		if (yMove_ < BLOCK_SIZE_)
		{
			yMove_ += GRAVITY_;
		}
	}
}

//描画
void Player::Draw()
{
	//描画
	Model::SetTransform(hModel_[direction_][Model_Number_], transform_);
	Model::Draw(hModel_[direction_][Model_Number_]);
}

//Playerの右操作をまとめる関数
//引数：なし
//戻り値：なし
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
		Model_Number_ = RUN_MODEL;
	}
	//右矢印キーを離した瞬間
	//モデル番号を変更
	else if (Input::IsKeyUp(DIK_RIGHT)) Model_Number_ = STANDING_MODEL;
}

//Playerの左操作をまとめる関数
//引数：なし
//戻り値：なし
void Player::PlayerLeftMove()
{
	//左移動
	//左矢印キーを押していたら
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= SPEED_;

		//モデル番号を変更
		direction_ = DIR_LEFT;
		Model_Number_ = RUN_MODEL;
	}
	//左矢印キーを離したら
	//モデル番号を変更
	else if (Input::IsKeyUp(DIK_LEFT)) Model_Number_ = STANDING_MODEL;
}

//Find処理をすべてまとめる関数
//引数：なし
//戻り値：なし
void Player::AllFind()
{
	//Stageクラスを探す
	//pStage_に探した情報が入る
	if (pStage_ == nullptr) pStage_ = (Stage*)Find("Stage");
}

//Playerの走っているモデル番号を返す関数
//引数：なし
//戻り値：modelNumber_
int Player::GetModelNumber()
{
	return Model_Number_;
}

//Player向きのモデル番号を返す関数
//引数：なし
//戻り値：direction_
int Player::GetDirection()
{
	return direction_;
}

//解放
void Player::Release()
{
}