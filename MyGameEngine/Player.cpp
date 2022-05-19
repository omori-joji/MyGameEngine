#include "Player.h"
#include "Stage.h"

Player::Player(GameObject* parent)
	: GameObject(parent, "Player"),
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
	direction_(0),					//Playerの向きのモデル番号
	modelNumber_(0),				//Playerの走っているモデル番号
	onGimmickNumber_(0),			//片方の同時押しボタンのモデル番号
	orGimmickNumber_(0),			//もう方の同時押しボタンのモデル番号
	hModel_(),						//モデルをロードするための多次元配列
	filePas_("Assets/Player/"),		//Playerのモデルが保存されているファイルパス
	isJump_(false),					//ジャンプ中か
	isPastMeanTimeButton_(false),	//1フレーム前、ボタンを踏んでいるかどうかの情報
	isPastDoubleButton_(),			//同時押しボタンのフラグ
	pStage_(nullptr),				//ステージの情報を入れるポインタ
	hSe_()
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	//サウンドファイルのロード
	hSe_[0] = Audio::Load("Assets/Sound/Jump.wav", 5);
	hSe_[1] = Audio::Load("Assets/Sound/Reset.wav", 5);
	hSe_[2] = Audio::Load("Assets/Sound/Warpe.wav", 5);
	hSe_[3] = Audio::Load("Assets/Sound/OpenWall.wav", 5);
	hSe_[4] = Audio::Load("Assets/Sound/ButtonDown.wav", 5);

	//右方向を向いているモデルのロード
	hModel_[DIR_RIGHT][STANDING_MODEL] = Model::Load(filePas_ + "PlayerRightStanding.fbx");
	hModel_[DIR_RIGHT][RUN_MODEL] = Model::Load(filePas_ + "PlayerRightRun.fbx");

	//左方向を向いているモデルのロード
	hModel_[DIR_LEFT][STANDING_MODEL] = Model::Load(filePas_ + "PlayerLeftStanding.fbx");
	hModel_[DIR_LEFT][RUN_MODEL] = Model::Load(filePas_ + "PlayerLeftRun.fbx");
}

void Player::Update()
{
	//Find処理をまとめる関数
	AllFind();

	//Playerの右移動をまとめた関数
	PlayerRightMove();

	//Playerの左移動をまとめた関数
	PlayerLeftMove();
	
	//Playerの当たり判定をまとめる関数
	Collision();

	//ジャンプ
	Jump();

	//初期位置に戻る処理をまとめた関数
	Reset();

	//ボタンに触れたかどうかを判定してStageの変数の値を変える関数
	MeanTimeButtonCheck();

	//同時押しボタンを押した瞬間と離れた瞬間の処理を行う関数
	OnDoubleButtonCheck();
	OrDoubleButtonCheck();

	//ボタンと壁のモデルを切り替える関数
	//引数に足元のブロックの情報を渡してあげる
	pStage_->ChengeButtonAndWall();

	//ゴールに触れたかどうかを判別する関数を呼ぶ
	pStage_->GoalCol((int)transform_.position_.x, (int)transform_.position_.y);

	//ワープブロックに触れたかを判別する関数を呼ぶ
	pStage_->WarpBlockCollision((int)transform_.position_.x, (int)(transform_.position_.y));
}

