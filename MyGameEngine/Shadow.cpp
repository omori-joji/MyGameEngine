#include "Shadow.h"
#include "Player.h"
#include "Stage.h"

Shadow::Shadow(GameObject* parent)
	:Actor(parent, "Shadow"),
	frame_Counter_(0),					//���t���[���������L�^���邽�߂̃J�E���^�[
	shadow_Direction_(0),				//Player�̌������L�^���铮�I�z��
	shadow_Model_Number_(0),			//�����Ă��郂�f���ԍ����L�^���铮�I�z��
	RESET_VALU_(0),						//�������p
	BACK_DRAW_(0.1f),					//Player�ɏd�Ȃ�Ȃ��悤�ɏ������ɕ`�悷��
	MATCH_VALU_(1),						//�z��̗v�f�������킹�邽�߂̒l
	hModel_(),							//�e�̃��f�����i�[���鑽�����z��
	s_Modele(),							//�e�̃��f���ԍ�
	file_Pas_("Assets/Shadow/"),		//Shadow�̃t�@�C���p�X
	isRecording_(false),				//Player�̓������L�^���Ă��邩
	pPlayer_(nullptr),					//�v���C���[�̏�������֐�
	pStage_(nullptr),					//�X�e�[�W�̏�������֐�
	double_Speed_(1)					//��{���ɂ��邽�ߕϐ�
{
}

//������
void Shadow::Initialize()
{
	//�E�����������Ă��郂�f���̃��[�h
	hModel_[S_DIR_RIGHT][STANDING_MODEL] = Model::Load(file_Pas_  + "ShadowRightStanding.fbx");
	hModel_[S_DIR_RIGHT][RUN_MODEL] = Model::Load(file_Pas_ + "ShadowRightRun.fbx");

	//�������������Ă��郂�f���̃��[�h
	hModel_[S_DIR_LEFT][STANDING_MODEL] = Model::Load(file_Pas_ + "ShadowLeftStanding.fbx");
	hModel_[S_DIR_LEFT][RUN_MODEL] = Model::Load(file_Pas_ +"ShadowLeftRun.fbx");
}

//�X�V
void Shadow::Update()
{
	AllFind();

	RecordingandPlayBack();

	CommonMeanTimeButtonDown();

	//Actor�N���X����p��
	No1DoubleButtonDown();
	No2DoubleButtonDown();

	//2�L�[�������Ă���Ԃ�����{���ɂ���
	if (Input::IsKeyDown(DIK_2)) double_Speed_ = 2;
	else if(Input::IsKeyUp(DIK_2)) double_Speed_ = 1;

	pStage_->ChengeButtonAndWall();
}

//Player�̓������L�^�ƍĐ�����֐�
//�����F�Ȃ�
//�߂�l�F�Ȃ�
void Shadow::RecordingandPlayBack()
{
	//�L�^��
	if (isRecording_ == false)
	{
		//���I�z��ɖ��t���[���v���C���[�̈ʒu���L�^����
		record_Data_.push_back(pPlayer_->transform_.position_);

		//���I�z��Ƀv���C���[�̌����Ă���������L�^����
		record_Direction_.push_back(pPlayer_->GetDirection());

		//���I�z��Ƀ��f���ԍ����L�^����
		record_Model_Number_.push_back(pPlayer_->GetModelNumber());
	}
	//�Đ���
	//���I�z��̃T�C�Y���e�̈ʒu��ς���
	//�v���C���[�̃A�j���[�V�������(���f���ԍ�)���e�ɔ��f����(�E��)
	else if (frame_Counter_ < record_Data_.size() - MATCH_VALU_ && isRecording_ == true)
	{
		//���t���[���e��Positon�ɋL�^����Playey�̈ʒu�𔽉f����
		transform_.position_ = record_Data_[frame_Counter_];

		//Player��艜�ɕ`�悷��
		transform_.position_.z += BACK_DRAW_;

		//�����Ă��郂�f���ԍ��̏����擾
		shadow_Model_Number_ = record_Model_Number_[frame_Counter_];

		//�����Ă��郂�f���ԍ��̏����擾
		shadow_Direction_ = record_Direction_[frame_Counter_];

		//���̃t���[����
		frame_Counter_ += double_Speed_;
	}
	//�Đ����I�������
	if (frame_Counter_ >= record_Data_.size() - MATCH_VALU_ && isRecording_ == true)
	{
		//��\��
		isRecording_ = false;

		//�t���[�����̃��Z�b�g
		frame_Counter_ = RESET_VALU_;

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
		Model::SetTransform(hModel_[shadow_Direction_][shadow_Model_Number_], transform_);
		Model::Draw(hModel_[shadow_Direction_][shadow_Model_Number_]);
	}
}

//�`��A�Đ��̍��}���o���֐�
void Shadow::ShadowIsPlayFlag()
{
	//�Đ��J�n
	isRecording_ = true;

	//�ŏ��̃t���[����
	frame_Counter_ = RESET_VALU_;
}

//���
void Shadow::Release()
{
}

//Find�������܂Ƃ߂�֐�
//�����F�Ȃ�
//�߂�l�F�Ȃ�
void Shadow::AllFind()
{
	//Player�̏����i�[
	if (pPlayer_ == nullptr) pPlayer_ = (Player*)Find("Player");
	//�X�e�[�W�̏����i�[
	if (pStage_ == nullptr) pStage_ = (Stage*)Find("Stage");
}