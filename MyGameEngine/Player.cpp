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
	isJump(false),//�W�����v����

	move_(0.01),//Y���̈ړ�
	gravity_(0.01),//�d��
 
	pStage_(nullptr)//�X�e�[�W�̏�������|�C���^
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	hModel_ = Model::Load("Assets/Player.fbx");
}

void Player::Update()
{
	//Stage�N���X��T��
	//pStage_�ɒT������񂪓���
	if (pStage_ == nullptr)
	{
		pStage_ = (Stage*)Find("Stage");
	}
	



	//�E�ړ�
	if (Input::IsKey(DIK_RIGHT))
	{
	    transform_.position_.x += SPEED;
	}

		//���ړ�
	if (Input::IsKey(DIK_LEFT))
	{
	    transform_.position_.x -= SPEED;
	}


	//�Đ��X�^�[�g
	if (Input::IsKeyDown(DIK_1))
	{
		transform_.position_ = pStage_->stertPos; //�����ʒu�ɖ߂�
	}




	//�v���C���[�̌��_�͏㉺�Ō���Ɖ��B���E�Ō���Ɛ^��
	//�����������ǂ���

	//
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
		if (Input::IsKeyDown(DIK_SPACE) && isJump == false)
		{
			isJump = true;//�W�����v���Ă���

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
		isJump = false;//���Ƀu���b�N���������獡�̓W�����v���Ă��Ȃ�
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

	pStage_->DownButton((int)transform_.position_.x, (int)(transform_.position_.y) - 1);
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{

}
