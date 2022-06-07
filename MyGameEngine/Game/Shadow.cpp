#include "Shadow.h"
#include "Player.h"
#include "Stage.h"

Shadow::Shadow(GameObject* parent)
	:Actor(parent, "Shadow"),
	frame_Counter_(0),					//毎フレーム動きを記録するためのカウンター
	shadow_Direction_(0),				//Playerの向きを記録する動的配列
	shadow_Model_Number_(0),			//走っているモデル番号を記録する動的配列
	RESET_VALU_(0),						//初期化用
	BACK_DRAW_(0.1f),					//Playerに重ならないように少し奥に描画する
	MATCH_VALU_(1),						//配列の要素数を合わせるための値
	hModel_(),							//影のモデルを格納する多次元配列
	s_Modele(),							//影のモデル番号
	file_Pas_("Assets/Shadow/"),		//Shadowのファイルパス
	isRecording_(false),				//Playerの動きを記録しているか
	pPlayer_(nullptr),					//プレイヤーの情報を入れる関数
	pStage_(nullptr),					//ステージの情報を入れる関数
	double_Speed_(1)					//二倍速にするため変数
{
}

//初期化
void Shadow::Initialize()
{
	//右方向を向いているモデルのロード
	hModel_[S_DIR_RIGHT][STANDING_MODEL] = Model::Load(file_Pas_  + "ShadowRightStanding.fbx");
	hModel_[S_DIR_RIGHT][RUN_MODEL] = Model::Load(file_Pas_ + "ShadowRightRun.fbx");

	//左方向を向いているモデルのロード
	hModel_[S_DIR_LEFT][STANDING_MODEL] = Model::Load(file_Pas_ + "ShadowLeftStanding.fbx");
	hModel_[S_DIR_LEFT][RUN_MODEL] = Model::Load(file_Pas_ +"ShadowLeftRun.fbx");
}

//更新
void Shadow::Update()
{
	AllFind();

	RecordingandPlayBack();

	CommonMeanTimeButtonDown();

	//Actorクラスから継承
	No1DoubleButtonDown();
	No2DoubleButtonDown();

	//2キーを押している間だけ二倍速にする
	if (Input::IsKeyDown(DIK_2)) double_Speed_ = 2;
	else if(Input::IsKeyUp(DIK_2)) double_Speed_ = 1;

	pStage_->ChengeButtonAndWall();
}

//Playerの動きを記録と再生する関数
//引数：なし
//戻り値：なし
void Shadow::RecordingandPlayBack()
{
	//記録中
	if (isRecording_ == false)
	{
		//動的配列に毎フレームプレイヤーの位置を記録する
		record_Data_.push_back(pPlayer_->transform_.position_);

		//動的配列にプレイヤーの向いている方向を記録する
		record_Direction_.push_back(pPlayer_->GetDirection());

		//動的配列にモデル番号を記録する
		record_Model_Number_.push_back(pPlayer_->GetModelNumber());
	}
	//再生中
	//動的配列のサイズ分影の位置を変える
	//プレイヤーのアニメーション情報(モデル番号)を影に反映する(右左)
	else if (frame_Counter_ < record_Data_.size() - MATCH_VALU_ && isRecording_ == true)
	{
		//毎フレーム影のPositonに記録したPlayeyの位置を反映する
		transform_.position_ = record_Data_[frame_Counter_];

		//Playerより奥に描画する
		transform_.position_.z += BACK_DRAW_;

		//走っているモデル番号の情報を取得
		shadow_Model_Number_ = record_Model_Number_[frame_Counter_];

		//立っているモデル番号の情報を取得
		shadow_Direction_ = record_Direction_[frame_Counter_];

		//次のフレームへ
		frame_Counter_ += double_Speed_;
	}
	//再生し終わったら
	if (frame_Counter_ >= record_Data_.size() - MATCH_VALU_ && isRecording_ == true)
	{
		//非表示
		isRecording_ = false;

		//フレーム数のリセット
		frame_Counter_ = RESET_VALU_;

		//位置がそのままだとボタンから離れる時の処理が行われないので影の位置を初期位置に戻す
		transform_.position_ = pStage_->GetStartPosition();
	}
}

//描画
void Shadow::Draw()
{
	//表示・非表示
	//再生中であれば処理を行う
	if (isRecording_)
	{
		Model::SetTransform(hModel_[shadow_Direction_][shadow_Model_Number_], transform_);
		Model::Draw(hModel_[shadow_Direction_][shadow_Model_Number_]);
	}
}

//描画、再生の合図を出す関数
void Shadow::ShadowIsPlayFlag()
{
	//再生開始
	isRecording_ = true;

	//最初のフレームへ
	frame_Counter_ = RESET_VALU_;
}

//解放
void Shadow::Release()
{
}

//Find処理をまとめる関数
//引数：なし
//戻り値：なし
void Shadow::AllFind()
{
	//Playerの情報を格納
	if (pPlayer_ == nullptr) pPlayer_ = (Player*)Find("Player");
	//ステージの情報を格納
	if (pStage_ == nullptr) pStage_ = (Stage*)Find("Stage");
}