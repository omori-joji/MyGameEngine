#include "Player.h"
#include "Stage.h"
#include "Shadow.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),
    hModel_(),                              //���ׂẴX�e�[�W���f�����i�[����ϐ�
    map_(),                                 //�X�e�[�W���Ǘ����鑽�����z��
    hSound_(),                              //SE��BGM���i�[����ϐ�
    PLAYER_GENERAT_POS_(200),               //Player�̏����ʒu
    SHADOW_NAMBER_(5),                      //�e�̍ő吔
    ALL_GIMMICKS_(10),                      //1��ނ̃M�~�b�N�������邩���ׂ�l
    RESET_VALU_(0),                         //�������p�̒l
    CHENGE_POSITIVE_GIMMICKS_(10),          //���f����ύX���邽�߂̒l
    BRINKING_BLOCKS_(81),                   //�_�ł���u���b�N
    FRAME_TIME_(60),                        //�_�ł���Ԋu
    BACK_GROUND_(3),                        //�w�i�̃��f���ԍ�
    MEANTIME_BUTTON_UP_(31),                //����ł���Ԕ�������{�^���̓��ޑO�̃��f���ԍ�
    MEANTIME_BUTTON_DOWN_(41),              //����ł���Ԕ�������{�^���̓��񂾂��Ƃ̃��f���ԍ�
    MEANTIME_WALL_(51),                     //�{�^�������܂�Ă��Ȃ��ԕ��Ă���ǂ̃��f���ԍ�
    MEANTIME_BLOCK_ALPHA_(61),              //�{�^�������܂�Ă���ԊJ���Ă���ǂ̃��f���ԍ�
    NO1_WARP_BLOCK_(91),                    //�Е��̃��[�v�u���b�N�̃��f���ԍ�
    NO2_WARP_BLOCK_(101),                   //�����Е��̃��[�v�u���b�N�̃��f���ԍ�
    GOAL_BLOCK_(3),                         //�S�[���u���b�N�̃��f���ԍ�
    shadowCount_(0),                        //������e�̐�
    timeCount_(0),                          //�b�����i�[����ϐ�
    FILE_PAS_("Assets/StageBlock/"),        //���f���̃t�@�C���p�X
    pPlayer_(nullptr),                      //Player�N���X���i�[����|�C���^
    pShadow_(),                             //Shadow�N���X���i�[����|�C���^
    pSceneManager_(nullptr),                //SceneManager�N���X���i�[����|�C���^
    stertPos_(0,0,0),                       //Player�̏����ʒu���L������ϐ�
    isBlinking_(true),                      //�ǂ��������������Ă��Ȃ���
    isWarp_(true),                          //���[�v���������Ă��Ȃ���
    isDoubleButton_(),                      //���������{�^���̓�����������ʂ���t���O
    steppingNumberMeanTime_(),              //�{�^���ɏ���Ă���l�����L������ϐ�
    steppingNumber_No1Double_(),            //�{�^���ɏ���Ă���l�����L������ϐ�
    steppingNumber_No2Double_(),            //�{�^���ɏ���Ă���l�����L������ϐ�
    NO1_DOUBLE_BUTTON_UP_(111),             //���������{�^���̕Е��B����ł��Ȃ���Ԃ̃��f���ԍ�
    NO1_DOUBLE_BUTTON_DOWN_(121),           //���������{�^���̕Е��B����ł����Ԃ̃��f���ԍ�
    NO2_DOUBLE_BUTTON_UP_(131),             //���������{�^���̂����Е��B����ł��Ȃ���Ԃ̃��f���ԍ�
    NO2_DOUBLE_BUTTON_DOWN_(141),           //���������{�^���̕Е��B����ł����Ԃ̃��f���ԍ�
    DOUBLE_BUTTON_WALL_(151),               //���������{�^���ɑΉ������ǁB�J���ĂȂ���Ԃ̃��f���ԍ�
    DOUBLE_BUTTON_WALL_ALPHA_(161)          //���������{�^���ɑΉ������ǁB�J���Ă����Ԃ̃��f���ԍ�
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
    //SceneManager�N���X�̏����i�[����
    if (pSceneManager_ == nullptr) pSceneManager_ = (SceneManager*)Find("SceneManager");

    //�ǂݍ��܂ꂽ�X�e�[�WID�ɑΉ�����CSV�t�@�C����ǂݍ���
    switch (pSceneManager_->nextSceneID_)
    {
    case SCENE_ID_STAGE1: csv.Load("Assets/Stage/Stage1.csv"); break;
    case SCENE_ID_STAGE2: csv.Load("Assets/Stage/Stage2.csv"); break;
    case SCENE_ID_STAGE3: csv.Load("Assets/Stage/Stage3.csv"); break;
    case SCENE_ID_STAGE4: csv.Load("Assets/Stage/Stage4.csv"); break;
    case SCENE_ID_DEBUG: csv.Load("Assets/Stage/Debug.csv"); break;
    }

    //�v���C���[�̐���
    //200�������Ă���}�X�Ƀv���C���[���o������
    //��
    for (int x = RESET_VALU_; x < MAP_BESIDE_; x++)
    {
        //�c
        for (int y = RESET_VALU_; y < MAP_VERTICAL; y++)
        {
            //�G�N�Z������y�̒l���t�Ȃ̂ŏc��-1�����Ă�����
            map_[x][y] = csv.GetValue(x, (MAP_VERTICAL - 1) - y);

            if (map_[x][y] == PLAYER_GENERAT_POS_)
            {
                //�v���C���[�̐���
                //�v���C���[�̈ʒu����
                //�v���C���[�̏����ʒu���L������
                Player* pPlayer = (Player*)Instantiate<Player>(this->pParent_);
                pPlayer->transform_.position_.x = (float)x;
                pPlayer->transform_.position_.y = (float)y;
                stertPos_ = pPlayer->transform_.position_;
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
    //Player���̊i�[
    if (pPlayer_ == nullptr)
    {
        pPlayer_ = (Player*)Find("Player");
    }

    //�e���Đ����鏈�����܂Ƃ߂��֐�
    PlayRecord();

    //��莞�Ԃ��ƂɃu���b�N�؂�ւ���
    Blinking(BRINKING_BLOCKS_, FRAME_TIME_);
}

//�`��
void Stage::Draw()
{
    //�w�i�̐���
    //�ǐ^�񒆂ɏo��
    Transform back;

    //�����̐^��
    back.position_.x = MAP_BESIDE_ / 2;

    //�c���̐^��
    back.position_.y = MAP_VERTICAL / 2 + 1;

    //��������
    back.position_.z = 0.5;

    //Calclation�N���X�ňړ��A��]�A�g��s��̏���������
    back.Calclation();

    //���f���̕\��
    Model::SetTransform(hModel_[BACK_GROUND_], back);
    Model::Draw(hModel_[BACK_GROUND_]);

    //�u���b�N�̔z�u
    for (int x = RESET_VALU_; x < MAP_BESIDE_; x++)
    {
        for (int y = RESET_VALU_; y < MAP_VERTICAL; y++)
        {
            //�v���C���[�̈ʒu�ƃu���b�N��u���Ȃ��ʒu
            //���̏ꍇ�͂���ȍ~�̏����͂��Ȃ�
            if (map_[x][y] == RESET_VALU_ || map_[x][y] == PLAYER_GENERAT_POS_) continue;

            //���f���ԍ��̊i�[
            int type = map_[x][y] - 1;

            //�ʒu
            //trans�̈ʒu�������߂�
            Transform trans;
            trans.position_.x = (float)x;
            trans.position_.y = (float)y;

            //Calclation�N���X�ňړ��A��]�A�g��s��̏���������
            trans.Calclation();

            //���f���̕\��
            Model::SetTransform(hModel_[type], trans);
            Model::Draw(hModel_[type]);
        }
    }
}

//����ł���Ԕ�������{�^�������邩�ǂ����̏��������s����
//������Player�������͉e�̑����̒l
//�߂�l�͖ړI�̃M�~�b�N�������true����ȊO��false���Ԃ����
bool Stage::MeanTimeButton(int x, int y)
{
    //�����Ă���ԃ{�^��
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //���ɂ���{�^��������ł���Ԃ����̃{�^���������͓��񂾌�̃{�^����������
        if (map_[x][y] == MEANTIME_BUTTON_UP_ + i || map_[x][y] == MEANTIME_BUTTON_DOWN_ + i) return true;
    }

    //���ꂽ���̏���
    CollisionExit();
    return false;
}

//���������{�^���̕Е������邩�ǂ����̏��������s����
//������Player�������͉e�̑����̒l
//�߂�l�͖ړI�̃M�~�b�N�������true����ȊO��false���Ԃ����
bool Stage::No1DoubleButton(int x, int y)
{
    //���������{�^��
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //���ɂ���{�^�������������{�^���̉����O�A�������͉�������̃��f����������
        if (map_[x][y] == NO1_DOUBLE_BUTTON_UP_ + i || map_[x][y] == NO1_DOUBLE_BUTTON_DOWN_ + i) return true;
    }
    //���ꂽ���̏���
    CollisionExit();
    return false;
}

