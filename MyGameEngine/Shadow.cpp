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
	rightModel_(0),          //�E�̃��f���ԍ�
	hModel_Right_(),
	hModel_Left_()
{

}

void Shadow::Initialize()
{
	hModel_[0][0] = Model::Load("Assets/Shadow/Shadow_Right.fbx");
	hModel_[0][1] = Model::Load("Assets/Shadow/ShadowRun_Right.fbx");


	hModel_[1][0] = Model::Load("Assets/Shadow/Shadow_Left.fbx");
	hModel_[1][1] = Model::Load("Assets/Shadow/ShadowRun_Left.fbx");
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
		recordDirection_.push_back(pPlayer_->GetDirection());

		recordModelNumber_.push_back(pPlayer_->GetModelNumber());

	}

	//�Đ���
	//���I�z��̃T�C�Y���e�̈ʒu��ς���
	//�v���C���[�̃A�j���[�V�������(���f���ԍ�)���e�ɔ��f����(�E��)
	else if(frameCounter_<recordData_.size()-1 && isRecording_ == true)
	{

		//���t���[���e��Positon���v���C���[��Position�ɂ��Ă�����
		transform_.position_ = recordData_[frameCounter_];
		transform_.position_.z += 0.1f;


		shadowModelNumber_ = recordModelNumber_[frameCounter_];
		shadowDirection_ = recordDirection_[frameCounter_];


		//���̃t���[����
		frameCounter_++;
	}


	//�Đ����I�������
	if (frameCounter_ >= recordData_.size() - 1 && isRecording_ == true)
	{
		for (int i = 0; i < 9; i++)
		{
			//�{�^���̃��f����؂�ւ���
			pStage_->CheckBlock(41 + i, false);

			//�ǂ̃��f����؂�ւ���
			pStage_->CheckBlock(61 + i, false);
		}

		//��\��
		isRecording_ = false;

		//�t���[�����̃��Z�b�g
		frameCounter_ = 0;
	}
}

void Shadow::Draw()
{
	//�\���E��\��
	//�Đ����ł���Ώ������s��
	if (isRecording_)
	{
		Model::SetTransform(hModel_[shadowDirection_][shadowModelNumber_], transform_);
		Model::Draw(hModel_[shadowDirection_][shadowModelNumber_]);
	}

}

void Shadow::Release()
{

}

//�ۑ������������Đ�����֐�
void Shadow::ShadowDisplayFlag()
{
	//�Đ��J�n
	isRecording_ = true;

	//�ŏ��̃t���[����
	frameCounter_ = 0;
}
