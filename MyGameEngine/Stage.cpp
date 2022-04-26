#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/CsvReader.h"
#include "Engine/SceneManager.h"
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
    isBlinking_(true),
    verticalValu(0),     //�}�b�v�c���̒l
    besideValu(0),       //�}�b�v�����̒l
    memoryBlock_(0)
{

}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    //�u���b�N�Ȃǂ̃��f�������[�h���鏈�����܂Ƃ߂��֐�
    ModelLoad();


    //Csv�t�@�C���̓ǂݍ���
    CsvReader csv;
    csv.Load("Assets/Stage3.csv");


    //Excel�Őݒ肵���}�X�̒l
    //�c
    verticalValu = 23;

    //��
    besideValu = 28;



    //�v���C���[�̐���
    //200�������Ă���}�X�Ƀv���C���[���o������
    for (int x = 0; x < besideValu; x++)
    {
        for (int y = 0; y < verticalValu; y++)
        {
            map_[x][y] = csv.GetValue(x, (verticalValu-1) - y); //�G�N�Z������y�̒l���t�Ȃ̂ŏc��-1�����Ă�����

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
    //Player���̊i�[
    if (pPlayer_ == nullptr)
    {
        pPlayer_ = (Player*)Find("Player");
    }


    //�Đ��X�^�[�g
    if (Input::IsKeyDown(DIK_1))
    {
        //�_�Ńu���b�N�̏������Z�b�g
        timeCount_ = 0;
        isBlinking_ = true;


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
        //������e��
        for (int i = 0; i <= shadowCount_; i++)
        {
            //�������
            pShadow[i]->killMe();
        }
        //�e�̐������Z�b�g
        shadowCount_ = 0;
    }
    //��莞�Ԃ��ƂɃu���b�N�����ւ���
    Blinking(81, 70);
}





//�`��
void Stage::Draw()
{
    //�u���b�N�̔z�u
    for (int x = 0; x < besideValu; x++)
    {
        for (int y = 0; y < verticalValu; y++)
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

    //�w�i�̐���
    //�ǐ^�񒆂ɏo��
    Transform back;

    //�����̐^��
    back.position_.x = besideValu / 2;
    //�c���̐^��
    back.position_.y = verticalValu / 2 + 1;
    //��������
    back.position_.z = 0.5;
    //�ʒu�̊m��
    back.Calclation();

    Model::SetTransform(hModel_[3], back);
    Model::Draw(hModel_[3]);
}





//�J��
void Stage::Release()
{
}







//���̃}�X�ɏ�Q�������邩�ǂ���
//�߂�l�A��������true,�����Ȃ�false
bool Stage::isCrash(int x, int y)
{
    for (int i = 0; i < 9; i++)
    {
        //�����ɂ̓u���b�N�͂Ȃ�
        if (map_[x][y] == 0 ||
            map_[x][y] == 3 ||
            map_[x][y] == 200 ||
            map_[x][y] == 91 ||
            map_[x][y] == 101 ||
            map_[x][y] == 61 ||
            map_[x][y] == 81)
        {
            return false;
        }
        //�����ɂ̓u���b�N�����邩��ʂ�Ȃ�
        else
        {
            return true;
        }
    }

}





//�{�^����Player�̑����ɂ��邩�ǂ����𔻒f����֐�
//�{�^���������Ă���z���map_[x][y] == 4�������Ă���
//���̊֐���Player�N���X�ŏ�ɌĂ΂�Ă���
void Stage::DownButton(int x, int y)
{
    for (int i = 0; i < 9; i++)
    {
        if (map_[x][y] == 31 + i)
        {

            //���f���ύX
            map_[x][y] = map_[x][y] + 10;

            memoryBlock_ = map_[x][y];

            //�ǂ��J������
            CheckBlock(memoryBlock_ + 10, true);
        }
    }
    
    

    //Player�����ꂽ��
    //�������̓��Z�b�g������
    if (map_[x][y] == 0||Input::IsKeyDown(DIK_1))
    {
        //�����Ă���Ԃ����̃{�^���̃��f�������Z�b�g����
        for (int i = 0; i <= shadowCount_; i++)
        {
            if (pShadow[i]->isRecording_ == false)
            {
                    CheckBlock(41, false);
                    CheckBlock(61, false);
            }
        }

        if (memoryBlock_ >= 31)
        {
            //�{�^���̃��f����؂�ւ���
            CheckBlock(memoryBlock_, false);

            //�ǂ̃��f����؂�ւ���
            CheckBlock(memoryBlock_ + 20, false);
        }
    }
}


//�ǂ��J���֐�
void Stage::OpenWall()
{
    CheckBlock(51, true);
}


//����̃u���b�N��T���āA���f����؂�ւ���֐�
//�������͐؂�ւ������u���b�N�̔ԍ�
//�������̓v���X���}�C�i�X��
void Stage::CheckBlock(int find , bool which)
{
    for (int x = 0; x < besideValu; x++)
    {
        for (int y = 0; y < verticalValu; y++)
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

//�_�Ńu���b�N
//�������͓_�ł��������u���b�N�̔ԍ�
//�������͕b���B�P�ʂ̓t���[��
//�ς��������f���ԍ�+10�ɂ͓����̃u���b�N�ݒ肵�Ă���
void Stage::Blinking(int blockNum, int time)
{
    //�v��
    timeCount_++;

    //�����ɂ���
    if (timeCount_ >= time && isBlinking_ == true)
    {
        //���f����؂�ւ���֐�
        CheckBlock(blockNum , false);

        isBlinking_ = false;

        //�v�����Ԃ����Z�b�g
        timeCount_ = 0;
    }
    //�s�����ɂ���
    else if(timeCount_ >= time && isBlinking_ == false)
    {
        CheckBlock(blockNum - 10, true);

        isBlinking_ = true;

        //�v�����Ԃ����Z�b�g
        timeCount_ = 0;
    }
}

//����̃u���b�N�̈ʒu�Ƀ��[�v����֐�
//�����͍��v���C���[�̂���ʒu�ɂ���}�X
bool Stage::WarpBlockEnter(int x, int y)
{
    //�����̓��[�v�u���b�N
    if (map_[x][y] == 91)
    {
        return true;
    }
    //�����Ȃ�
    else
    {
        return false;
    }
}

//�S�[���̏���������֐�
//�����͍��v���C���[�̂���ʒu�ɂ���}�X
void Stage::GoalCol(int x, int y)
{
    //�����̓S�[��
    if (map_[x][y] == 3)
    {
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_CLEAR);
    }

}

//
void Stage::WarpBlockExit()
{
    for (int x = 0; x < besideValu; x++)
    {
        for (int y = 0; y < verticalValu; y++)
        {
            if (map_[x][y] == 101)
            {
                pPlayer_->transform_.position_.x = x;
                pPlayer_->transform_.position_.y = y;
            }
        }
    }
}



void Stage::ModelLoad()
{

    //�X�e�[�W���\������u���b�N
    hModel_[0] = Model::Load("Assets/Block.fbx");
    hModel_[1] = Model::Load("Assets/NaturalBlock.fbx");
    hModel_[2] = Model::Load("Assets/Goal.fbx");
    hModel_[3] = Model::Load("Assets/BackGround.fbx");
    hModel_[4] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[5] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[6] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[7] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[8] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[9] = Model::Load("Assets/GreenBlock.fbx");


    //�������甭������b�{�^��
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


    //��������J���������
    hModel_[20] = Model::Load("Assets/Wall.fbx");
    hModel_[21] = Model::Load("Assets/Wall.fbx");
    hModel_[22] = Model::Load("Assets/Wall.fbx");
    hModel_[23] = Model::Load("Assets/Wall.fbx");
    hModel_[24] = Model::Load("Assets/Wall.fbx");
    hModel_[25] = Model::Load("Assets/Wall.fbx");
    hModel_[26] = Model::Load("Assets/Wall.fbx");
    hModel_[27] = Model::Load("Assets/Wall.fbx");
    hModel_[28] = Model::Load("Assets/Wall.fbx");
    hModel_[29] = Model::Load("Assets/Wall.fbx");


    //�����Ă���Ԃ�����������{�^��(�����O)
    hModel_[30] = Model::Load("Assets/UpButton.fbx");
    hModel_[31] = Model::Load("Assets/UpButton.fbx");
    hModel_[32] = Model::Load("Assets/UpButton.fbx");
    hModel_[33] = Model::Load("Assets/UpButton.fbx");
    hModel_[34] = Model::Load("Assets/UpButton.fbx");
    hModel_[35] = Model::Load("Assets/UpButton.fbx");
    hModel_[36] = Model::Load("Assets/UpButton.fbx");
    hModel_[37] = Model::Load("Assets/UpButton.fbx");
    hModel_[38] = Model::Load("Assets/UpButton.fbx");
    hModel_[39] = Model::Load("Assets/UpButton.fbx");


    //�����Ă���Ԃ�����������{�^��(��������)
    hModel_[40] = Model::Load("Assets/UpButton2.fbx");
    hModel_[41] = Model::Load("Assets/UpButton2.fbx");
    hModel_[42] = Model::Load("Assets/UpButton2.fbx");
    hModel_[43] = Model::Load("Assets/UpButton2.fbx");
    hModel_[44] = Model::Load("Assets/UpButton2.fbx");
    hModel_[45] = Model::Load("Assets/UpButton2.fbx");
    hModel_[46] = Model::Load("Assets/UpButton2.fbx");
    hModel_[47] = Model::Load("Assets/UpButton2.fbx");
    hModel_[48] = Model::Load("Assets/UpButton2.fbx");
    hModel_[49] = Model::Load("Assets/UpButton2.fbx");


    //�J����
    hModel_[50] = Model::Load("Assets/Wall.fbx");
    hModel_[51] = Model::Load("Assets/Wall.fbx");
    hModel_[52] = Model::Load("Assets/Wall.fbx");
    hModel_[53] = Model::Load("Assets/Wall.fbx");
    hModel_[54] = Model::Load("Assets/Wall.fbx");
    hModel_[55] = Model::Load("Assets/Wall.fbx");
    hModel_[56] = Model::Load("Assets/Wall.fbx");
    hModel_[57] = Model::Load("Assets/Wall.fbx");
    hModel_[58] = Model::Load("Assets/Wall.fbx");
    hModel_[59] = Model::Load("Assets/Wall.fbx");


    //�J���Ă���Ԃ̉����Ȃ��u���b�N
    hModel_[60] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[61] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[62] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[63] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[64] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[65] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[66] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[67] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[68] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[69] = Model::Load("Assets/AlphaBlock.fbx");


    //�_�ł���u���b�N(������O)
    hModel_[70] = Model::Load("Assets/Wall.fbx");
    hModel_[71] = Model::Load("Assets/Wall.fbx");
    hModel_[72] = Model::Load("Assets/Wall.fbx");
    hModel_[73] = Model::Load("Assets/Wall.fbx");
    hModel_[74] = Model::Load("Assets/Wall.fbx");
    hModel_[75] = Model::Load("Assets/Wall.fbx");
    hModel_[76] = Model::Load("Assets/Wall.fbx");
    hModel_[77] = Model::Load("Assets/Wall.fbx");
    hModel_[78] = Model::Load("Assets/Wall.fbx");
    hModel_[79] = Model::Load("Assets/Wall.fbx");


    //�_�ł���u���b�N(��������)
    hModel_[80] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[81] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[82] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[83] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[84] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[85] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[86] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[87] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[88] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[89] = Model::Load("Assets/AlphaBlock.fbx");


    //���[�v�u���b�N(����)
    hModel_[90] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[91] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[92] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[93] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[94] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[95] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[96] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[97] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[98] = Model::Load("Assets/WarpEntrance.fbx");
    hModel_[99] = Model::Load("Assets/WarpEntrance.fbx");


    //���[�v�u���b�N(�o��)
    hModel_[100] = Model::Load("Assets/WarpExit.fbx");
    hModel_[101] = Model::Load("Assets/WarpExit.fbx");
    hModel_[102] = Model::Load("Assets/WarpExit.fbx");
    hModel_[103] = Model::Load("Assets/WarpExit.fbx");
    hModel_[104] = Model::Load("Assets/WarpExit.fbx");
    hModel_[105] = Model::Load("Assets/WarpExit.fbx");
    hModel_[106] = Model::Load("Assets/WarpExit.fbx");
    hModel_[107] = Model::Load("Assets/WarpExit.fbx");
    hModel_[108] = Model::Load("Assets/WarpExit.fbx");
    hModel_[109] = Model::Load("Assets/WarpExit.fbx");


}

