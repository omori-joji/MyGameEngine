#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Shadow.h"
#include "Stage.h"
#include "Player.h"


Shadow::Shadow(GameObject* parent)
	:GameObject(parent, "Shadow"),  //�e���
	pPlayer_(nullptr),       //�v���C���[�̏�������֐�
	pStage_(nullptr),        //�X�e�[�W�̏�������֐�
    hModel_(-1),             //���f���ԍ�
	isRecording_(false),     //Player�̓������L�^���Ă��邩
	frameCounter_(0),         //���t���[���������L�^���邽�߂̃J�E���^�[
	sWIDTH(0.3f),
	sMARGIN(0.11f)
{

}

void Shadow::Initialize()
{
	//����FBX�t�@�C�������[�h���邩
	hModel_ = Model::Load("Assets/Player.fbx");
}

void Shadow::Update()
{
	if (pPlayer_ == nullptr)
	{
		pPlayer_ = (Player*)Find("Player");
	}

	if (pStage_ == nullptr)
	{
		pStage_ = (Stage*)Find("Stage");
	}



	//�L�^��
	if (isRecording_ == false)
	{
		//�ϒ��z��ɖ��t���[���v���C���[�̈ʒu���L�^����
		recordData_.push_back(pPlayer_->transform_.position_);
	}
	//�Đ���
	else if(frameCounter_<recordData_.size()-1 && isRecording_ == true)
	{

		//���t���[���e��Positon���v���C���[��Position�ɂ��Ă�����
		transform_.position_ = recordData_[frameCounter_];

		//���̃t���[����
		frameCounter_++;
	}



	//�Đ����I�������
	if (frameCounter_ >= recordData_.size() - 1)
	{

		//��\��
		isRecording_ = false;

		//�t���[�����̃��Z�b�g
		frameCounter_ = 0;
	}



	int checkX1, checkX2;
	int checkY1, checkY2;


	checkX1 = (int)(transform_.position_.x + (sWIDTH - sMARGIN));
	checkX2 = (int)(transform_.position_.x - (sWIDTH - sMARGIN));
	checkY1 = (int)(transform_.position_.y);
	checkY2 = (int)(transform_.position_.y);

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		pStage_->DownButton(transform_.position_.x, transform_.position_.y);
	}
}

void Shadow::Draw()
{
	//�\���E��\��
	if (isRecording_)
	{
		Model::SetTransform(hModel_, transform_);
		Model::Draw(hModel_);
	}

}

void Shadow::Release()
{
}

void Shadow::Collision()
{

}

//�ۑ������������Đ�����֐�
void Shadow::Flag()
{
	isRecording_ = true;
	frameCounter_ = 0;
}
