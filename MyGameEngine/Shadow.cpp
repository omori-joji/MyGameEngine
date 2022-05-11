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
	pStage_(nullptr),					//�X�e�[�W�̏�������֐�
	RESET_VALU_(0),
	BACK_DRAW_(0.1f),
	ALL_GIMICKS_(9),
	MEANTIME_BLOCK_ALPHA_(61),
	MEANTIME_BUTTON_DOWN_(41),
	MATCH_VALU_(1),
	isShadowPastButton(false),
	SHADOW_FOOT_(1)
{
}

void Shadow::Initialize()
{
	hModel_[SDIR_RIGHT][STANDING_MODEL] = Model::Load("Assets/Shadow/Shadow_Right.fbx");
	hModel_[SDIR_RIGHT][RUN_MODEL] = Model::Load("Assets/Shadow/ShadowRun_Right.fbx");

	hModel_[SDIR_LEFT][STANDING_MODEL] = Model::Load("Assets/Shadow/Shadow_Left.fbx");
	hModel_[SDIR_LEFT][RUN_MODEL] = Model::Load("Assets/Shadow/ShadowRun_Left.fbx");
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
	else if (frameCounter_ < recordData_.size() - MATCH_VALU_ && isRecording_ == true)
	{

		//���t���[���e��Positon�ɋL�^����Playey�̈ʒu�𔽉f���邵�Ă�����
		transform_.position_ = recordData_[frameCounter_];
		transform_.position_.z += BACK_DRAW_;

		shadowModelNumber_ = recordModelNumber_[frameCounter_];

		shadowDirection_ = recordDirection_[frameCounter_];

		//���̃t���[����
		frameCounter_++;

		ShadowFootButtonCheck();
	}

	//�Đ����I�������
	if (frameCounter_ >= recordData_.size() - MATCH_VALU_ && isRecording_ == true)
	{
		for (int i = RESET_VALU_; i < ALL_GIMICKS_; i++)
		{
			//�{�^���̃��f����؂�ւ���
			pStage_->CheckBlock(MEANTIME_BUTTON_DOWN_ + i, false);

			//�ǂ̃��f����؂�ւ���
			pStage_->CheckBlock(MEANTIME_BLOCK_ALPHA_ + i, false);
		}

		//��\��
		isRecording_ = false;

		//�t���[�����̃��Z�b�g
		frameCounter_ = RESET_VALU_;
	}
}

//�ۑ������������Đ�����֐�
void Shadow::ShadowDisplayFlag()
{
	//�Đ��J�n
	isRecording_ = true;

	//�ŏ��̃t���[����
	frameCounter_ = RESET_VALU_;
}

void Shadow::ShadowFootButtonCheck()
{
	//�ϐ����쐬
	bool nowButton;

	//�{�^���𓥂�ł����true����ł��Ȃ����false���Ԃ����
	nowButton = pStage_->DownButton((int)transform_.position_.x, (int)(transform_.position_.y) - SHADOW_FOOT_);

	//1�t���[���O�͓���ł��Ȃ�
	if (!isShadowPastButton)
	{
		//���͓���ł���
		if (nowButton)
		{
			//�J�E���g�A�b�v
			pStage_->StepNumberCountUp();
		}
	}
	//1�t���[���O�͓���ł���
	else if (isShadowPastButton)
	{
		//���͓���ł��Ȃ�
		if (!nowButton)
		{
			//�J�E���g�_�E��
			pStage_->StepNumberCountDown();
		}
	}
	//������ł��邩�ǂ����̏���1�t���[���O�̏��Ɋi�[����
	isShadowPastButton = nowButton;
}
