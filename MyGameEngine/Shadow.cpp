#include "Shadow.h"
#include "Stage.h"
#include "Engine/Model.h"
#include "Player.h"

Shadow::Shadow(GameObject* parent)
	:GameObject(parent, "Shadow"),
	pPlayer_(nullptr),
    hModel_(-1)
{
}

void Shadow::Initialize()
{
	hModel_ = Model::Load("Assets/Player.fbx");

	if (pPlayer_ == nullptr)
	{
		pPlayer_ = (Player*)Find("Player");
	}

	transform_.position_ = pPlayer_->stertPos_;
}

void Shadow::Update()
{
	//再生中
	//frameCounter_フレーム目に保存された位置へ
	transform_.position_ = pPlayer_->recordData_[pPlayer_->frameCounter_];

		//保存された最後のフレームまで行ってなかったら
		if (pPlayer_->frameCounter_ < pPlayer_->recordData_.size() - 1)
		{
			//次のフレームへ
			pPlayer_->frameCounter_++;
		}
		else
		{
			pPlayer_->frameCounter_ = 0;
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

void Shadow::Collision()
{
}