//���������{�^���̂����Е������邩�ǂ����̏��������s����
//������Player�������͉e�̑����̒l
//�߂�l�͖ړI�̃M�~�b�N�������true����ȊO��false���Ԃ����
bool Stage::No2DoubleButton(int x, int y)
{
    //���������{�^��
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //���ɂ���{�^�������������{�^���̉����O�A�������͉�������̃��f����������
        if (map_[x][y] == NO2_DOUBLE_BUTTON_UP_ + i || map_[x][y] == NO2_DOUBLE_BUTTON_DOWN_ + i) return true;
    }
    //���ꂽ���̏���
    CollisionExit();
    return false;
}

//�M�~�b�N���痣�ꂽ���̏��������s����֐�
void Stage::CollisionExit()
{
    //�����Ă���Ԃ����̃{�^��
    //���ׂẴM�~�b�N�𒲂ׂ�
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //�����Ă���Ԃ�����������{�^���ɏ���Ă���l����0�l��������
        if (steppingNumberMeanTime_[i] == 0)
        {
            //�{�^���̃��f����؂�ւ���
            CheckBlock(MEANTIME_BUTTON_DOWN_ + i, false);

            //�ǂ̃��f����؂�ւ���
            CheckBlock(MEANTIME_BLOCK_ALPHA_ + i, false);
        }
    }

    //���������{�^���̕Е��̃{�^��
    //���ׂẴM�~�b�N�𒲂ׂ�
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //���������{�^���̕Е��̃{�^���ɏ���Ă���l����0�l��������
        if (steppingNumber_No1Double_[i] == 0)
        {
            //�{�^���̃��f����؂�ւ���
            CheckBlock(NO1_DOUBLE_BUTTON_DOWN_ + i, false);

            //�ǂ��J���t���O��true�ɂ���
            isDoubleButton_[0] = false;
        }
    }

    //���������{�^���̂����Е��̃{�^��
    //���ׂẴM�~�b�N�𒲂ׂ�
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //���������{�^���̂����Е��̃{�^���ɏ���Ă���l����0�l��������
        if (steppingNumber_No2Double_[i] == 0)
        {
            //�{�^���̃��f����؂�ւ���
            CheckBlock(NO2_DOUBLE_BUTTON_DOWN_ + i, false);

            //�ǂ��J���t���O��true�ɂ���
            isDoubleButton_[1] = false;
        }
    }
}

