#include "Player.h"
#include "Stage.h"

Player::Player(GameObject* parent)
	: GameObject(parent, "Player"),
	SPEED_(0.1f),					//�ړ����x
	WIDTH_(0.3f),					//Player�̕�
	HEIGHT_(0.6f),					//Player�̍���
	MARGIN_(0.11f),					//�����蔻��̗V��
	BLOCK_SIZE_(1.0f),				//�u���b�N�̃T�C�Y
	MAX_JUMP_(3.0f),				//�W�����v�̏��
	GRAVITY_(0.01f),				//�d�͂̒l
	RESET_VALU_(0),					//�������p�̒萔
	PLAYER_FOOT_(1),				//Player�̑��������邽�߂�Y����-1����萔
	BACK_POSITION_LEFT_(1.3f),		//�G��Ă�����ʒu��߂��l
	BACK_POSITION_RIGHT_(0.3f),		//�G��Ă�����ʒu��߂��l
	BACK_POSITION_UP_(0.6f),		//�G��Ă�����ʒu��߂��l
	BACK_POSITION_DOWN_(1.0f),		//�G��Ă�����ʒu��߂��l
	DROP_DOWN_(-0.2f),				//Player�̉��ɉ����Ȃ���Ή��ɗ����邽�߂̒萔
	yMove_(0.02f),					//Y���̈ړ�
	direction_(0),					//Player�̌����̃��f���ԍ�
	modelNumber_(0),				//Player�̑����Ă��郂�f���ԍ�
	onGimmickNumber_(0),			//�Е��̓��������{�^���̃��f���ԍ�
	orGimmickNumber_(0),			//�������̓��������{�^���̃��f���ԍ�
	hModel_(),						//���f�������[�h���邽�߂̑������z��
	filePas_("Assets/Player/"),		//Player�̃��f�����ۑ�����Ă���t�@�C���p�X
	isJump_(false),					//�W�����v����
	isPastMeanTimeButton_(false),	//1�t���[���O�A�{�^���𓥂�ł��邩�ǂ����̏��
	isPastDoubleButton_(),			//���������{�^���̃t���O
	pStage_(nullptr),				//�X�e�[�W�̏�������|�C���^
	hSe_()
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	//�T�E���h�t�@�C���̃��[�h
	hSe_[0] = Audio::Load("Assets/Sound/Jump.wav", 5);
	hSe_[1] = Audio::Load("Assets/Sound/Reset.wav", 5);
	hSe_[2] = Audio::Load("Assets/Sound/Warpe.wav", 5);
	hSe_[3] = Audio::Load("Assets/Sound/OpenWall.wav", 5);
	hSe_[4] = Audio::Load("Assets/Sound/ButtonDown.wav", 5);

	//�E�����������Ă��郂�f���̃��[�h
	hModel_[DIR_RIGHT][STANDING_MODEL] = Model::Load(filePas_ + "PlayerRightStanding.fbx");
	hModel_[DIR_RIGHT][RUN_MODEL] = Model::Load(filePas_ + "PlayerRightRun.fbx");

	//�������������Ă��郂�f���̃��[�h
	hModel_[DIR_LEFT][STANDING_MODEL] = Model::Load(filePas_ + "PlayerLeftStanding.fbx");
	hModel_[DIR_LEFT][RUN_MODEL] = Model::Load(filePas_ + "PlayerLeftRun.fbx");
}

