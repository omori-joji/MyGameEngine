#include "Setumei.h"
#include "Title.h"
#include "Engine/SceneManager.h"
#include "Engine/Model.h"
//�R���X�g���N�^
Setumei::Setumei(GameObject* parent)
	: GameObject(parent, "Setumei"),hModel_(-1), sceneMoveTime_(0), pTitle(nullptr)
{
}

//������
void Setumei::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Assets/Setumei.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Setumei::Update()
{
    if (pTitle == nullptr)
    {
        pTitle = (Title*)Find("Title");
    }
}

//�`��
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

//�J��
void Setumei::Release()
{
}