//�{�^���̃��f���ƕǂ̃��f����ύX����֐�
//�����͉e��Player��1�u���b�N���̈ʒu
void Stage::ChengeButtonAndWall()
{
    //�����Ă���Ԕ�������{�^��
    //���ׂĂ̕ǂ�T��
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //�N���������Ă���Ԕ�������{�^���ɏ���Ă�����
        if (steppingNumberMeanTime_[i] != 0)
        {
            //���f���ύX
            //�{�^�����ɕς���Ƃ���ɑΉ������ǂ��Ђ炯�Ȃ��̂ŕǂ��ɕς���
            CheckBlock((MEANTIME_BUTTON_UP_ + i) + 20, true);

            //�{�^���̃��f��
            CheckBlock(MEANTIME_BUTTON_UP_ + i, true);
        }
    }

    //�Е��̓��������{�^��
    //���ׂĂ̕ǂ𒲂ׂ�
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //�N���������{�^���ɏ���Ă�����
        if (steppingNumber_No1Double_[i] != 0)
        {
            //���f���ύX
            CheckBlock(NO1_DOUBLE_BUTTON_UP_ + i, true);

            //�ǂ��J���t���O��true�ɂ���
            isDoubleButton_[0] = true;

            //�����{�^����2�Ƃ�������Ă�����ǂ��J������������֐�
            SimultaneousWallOpen();
        }
    }

    //��L�Ɠ��������Ȃ̂ŃR�����g�͏ȗ�
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        if (steppingNumber_No2Double_[i] != 0)
        {
            CheckBlock(NO2_DOUBLE_BUTTON_UP_ + i, true);
            isDoubleButton_[1] = true;
            SimultaneousWallOpen();
        }
    }
}

