#include "Stage.h"
#include "Engine/Model.h"
#include "Player.h"
#include "Shadow.h"
#include "Engine/CsvReader.h"
#include "Engine/Input.h"
#include "time.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),
    isOpenWall_(true),
    pPlayer_(nullptr),
    shadowCount_(0),
    a(0)
{

}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    //�X�e�[�W���\������u���b�N
    hModel_[0] = Model::Load("Assets/BlueBlock.fbx");
    hModel_[1] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[2] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[3] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[4] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[5] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[6] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[7] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[8] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[9] = Model::Load("Assets/GreenBlock.fbx");


    //�������甭������u���b�N
    hModel_[10] = Model::Load("Assets/PushButton.fbx");
    hModel_[11] = Model::Load("Assets/PushButton.fbx");
    hModel_[12] = Model::Load("Assets/PushButton.fbx");
    hModel_[13] = Model::Load("Assets/PushButton.fbx");
    hModel_[14] = Model::Load("Assets/PushButton.fbx");
    hModel_[15] = Model::Load("Assets/PushButton.fbx");
    hModel_[16] = Model::Load("Assets/PushButton.fbx");
    hModel_[17] = Model::Load("Assets/PushButton.fbx");
    hModel_[18] = Model::Load("Assets/PushButton.fbx");
    hModel_[19] = Model::Load("Assets/PushButton.fbx");


    //�����Ă���Ԃ�����������u���b�N(�����O)
    hModel_[20] = Model::Load("Assets/UpButton.fbx");
    hModel_[21] = Model::Load("Assets/UpButton.fbx");
    hModel_[22] = Model::Load("Assets/UpButton.fbx");
    hModel_[23] = Model::Load("Assets/UpButton.fbx");
    hModel_[24] = Model::Load("Assets/UpButton.fbx");
    hModel_[25] = Model::Load("Assets/UpButton.fbx");
    hModel_[26] = Model::Load("Assets/UpButton.fbx");
    hModel_[27] = Model::Load("Assets/UpButton.fbx");
    hModel_[28] = Model::Load("Assets/UpButton.fbx");
    hModel_[29] = Model::Load("Assets/UpButton.fbx");


    //�����Ă���Ԃ�����������u���b�N(��������)
    hModel_[30] = Model::Load("Assets/UpButton2.fbx");
    hModel_[31] = Model::Load("Assets/UpButton2.fbx");
    hModel_[32] = Model::Load("Assets/UpButton2.fbx");
    hModel_[33] = Model::Load("Assets/UpButton2.fbx");
    hModel_[34] = Model::Load("Assets/UpButton2.fbx");
    hModel_[35] = Model::Load("Assets/UpButton2.fbx");
    hModel_[36] = Model::Load("Assets/UpButton2.fbx");
    hModel_[37] = Model::Load("Assets/UpButton2.fbx");
    hModel_[38] = Model::Load("Assets/UpButton2.fbx");
    hModel_[39] = Model::Load("Assets/UpButton2.fbx");


    //�J����
    hModel_[40] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[41] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[42] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[43] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[44] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[45] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[46] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[47] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[48] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[49] = Model::Load("Assets/GreenBlock.fbx");


    //�J���Ă���Ԃ̉����Ȃ��u���b�N
    hModel_[50] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[51] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[52] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[53] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[54] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[55] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[56] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[57] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[58] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[59] = Model::Load("Assets/YellowBlock.fbx");

    //Csv�t�@�C���̓ǂݍ���
    CsvReader csv;
    csv.Load("Assets/Stage1.csv");


    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 12; y++)
        {
            map_[x][y] = csv.GetValue(x, 11 - y); //�G�N�Z������y�̒l���t�Ȃ̂�-9�����Ă�����

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
    int s = 0;

    a += DeltaTime();

    if (a >= 3)
    {
        int A;
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
        for (int y = 0; y < 12; y++)
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
    if(map_[x][y] == 21)
    {
        map_[x][y] = map_[x][y] + 10;

        isOpenWall_ = false;//�ǂ��J����

        OpenWall();//�ǂ��J������
    }


    //Player�����ꂽ��
    if (map_[x][y] == 0 || Input::IsKeyDown(DIK_1))
    {
        //�{�^���̃��f����؂�ւ���
        CheckBrock(31);

        //�ǂ̃��f����؂�ւ���
        CheckBrock(51);
    }
}




void Stage::OpenWall()
{
    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 12; y++)
        {
            if (map_[x][y] == 41 && isOpenWall_ == false)
            {
                //�ǂ��z�u����Ă�����0�����Ă�����
                map_[x][y] = map_[x][y] + 10;
            }
        }
    }

    //�ǂ��S���J����
    isOpenWall_ = true;
}


//����̃u���b�N��T���āA���f����؂�ւ���֐�
void Stage::CheckBrock(int find)
{
    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 12; y++)
        {
            if (map_[x][y] == find)
            {
                map_[x][y] = map_[x][y] - 10;
            }
        }
    }
}

