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
	//�Đ���
	//frameCounter_�t���[���ڂɕۑ����ꂽ�ʒu��
	transform_.position_ = pPlayer_->recordData_[pPlayer_->frameCounter_];

		//�ۑ����ꂽ�Ō�̃t���[���܂ōs���ĂȂ�������
		if (pPlayer_->frameCounter_ < pPlayer_->recordData_.size() - 1)
		{
			//���̃t���[����
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