//�����{�^���̃t���O���ǂ����true��������ǂ��J���֐�
void Stage::SimultaneousWallOpen()
{
    //�����{�^���̃M�~�b�N
    //�ǂ�����{�^���������Ă�����ǂ��J��
    if (isDoubleButton_[0] && isDoubleButton_[1]) CheckBlock(DOUBLE_BUTTON_WALL_, true);

    //����ȊO�̏����̏ꍇ
    //�ǂ����
    else CheckBlock(DOUBLE_BUTTON_WALL_ALPHA_, false);
}

//Player���e�����񂾃M�~�b�N�̃��f���ԍ���1�̈ʂ�Ԃ��֐�
//�{�^���ɏ���Ă���l���𒲂ׂ邽�߂Ɏg��
//������Player���e�̑���
int Stage::CheckFootBlock(int x, int y)
{
    //1�̈ʂ�Ԃ�
    return (map_[x][y] % 10) -1;
}

//�e���o�����������ɍs������
void Stage::PlayRecord()
{
    //�Đ��X�^�[�g
    if (Input::IsKeyDown(DIK_1))
    {
        //�_�Ńu���b�N�̏������Z�b�g
        timeCount_ = RESET_VALU_;
        isBlinking_ = true;

        //���łɐ������Ă���e��\�����A������x�Đ�����
        if (shadowCount_ <= SHADOW_NAMBER_)
        {
            //���łɐ������Ă���e��������x1����Đ�����
            for (int i = RESET_VALU_; i <= shadowCount_; i++)
            {
                //�\������t���O
                pShadow_[i]->ShadowIsPlayFlag();
            }

            //�e�̐����܂��]���Ă�����
            //��̖ڈȍ~�̉e�̔ԍ�
            if (shadowCount_ <= SHADOW_NAMBER_ -1) shadowCount_++;
        }
        //�e�̐���
        if (shadowCount_ <= SHADOW_NAMBER_) { pShadow_[shadowCount_] = (Shadow*)Instantiate<Shadow>(this); }
    }
}

//�����Ă���Ԕ�������{�^���ɏ���Ă���l�����J�E���g�A�b�v����֐�
//�����͑Ή�����M�~�b�N�̔ԍ�
void Stage::SetMeanTimeStepNumberCountUp(int meanTimeNum)
{
    steppingNumberMeanTime_[meanTimeNum]++;
}

