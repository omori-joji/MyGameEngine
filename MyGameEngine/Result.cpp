#include "Result.h"
#include "Engine/SceneManager.h"

//コンストラクタ
Result::Result(GameObject* parent)
	: GameObject(parent, "Result"), 
	hModel_(-1),				//モデル番号を格納する変数
	BACK_GROUND_VERTICAL_(23),	//背景のY軸の高さ
	BACK_GROUND_BESIDE_(28),	//背景のX軸の高さ
	BACK_GROUND_DEPTH_(-21.4f)	//背景の奥行
{
}

//初期化
void Result::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("Assets/StageBlock/Result.fbx");
}

//更新
void Result::Update()
{
	//SPACEキーを押したらタイトル画面に移行
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE2);
	}
}

//描画
void Result::Draw()
{
	//背景を描画
	Transform trans;

	//位置決定
	trans.position_.x = BACK_GROUND_BESIDE_ /2;
	trans.position_.y = BACK_GROUND_VERTICAL_ /2;
	trans.position_.z = BACK_GROUND_DEPTH_;

	//ワールド行列
	trans.Calclation();

	//描画開始
	Model::SetTransform(hModel_, trans);
	Model::Draw(hModel_);
}

//開放
void Result::Release()
{
}