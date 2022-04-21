#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Shadow.h"
#include "Stage.h"
#include "Player.h"


Shadow::Shadow(GameObject* parent)
	:GameObject(parent, "Shadow"),  //�e���
	pPlayer_(nullptr),       //�v���C���[�̏�������֐�
	pStage_(nullptr),        //�X�e�[�W�̏�������֐�
	isRecording_(false),     //Player�̓������L�^���Ă��邩
	frameCounter_(0),         //���t���[���������L�^���邽�߂̃J�E���^�[
	sWIDTH(0.3f),
	sMARGIN(0.11f)
{

}

void Shadow::Initialize()
{
	//����FBX�t�@�C�������[�h���邩
	hModel_Right[0] = Model::Load("Assets/Shadow_Right.fbx");
	hModel_Right[1] = Model::Load("Assets/ShadowRun_Right.fbx");

	hModel_Left[0] = Model::Load("Assets/Shadow_Left.fbx");
	hModel_Left[1] = Model::Load("Assets/ShadowRun_Left.fbx");
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

		//���I�z��ɖ��t���[���v���C���[�̈ʒu���L�^����
		recordData_.push_back(pPlayer_->transform_.position_);


		//���I�z��Ƀv���C���[�̌����Ă���������L�^����
		recordCheck_.push_back(pPlayer_->isDirection);


		//���I�z��Ɍ��݂̃v���C���[�̃��f���ԍ����L�^����
		recordLeftMove_.push_back(pPlayer_->plyerLeftMoveCount);


		//���I�z��Ɍ��݂̃v���C���[�̃��f���ԍ����L�^����
		recordRightMove_.push_back(pPlayer_->plyerRightMoveCount);
	}
	//�Đ���
	else if(frameCounter_<recordData_.size()-1 && isRecording_ == true)
	{

		//���t���[���e��Positon���v���C���[��Position�ɂ��Ă�����
		transform_.position_ = recordData_[frameCounter_];


		//���t���[���v���C���[�̌����Ă���������i�[����
		isRecordCheck = recordCheck_[frameCounter_];


		//���t���[���v���C���[�̃��f���ԍ����i�[����
		leftModel = recordLeftMove_[frameCounter_];


		//���t���[���v���C���[�̃��f���ԍ����i�[����
		rightModel = recordRightMove_[frameCounter_];


		//���̃t���[����
		frameCounter_++;
	}



	//�Đ����I�������
	if (frameCounter_ >= recordData_.size() - 1)
	{
		pStage_->CheckBlock(51,true);
		//pStage_->CheckBlock(31, false);

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
		if (isRecordCheck)
		{
			Model::SetTransform(hModel_Right[rightModel], transform_);
			Model::Draw(hModel_Right[rightModel]);
		}
		else
		{
			Model::SetTransform(hModel_Left[leftModel], transform_);
			Model::Draw(hModel_Left[leftModel]);
		}



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
