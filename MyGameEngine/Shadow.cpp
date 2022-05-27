#include "Shadow.h"
#include "Player.h"
#include "Stage.h"

Shadow::Shadow(GameObject* parent)
	:Basic(parent, "Shadow"),
	frameCounter_(0),					//���t���[���������L�^���邽�߂̃J�E���^�[
	shadowDirection_(0),				//Player�̌������L�^���铮�I�z��
	shadowModelNumber_(0),				//�����Ă��郂�f���ԍ����L�^���铮�I�z��
	RESET_VALU_(0),						//�������p
	BACK_DRAW_(0.1f),					//Player�ɏd�Ȃ�Ȃ��悤�ɏ������ɕ`�悷��
	MATCH_VALU_(1),						//�z��̗v�f�������킹�邽�߂̒l
	hModel_(),							//�e�̃��f�����i�[���鑽�����z��
	filePas_("Assets/Shadow/"),			//Shadow�̃t�@�C���p�X
	isRecording_(false),				//Player�̓������L�^���Ă��邩
	pPlayer_(nullptr),					//�v���C���[�̏�������֐�
	pStage_(nullptr)					//�X�e�[�W�̏�������֐�
{
}

//������
void Shadow::Initialize()
{
	//�E�����������Ă��郂�f���̃��[�h
	hModel_[SDIR_RIGHT][STANDING_MODEL] = Model::Load(filePas_  + "Shadow_Right.fbx");
	hModel_[SDIR_RIGHT][RUN_MODEL] = Model::Load(filePas_ + "ShadowRun_Right.fbx");

	//�������������Ă��郂�f���̃��[�h
	hModel_[SDIR_LEFT][STANDING_MODEL] = Model::Load(filePas_ + "Shadow_Left.fbx");
	hModel_[SDIR_LEFT][RUN_MODEL] = Model::Load(filePas_ +"ShadowRun_Left.fbx");
}

//�X�V
void Shadow::Update()
{
	//Find�������܂Ƃ߂�֐�
	AllFind();

	//Player�̓������L�^�A�Đ�����֐�
	RecordingandPlayBack();

	//�{�^���𓥂񂾂����ꂽ������������֐�
	CommonMeanTimeButtonDown();

	//���������{�^�����������u�ԂƗ��ꂽ�u�Ԃ̏������s���֐�
	No1DoubleButtonDown();
	No2DoubleButtonDown();

	//�{�^���ƕǂ̃��f����؂�ւ���֐�
	//�����ɑ����̃u���b�N�̏���n���Ă�����
	pStage_->ChengeButtonAndWall();
}

//�e�̕\����\���A�Đ������L�^���������Ǘ�����֐�
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

		//�ʒu�����̂܂܂��ƃ{�^�����痣��鎞�̏������s���Ȃ��̂ŉe�̈ʒu�������ʒu�ɖ߂�
		transform_.position_ = pStage_->GetStartPosition();
	}
}

//�`��
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

//�`��A�Đ��̍��}���o���֐�
void Shadow::ShadowIsPlayFlag()
{
	//�Đ��J�n
	isRecording_ = true;

	//�ŏ��̃t���[����
	frameCounter_ = RESET_VALU_;
}

//���
void Shadow::Release()
{
}

//Find�������܂Ƃ߂��֐�
void Shadow::AllFind()
{
	//Player�̏����i�[
	if (pPlayer_ == nullptr) pPlayer_ = (Player*)Find("Player");
	//�X�e�[�W�̏����i�[
	if (pStage_ == nullptr) pStage_ = (Stage*)Find("Stage");
}