#include "Player.h"

Player::Player(GameObject* parent)
	: GameObject(parent, "Player"),
	SPEED_(0.1f),					//�ړ����x
	WIDTH_(0.3f),					//Player�̕�
	HEIGHT_(0.6f),					//Player�̍���
	MARGIN_(0.11f),					//�����蔻��̗V��
	BLOCK_SIZE_(1.0f),				//�u���b�N�̃T�C�Y
	MAX_JUMP_(3.0f),				//�W�����v�̏��
	BACK_POSITION_LEFT_(1.3f),		//�G��Ă�����ʒu��߂��l
	BACK_POSITION_RIGHT_(0.3f),		//�G��Ă�����ʒu��߂��l
	BACK_POSITION_UP_(0.6f),		//�G��Ă�����ʒu��߂��l
	BACK_POSITION_DOWN_(1.0f),		//�G��Ă�����ʒu��߂��l
	RESET_VALU_(0),					//�������p�̒萔
	PLAYER_FOOT_(1),				//Player�̑��������邽�߂�Y����-1����萔
	GRAVITY_(0.01f),				//�d�͂̒l
	DROP_DOWN_(-0.2f),				//Player�̉��ɉ����Ȃ���Ή��ɗ����邽�߂̒萔
	move_(0.01f),					//Y���̈ړ�
	direction_(0),					//Player�̌����̃��f���ԍ�
	modelNumber_(0),				//Player�̑����Ă��郂�f���ԍ�
	isJump_(false),					//�W�����v����
	isPastButton(false),			//1�t���[���O�A�{�^���𓥂�ł��邩�ǂ����̏��
	pStage_(nullptr)				//�X�e�[�W�̏�������|�C���^
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	hModel_[DIR_RIGHT][STANDING_MODEL] = Model::Load("Assets/Player/PlayerRightStanding.fbx");
	hModel_[DIR_RIGHT][RUN_MODEL] = Model::Load("Assets/Player/PlayerRightRun.fbx");

	hModel_[DIR_LEFT][STANDING_MODEL] = Model::Load("Assets/Player/PlayerLeftStanding.fbx");
	hModel_[DIR_LEFT][RUN_MODEL] = Model::Load("Assets/Player/PlayerLeftRun.fbx");
}

void Player::Update()
{
	//Find�������܂Ƃ߂�֐�
	AllFind();

	//Player�̑�����܂Ƃ߂�֐�
	PlayerRightMove();
	PlayerLeftMove();
	
	//Player�̓����蔻����܂Ƃ߂�֐�
	PlayerCollision();

	//���Z�b�g�{�^������������
	//�L�^�����e�����ׂĂ܂�����ȏ�Ԃɂ�����
	if (Input::IsKeyDown(DIK_1) || Input::IsKeyDown(DIK_2))
	{
		//�����ʒu�ɖ߂�
		transform_.position_ = pStage_->GetStartPosition();
	}

	//�{�^���ɐG�ꂽ���ǂ����𔻒肵��Stage�̕ϐ��̒l��ς���֐�
	FootButtonCheck();

	//�S�[���ɐG�ꂽ���ǂ����𔻕ʂ���֐����Ă�
	pStage_->GoalCol((int)transform_.position_.x, (int)transform_.position_.y);

	//���[�v�u���b�N�ɐG�ꂽ���𔻕ʂ���֐����Ă�
	pStage_->WarpBlockCollision((int)transform_.position_.x, (int)(transform_.position_.y));
}

void Player::Draw()
{
	Model::SetTransform(hModel_[direction_][modelNumber_], transform_);
	Model::Draw(hModel_[direction_][modelNumber_]);
}

void Player::Release()
{
}

void Player::AllFind()
{
	//Stage�N���X��T��
	//pStage_�ɒT������񂪓���
	if (pStage_ == nullptr)
	{
		pStage_ = (Stage*)Find("Stage");
	}
}

void Player::PlayerRightMove()
{
	//�E�ړ�
	//�E���L�[�������Ă�����
	if (Input::IsKey(DIK_RIGHT))
	{
		//�E�ړ�
		transform_.position_.x += SPEED_;

		//���f���ԍ���ύX
		direction_ = DIR_RIGHT;
		modelNumber_ = RUN_MODEL;
	}

	//�E���L�[���������u��
	if (Input::IsKeyDown(DIK_RIGHT))
	{
		//���f���ԍ���ύX
		direction_ = DIR_RIGHT;
		modelNumber_ = STANDING_MODEL;
	}

	//�E���L�[�𗣂����u��
	if (Input::IsKeyUp(DIK_RIGHT))
	{
		//���f���ԍ���ύX
		modelNumber_ = STANDING_MODEL;
	}
}

void Player::PlayerLeftMove()
{
	//���ړ�
	//�����L�[�������Ă�����
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= SPEED_;

		//���f���ԍ���ύX
		direction_ = DIR_LEFT;
		modelNumber_ = RUN_MODEL;
	}

	//�����L�[���������u��
	if (Input::IsKeyDown(DIK_LEFT))
	{
		//���f���ԍ���ύX
		direction_ = DIR_LEFT;
		modelNumber_ = STANDING_MODEL;
	}

	//�����L�[�𗣂�����
	if (Input::IsKeyUp(DIK_LEFT))
	{
		//���f���ԍ���ύX
		modelNumber_ = STANDING_MODEL;
	}
}

