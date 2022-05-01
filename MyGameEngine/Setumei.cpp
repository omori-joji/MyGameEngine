#include "Setumei.h"
#include "Title.h"
#include "Engine/SceneManager.h"
#include "Engine/Model.h"
//コンストラクタ
Setumei::Setumei(GameObject* parent)
	: GameObject(parent, "Setumei"),hModel_(-1), sceneMoveTime_(0), pTitle(nullptr)
{
}

//初期化
void Setumei::Initialize()
{
	//モデルデータのロード
	hModel_ = Model::Load("Assets/Setumei.fbx");
	assert(hModel_ >= 0);
}

//更新
void Setumei::Update()
{
    if (pTitle == nullptr)
    {
        pTitle = (Title*)Find("Title");
    }
}

//描画
void Setumei::Draw()
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
void Setumei::Release()
{
}