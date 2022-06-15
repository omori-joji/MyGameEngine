#include "Player.h"
#include "Stage.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
	: Actor(parent, "Player"),
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
	//direction_(),					//Player�̌����̃��f���ԍ�
	//se_(),							//�T�E���h�t�@�C�����i�[����z��
	Model_Number_(0),				//Player�̑����Ă��郂�f���ԍ�
	hModel_(),						//���f�������[�h���邽�߂̑������z��
	MODEL_FILE_PAS_("Assets/Player/"),//Player�̃��f�����ۑ�����Ă���t�@�C���p�X
	SE_FILE_PAS_("Assets/Sound/"),	//�T�E���h�t�@�C���̃t�@�C���p�X
	isJump_(false),					//�W�����v����
	pStage_(nullptr),				//�X�e�[�W�̏�������|�C���^
	hSe_()							//SE�����[�h���邽�߂̔z��
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
	//�T�E���h�t�@�C���̃��[�h
	hSe_[JUMP] = Audio::Load(SE_FILE_PAS_ + "Jump.wav", 2);
	hSe_[RESET] = Audio::Load(SE_FILE_PAS_ + "Reset.wav", 2);

	//�E�����������Ă��郂�f���̃��[�h
	hModel_[DIR_RIGHT][STANDING_MODEL] = Model::Load(MODEL_FILE_PAS_ + "PlayerRightStanding.fbx");
	hModel_[DIR_RIGHT][RUN_MODEL] = Model::Load(MODEL_FILE_PAS_ + "PlayerRightRun.fbx");

	//�������������Ă��郂�f���̃��[�h
	hModel_[DIR_LEFT][STANDING_MODEL] = Model::Load(MODEL_FILE_PAS_ + "PlayerLeftStanding.fbx");
	hModel_[DIR_LEFT][RUN_MODEL] = Model::Load(MODEL_FILE_PAS_ + "PlayerLeftRun.fbx");
}

//�X�V
void Player::Update()
{
	AllFind();

	PlayerRightMove();

	PlayerLeftMove();
	
	Jump();

	Collision();

	Reset();

	CommonMeanTimeButtonDown();

	//Actor�N���X����p��
	No1DoubleButtonDown();
	No2DoubleButtonDown();

	pStage_->ChengeButtonAndWall();

	pStage_->GoalCol((int)transform_.position_.x, (int)transform_.position_.y);

	pStage_->WarpBlockCollision((int)transform_.position_.x, (int)(transform_.position_.y));
}

//Playyer�̓����蔻����܂Ƃ߂�֐�
//�����F�Ȃ�
//�߂�l�F�Ȃ�
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
	else
	{
		//�W�����v���Ă���
		isJump_ = true;
	}
}

//�����ʒu�ɖ߂鏈�����܂Ƃ߂��֐�
//�����F�Ȃ�
//�߂�l�F�Ȃ�
void Player::Reset()
{
	//���Z�b�g�{�^������������
	//�L�^�����e�����ׂĂ܂�����ȏ�Ԃɂ�����
	if (Input::IsKeyDown(DIK_1))
	{
		//�����ʒu�ɖ߂�
		transform_.position_ = pStage_->GetStartPosition();
		Audio::Play(hSe_[1]);
	}
}

//�W�����v�̏������܂Ƃ߂��֐�
//�����F�Ȃ�
//�߂�l�F�Ȃ�
void Player::Jump()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		//�����Ƀu���b�N���Ȃ�������
		if (!pStage_->isCrash((int)transform_.position_.x, transform_.position_.y-0.1))
		{
			return;
		}

		//SE��炷
		Audio::Play(hSe_[0]);

		//Y���̈ړ�
		transform_.position_.y += yMove_;

		//gravity�̒l���}�C�i�X�̒l�ɂ��āA���x�͏�����ɏd�͂�������悤�ɂȂ�
		yMove_ = DROP_DOWN_;
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

//�`��
void Player::Draw()
{
	//�`��
	Model::SetTransform(hModel_[direction_][Model_Number_], transform_);
	Model::Draw(hModel_[direction_][Model_Number_]);
}

//Player�̉E������܂Ƃ߂�֐�
//�����F�Ȃ�
//�߂�l�F�Ȃ�
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
		Model_Number_ = RUN_MODEL;
	}
	//�E���L�[�𗣂����u��
	//���f���ԍ���ύX
	else if (Input::IsKeyUp(DIK_RIGHT)) Model_Number_ = STANDING_MODEL;
}

//Player�̍�������܂Ƃ߂�֐�
//�����F�Ȃ�
//�߂�l�F�Ȃ�
void Player::PlayerLeftMove()
{
	//���ړ�
	//�����L�[�������Ă�����
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= SPEED_;

		//���f���ԍ���ύX
		direction_ = DIR_LEFT;
		Model_Number_ = RUN_MODEL;
	}
	//�����L�[�𗣂�����
	//���f���ԍ���ύX
	else if (Input::IsKeyUp(DIK_LEFT)) Model_Number_ = STANDING_MODEL;
}

//Find���������ׂĂ܂Ƃ߂�֐�
//�����F�Ȃ�
//�߂�l�F�Ȃ�
void Player::AllFind()
{
	//Stage�N���X��T��
	//pStage_�ɒT������񂪓���
	if (pStage_ == nullptr) pStage_ = (Stage*)Find("Stage");
}

//Player�̑����Ă��郂�f���ԍ���Ԃ��֐�
//�����F�Ȃ�
//�߂�l�FmodelNumber_
int Player::GetModelNumber()
{
	return Model_Number_;
}

//Player�����̃��f���ԍ���Ԃ��֐�
//�����F�Ȃ�
//�߂�l�Fdirection_
int Player::GetDirection()
{
	return direction_;
}

//���
void Player::Release()
{
}