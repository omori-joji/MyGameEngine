#include "Stage.h"
#include "Engine/Model.h"
#include "Player.h"
#include "Shadow.h"
#include "Engine/CsvReader.h"
#include "Engine/Input.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),
    isOpenWall_(true),
    isButtonCol_(true),
    pPlayer_(nullptr),
    shadowCount_(0)
    
{
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    hModel_[0] = Model::Load("Assets/BlueBlock.fbx");
    hModel_[1] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[2] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[3] = Model::Load("Assets/PushButton.fbx");
    hModel_[4] = Model::Load("Assets/PushButton2.fbx");
    hModel_[5] = Model::Load("Assets/UpButton.fbx");
    hModel_[6] = Model::Load("Assets/UpButton2.fbx");


    //Csv�t�@�C���̓ǂݍ���
    CsvReader csv;
    csv.Load("Assets/Stage1.csv");


    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            map_[x][y] = csv.GetValue(x, 9 - y); //�G�N�Z������y�̒l���t�Ȃ̂�-9�����Ă�����

            if (map_[x][y] == 99)
            {
                //�v���C���[�̐���
                //�v���C���[�̈ʒu����
                //�v���C���[�̏����ʒu���L������
                Player* pPlayer = (Player*)Instantiate<Player>(this->pParent_);
                pPlayer->transform_.position_.x = x;
                pPlayer->transform_.position_.y = y;
                stertPos = pPlayer->transform_.position_;
            }
        }
    }


    //�e�̐���
    pShadow[shadowCount_] = (Shadow*)Instantiate<Shadow>(this->pParent_);
    
}

//�X�V
void Stage::Update()
{
    if (pPlayer_ == nullptr)
    {
        pPlayer_ = (Player*)Find("Player");
    }





    //�Đ��X�^�[�g
    if (Input::IsKeyDown(DIK_1))
    {
        //���łɐ������Ă���e��\�����A������x�Đ�����
        if (shadowCount_ <= 5)
        {
            //���łɐ������Ă���e��������x1����Đ�����
            for (int i = 0; i <= shadowCount_; i++)
            {
                //�\������t���O
                pShadow[i]->Flag();
            }

            if (shadowCount_ <= 4)
            {
                //��̖ڈȍ~�̉e�̔ԍ�
                shadowCount_++;
            }
        }


        //�e�̐���
        if (shadowCount_ <= 5)
        {
            pShadow[shadowCount_] = (Shadow*)Instantiate<Shadow>(this);
        }
    }
}





//�`��
void Stage::Draw()
{
    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            if (map_[x][y] == 0 || map_[x][y] == 99)
            {
                continue;
            }

            int type = map_[x][y] - 1;
            Transform trans;
            trans.position_.x = x;
            trans.position_.y = y;
            trans.Calclation();



            Model::SetTransform(hModel_[type], trans);
            Model::Draw(hModel_[type]);
            int a = 0;
        }
    }
}





//�J��
void Stage::Release()
{
}





//���̃}�X�ɏ�Q�������邩�ǂ���
//�߂�l�A��������true,�����Ȃ�false
bool Stage::isCrash(int x, int y)
{
    //�z���1�������Ă���Βʂ�Ȃ�
    if (map_[x][y] == 0 || map_[x][y] == 99)
    {
        return false;
    }
    else
    {
        return true;
    }
}





//�{�^����Player�̑����ɂ��邩�ǂ����𔻒f����֐�
//�{�^���������Ă���z���map_[x][y] == 4�������Ă���
//���̊֐���Player�N���X�ŏ�ɌĂ΂�Ă���
void Stage::DownButton(int x, int y)
{
    //��������̃��f���ɍ����ւ���
    if(map_[x][y] == 4)
    {
        map_[x][y] = 5;

        isOpenWall_ = false;//�ǂ��J����

        OpenWall();//�ǂ��J������
    }
    else if (map_[x][y] == 5 && isButtonCol_ == true)
    {
        pPlayer_->transform_.position_.y -= 0.5f;

        isButtonCol_ = false;
    }
}




void Stage::OpenWall()
{
    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            if (map_[x][y] == 6 && isOpenWall_ == false)
            {
                //�ǂ��z�u����Ă�����0�����Ă�����
                map_[x][y] = 0;
            }
        }
    }

    //�ǂ��S���J����
    isOpenWall_ = true;
}