//�����Ă���Ԕ�������{�^���ɏ���Ă���l�����J�E���g�_�E������֐�
//�����͑Ή�����M�~�b�N�̔ԍ�
void Stage::SetMeanTimeStepNumberCountDown(int meanTimeNum)
{
    steppingNumberMeanTime_[meanTimeNum]--;
}

//�����{�^���̕Е��ɏ���Ă���l�����J�E���g�A�b�v����֐�
//�����͑Ή�����M�~�b�N�̔ԍ�
void Stage::SetNo1DoubleStepNumberCountUp(int onDoubleNum)
{
    steppingNumber_No1Double_[onDoubleNum]++;
}

//�����{�^���̕Е��ɏ���Ă���l�����J�E���g�_�E������֐�
//�����͑Ή�����M�~�b�N�̔ԍ�
void Stage::SetNo1DoubleStepNumberCountDown(int onDoubleNum)
{
    steppingNumber_No1Double_[onDoubleNum]--;
}

//�����{�^���̂������ɏ���Ă���l�����J�E���g�A�b�v����֐�
//�����͑Ή�����M�~�b�N�̔ԍ�
void Stage::SetNo2DoubleStepNumberCountUp(int orDunbleNum)
{
    steppingNumber_No2Double_[orDunbleNum]++;
}

//�����{�^���̂������ɏ���Ă���l�����J�E���g�A�b�v����֐�
//�����͑Ή�����M�~�b�N�̔ԍ�
void Stage::SetNo2DoubleStepNumberCountDown(int orDunbleNum)
{
    steppingNumber_No2Double_[orDunbleNum]--;
}

//���[�v�u���b�N�ɓ��������̏��������s����
//������Player�������͉e��
void Stage::WarpBlockCollision(int getX, int getY)
{
    //���ׂẴ��[�v�u���b�N�𒲂ׂ�
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //���������[�v�u���b�N��������
        if (map_[getX][getY] == NO1_WARP_BLOCK_ + i && isWarp_ == true)
        {
            //Stage�̃T�C�Y�����ׂ�
            //��
            for (int x = RESET_VALU_; x < MAP_BESIDE_; x++)
            {
                //�c
                for (int y = RESET_VALU_; y < MAP_VERTICAL; y++)
                {
                    //���������[�v�u���b�N�̏o����������
                    if (map_[x][y] == NO2_WARP_BLOCK_ + i)
                    {
                        //Player�̈ʒu�������̃��[�v�u���b�N�ɔ��f������
                        pPlayer_->transform_.position_.x = (float)x;
                        pPlayer_->transform_.position_.y = (float)y;

                        //�i�v���[�v�h�~�̂��߂Ƀt���O���������Ă���
                        isWarp_ = false;
                    }
                }
            }
        }
    }

    //���ׂẴ��[�v�u���b�N�𒲂ׂ�
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //���������[�v�u���b�N��������
        if (map_[getX][getY] == NO2_WARP_BLOCK_ + i && isWarp_ == true)
        {
            //Stage�̃T�C�Y�����ׂ�
            //��
            for (int x = RESET_VALU_; x < MAP_BESIDE_; x++)
            {
                //�c
                for (int y = RESET_VALU_; y < MAP_VERTICAL; y++)
                {
                    //���������[�v�u���b�N�̏o����������
                    if (map_[x][y] == NO1_WARP_BLOCK_ + i)
                    {
                        //Player�̈ʒu�������̃��[�v�u���b�N�ɔ��f������
                        pPlayer_->transform_.position_.x = (float)x;
                        pPlayer_->transform_.position_.y = (float)y;

                        //�i�v���[�v�h�~�̂��߂Ƀt���O���������Ă���
                        isWarp_ = false;
                    }
                }
            }
        }
    }
    //�t���O�����̏�����
    //Player�����[�v�u���b�N���痣�ꂽ��
    //���[�v�u���b�N���痣�ꂽ��t���O�����������Ă�����x�����悤�ɂ���
    if (map_[getX][getY] == RESET_VALU_) isWarp_ = true;
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
        CheckBlock(blockNum, false);

        //�t���O��false�ɂ���
        isBlinking_ = false;

        //�v�����Ԃ����Z�b�g
        timeCount_ = RESET_VALU_;
    }
    //�s�����ɂ���
    else if (timeCount_ >= time && isBlinking_ == false)
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

