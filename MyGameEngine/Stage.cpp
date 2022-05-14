#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/CsvReader.h"
#include "Engine/SceneManager.h"
#include "Stage.h"
#include "Player.h"
#include "Shadow.h"
#include "Engine/Audio.h"
#include "Engine/VisualEffect.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hSound_(-1),
    PLAYER_GENERAT_POS_(200),
    VERTICAL_VALU_(23),     //�}�b�v�c���̒l
    BESIDE_VALU_(28),       //�}�b�v�����̒l
    SHADOW_NAMBER_(5),
    ALL_GIMMICKS_(9),
    RESET_VALU_(0),
    CHENGE_POSITIVE_GIMMICKS_(10),
    BRINKING_BLOCKS_(81),
    FRAME_TIME_(60),
    DOBLE_BLOCKS_(151),
    BACK_GROUND_(3),
    TWO_BLOCKS_(161),
    MEANTIME_WALL_(51),
    MEANTIME_BUTTON_UP_(31),
    MEANTIME_BUTTON_DOWN_(41),
    MEANTIME_BLOCK_ALPHA_(61),
    WARP_BLOCK_ENTRANS_(91),
    WARP_BLOCK_EXIT_(101),
    GOAL_BLOCK_(3),
    downNum_(0),


    shadowCount_(0),
    timeCount_(0),


    pPlayer_(nullptr),
    pSceneManager_(nullptr),


    isBlinking_(true),
    isWarp_(true),
    isdoubleButton1_(false),
    isdoubleButton2_(false),

    steppingNumber(0),
    isOnButton(false)
{

}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    int a = 0;

    //�T�E���h�f�[�^�̃��[�h
    hSound_ = Audio::Load("Assets/get1.wav",1);
    assert(hSound_ >= 0);

    //�G�t�F�N�g�̉摜�����[�h
    //�����́u�t�@�C�����v�u���ɉ�����ł邩�v�u�c�ɉ�����ł邩�v
    //�߂�l�͉摜�ԍ�
    hVfxA = VisualEffect::Load("Assets/SampleEffectA.png", 7, 7);
    hVfxB = VisualEffect::Load("Assets/SampleEffectB.png", 6, 5);


    //1�G�t�F�N�g���o��
    Transform transform;
    transform.position_ = XMFLOAT3(6, 7, -1);       //�ʒu
    transform.scale_ = XMFLOAT3(3.0f, 3.0f, 1.0f);  //�T�C�Y�i�f�t�H���g����1�ӂ�2���j
    VisualEffect::Add(hVfxA, transform, 0.5f, true);//�o���i�����́u�摜�ԍ��v�u�g�����X�t�H�[���v�u�Đ����x�v�u���[�v�����邩�ǂ����v�j

    //�u���b�N�Ȃǂ̃��f�������[�h���鏈�����܂Ƃ߂��֐�
    ModelLoad();


    //SceneManager�N���X�̏����i�[����
    if (pSceneManager_ == nullptr)
    {
        pSceneManager_ = (SceneManager*)Find("SceneManager");
    }


    //Csv�t�@�C���̓ǂݍ���
    CsvReader csv;


    //�ǂݍ��܂ꂽ�X�e�[�WID�ɑΉ�����CSV�t�@�C����ǂݍ���
    switch(pSceneManager_->nextSceneID_)
    {
    case SCENE_ID_STAGE1: csv.Load("Assets/Stage/Stage1.csv");break;
    case SCENE_ID_STAGE2: csv.Load("Assets/Stage/Stage2.csv");break;
    case SCENE_ID_STAGE3: csv.Load("Assets/Stage/Stage3.csv");break;
    case SCENE_ID_STAGE4: csv.Load("Assets/Stage/Stage4.csv");break;
    }

    //�v���C���[�̐���
    //200�������Ă���}�X�Ƀv���C���[���o������
    //��
    for (int x = RESET_VALU_; x < BESIDE_VALU_; x++)
    {
        //�c
        for (int y = RESET_VALU_; y < VERTICAL_VALU_; y++)
        {
            //�G�N�Z������y�̒l���t�Ȃ̂ŏc��-1�����Ă�����
            map_[x][y] = csv.GetValue(x, (VERTICAL_VALU_-1) - y); 

            if (map_[x][y] == PLAYER_GENERAT_POS_)
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
    //�ŏ��͔�\���ŉe�𐶐�����
    pShadow_[shadowCount_] = (Shadow*)Instantiate<Shadow>(this->pParent_);
}



//�X�V
void Stage::Update()
{
    if (Input::IsKeyDown(DIK_SPACE))
    {
        //1�G�t�F�N�g���o��
        Transform transform;
        transform.position_ = XMFLOAT3(15, 15, -1);       //�ʒu
        transform.scale_ = XMFLOAT3(3.0f, 3.0f, 1.0f);  //�T�C�Y�i�f�t�H���g����1�ӂ�2���j
        VisualEffect::Add(hVfxB, transform, 0.5f, false);//�o���i�����́u�摜�ԍ��v�u�g�����X�t�H�[���v�u�Đ����x�v�u���[�v�����邩�ǂ����v�j
    }

    //Player���̊i�[
    if (pPlayer_ == nullptr)
    {
        pPlayer_ = (Player*)Find("Player");
    }


    //�Đ��X�^�[�g
    if (Input::IsKeyDown(DIK_1))
    {
        Audio::Play(hSound_);

        //�_�Ńu���b�N�̏������Z�b�g
        timeCount_ = RESET_VALU_;
        isBlinking_ = true;

        for (int i = RESET_VALU_; i <= shadowCount_; i++)
        {
            CheckBlock(41 + i, false);
            CheckBlock(61 + i, false);
        }

        //���łɐ������Ă���e��\�����A������x�Đ�����
        if (shadowCount_ <= SHADOW_NAMBER_)
        {
            //���łɐ������Ă���e��������x1����Đ�����
            for (int i = RESET_VALU_; i <= shadowCount_; i++)
            {
                //�\������t���O
                pShadow_[i]->ShadowIsPlayFlag();
            }

            if (shadowCount_ <= SHADOW_NAMBER_ -1)
            {
                //��̖ڈȍ~�̉e�̔ԍ�
                shadowCount_++;
            }
        }

        //�e�̐���
        if (shadowCount_ <= SHADOW_NAMBER_)
        {
            pShadow_[shadowCount_] = (Shadow*)Instantiate<Shadow>(this);
        }
    }

    //�ۑ����ꂽ�e�̓��������ׂă��Z�b�g����
    if (Input::IsKeyDown(DIK_2))
    {
        //������e��
        for (int i = RESET_VALU_; i <= shadowCount_; i++)
        {
            //�������
            pShadow_[i]->killMe();
        }
        //�e�̐������Z�b�g
        shadowCount_ = RESET_VALU_;
    }

    //��莞�Ԃ��ƂɃu���b�N�؂�ւ���
    Blinking(BRINKING_BLOCKS_, FRAME_TIME_);


    //�����{�^���̃M�~�b�N
    //�ǂ�����{�^���������Ă����甭������
    if (isdoubleButton1_ && isdoubleButton2_)
    {
        for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
        {
            //���f����؂�ւ���
            CheckBlock(151 + i, true);
        }
    }
    //�ǂ��炩���A���邢�͂ǂ���������Ă��Ȃ���΃{�^���͌��ɖ߂�
    else
    {
        for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
        {
            //���f����؂�ւ���
            CheckBlock(161 + i, false);
        }
    }
    ChengeButton();
}


//�`��
void Stage::Draw()
{
    //�u���b�N�̔z�u
    for (int x = RESET_VALU_; x < BESIDE_VALU_; x++)
    {
        for (int y = RESET_VALU_; y < VERTICAL_VALU_; y++)
        {
            //�v���C���[�̈ʒu�ƃu���b�N��u���Ȃ��ʒu
            //���̏ꍇ�͂���ȍ~�̏����͂��Ȃ�
            if (map_[x][y] == RESET_VALU_ || map_[x][y] == PLAYER_GENERAT_POS_)
            {
                continue;
            }

            //���f���ԍ��̊i�[
            int type = map_[x][y] - 1;

            //�ʒu
            //trans�̈ʒu�������߂�
            Transform trans;
            trans.position_.x = x;
            trans.position_.y = y;

            //Calclation�N���X�ňړ��A��]�A�g��s��̏���������
            trans.Calclation();


            //���f���̕\��
            Model::SetTransform(hModel_[type], trans);
            Model::Draw(hModel_[type]);
        }
    }

    //�w�i�̐���
    //�ǐ^�񒆂ɏo��
    Transform back;

    //�����̐^��
    back.position_.x = BESIDE_VALU_ / 2;

    //�c���̐^��
    back.position_.y = VERTICAL_VALU_ / 2 + 1;

    //��������
    back.position_.z = 0.5;

    //Calclation�N���X�ňړ��A��]�A�g��s��̏���������
    back.Calclation();

    //���f���̕\��
    Model::SetTransform(hModel_[BACK_GROUND_], back);
    Model::Draw(hModel_[BACK_GROUND_]);
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
        map_[x][y] == BACK_GROUND_ ||
        map_[x][y] == PLAYER_GENERAT_POS_ ||
        map_[x][y] == 91||
        map_[x][y] == 101||
        map_[x][y] == MEANTIME_BLOCK_ALPHA_ ||
        map_[x][y] == 62||
        map_[x][y] == 81||
        map_[x][y] == 161)
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
bool Stage::DownButton(int x, int y)
{
    //�����Ă���ԃ{�^��
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        if (map_[x][y] == MEANTIME_BUTTON_UP_ + i || map_[x][y] == MEANTIME_BUTTON_DOWN_ + i)
        {
            return true;
        }
    }


    
    //���������{�^��
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        if (map_[x][y] == 111 + i)
        {
            //�{�^���̃��f����؂�ւ���
            CheckBlock(map_[x][y], true);

            //�t���O��true�ɂ���
            isdoubleButton1_ = true;
        }
        else if(map_[x][y] == 131 + i)
        {
            //�{�^���̃��f����؂�ւ���
            CheckBlock(map_[x][y], true);

            //�t���O��true�ɂ���
            isdoubleButton2_ = true;
        }
    }
    
    //Player�����ꂽ��
    //�������̓��Z�b�g������
    if (steppingNumber == 0)
    {
        for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
        {
            //�{�^���̃��f����؂�ւ���
            CheckBlock(MEANTIME_BUTTON_DOWN_ + i, false);

            //�ǂ̃��f����؂�ւ���
            CheckBlock(MEANTIME_BLOCK_ALPHA_ + i, false);

            //��������̃{�^����؂�ւ���
            CheckBlock(121 + i, false);

            //�J�����ǂ����ɖ߂�
            CheckBlock(141 + i, false);
        }

        //�����{�^���̃t���O������������
        isdoubleButton1_ = false;
        isdoubleButton2_ = false;

    }
    return false;
}