//Playerの当たり判定の処理をまとめた関数
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
		//Y軸の移動を初期化する
		yMove_ = 0;

		isJump_ = false;

		//位置を戻す
		transform_.position_.y = (float)checkY1 + BACK_POSITION_DOWN_;
	}
	else if(!pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
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

//ボタンを踏んだ瞬間か離れた瞬間の処理を行う関数
void Player::MeanTimeButtonCheck()
{
	//変数を作成
	//1フレーム前は踏んでいるかどうか
	bool nowMeanTimeButton;

	//ボタンを踏んでいればtrue踏んでいなければfalseが返される
	nowMeanTimeButton = pStage_->MeanTimeButton((int)transform_.position_.x, (int)(transform_.position_.y) - PLAYER_FOOT_);

	//1フレーム前は踏んでいない
	if (!isPastMeanTimeButton_)
	{
		//今は踏んでいる
		if (nowMeanTimeButton)
		{
			//踏んだ瞬間の処理
			//ギミックのモデル番号を調べる
			//踏んだボタンのモデル番号の1の位が返される
			meanTimeGimmickNumber_ = pStage_->CheckFootBlock((int)transform_.position_.x, (int)(transform_.position_.y) - PLAYER_FOOT_);

			//踏んだボタンに対応する変数をカウントアップ
			//引数には踏んだモデル番号の1の位を渡す
			pStage_->SetMeanTimeStepNumberCountUp(meanTimeGimmickNumber_);
		}
	}
	//1フレーム前は踏んでいる
	else if (isPastMeanTimeButton_)
	{
		//今は踏んでいない
		if (!nowMeanTimeButton)
		{
			//離れた瞬間の処理
			//離れたボタンに対応する変数をカウントダウン
			//引数には離れたモデル番号の1の位を渡す
			pStage_->SetMeanTimeStepNumberCountDown(meanTimeGimmickNumber_);
		}
	}
	//フレームを１つ進める
	isPastMeanTimeButton_ = nowMeanTimeButton;
}
	
//同時押しボタンの片方
//押した直後のタイミングと離れた瞬間の処理を行う
void Player::OnDoubleButtonCheck()
{
	//変数宣言
	//1フレーム前は踏んでいるかどうか
	bool onDoubleButton;

	//踏んだらtrueが返されて、何もなければfalseが返される
	onDoubleButton = pStage_->OnDoubleButton((int)transform_.position_.x, (int)(transform_.position_.y) - PLAYER_FOOT_);

	//1フレーム前は踏んでいない
	if (!isPastDoubleButton_[ON_DOUBLE_BUTTON])
	{
		//今は踏んでいる
		if (onDoubleButton)
		{
			//踏んだ瞬間の処理
			//ギミックのモデル番号を調べる
			//踏んだボタンのモデル番号の1の位が返される
			onGimmickNumber_ = pStage_->CheckFootBlock((int)transform_.position_.x, (int)(transform_.position_.y) - PLAYER_FOOT_);

			//踏んだボタンに対応する変数をカウントアップ
			//引数には踏んだモデル番号の1の位を渡す
			pStage_->SetOnDoubleStepNumberCountUp(onGimmickNumber_);
		}
	}
	//1フレーム前は踏んでいる
	else if (isPastDoubleButton_[ON_DOUBLE_BUTTON])
	{
		//今は踏んでいない
		if (!onDoubleButton)
		{
			//離れた瞬間の処理
			//離れたボタンに対応する変数をカウントダウン
			//引数には離れたモデル番号の1の位を渡す
			pStage_->SetOnDoubleStepNumberCountDown(onGimmickNumber_);
		}
	}
	//フレームを１つ進める
	isPastDoubleButton_[ON_DOUBLE_BUTTON] = onDoubleButton;
}

//同時押しボタンのもう片方の処理
//内容は同じなのでコメントは省略
void Player::OrDoubleButtonCheck()
{
	bool orDoubleButton;

	orDoubleButton = pStage_->OrDoubleButton((int)transform_.position_.x, (int)(transform_.position_.y) - PLAYER_FOOT_);

	if (!isPastDoubleButton_[OR_DOUBLE_BUTTON])
	{
		if (orDoubleButton)
		{
			orGimmickNumber_ = pStage_->CheckFootBlock((int)transform_.position_.x, (int)(transform_.position_.y) - PLAYER_FOOT_);
			pStage_->SetOrDoubleStepNumberCountUp(orGimmickNumber_);
		}
	}
	else if (isPastDoubleButton_[OR_DOUBLE_BUTTON])
	{
		if (!orDoubleButton)
		{
			pStage_->SetOrDoubleStepNumberCountDown(orGimmickNumber_);
		}
	}
	isPastDoubleButton_[OR_DOUBLE_BUTTON] = orDoubleButton;
}

//初期位置に戻る処理をまとめた関数
void Player::Reset()
{
	//リセットボタンを押したら
	//記録した影をすべてまっさらな状態にしたら
	if (Input::IsKeyDown(DIK_1) || Input::IsKeyDown(DIK_2))
	{
		//初期位置に戻る
		transform_.position_ = pStage_->GetStartPosition();
		Audio::Play(hSe_[1]);
	}
}

//ジャンプの処理をまとめた関数
void Player::Jump()
{
	if (Input::IsKeyDown(DIK_SPACE) && !isJump_)
	{
		Audio::Play(hSe_[0]);
		isJump_ = true;

		//Y軸の移動
		transform_.position_.y += yMove_;

		//gravityの値をマイナスの値にして、今度は上方向に重力がかかるようになる
		yMove_ = DROP_DOWN_;
	}
}

void Player::Draw()
{
	//描画
	Model::SetTransform(hModel_[direction_][modelNumber_], transform_);
	Model::Draw(hModel_[direction_][modelNumber_]);
}

//右移動の処理
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
		modelNumber_ = RUN_MODEL;
	}
	//右矢印キーを離した瞬間
	//モデル番号を変更
	else if (Input::IsKeyUp(DIK_RIGHT)) modelNumber_ = STANDING_MODEL;
}

//左移動の処理
void Player::PlayerLeftMove()
{
	//左移動
	//左矢印キーを押していたら
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= SPEED_;

		//モデル番号を変更
		direction_ = DIR_LEFT;
		modelNumber_ = RUN_MODEL;
	}
	//左矢印キーを離したら
	//モデル番号を変更
	else if (Input::IsKeyUp(DIK_LEFT)) modelNumber_ = STANDING_MODEL;
}

//Find処理をまとめた関数
void Player::AllFind()
{
	//Stageクラスを探す
	//pStage_に探した情報が入る
	if (pStage_ == nullptr) pStage_ = (Stage*)Find("Stage");
}

//モデル番号を返す
int Player::GetModelNumber()
{
	return modelNumber_;
}

//毎フレーム向いている方向を返す
int Player::GetDirection()
{
	return direction_;
}

void Player::Release()
{
}