//���ׂẴu���b�N��T���āA���f����؂�ւ���֐�
//�������͐؂�ւ������u���b�N�̔ԍ�
//�������̓v���X���}�C�i�X��
void Stage::CheckBlock(int find, bool which)
{
    //Stage�̃T�C�Y�����ׂ�
    //��
    for (int x = RESET_VALU_; x < MAP_BESIDE_; x++)
    {
        //�c
        for (int y = RESET_VALU_; y < MAP_VERTICAL; y++)
        {
            //�����������Ŏ󂯎�����u���b�N��������
            //��������false�Ń��f���ԍ�-10�̃��f���ɐ؂�ւ���
            if (map_[x][y] == find && which == false) map_[x][y] = find - CHENGE_POSITIVE_GIMMICKS_;

            //�����������Ŏ󂯎�����u���b�N��������
            //��������true�Ń��f���ԍ�+10�̃��f���ɐ؂�ւ���
            else if (map_[x][y] == find && which == true) map_[x][y] = find + CHENGE_POSITIVE_GIMMICKS_;
        }
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

//���̃}�X�ɏ�Q�������邩�ǂ���
//�߂�l�A��������true,�����Ȃ�false
//������Player���e�̈ʒu
bool Stage::isCrash(int x, int y)
{
    //�����蔻��̂Ȃ��u���b�N��ݒ肷��
    if (map_[x][y] == 0 ||
        map_[x][y] == BACK_GROUND_ ||
        map_[x][y] == PLAYER_GENERAT_POS_ ||
        map_[x][y] == NO1_WARP_BLOCK_ ||
        map_[x][y] == NO2_WARP_BLOCK_ ||
        map_[x][y] == MEANTIME_BLOCK_ALPHA_ ||
        map_[x][y] == MEANTIME_BLOCK_ALPHA_ + 1 ||
        map_[x][y] == BRINKING_BLOCKS_ ||
        map_[x][y] == DOUBLE_BUTTON_WALL_ALPHA_)
    {
        return false;
    }
    return true;
}

//�X�|�[���n�_��n���֐�
XMFLOAT3 Stage::GetStartPosition()
{
    return stertPos_;
}

//�J��
void Stage::Release()
{
}

//���f�������[�h���鏈�����܂Ƃ߂��֐�
//�X�e�[�W�ɒu���M�~�b�N��������ƃ��f�����ς��̂Ń��[�v�����͂��Ȃ�
void Stage::ModelLoad()
{
    //�T�E���h�f�[�^�̃��[�h
    hSound_[0] = Audio::Load("Assets/Sound/ButtonDown.wav",4);
    hSound_[1] = Audio::Load("Assets/Sound/Goal.wav",4);
    hSound_[2] = Audio::Load("Assets/Sound/OpenWall.wav",4);
    hSound_[3] = Audio::Load("Assets/Sound/Warpe.wav",4);

    //�X�e�[�W���\������u���b�N
    hModel_[0] = Model::Load(FILE_PAS_ + "Block.fbx");
    hModel_[1] = Model::Load(FILE_PAS_ + "NaturalBlock.fbx");
    hModel_[2] = Model::Load(FILE_PAS_ + "Goal.fbx");
    hModel_[3] = Model::Load(FILE_PAS_ + "GameBG.fbx");
    hModel_[4] = Model::Load(FILE_PAS_ + "GreenBlock.fbx");
    hModel_[5] = Model::Load(FILE_PAS_ + "GreenBlock.fbx");
    hModel_[6] = Model::Load(FILE_PAS_ + "GreenBlock.fbx");
    hModel_[7] = Model::Load(FILE_PAS_ + "GreenBlock.fbx");
    hModel_[8] = Model::Load(FILE_PAS_ + "GreenBlock.fbx");
    hModel_[9] = Model::Load(FILE_PAS_ + "GreenBlock.fbx");

    //�������甭������{�^��
    hModel_[10] = Model::Load(FILE_PAS_ + "PushButton.fbx");
    hModel_[11] = Model::Load(FILE_PAS_ + "PushButton.fbx");
    hModel_[12] = Model::Load(FILE_PAS_ + "PushButton.fbx");
    hModel_[13] = Model::Load(FILE_PAS_ + "PushButton.fbx");
    hModel_[14] = Model::Load(FILE_PAS_ + "PushButton.fbx");
    hModel_[15] = Model::Load(FILE_PAS_ + "PushButton.fbx");
    hModel_[16] = Model::Load(FILE_PAS_ + "PushButton.fbx");
    hModel_[17] = Model::Load(FILE_PAS_ + "PushButton.fbx");
    hModel_[18] = Model::Load(FILE_PAS_ + "PushButton.fbx");
    hModel_[19] = Model::Load(FILE_PAS_ + "PushButton.fbx");

    //��������J���������
    hModel_[20] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[21] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[22] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[23] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[24] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[25] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[26] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[27] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[28] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[29] = Model::Load(FILE_PAS_ + "Wall.fbx");

    //�����Ă���Ԃ�����������{�^��(�����O)
    hModel_[30] = Model::Load(FILE_PAS_ + "UpButton.fbx");
    hModel_[31] = Model::Load(FILE_PAS_ + "UpButton.fbx");
    hModel_[32] = Model::Load(FILE_PAS_ + "UpButton.fbx");
    hModel_[33] = Model::Load(FILE_PAS_ + "UpButton.fbx");
    hModel_[34] = Model::Load(FILE_PAS_ + "UpButton.fbx");
    hModel_[35] = Model::Load(FILE_PAS_ + "UpButton.fbx");
    hModel_[36] = Model::Load(FILE_PAS_ + "UpButton.fbx");
    hModel_[37] = Model::Load(FILE_PAS_ + "UpButton.fbx");
    hModel_[38] = Model::Load(FILE_PAS_ + "UpButton.fbx");
    hModel_[39] = Model::Load(FILE_PAS_ + "UpButton.fbx");

    //�����Ă���Ԃ�����������{�^��(��������)
    hModel_[40] = Model::Load(FILE_PAS_ + "UpButton2.fbx");
    hModel_[41] = Model::Load(FILE_PAS_ + "UpButton2.fbx");
    hModel_[42] = Model::Load(FILE_PAS_ + "UpButton2.fbx");
    hModel_[43] = Model::Load(FILE_PAS_ + "UpButton2.fbx");
    hModel_[44] = Model::Load(FILE_PAS_ + "UpButton2.fbx");
    hModel_[45] = Model::Load(FILE_PAS_ + "UpButton2.fbx");
    hModel_[46] = Model::Load(FILE_PAS_ + "UpButton2.fbx");
    hModel_[47] = Model::Load(FILE_PAS_ + "UpButton2.fbx");
    hModel_[48] = Model::Load(FILE_PAS_ + "UpButton2.fbx");
    hModel_[49] = Model::Load(FILE_PAS_ + "UpButton2.fbx");

    //�J����
    hModel_[50] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[51] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[52] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[53] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[54] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[55] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[56] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[57] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[58] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[59] = Model::Load(FILE_PAS_ + "Wall.fbx");

    //�J���Ă���Ԃ̉����Ȃ��u���b�N
    hModel_[60] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[61] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[62] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[63] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[64] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[65] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[66] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[67] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[68] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[69] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");


    //�_�ł���u���b�N(������O)
    hModel_[70] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[71] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[72] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[73] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[74] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[75] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[76] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[77] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[78] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[79] = Model::Load(FILE_PAS_ + "Wall.fbx");


    //�_�ł���u���b�N(��������)
    hModel_[80] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[81] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[82] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[83] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[84] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[85] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[86] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[87] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[88] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[89] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");


    //���[�v�u���b�N(����)
    hModel_[90] = Model::Load(FILE_PAS_ + "WarpEntrance.fbx");
    hModel_[91] = Model::Load(FILE_PAS_ + "WarpEntrance.fbx");
    hModel_[92] = Model::Load(FILE_PAS_ + "WarpEntrance.fbx");
    hModel_[93] = Model::Load(FILE_PAS_ + "WarpEntrance.fbx");
    hModel_[94] = Model::Load(FILE_PAS_ + "WarpEntrance.fbx");
    hModel_[95] = Model::Load(FILE_PAS_ + "WarpEntrance.fbx");
    hModel_[96] = Model::Load(FILE_PAS_ + "WarpEntrance.fbx");
    hModel_[97] = Model::Load(FILE_PAS_ + "WarpEntrance.fbx");
    hModel_[98] = Model::Load(FILE_PAS_ + "WarpEntrance.fbx");
    hModel_[99] = Model::Load(FILE_PAS_ + "WarpEntrance.fbx");


    //���[�v�u���b�N(�o��)
    hModel_[100] = Model::Load(FILE_PAS_ + "WarpExit.fbx");
    hModel_[101] = Model::Load(FILE_PAS_ + "WarpExit.fbx");
    hModel_[102] = Model::Load(FILE_PAS_ + "WarpExit.fbx");
    hModel_[103] = Model::Load(FILE_PAS_ + "WarpExit.fbx");
    hModel_[104] = Model::Load(FILE_PAS_ + "WarpExit.fbx");
    hModel_[105] = Model::Load(FILE_PAS_ + "WarpExit.fbx");
    hModel_[106] = Model::Load(FILE_PAS_ + "WarpExit.fbx");
    hModel_[107] = Model::Load(FILE_PAS_ + "WarpExit.fbx");
    hModel_[108] = Model::Load(FILE_PAS_ + "WarpExit.fbx");
    hModel_[109] = Model::Load(FILE_PAS_ + "WarpExit.fbx");



    //���������{�^��(�����O)
    hModel_[110] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[111] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[112] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[113] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[114] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[115] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[116] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[117] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[118] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[119] = Model::Load(FILE_PAS_ + "&Button.fbx");



    //�J����(�J���O)
    hModel_[120] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[121] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[122] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[123] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[124] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[125] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[126] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[127] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[128] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[129] = Model::Load(FILE_PAS_ + "OrButton.fbx");




    //���������{�^��(�����O)
    hModel_[130] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[131] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[132] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[133] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[134] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[135] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[136] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[137] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[138] = Model::Load(FILE_PAS_ + "&Button.fbx");
    hModel_[139] = Model::Load(FILE_PAS_ + "&Button.fbx");



    //�J����(�J������)
    hModel_[140] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[141] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[142] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[143] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[144] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[145] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[146] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[147] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[148] = Model::Load(FILE_PAS_ + "OrButton.fbx");
    hModel_[149] = Model::Load(FILE_PAS_ + "OrButton.fbx");


    //�����{�^���������ꂽ��J����
    hModel_[150] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[151] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[152] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[153] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[154] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[155] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[156] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[157] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[158] = Model::Load(FILE_PAS_ + "Wall.fbx");
    hModel_[159] = Model::Load(FILE_PAS_ + "Wall.fbx");


    //�����{�^�������ꂽ������
    hModel_[160] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[161] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[162] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[163] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[164] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[165] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[166] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[167] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[168] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
    hModel_[169] = Model::Load(FILE_PAS_ + "AlphaBlock.fbx");
}