//���ׂẴu���b�N��T���āA���f����؂�ւ���֐�
//�������͐؂�ւ������u���b�N�̔ԍ�
//�������̓v���X���}�C�i�X��
void Stage::CheckBlock(int find , bool which)
{
    //��
    for (int x = RESET_VALU_; x < BESIDE_VALU_; x++)
    {
        //�c
        for (int y = RESET_VALU_; y < VERTICAL_VALU_; y++)
        {

            //�����������Ŏ󂯎�����u���b�N��������
            //��������false�Ń��f���ԍ�-10�̃��f���ɐ؂�ւ���
            if (map_[x][y] == find && which == false)
            {
                map_[x][y] = find - CHENGE_POSITIVE_GIMMICKS_;
            }

            //�����������Ŏ󂯎�����u���b�N��������
            //��������true�Ń��f���ԍ�+10�̃��f���ɐ؂�ւ���
            else if(map_[x][y] == find && which == true)
            {
                map_[x][y] = find + CHENGE_POSITIVE_GIMMICKS_;
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

        //�t���O��false�ɂ���
        isBlinking_ = false;

        //�v�����Ԃ����Z�b�g
        timeCount_ = RESET_VALU_;
    }
    //�s�����ɂ���
    else if(timeCount_ >= time && isBlinking_ == false)
    {
        //���f����؂�ւ���֐�
        //�����ɓn���ꂽ�l��-10�̃��f���ԍ���ς���
        CheckBlock(blockNum - CHENGE_POSITIVE_GIMMICKS_, true);

        //�t���O��true�ɂ���
        isBlinking_ = true;

        //�v�����Ԃ����Z�b�g
        timeCount_ = RESET_VALU_;
    }
}

//�S�[���̏���������֐�
//�����͍��v���C���[�̂���ʒu�ɂ���}�X
void Stage::GoalCol(int x, int y)
{
    //�����̓S�[��
    if (map_[x][y] == GOAL_BLOCK_)
    {
        //�V�[���ړ�
        //Find�֐���SceneManager�N���X��T����
        //ChangeScene�֐��̈����Ɉړ��������V�[����ID��n��
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_CLEAR);
    }
}

int Stage::NawBox(int x, int y)
{


    return 0;
}

void Stage::WarpBlockCollision(int getX,int getY)
{
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //Player��Position�������Ŏ󂯎��
        //���������[�v�u���b�N��������
        if (map_[getX][getY] == WARP_BLOCK_ENTRANS_ + i && isWarp_ == true)
        {
            //Stage�̃T�C�Y�����ׂ�
            //��
            for (int x = RESET_VALU_; x < BESIDE_VALU_; x++)
            {
                //�c
                for (int y = RESET_VALU_; y < VERTICAL_VALU_; y++)
                {
                    //���������[�v�u���b�N�̏o����������
                    if (map_[x][y] == WARP_BLOCK_EXIT_ + i)
                    {
                        //Player�̈ʒu�������̃��[�v�u���b�N�ɔ��f������
                        pPlayer_->transform_.position_.x = x;
                        pPlayer_->transform_.position_.y = y;

                        //�i�v���[�v�h�~�̂��߂Ƀt���O���������Ă���
                        isWarp_ = false;
                    }
                }
            }
        }
    }


    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {

        //Player��Position�������Ŏ󂯎��
        //���������[�v�u���b�N��������
        if (map_[getX][getY] == WARP_BLOCK_EXIT_ + i && isWarp_ == true)
        {

            //Stage�̃T�C�Y�����ׂ�
            //��
            for (int x = RESET_VALU_; x < BESIDE_VALU_; x++)
            {
                //�c
                for (int y = RESET_VALU_; y < VERTICAL_VALU_; y++)
                {
                    //���������[�v�u���b�N�̏o����������
                    if (map_[x][y] == WARP_BLOCK_ENTRANS_ + i)
                    {
                        //Player�̈ʒu�������̃��[�v�u���b�N�ɔ��f������
                        pPlayer_->transform_.position_.x = x;
                        pPlayer_->transform_.position_.y = y;

                        //�i�v���[�v�h�~�̂��߂Ƀt���O���������Ă���
                        isWarp_ = false;
                    }
                }
            }
        }
    }


    //�t���O�����̏�����
    //������Player�̈ʒu
    //���[�v�u���b�N���痣�ꂽ��t���O�����������Ă�����x�����悤�ɂ���
    if (map_[getX][getY] == RESET_VALU_)
    {
        isWarp_ = true;
    }
}

