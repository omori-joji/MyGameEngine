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
	isJump_(false),//�W�����v����

	move_(0.01),//Y���̈ړ�
	gravity_(0.01),//�d��
 
	pStage_(nullptr),//�X�e�[�W�̏�������|�C���^
	plyerRightMoveCount(0),
	isDirection(true),
	plyerLeftMoveCount(0),
	hModel_Left(),
	hModel_Right()
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

	//Stage�N���X��T��
	//pStage_�ɒT������񂪓���
	if (pStage_ == nullptr)
	{
		pStage_ = (Stage*)Find("Stage");
	}
	



	

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



	//���Z�b�g�{�^������������
	//�L�^�����e�����ׂĂ܂�����ȏ�Ԃɂ�����
	if (Input::IsKeyDown(DIK_1) || Input::IsKeyDown(DIK_2))
	{
		//�����ʒu�ɖ߂�
		transform_.position_ = pStage_->stertPos; 
	}




	//�v���C���[�̌��_�͏㉺�Ō���Ɖ��B���E�Ō���Ɛ^��
	//�����������ǂ���

	//�����蔻��̕ϐ��錾
	int checkX1 , checkX2;
	int checkY1 , checkY2;


	//��
	checkX1 = (int)(transform_.position_.x - WIDTH);
	checkX2 = (int)(transform_.position_.x - WIDTH);
	checkY1 = (int)(transform_.position_.y + (HEIGHT- MARGIN));
	checkY2 = (int)(transform_.position_.y + MARGIN);

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		transform_.position_.x = (float)checkX1 + 1.3f;
	}

	//�E
	checkX1 = (int)(transform_.position_.x + WIDTH);
	checkX2 = (int)(transform_.position_.x + WIDTH);
	checkY1 = (int)(transform_.position_.y + (HEIGHT - MARGIN));
	checkY2 = (int)(transform_.position_.y + MARGIN);

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		transform_.position_.x = (float)checkX1 - 0.3f;
	}


	//��
	checkX1 = (int)(transform_.position_.x + (WIDTH- MARGIN));
	checkX2 = (int)(transform_.position_.x - (WIDTH - MARGIN));
	checkY1 = (int)(transform_.position_.y + HEIGHT);
	checkY2 = (int)(transform_.position_.y + HEIGHT);

	if (pStage_->isCrash(checkX1, checkY1) || pStage_->isCrash(checkX2, checkY2))
	{
		transform_.position_.y = (float)checkY1 - 0.6f;
	}
	else
	{
		//�W�����v
		if (Input::IsKeyDown(DIK_SPACE) && isJump_ == false)
		{
			isJump_ = true;//�W�����v���Ă���

			//gravity�̒l���}�C�i�X�ɂ��邱�Ƃɂ���č��x�͏�����ɏd�͂�������悤�ɂȂ�
			transform_.position_.y += move_;
			move_ = -0.2f;
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

		move_ = 0;

		transform_.position_.y = (float)checkY1 + 1.0f;
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
			move_ += gravity_;
		}
	}

	//�����Ƀ{�^�������邩�Ȃ����𔻕ʂ���֐�
	pStage_->DownButton((int)transform_.position_.x, (int)(transform_.position_.y)-1);

	pStage_->GoalCol((int)transform_.position_.x, (int)transform_.position_.y);

	if (pStage_->WarpBlockEnter((int)transform_.position_.x, (int)transform_.position_.y))
	{
		pStage_->WarpBlockExit((int)transform_.position_.x, (int)(transform_.position_.y));
	}

	pStage_->WarpBlockExit((int)transform_.position_.x, (int)(transform_.position_.y));
}

void Player::Draw()
{
	if (isDirection)
	{
		Model::SetTransform(hModel_Right[plyerRightMoveCount], transform_);
		Model::Draw(hModel_Right[plyerRightMoveCount]);
	}
	else if(!isDirection)
	{
		Model::SetTransform(hModel_Left[plyerLeftMoveCount], transform_);
		Model::Draw(hModel_Left[plyerLeftMoveCount]);
	}

}

void Player::Release()
{

}
