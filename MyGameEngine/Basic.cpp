#include "Basic.h"

void Basic::Initialize()
{
}

void Basic::Update
}

void Basic::Draw()
{
}

void Basic::Release()
{
}

Basic::Basic(GameObject* parent, const std::string& name)
	:GameObject(parent, name),
	isPastMeanTimeButton_(false),
	pStage_(nullptr),
	meanTimeGimmickNumber_(0),
	no1DoubleGimmickNumber_(0),
	no2DoubleGimmickNumber_(0),
	isPastDoubleButton_()
{
}

void Basic::CommonMeanTimeButtonDown()
{
	if (pStage_ == nullptr) pStage_ = (Stage*)Find("Stage");

	bool nowMeanTimeButton;

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

void Basic::No1DoubleButtonDown()
{
	//�ϐ��錾
	//1�t���[���O�͓���ł��邩�ǂ���
	bool nowNo1DoubleButton;

	//���񂾂�true���Ԃ���āA�����Ȃ����false���Ԃ����
	nowNo1DoubleButton = pStage_->OnDoubleButton((int)transform_.position_.x, (int)(transform_.position_.y) - 1);

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
			pStage_->SetOnDoubleStepNumberCountUp(no1DoubleGimmickNumber_);
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
			pStage_->SetOnDoubleStepNumberCountDown(no1DoubleGimmickNumber_);
		}
	}
	//�t���[�����P�i�߂�
	isPastDoubleButton_[0] = nowNo1DoubleButton;
}

void Basic::No2DoubleButtonDown()
{
	bool nowNo2DoubleButton;

	nowNo2DoubleButton = pStage_->OrDoubleButton((int)transform_.position_.x, (int)(transform_.position_.y) - 1);

	if (!isPastDoubleButton_[1])
	{
		if (nowNo2DoubleButton)
		{
			no2DoubleGimmickNumber_ = pStage_->CheckFootBlock((int)transform_.position_.x, (int)(transform_.position_.y) - 1);
			pStage_->SetOrDoubleStepNumberCountUp(no2DoubleGimmickNumber_);
		}
	}
	else if (isPastDoubleButton_[1])
	{
		if (!nowNo2DoubleButton)
		{
			pStage_->SetOrDoubleStepNumberCountDown(no2DoubleGimmickNumber_);
		}
	}
	isPastDoubleButton_[1] = nowNo2DoubleButton;
}
