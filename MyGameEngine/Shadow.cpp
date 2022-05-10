#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Shadow.h"
#include "Stage.h"
#include "Player.h"


Shadow::Shadow(GameObject* parent)
	:GameObject(parent, "Shadow"),

	frameCounter_(0),					//���t���[���������L�^���邽�߂̃J�E���^�[
	shadowDirection_(0),				//Player�̌������L�^���铮�I�z��
	shadowModelNumber_(0),				//�����Ă��郂�f���ԍ����L�^���铮�I�z��

	hModel_(),							//�e�̃��f�����i�[���鑽�����z��

	isRecording_(false),				//Player�̓������L�^���Ă��邩

	pPlayer_(nullptr),					//�v���C���[�̏�������֐�
	pStage_(nullptr)					//�X�e�[�W�̏�������֐�
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
	AllFind();

	RecordingandPlayBack();
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

void Shadow::AllFind()
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
}

void Shadow::RecordingandPlayBack()
{
	//�L�^��
	if (isRecording_ == false)
	{
		//���I�z��ɖ��t���[���v���C���[�̈ʒu���L�^����
		recordData_.push_back(pPlayer_->transform_.position_);

		//���I�z��Ƀv���C���[�̌����Ă���������L�^����
		recordDirection_.push_back(pPlayer_->GetDirection());

		//���I�z��Ƀ��f���ԍ����L�^����
		recordModelNumber_.push_back(pPlayer_->GetModelNumber());

	}

	//�Đ���
	//���I�z��̃T�C�Y���e�̈ʒu��ς���
	//�v���C���[�̃A�j���[�V�������(���f���ԍ�)���e�ɔ��f����(�E��)
	else if (frameCounter_ < recordData_.size() - 1 && isRecording_ == true)
	{

		//���t���[���e��Positon�ɋL�^����Playey�̈ʒu�𔽉f���邵�Ă�����
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

//�ۑ������������Đ�����֐�
void Shadow::ShadowDisplayFlag()
{
	//�Đ��J�n
	isRecording_ = true;

	//�ŏ��̃t���[����
	frameCounter_ = 0;
}