void Player::Update()
{
	//Find�������܂Ƃ߂�֐�
	AllFind();

	//Player�̉E�ړ����܂Ƃ߂��֐�
	PlayerRightMove();

	//Player�̍��ړ����܂Ƃ߂��֐�
	PlayerLeftMove();
	
	if (yMove_ == 0)
	{
		isJump_ = false;
	}

	//�W�����v
	Jump();

	//Player�̓����蔻����܂Ƃ߂�֐�
	Collision();

	//�����ʒu�ɖ߂鏈�����܂Ƃ߂��֐�
	Reset();

	//�{�^���ɐG�ꂽ���ǂ����𔻒肵��Stage�̕ϐ��̒l��ς���֐�
	MeanTimeButtonCheck();

	//���������{�^�����������u�ԂƗ��ꂽ�u�Ԃ̏������s���֐�
	OnDoubleButtonCheck();
	OrDoubleButtonCheck();

	//�{�^���ƕǂ̃��f����؂�ւ���֐�
	//�����ɑ����̃u���b�N�̏���n���Ă�����
	pStage_->ChengeButtonAndWall();

	//�S�[���ɐG�ꂽ���ǂ����𔻕ʂ���֐����Ă�
	pStage_->GoalCol((int)transform_.position_.x, (int)transform_.position_.y);

	//���[�v�u���b�N�ɐG�ꂽ���𔻕ʂ���֐����Ă�
	pStage_->WarpBlockCollision((int)transform_.position_.x, (int)(transform_.position_.y));
}

//Player�̓����蔻��̏������܂Ƃ߂��֐�
void Player::Collision()
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
		isJump_ = false;

		//Y���̈ړ�������������
		yMove_ = 0;

		//�ʒu��߂�
		transform_.position_.y = (float)checkY1 + BACK_POSITION_DOWN_;
	}
	else if(!pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		isJump_ = true;
	}
}