XMFLOAT3 Stage::GetStartPosition()
{
    steppingNumber = 0;
    return stertPos;
}

void Stage::Reset(int x, int y)
{
    if (map_[x][y] <= 2)
    {
        isOnButton = false;
    }
}

void Stage::ChengeButton()
{
    if (steppingNumber != downNum_)
    {
        //���f���ύX
        CheckBlock(MEANTIME_BUTTON_UP_, true);

        //�ǂ��J������
        CheckBlock(MEANTIME_WALL_, true);
    }
}

void Stage::StepNumberCountUp()
{
    steppingNumber++;
}

void Stage::StepNumberCountDown()
{
    steppingNumber--;
}

void Stage::SetDownNum(bool which)
{
    if (which)
    {
        downNum_++;
    }
    else
    {
        downNum_--;
    }
}



void Stage::ModelLoad()
{

    //�X�e�[�W���\������u���b�N
    hModel_[0] = Model::Load("Assets/StageBlock/Block.fbx");
    hModel_[1] = Model::Load("Assets/StageBlock/NaturalBlock.fbx");
    hModel_[2] = Model::Load("Assets/StageBlock/Goal.fbx");
    hModel_[3] = Model::Load("Assets/StageBlock/BackGround.fbx");
    hModel_[4] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[5] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[6] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[7] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[8] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[9] = Model::Load("Assets/GreenBlock.fbx");


    //�������甭������{�^��
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



    //���������{�^��(�����O)
    hModel_[110] = Model::Load("Assets/&Button.fbx");
    hModel_[111] = Model::Load("Assets/&Button.fbx");
    hModel_[112] = Model::Load("Assets/&Button.fbx");
    hModel_[113] = Model::Load("Assets/&Button.fbx");
    hModel_[114] = Model::Load("Assets/&Button.fbx");
    hModel_[115] = Model::Load("Assets/&Button.fbx");
    hModel_[116] = Model::Load("Assets/&Button.fbx");
    hModel_[117] = Model::Load("Assets/&Button.fbx");
    hModel_[118] = Model::Load("Assets/&Button.fbx");
    hModel_[119] = Model::Load("Assets/&Button.fbx");



    //�J����(�J���O)
    hModel_[120] = Model::Load("Assets/OrButton.fbx");
    hModel_[121] = Model::Load("Assets/OrButton.fbx");
    hModel_[122] = Model::Load("Assets/OrButton.fbx");
    hModel_[123] = Model::Load("Assets/OrButton.fbx");
    hModel_[124] = Model::Load("Assets/OrButton.fbx");
    hModel_[125] = Model::Load("Assets/OrButton.fbx");
    hModel_[126] = Model::Load("Assets/OrButton.fbx");
    hModel_[127] = Model::Load("Assets/OrButton.fbx");
    hModel_[128] = Model::Load("Assets/OrButton.fbx");
    hModel_[129] = Model::Load("Assets/OrButton.fbx");




    //���������{�^��(�����O)
    hModel_[130] = Model::Load("Assets/&Button.fbx");
    hModel_[131] = Model::Load("Assets/&Button.fbx");
    hModel_[132] = Model::Load("Assets/&Button.fbx");
    hModel_[133] = Model::Load("Assets/&Button.fbx");
    hModel_[134] = Model::Load("Assets/&Button.fbx");
    hModel_[135] = Model::Load("Assets/&Button.fbx");
    hModel_[136] = Model::Load("Assets/&Button.fbx");
    hModel_[137] = Model::Load("Assets/&Button.fbx");
    hModel_[138] = Model::Load("Assets/&Button.fbx");
    hModel_[139] = Model::Load("Assets/&Button.fbx");



    //�J����(�J������)
    hModel_[140] = Model::Load("Assets/OrButton.fbx");
    hModel_[141] = Model::Load("Assets/OrButton.fbx");
    hModel_[142] = Model::Load("Assets/OrButton.fbx");
    hModel_[143] = Model::Load("Assets/OrButton.fbx");
    hModel_[144] = Model::Load("Assets/OrButton.fbx");
    hModel_[145] = Model::Load("Assets/OrButton.fbx");
    hModel_[146] = Model::Load("Assets/OrButton.fbx");
    hModel_[147] = Model::Load("Assets/OrButton.fbx");
    hModel_[148] = Model::Load("Assets/OrButton.fbx");
    hModel_[149] = Model::Load("Assets/OrButton.fbx");


    //�����{�^���������ꂽ��J����
    hModel_[150] = Model::Load("Assets/Wall.fbx");
    hModel_[151] = Model::Load("Assets/Wall.fbx");
    hModel_[152] = Model::Load("Assets/Wall.fbx");
    hModel_[153] = Model::Load("Assets/Wall.fbx");
    hModel_[154] = Model::Load("Assets/Wall.fbx");
    hModel_[155] = Model::Load("Assets/Wall.fbx");
    hModel_[156] = Model::Load("Assets/Wall.fbx");
    hModel_[157] = Model::Load("Assets/Wall.fbx");
    hModel_[158] = Model::Load("Assets/Wall.fbx");
    hModel_[159] = Model::Load("Assets/Wall.fbx");


    //�����{�^�������ꂽ������
    hModel_[160] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[161] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[162] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[163] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[164] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[165] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[166] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[167] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[168] = Model::Load("Assets/AlphaBlock.fbx");
    hModel_[169] = Model::Load("Assets/AlphaBlock.fbx");
}

