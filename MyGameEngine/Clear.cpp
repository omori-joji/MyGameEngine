#include "Clear.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//コンストラクタ
Clear::Clear(GameObject* parent)
	: GameObject(parent, "Clear"), hModel_(-1)
{
}

//初期化
void Clear::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("Assets/Clear.fbx");
	assert(hModel_ >= 0);
}

//更新
void Clear::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_STAGE2);
	}
}

//描画
void Clear::Draw()
{
	Transform trans;

	trans.position_.x = 10;
	trans.position_.y = 15;
	trans.position_.z = 40;

	trans.Calclation();

	Model::SetTransform(hModel_, trans);
	Model::Draw(hModel_);
}

//開放
void Clear::Release()
{
}