//�{�^���𓥂񂾏u�Ԃ����ꂽ�u�Ԃ̏������s���֐�
void Player::MeanTimeButtonCheck()
{
	//�ϐ����쐬
	//1�t���[���O�͓���ł��邩�ǂ���
	bool nowMeanTimeButton;

	//�{�^���𓥂�ł����true����ł��Ȃ����false���Ԃ����
	nowMeanTimeButton = pStage_->MeanTimeButton((int)transform_.position_.x, (int)(transform_.position_.y) - PLAYER_FOOT_);

	//1�t���[���O�͓���ł��Ȃ�
	if (!isPastMeanTimeButton_)
	{
		//���͓���ł���
		if (nowMeanTimeButton)
		{
			//���񂾏u�Ԃ̏���
			//�M�~�b�N�̃��f���ԍ��𒲂ׂ�
			//���񂾃{�^���̃��f���ԍ���1�̈ʂ��Ԃ����
			meanTimeGimmickNumber_ = pStage_->CheckFootBlock((int)transform_.position_.x, (int)(transform_.position_.y) - PLAYER_FOOT_);

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
	
//���������{�^���̕Е�
//����������̃^�C�~���O�Ɨ��ꂽ�u�Ԃ̏������s��
void Player::OnDoubleButtonCheck()
{
	//�ϐ��錾
	//1�t���[���O�͓���ł��邩�ǂ���
	bool onDoubleButton;

	//���񂾂�true���Ԃ���āA�����Ȃ����false���Ԃ����
	onDoubleButton = pStage_->OnDoubleButton((int)transform_.position_.x, (int)(transform_.position_.y) - PLAYER_FOOT_);

	//1�t���[���O�͓���ł��Ȃ�
	if (!isPastDoubleButton_[ON_DOUBLE_BUTTON])
	{
		//���͓���ł���
		if (onDoubleButton)
		{
			//���񂾏u�Ԃ̏���
			//�M�~�b�N�̃��f���ԍ��𒲂ׂ�
			//���񂾃{�^���̃��f���ԍ���1�̈ʂ��Ԃ����
			onGimmickNumber_ = pStage_->CheckFootBlock((int)transform_.position_.x, (int)(transform_.position_.y) - PLAYER_FOOT_);

			//���񂾃{�^���ɑΉ�����ϐ����J�E���g�A�b�v
			//�����ɂ͓��񂾃��f���ԍ���1�̈ʂ�n��
			pStage_->SetOnDoubleStepNumberCountUp(onGimmickNumber_);
		}
	}
	//1�t���[���O�͓���ł���
	else if (isPastDoubleButton_[ON_DOUBLE_BUTTON])
	{
		//���͓���ł��Ȃ�
		if (!onDoubleButton)
		{
			//���ꂽ�u�Ԃ̏���
			//���ꂽ�{�^���ɑΉ�����ϐ����J�E���g�_�E��
			//�����ɂ͗��ꂽ���f���ԍ���1�̈ʂ�n��
			pStage_->SetOnDoubleStepNumberCountDown(onGimmickNumber_);
		}
	}
	//�t���[�����P�i�߂�
	isPastDoubleButton_[ON_DOUBLE_BUTTON] = onDoubleButton;
}

//���������{�^���̂����Е��̏���
//���e�͓����Ȃ̂ŃR�����g�͏ȗ�
void Player::OrDoubleButtonCheck()
{
	bool orDoubleButton;

	orDoubleButton = pStage_->OrDoubleButton((int)transform_.position_.x, (int)(transform_.position_.y) - PLAYER_FOOT_);

	if (!isPastDoubleButton_[OR_DOUBLE_BUTTON])
	{
		if (orDoubleButton)
		{
			orGimmickNumber_ = pStage_->CheckFootBlock((int)transform_.position_.x, (int)(transform_.position_.y) - PLAYER_FOOT_);
			pStage_->SetOrDoubleStepNumberCountUp(orGimmickNumber_);
		}
	}
	else if (isPastDoubleButton_[OR_DOUBLE_BUTTON])
	{
		if (!orDoubleButton)
		{
			pStage_->SetOrDoubleStepNumberCountDown(orGimmickNumber_);
		}
	}
	isPastDoubleButton_[OR_DOUBLE_BUTTON] = orDoubleButton;
}

//�����ʒu�ɖ߂鏈�����܂Ƃ߂��֐�
void Player::Reset()
{
	//���Z�b�g�{�^������������
	//�L�^�����e�����ׂĂ܂�����ȏ�Ԃɂ�����
	if (Input::IsKeyDown(DIK_1) || Input::IsKeyDown(DIK_2))
	{
		//�����ʒu�ɖ߂�
		transform_.position_ = pStage_->GetStartPosition();
		Audio::Play(hSe_[1]);
	}
}

//�W�����v�̏������܂Ƃ߂��֐�
void Player::Jump()
{
	if (Input::IsKeyDown(DIK_SPACE) && !isJump_)
	{
		Audio::Play(hSe_[0]);

		//Y���̈ړ�
		transform_.position_.y += yMove_;

		//gravity�̒l���}�C�i�X�̒l�ɂ��āA���x�͏�����ɏd�͂�������悤�ɂȂ�
		yMove_ = DROP_DOWN_;

		isJump_ = true;
	}

	if (isJump_)
	{
		//���ɗ�����
		transform_.position_.y -= yMove_;

		//�u���b�N�̒��a���l���傫���Ȃ�Ƃ��蔲���Ă��܂��̂�
		//�u���b�N�̒��n���͑傫���Ȃ�Ȃ��悤�ɂ���
		if (yMove_ < BLOCK_SIZE_)
		{
			yMove_ += GRAVITY_;
		}
	}
}

void Player::Draw()
{
	//�`��
	Model::SetTransform(hModel_[direction_][modelNumber_], transform_);
	Model::Draw(hModel_[direction_][modelNumber_]);
}

//�E�ړ��̏���
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
	//�E���L�[�𗣂����u��
	//���f���ԍ���ύX
	else if (Input::IsKeyUp(DIK_RIGHT)) modelNumber_ = STANDING_MODEL;
}

//���ړ��̏���
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
	//�����L�[�𗣂�����
	//���f���ԍ���ύX
	else if (Input::IsKeyUp(DIK_LEFT)) modelNumber_ = STANDING_MODEL;
}

//Find�������܂Ƃ߂��֐�
void Player::AllFind()
{
	//Stage�N���X��T��
	//pStage_�ɒT������񂪓���
	if (pStage_ == nullptr) pStage_ = (Stage*)Find("Stage");
}

//���f���ԍ���Ԃ�
int Player::GetModelNumber()
{
	return modelNumber_;
}

//���t���[�������Ă��������Ԃ�
int Player::GetDirection()
{
	return direction_;
}

void Player::Release()
{
}