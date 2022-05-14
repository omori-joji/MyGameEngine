#include "Shadow.h"

Shadow::Shadow(GameObject* parent)
	:GameObject(parent, "Shadow"),

	frameCounter_(0),					//���t���[���������L�^���邽�߂̃J�E���^�[
	shadowDirection_(0),				//Player�̌������L�^���铮�I�z��
	shadowModelNumber_(0),				//�����Ă��郂�f���ԍ����L�^���铮�I�z��
	RESET_VALU_(0),						//�������p
	BACK_DRAW_(0.1f),					//Player�ɏd�Ȃ�Ȃ��悤�ɏ������ɕ`�悷��
	ALL_GIMICKS_(9),					//������ނ̃M�~�b�N���ׂĂ�T�����߂̒l
	MEANTIME_BLOCK_ALPHA_(61),			//�J���Ă���ǂ̃��f���ԍ�
	MEANTIME_BUTTON_DOWN_(41),			//����ł���Ԕ�������{�^���̃��f���ԍ�
	MATCH_VALU_(1),						//�z��̗v�f�������킹�邽�߂̒l
	SHADOW_FOOT_(1),					//�e�̑��������邽�߂̒l
	hModel_(),							//�e�̃��f�����i�[���鑽�����z��
	filePas_("Assets/Shadow/"),			//Shadow�̃t�@�C���p�X
	isRecording_(false),				//Player�̓������L�^���Ă��邩
	isShadowPastButton_(false),			//�{�^���𓥂�ł��邩
	pPlayer_(nullptr),					//�v���C���[�̏�������֐�
	pStage_(nullptr)					//�X�e�[�W�̏�������֐�
{
}

void Shadow::Initialize()
{
	//�E�����������Ă��郂�f���̃��[�h
	hModel_[SDIR_RIGHT][STANDING_MODEL] = Model::Load(filePas_  + "Shadow_Right.fbx");
	hModel_[SDIR_RIGHT][RUN_MODEL] = Model::Load(filePas_ + "ShadowRun_Right.fbx");

	//�������������Ă��郂�f���̃��[�h
	hModel_[SDIR_LEFT][STANDING_MODEL] = Model::Load(filePas_ + "Shadow_Left.fbx");
	hModel_[SDIR_LEFT][RUN_MODEL] = Model::Load(filePas_ +"ShadowRun_Left.fbx");
}

void Shadow::Update()
{
	//Find�������܂Ƃ߂�֐�
	AllFind();

	//Player�̓������L�^�A�Đ�����֐�
	RecordingandPlayBack();

	//�{�^���𓥂񂾂����ꂽ������������֐�
	ShadowFootButtonCheck();

	//�{�^���ƕǂ̃��f����؂�ւ���֐�
�@�@//�����ɑ����̃u���b�N�̏���n���Ă�����
	pStage_->ChengeButton((int)transform_.position_.x, (int)transform_.position_.y - SHADOW_FOOT_);
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
		//���t���[���e��Positon�ɋL�^����Playey�̈ʒu�𔽉f����
		transform_.position_ = recordData_[frameCounter_];

		//Player��艜�ɕ`�悷��
		transform_.position_.z += BACK_DRAW_;

		//�����Ă��郂�f���ԍ��̏����擾
		shadowModelNumber_ = recordModelNumber_[frameCounter_];

		//�����Ă��郂�f���ԍ��̏����擾
		shadowDirection_ = recordDirection_[frameCounter_];



		//���̃t���[����
		frameCounter_++;
	}
	//�Đ����I�������
	if (frameCounter_ >= recordData_.size() - MATCH_VALU_ && isRecording_ == true)
	{
		//��\��
		isRecording_ = false;

		//�t���[�����̃��Z�b�g
		frameCounter_ = RESET_VALU_;

		transform_.position_ = pStage_->GetStartPosition();
	}
}

//�`��A�Đ��̍��}���o���֐�
void Shadow::ShadowIsPlayFlag()
{
	//�Đ��J�n
	isRecording_ = true;

	//�ŏ��̃t���[����
	frameCounter_ = RESET_VALU_;
}

bool Shadow::GetIsRecording()
{
	return isRecording_;
}

void Shadow::ShadowFootButtonCheck()
{
	//�ϐ����쐬
	bool nowButton;

	//�{�^���𓥂�ł����true����ł��Ȃ����false���Ԃ����
	nowButton = pStage_->DownButton((int)transform_.position_.x, (int)(transform_.position_.y) - SHADOW_FOOT_);

	//1�t���[���O�͓���ł��Ȃ�
	if (!isShadowPastButton_)
	{
		//���͓���ł���
		if (nowButton)
		{
			//�J�E���g�A�b�v
			pStage_->StepNumberCountUp();
		}
	}
	//1�t���[���O�͓���ł���
	else if (isShadowPastButton_)
	{
		//���͓���ł��Ȃ�
		if (!nowButton)
		{
			//�J�E���g�_�E��
			pStage_->StepNumberCountDown();
		}
	}
	//������ł��邩�ǂ����̏���1�t���[���O�̏��Ɋi�[����
	isShadowPastButton_ = nowButton;
}
