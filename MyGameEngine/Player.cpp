#include "Player.h"
#include "Shadow.h"
#include "Engine/Model.h"
#include "Engine/Input.h"





Player::Player(GameObject* parent)
	: GameObject(parent, "Player"),

	//�ړ����x
	SPEED(0.1f),

	WIDTH(0.3f),//Player�̕�
	HEIGHT(0.6f),//Player�̍���
	MARGIN(0.11f),//�����蔻��̗V��
	BLOCK_SIZE(1.0f),//�u���b�N�̃T�C�Y
	MAX_JUMP(3.0f),//�W�����v�̏��
	BACK_POSITION_LEFT_(1.3f),
	BACK_POSITION_RIGHT_(0.3f),
	BACK_POSITION_UP_(0.6f),
	BACK_POSITION_DOWN_(1.0f),
	RESET_VALU_(0),
	PLAYER_FOOT_(1),
	GRAVITY_(0.01f),
	DROP_DOWN_(-0.2f),
	isJump_(false),//�W�����v����

	move_(0.01f),//Y���̈ړ�
 
	pStage_(nullptr),//�X�e�[�W�̏�������|�C���^
	plyerRightMoveCount(0),
	isDirection(true),
	plyerLeftMoveCount(0),
	hModel_Left(),
	hModel_Right(),
	isPastButton(false)
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	hModel_Right[0] = Model::Load("Assets/Player/PlayerRightStanding.fbx");
	hModel_Right[1] = Model::Load("Assets/Player/PlayerRightRun.fbx");

	hModel_Left[0] = Model::Load("Assets/Player/PlayerLeftStanding.fbx");
	hModel_Left[1] = Model::Load("Assets/Player/PlayerLeftRun.fbx");
}

void Player::Update()
{
	//Find�������܂Ƃ߂�֐�
	AllFind();

	//Player�̑�����܂Ƃ߂�֐�
	PlayerMove();
	
	//Player�̓����蔻����܂Ƃ߂�֐�
	PlayerCollision();



	//���Z�b�g�{�^������������
	//�L�^�����e�����ׂĂ܂�����ȏ�Ԃɂ�����
	if (Input::IsKeyDown(DIK_1) || Input::IsKeyDown(DIK_2))
	{
		//�����ʒu�ɖ߂�
		transform_.position_ = pStage_->GetStartPosition();
	}








	

	//�S�[���ɐG�ꂽ���ǂ����𔻕ʂ���֐����Ă�
	pStage_->GoalCol((int)transform_.position_.x, (int)transform_.position_.y);


	//���[�v�u���b�N�ɐG�ꂽ���𔻕ʂ���֐����Ă�
	pStage_->WarpBlockExit((int)transform_.position_.x, (int)(transform_.position_.y));





	bool nowButton;
	nowButton = pStage_->DownButton((int)transform_.position_.x, (int)(transform_.position_.y) - PLAYER_FOOT_);
	

		
    //�ߋ��͓���ł��Ȃ����͓���ł���
    if (!isPastButton)
	{
	   //���͓���ł���
	   if (nowButton)
	   {
		   pStage_->steppingNumber++;
	   }
	}
	//�ߋ��͓���ł��鍡�͓���ł��Ȃ�
	else if (isPastButton)
	{
	   if (!nowButton)
	   {
		   pStage_->steppingNumber--;
	   }
	}	
	isPastButton = nowButton;
	
}







