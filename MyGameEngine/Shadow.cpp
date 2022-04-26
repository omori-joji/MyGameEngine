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
	frameCounter_(0),        //���t���[���������L�^���邽�߂̃J�E���^�[
	sWIDTH(0.3f),            //�e�̕�
	sMARGIN(0.11f),          //�����蔻��̗V��
	isRecordCheck_(true),    //�v���C���[���E�������Ă��邩���������Ă��邩
	leftModel_(0),           //���̃��f���ԍ�
	rightModel_(0)           //�E�̃��f���ԍ�
{

}

void Shadow::Initialize()
{
	//�E�������Ă��郂�f��
	hModel_Right_[0] = Model::Load("Assets/Shadow_Right.fbx");
	hModel_Right_[1] = Model::Load("Assets/ShadowRun_Right.fbx");

	//���������Ă��郂�f��
	hModel_Left_[0] = Model::Load("Assets/Shadow_Left.fbx");
	hModel_Left_[1] = Model::Load("Assets/ShadowRun_Left.fbx");
}

void Shadow::Update()
{
	//Player�̏����i�[
	if (pPlayer_ == nullptr)
	{
		pPlayer_ = (Player*)Find("Player");
	}

	//�X�e�[�W�̏����i�[
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
	//���I�z��̃T�C�Y���e�̈ʒu��ς���
	//�v���C���[�̃A�j���[�V�������(���f���ԍ�)���e�ɔ��f����(�E��)
	else if(frameCounter_<recordData_.size()-1 && isRecording_ == true)
	{

		//���t���[���e��Positon���v���C���[��Position�ɂ��Ă�����
		transform_.position_ = recordData_[frameCounter_];
		transform_.position_.z += 0.1f;


		//���t���[���v���C���[�̌����Ă���������i�[����
		isRecordCheck_ = recordCheck_[frameCounter_];


		//���t���[���v���C���[�̃��f���ԍ����i�[����
		leftModel_ = recordLeftMove_[frameCounter_];


		//���t���[���v���C���[�̃��f���ԍ����i�[����
		rightModel_ = recordRightMove_[frameCounter_];


		//���̃t���[����
		frameCounter_++;
	}



	//�Đ����I�������
	if (frameCounter_ >= recordData_.size() - 1)
	{
		//�{�^���𓥂�ł����Ԃŉe�̍Đ����I�������Ƃ��{�^�������ɖ߂�
		pStage_->CheckBlock(41, false);

		//��\��
		isRecording_ = false;

		//�t���[�����̃��Z�b�g
		frameCounter_ = 0;
	}



	//���̓����蔻��
	int checkX1, checkX2;
	int checkY1, checkY2;

	//�����蔻��̈ʒu�ݒ�
	checkX1 = (int)(transform_.position_.x + (sWIDTH - sMARGIN));
	checkX2 = (int)(transform_.position_.x - (sWIDTH - sMARGIN));
	checkY1 = (int)(transform_.position_.y);
	checkY2 = (int)(transform_.position_.y);

	//��̍s�Őݒ肵���ʒu�Ƀu���b�N���z�u���ꂽ�z�񂪂���Ȃ�false���Ԃ����
	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		//�����ɂ���{�^����T��
		pStage_->DownButton(transform_.position_.x, transform_.position_.y);
	}
}

void Shadow::Draw()
{
	//�\���E��\��
	//�Đ����ł���Ώ������s��
	if (isRecording_)
	{
		//�E�������Ă����炱���������s
		if (isRecordCheck_)
		{
			Model::SetTransform(hModel_Right_[rightModel_], transform_);
			Model::Draw(hModel_Right_[rightModel_]);
		}
		//���������Ă����炱���������s
		else
		{
			Model::SetTransform(hModel_Left_[leftModel_], transform_);
			Model::Draw(hModel_Left_[leftModel_]);
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
	//�Đ��J�n
	isRecording_ = true;

	//�ŏ��̃t���[����
	frameCounter_ = 0;
}
