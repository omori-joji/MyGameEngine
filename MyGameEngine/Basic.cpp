#include "Basic.h"


void Basic::Initialize()
{
}

void Basic::Update()
{
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
	meanTimeGimmickNumber_(0)
{

}

void Basic::CommonMeanTimeButtonDown()
{
	int a = 0;
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