void Player::PlayerCollision()
{
	//�v���C���[�̌��_�͏㉺�Ō���Ɖ��B���E�Ō���Ɛ^��
	//�����������ǂ���
	//�����蔻��̕ϐ��錾
	int checkX1, checkX2;
	int checkY1, checkY2;

	//���̓����蔻��
	//4�_�ɓ����蔻����쐬
	checkX1 = (int)(transform_.position_.x - WIDTH_);
	checkX2 = (int)(transform_.position_.x - WIDTH_);
	checkY1 = (int)(transform_.position_.y + (HEIGHT_ - MARGIN_));
	checkY2 = (int)(transform_.position_.y + MARGIN_);

	//�ړ�������Ƀu���b�N���������炪true���Ԃ��Ă��āA�����Ȃ����false���Ԃ����
	//�����ړ���Ƀu���b�N����������
	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		//�ʒu��߂�
		transform_.position_.x = (float)checkX1 + BACK_POSITION_LEFT_;
	}

	//�E�̓����蔻��
	//4�_�ɓ����蔻����쐬
	checkX1 = (int)(transform_.position_.x + WIDTH_);
	checkX2 = (int)(transform_.position_.x + WIDTH_);
	checkY1 = (int)(transform_.position_.y + (HEIGHT_ - MARGIN_));
	checkY2 = (int)(transform_.position_.y + MARGIN_);

	//�ړ�������Ƀu���b�N���������炪true���Ԃ��Ă��āA�����Ȃ����false���Ԃ����
	//�����ړ���Ƀu���b�N����������
	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		//�ʒu��߂�
		transform_.position_.x = (float)checkX1 - BACK_POSITION_RIGHT_;
	}

	//��̓����蔻��
	//4�_�ɓ����蔻����쐬
	checkX1 = (int)(transform_.position_.x + (WIDTH_ - MARGIN_));
	checkX2 = (int)(transform_.position_.x - (WIDTH_ - MARGIN_));
	checkY1 = (int)(transform_.position_.y + HEIGHT_);
	checkY2 = (int)(transform_.position_.y + HEIGHT_);

	//�ړ�������Ƀu���b�N���������炪true���Ԃ��Ă��āA�����Ȃ����false���Ԃ����
	//�����ړ���Ƀu���b�N����������
	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		//�ʒu��߂�
		transform_.position_.y = (float)checkY1 - BACK_POSITION_UP_;
	}
	//�u���b�N���Ȃ�������
	else
	{
		//�W�����v
		if (Input::IsKeyDown(DIK_SPACE) && isJump_ == false)
		{
			//�W�����v���Ă���
			isJump_ = true;

			//Y���̈ړ�
			transform_.position_.y += move_;

			//gravity�̒l���}�C�i�X�̒l�ɂ��āA���x�͏�����ɏd�͂�������悤�ɂȂ�
			move_ = DROP_DOWN_;
		}
	}

	//���̓����蔻��
	//4�_�ɓ����蔻����쐬
	checkX1 = (int)(transform_.position_.x + (WIDTH_ - MARGIN_));
	checkX2 = (int)(transform_.position_.x - (WIDTH_ - MARGIN_));
	checkY1 = (int)(transform_.position_.y);
	checkY2 = (int)(transform_.position_.y);

	//�ړ�������Ƀu���b�N���������炪true���Ԃ��Ă��āA�����Ȃ����false���Ԃ����
	//�����ړ���Ƀu���b�N����������
	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		//���Ƀu���b�N���������獡�̓W�����v���Ă��Ȃ�
		isJump_ = false;

		//Y���̈ړ�������������
		move_ = RESET_VALU_;

		//�ʒu��߂�
		transform_.position_.y = (float)checkY1 + BACK_POSITION_DOWN_;
	}
	//�d��
	//���ɉ����Ȃ�������
	else
	{
		//���ɗ�����
		transform_.position_.y -= move_;

		//�u���b�N�̒��a���l���傫���Ȃ�Ƃ��蔲���Ă��܂��̂�
		//�u���b�N�̒��n���͑傫���Ȃ�Ȃ��悤�ɂ���
		if (move_ < BLOCK_SIZE_)
		{
			move_ += GRAVITY_;
		}
	}
}

void Player::FootButtonCheck()
{
	//�ϐ����쐬
	bool nowButton;

	//�{�^���𓥂�ł����true����ł��Ȃ����false���Ԃ����
	nowButton = pStage_->DownButton((int)transform_.position_.x, (int)(transform_.position_.y) - PLAYER_FOOT_);

	//1�t���[���O�͓���ł��Ȃ�
	if (!isPastButton)
	{
		//���͓���ł���
		if (nowButton)
		{
			//�J�E���g�A�b�v
			pStage_->StepNumberCountUp();
		}
	}
	//1�t���[���O�͓���ł���
	else if (isPastButton)
	{
		//���͓���ł��Ȃ�
		if (!nowButton)
		{
			//�J�E���g�_�E��
			pStage_->StepNumberCountDown();
		}
	}
	//������ł��邩�ǂ����̏���1�t���[���O�̏��Ɋi�[����
	isPastButton = nowButton;
}

int Player::GetModelNumber()
{
	return modelNumber_;
}

int Player::GetDirection()
{
	return direction_;
}
