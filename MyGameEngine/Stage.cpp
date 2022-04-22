#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/CsvReader.h"
#include "Engine/Audio.h"
#include "Stage.h"
#include "Player.h"
#include "Shadow.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hSound_(-1),
    isOpenWall_(true),
    pPlayer_(nullptr),
    shadowCount_(0),
    timeCount_(0),
    isBlinking_(true)
{

}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    ModelLoad();


    //�T�E���h�f�[�^�̃��[�h
    hSound_ = Audio::Load("Assets/Dog.wav");
    assert(hSound_ >= 0);



    //Csv�t�@�C���̓ǂݍ���
    CsvReader csv;
    csv.Load("Assets/Stage1.csv");


    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 12; y++)
        {
            map_[x][y] = csv.GetValue(x, 11 - y); //�G�N�Z������y�̒l���t�Ȃ̂�-9�����Ă�����

            if (map_[x][y] == 200)
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
    

    //��莞�Ԃ��ƂɃu���b�N�����ւ���
    Blinking(71, 60);


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

    //�ۑ����ꂽ�e�̓��������ׂă��Z�b�g����
    if (Input::IsKeyDown(DIK_2))
    {
        for (int i = 0; i <= shadowCount_; i++)
        {
            pShadow[i]->killMe();
        }

        shadowCount_ = 0;
    }
}





//�`��
void Stage::Draw()
{
    //�u���b�N�̔z�u
    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 12; y++)
        {
            //�v���C���[�̈ʒu�ƃu���b�N��u���Ȃ��ʒu�̏ꍇ
            if (map_[x][y] == 0 || map_[x][y] == 200)
            {
                continue;
            }

            //���f���ԍ��̊i�[
            int type = map_[x][y] - 1;

            //�ʒu
            Transform trans;
            trans.position_.x = x;
            trans.position_.y = y;

            //Calclation�N���X�ňʒu��ύX����
            trans.Calclation();


            //���f���̃��[�h
            Model::SetTransform(hModel_[type], trans);
            Model::Draw(hModel_[type]);
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
    //�����ɂ̓u���b�N�͂Ȃ�
    if (map_[x][y] == 0 || 
        map_[x][y] == 200 || 
        map_[x][y] == 81 || 
        map_[x][y] == 91 ||
        map_[x][y] == 51 ||
        map_[x][y] == 71)
    {
        return false;
    }
    //�����ɂ̓u���b�N�����邩��ʂ�Ȃ�
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
    if (map_[x][y] == 21)
    {

        Audio::Play(hSound_);


        map_[x][y] = map_[x][y] + 10;

        isOpenWall_ = false;//�ǂ��J����

        OpenWall();//�ǂ��J������
    }


    //Player�����ꂽ��
    if (map_[x][y] == 0||Input::IsKeyDown(DIK_1))
    {
        for (int i = 0; i <= shadowCount_; i++)
        {
            if (pShadow[i]->isRecording_ == false)
            {
                CheckBlock(31, false);
                CheckBlock(51, false);
            }
            
        }
        //�{�^���̃��f����؂�ւ���
        CheckBlock(31 , false);

        //�ǂ̃��f����؂�ւ���
        CheckBlock(51 , false);
    }
}


//�ǂ��J���֐�
void Stage::OpenWall()
{
    CheckBlock(41, true);

    //�ǂ��S���J����
    isOpenWall_ = true;
}


//����̃u���b�N��T���āA���f����؂�ւ���֐�
//�������͐؂�ւ������u���b�N�̔ԍ�
//�������̓v���X���}�C�i�X��
void Stage::CheckBlock(int find , bool which)
{
    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 12; y++)
        {
            if (map_[x][y] == find && which == false)
            {
                map_[x][y] = map_[x][y] - 10;
            }
            else if(map_[x][y] == find && which == true)
            {
                map_[x][y] = find + 10;
            }
        }
    }
}

void Stage::Blinking(int blockNum, int time)
{
    timeCount_++;

    if (timeCount_ >= time && isBlinking_ == true)
    {
        //���f����؂�ւ���֐�
        CheckBlock(blockNum , false);

        isBlinking_ = false;

        //�v�����Ԃ����Z�b�g
        timeCount_ = 0;
    }
    else if(timeCount_ >= time && isBlinking_ == false)
    {
        CheckBlock(blockNum - 10, true);

        isBlinking_ = true;

        //�v�����Ԃ����Z�b�g
        timeCount_ = 0;
    }
}

//����̃u���b�N�̈ʒu�Ƀ��[�v����֐�
void Stage::WarpBlock(int x, int y)
{
    if (map_[x][y] == 81)
    {
        pPlayer_->killMe();

        Player* pPlayer = (Player*)Instantiate<Player>(this->pParent_);

        pPlayer->transform_.position_.x = map_[x][y]+10;
        pPlayer->transform_.position_.y = map_[x][y]+10;
    }
}



void Stage::ModelLoad()
{

    //�X�e�[�W���\������u���b�N
    hModel_[0] = Model::Load("Assets/Block.fbx");
    hModel_[1] = Model::Load("Assets/NaturalBlock.fbx");
    hModel_[2] = Model::Load("Assets/Goal.fbx");
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
    hModel_[40] = Model::Load("Assets/Wall.fbx");
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
    hModel_[50] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[51] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[52] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[53] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[54] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[55] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[56] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[57] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[58] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[59] = Model::Load("Assets/YellowBlock.fbx");


    //������u���b�N(������O)
    hModel_[60] = Model::Load("Assets/Wall.fbx");
    hModel_[61] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[62] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[63] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[64] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[65] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[66] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[67] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[68] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[69] = Model::Load("Assets/YellowBlock.fbx");


    //������u���b�N(��������)
    hModel_[70] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[71] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[72] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[73] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[74] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[75] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[76] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[77] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[78] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[79] = Model::Load("Assets/GreenBlock.fbx");


    //���[�v�u���b�N(����)
    hModel_[80] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[81] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[82] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[83] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[84] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[85] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[86] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[87] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[88] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[89] = Model::Load("Assets/WarpEntrance.fbx");


    //���[�v�u���b�N(�o��)
    hModel_[90] = Model::Load("Assets/WarpExit.fbx");
    hModel_[91] = Model::Load("Assets/WarpExit.fbx");
    hModel_[92] = Model::Load("Assets/WarpExit.fbx");
    hModel_[93] = Model::Load("Assets/WarpExit.fbx");
    hModel_[94] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[95] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[96] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[97] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[98] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[99] = Model::Load("Assets/WarpEntrance.fbx");


}