void Player::Draw()
{
	if (isDirection)
	{
		Model::SetTransform(hModel_Right[plyerRightMoveCount], transform_);
		Model::Draw(hModel_Right[plyerRightMoveCount]);
	}
	else
	{
		Model::SetTransform(hModel_Left[plyerLeftMoveCount], transform_);
		Model::Draw(hModel_Left[plyerLeftMoveCount]);
	}

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

void Player::PlayerMove()
{
	//���ړ�
//�����L�[�������Ă�����
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.position_.x -= SPEED;
	}

	//�����L�[���������u��
	if (Input::IsKeyDown(DIK_LEFT))
	{
		//���������Ă���t���O
		isDirection = false;

		//���f���ԍ���ύX
		plyerLeftMoveCount++;
	}

	//�����L�[�𗣂�����
	if (Input::IsKeyUp(DIK_LEFT))
	{
		//���f���ԍ���ύX
		plyerLeftMoveCount--;
	}



	//�E�ړ�
	//�E���L�[�������Ă�����
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.position_.x += SPEED;
	}

	//�E���L�[���������u��
	if (Input::IsKeyDown(DIK_RIGHT))
	{
		//�E�������Ă���t���O
		isDirection = true;

		plyerRightMoveCount++;
	}

	//�E���L�[�𗣂����u��
	if (Input::IsKeyUp(DIK_RIGHT))
	{
		//���f���ԍ���ύX
		plyerRightMoveCount--;
	}
}

void Player::PlayerCollision()
{
	//�v���C���[�̌��_�͏㉺�Ō���Ɖ��B���E�Ō���Ɛ^��
	//�����������ǂ���

	//�����蔻��̕ϐ��錾
	int checkX1, checkX2;
	int checkY1, checkY2;


	//��
	checkX1 = (int)(transform_.position_.x - WIDTH);
	checkX2 = (int)(transform_.position_.x - WIDTH);
	checkY1 = (int)(transform_.position_.y + (HEIGHT - MARGIN));
	checkY2 = (int)(transform_.position_.y + MARGIN);

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		transform_.position_.x = (float)checkX1 + BACK_POSITION_LEFT_;
	}

	//�E
	checkX1 = (int)(transform_.position_.x + WIDTH);
	checkX2 = (int)(transform_.position_.x + WIDTH);
	checkY1 = (int)(transform_.position_.y + (HEIGHT - MARGIN));
	checkY2 = (int)(transform_.position_.y + MARGIN);

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		transform_.position_.x = (float)checkX1 - BACK_POSITION_RIGHT_;
	}


	//��
	checkX1 = (int)(transform_.position_.x + (WIDTH - MARGIN));
	checkX2 = (int)(transform_.position_.x - (WIDTH - MARGIN));
	checkY1 = (int)(transform_.position_.y + HEIGHT);
	checkY2 = (int)(transform_.position_.y + HEIGHT);

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		transform_.position_.y = (float)checkY1 - BACK_POSITION_UP_;
	}
	else
	{
		//�W�����v
		if (Input::IsKeyDown(DIK_SPACE) && isJump_ == false)
		{
			isJump_ = true;//�W�����v���Ă���

			//gravity�̒l���}�C�i�X�ɂ��邱�Ƃɂ���č��x�͏�����ɏd�͂�������悤�ɂȂ�
			transform_.position_.y += move_;
			move_ = DROP_DOWN_;
		}
	}


	//��
	checkX1 = (int)(transform_.position_.x + (WIDTH - MARGIN));
	checkX2 = (int)(transform_.position_.x - (WIDTH - MARGIN));
	checkY1 = (int)(transform_.position_.y);
	checkY2 = (int)(transform_.position_.y);

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		isJump_ = false;//���Ƀu���b�N���������獡�̓W�����v���Ă��Ȃ�

		move_ = RESET_VALU_;

		transform_.position_.y = (float)checkY1 + BACK_POSITION_DOWN_;
	}
	//�d��
	//���ɉ����Ȃ�������ǂ�ǂ񉺂���
	else
	{

		transform_.position_.y -= move_;

		//�u���b�N�̒��a���l���傫���Ȃ�Ƃ��蔲���Ă��܂��̂�
		//�u���b�N�̒��n���͑傫���Ȃ�Ȃ��悤�ɂ���
		//gravity�̒l��0.01
		if (move_ < BLOCK_SIZE)
		{
			move_ += GRAVITY_;
		}
	}
}
