#include "Shadow.h"
#include "Player.h"
#include "Stage.h"
#include "Engine/Model.h"

Shadow::Shadow(GameObject* parent)
	:GameObject(parent, "Shadow"),
	pPlayer_(nullptr),
     hModel_(-1)
{
}

void Shadow::Initialize()
{
	hModel_ = Model::Load("Assets/Shadows.fbx");

	transform_.position_ = pPlayer_->stertPos_;
}

void Shadow::Update()
{
	if (pPlayer_ == nullptr)
	{
		pPlayer_ = (Player*)Find("Player");
	}




}

void Shadow::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Shadow::Release()
{
}
