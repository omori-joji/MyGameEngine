#include "Actor.h"

//������
void Actor::Initialize()
{
}

//�X�V
void Actor::Update()
{
}

//�`��
void Actor::Draw()
{
}

//���
void Actor::Release()
{
}

//�R���X�g���N�^
Actor::Actor(GameObject* parent, const std::string& name)
	:GameObject(parent, name),
	meanTimeGimmickNumber_(0),			//�����Ă���Ԕ�������{�^����1�̈�
	no1DoubleGimmickNumber_(0),			//�Е��̓��������{�^����1�̈�
	no2DoubleGimmickNumber_(0),			//�����Е��̓��������{�^����1�̈�
	isPastDoubleButton_(),				//1�t���[���O�ɓ����{�^���𓥂�ł��邩���Ȃ���
	isPastMeanTimeButton_(false),		//1�t���[���O�ɓ���ł���Ԕ�������{�^���𓥂�ł��邩���Ȃ���
	pStage_(nullptr)					//Stage�N���X���i�[����|�C���^
{
}

//����ł���Ԕ�������{�^���𓥂񂾏u�Ԃ̏���
//�����F�Ȃ�
//�߂�l�F�Ȃ�
void Actor::CommonMeanTimeButtonDown()
{
	//Stage�N���X���i�[
	if (pStage_ == nullptr) pStage_ = (Stage*)Find("Stage");

	//�ϐ��錾
	//���{�^���𓥂�ł��邩���Ȃ����𔻒f����
	bool nowMeanTimeButton;

	//����ł���Ԕ�������{�^���𓥂�ł�����true�B����ł��Ȃ�������false���Ԃ����
	nowMeanTimeButton = pStage_->MeanTimeButton((int)transform_.position_.x, (int)(transform_.position_.y) - 1);

	//1�t���[���O�͓���ł��Ȃ�
	if (!isPastMeanTimeButton_)
	{
		//���͓���ł���
		if (nowMeanTimeButton)
		{
			//���񂾏u�Ԃ̏���
			//�M�~�b�N�̃��f���ԍ��𒲂ׂ�
			//���񂾃{�^���̃��f���ԍ���1�̈ʂ��Ԃ����
			meanTimeGimmickNumber_ = pStage_->CheckFootBlock((int)transform_.position_.x, (int)(transform_.position_.y) - 1);

			//���񂾃{�^���ɑΉ�����ϐ����J�E���g�A�b�v
			//�����ɂ͓��񂾃��f���ԍ���1�̈ʂ�n��
			pStage_->SetMeanTimeStepNumberCountUp(meanTimeGimmickNumber_);
		}
	}
	//1�t���[���O�͓���ł���
	else if (isPastMeanTimeButton_)
	{
		//���͓���ł��Ȃ�
		if (!nowMeanTimeButton)
		{
			//���ꂽ�u�Ԃ̏���
			//���ꂽ�{�^���ɑΉ�����ϐ����J�E���g�_�E��
			//�����ɂ͗��ꂽ���f���ԍ���1�̈ʂ�n��
			pStage_->SetMeanTimeStepNumberCountDown(meanTimeGimmickNumber_);
		}
	}
	//�t���[�����P�i�߂�
	isPastMeanTimeButton_ = nowMeanTimeButton;
}


//���������{�^���̕Е��𓥂񂾏u�Ԃ̏���
//�����F�Ȃ�
//�߂�l�F�Ȃ�
void Actor::No1DoubleButtonDown()
{
	//�ϐ��錾
	//1�t���[���O�͓���ł��邩�ǂ���
	bool nowNo1DoubleButton;

	//���񂾂�true���Ԃ���āA�����Ȃ����false���Ԃ����
	nowNo1DoubleButton = pStage_->No1DoubleButton((int)transform_.position_.x, (int)(transform_.position_.y) - 1);

	//1�t���[���O�͓���ł��Ȃ�
	if (!isPastDoubleButton_[0])
	{
		//���͓���ł���
		if (nowNo1DoubleButton)
		{
			//���񂾏u�Ԃ̏���
			//�M�~�b�N�̃��f���ԍ��𒲂ׂ�
			//���񂾃{�^���̃��f���ԍ���1�̈ʂ��Ԃ����
			no1DoubleGimmickNumber_ = pStage_->CheckFootBlock((int)transform_.position_.x, (int)(transform_.position_.y) - 1);

			//���񂾃{�^���ɑΉ�����ϐ����J�E���g�A�b�v
			//�����ɂ͓��񂾃��f���ԍ���1�̈ʂ�n��
			pStage_->SetNo1DoubleStepNumberCountUp(no1DoubleGimmickNumber_);
		}
	}
	//1�t���[���O�͓���ł���
	else if (isPastDoubleButton_[0])
	{
		//���͓���ł��Ȃ�
		if (!nowNo1DoubleButton)
		{
			//���ꂽ�u�Ԃ̏���
			//���ꂽ�{�^���ɑΉ�����ϐ����J�E���g�_�E��
			//�����ɂ͗��ꂽ���f���ԍ���1�̈ʂ�n��
			pStage_->SetNo1DoubleStepNumberCountDown(no1DoubleGimmickNumber_);
		}
	}
	//�t���[�����P�i�߂�
	isPastDoubleButton_[0] = nowNo1DoubleButton;
}


//�����Е��̓��������{�^���𓥂񂾏u�Ԃ̏���
//�����F�Ȃ�
//�߂�l�F�Ȃ�
//��L�Ɠ��������Ȃ̂ŃR�����g�͏ȗ�
void Actor::No2DoubleButtonDown()
{
	bool nowNo2DoubleButton;

	nowNo2DoubleButton = pStage_->No2DoubleButton((int)transform_.position_.x, (int)(transform_.position_.y) - 1);

	if (!isPastDoubleButton_[1])
	{
		if (nowNo2DoubleButton)
		{
			no2DoubleGimmickNumber_ = pStage_->CheckFootBlock((int)transform_.position_.x, (int)(transform_.position_.y) - 1);
			pStage_->SetNo2DoubleStepNumberCountUp(no2DoubleGimmickNumber_);
		}
	}
	else if (isPastDoubleButton_[1])
	{
		if (!nowNo2DoubleButton)
		{
			pStage_->SetNo2DoubleStepNumberCountDown(no2DoubleGimmickNumber_);
		}
	}
	isPastDoubleButton_[1] = nowNo2DoubleButton;
}
