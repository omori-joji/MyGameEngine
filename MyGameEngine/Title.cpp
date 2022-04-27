#include "Title.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

//コンストラクタ
Title::Title(GameObject* parent)
	: GameObject(parent, "Title"), hModel_(-1)
{
}

//初期化
void Title::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Assets/Title.fbx");
    assert(hModel_ >= 0);
}

//更新
void Title::Update()
{
    if (Input::IsKeyDown(DIK_1))
    {
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_STAGE1);
    }

    if (Input::IsKeyDown(DIK_2))
    {
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_STAGE2);
    }

    if (Input::IsKeyDown(DIK_3))
    {
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_STAGE3);
    }
}

//描画
void Title::Draw()
{
    Transform trans;
    trans.position_.x = 28 / 2;
    trans.position_.y = 23 / 2;
    trans.position_.z = -21.4;

    trans.Calclation();

    Model::SetTransform(hModel_, trans);
    Model::Draw(hModel_);
}

//開放
void Title::Release()
{
}