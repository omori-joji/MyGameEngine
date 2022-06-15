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
    isMultiButton_(),                       //���������{�^���̓�����������ʂ���t���O
    steppingNumberMeanTime_(),              //�{�^���ɏ���Ă���l�����L������ϐ�
    steppingNumber_No1Multi_(),             //�{�^���ɏ���Ă���l�����L������ϐ�
    steppingNumber_No2Multi_(),             //�{�^���ɏ���Ă���l�����L������ϐ�
    NO1_MULTI_BUTTON_UP_(111),              //���������{�^���̕Е��B����ł��Ȃ���Ԃ̃��f���ԍ�
    NO1_MULTI_BUTTON_DOWN_(121),            //���������{�^���̕Е��B����ł����Ԃ̃��f���ԍ�
    NO2_MULTI_BUTTON_UP_(131),              //���������{�^���̂����Е��B����ł��Ȃ���Ԃ̃��f���ԍ�
    NO2_MULTI_BUTTON_DOWN_(141),            //���������{�^���̕Е��B����ł����Ԃ̃��f���ԍ�
    MULTI_BUTTON_WALL_(151),                //���������{�^���ɑΉ������ǁB�J���ĂȂ���Ԃ̃��f���ԍ�
    MULTI_BUTTON_WALL_ALPHA_(161)           //���������{�^���ɑΉ������ǁB�J���Ă����Ԃ̃��f���ԍ�
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

    //BGN��炷
    Audio::Play(hSound_[BGM]);
}

//�X�V
void Stage::Update()
{
    //Player���̊i�[
    if (pPlayer_ == nullptr) pPlayer_ = (Player*)Find("Player");

    PlayRecord();

    Blinking(BRINKING_BLOCKS_, FRAME_TIME_);
}

//�`��
void Stage::Draw()
{
    //�w�i�̐���
    //�ǐ^�񒆂ɏo��
    Transform back;
    back.position_.x = MAP_BESIDE_ / 2;         //�����̐^��
    back.position_.y = MAP_VERTICAL / 2 + 1;    //�c���̐^��
    back.position_.z = 0.5;                     //��������
    back.Calclation();                          //Calclation�N���X�ňړ��A��]�A�g��s��̏���������

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
//�����FPlayer�AShadow��Position.x_��Position.y_ -1(����)
//�߂�l�F����ł����true����ł��Ȃ����false
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

//���������{�^���̕Е��ɏ������true����ȊO��false��Ԃ��֐�
//�����FPlayer�AShadow��Position.x_��Position.y_ -1(����)
//�߂�l�F����ł����true����ł��Ȃ����false
bool Stage::No1MultiButton(int x, int y)
{
    //���������{�^��
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //���ɂ���{�^�������������{�^���̉����O�A�������͉�������̃��f����������
        if (map_[x][y] == NO1_MULTI_BUTTON_UP_ + i || map_[x][y] == NO1_MULTI_BUTTON_DOWN_ + i) return true;
    }
    //���ꂽ���̏���
    CollisionExit();
    return false;
}

//���������{�^���̂����Е��ɏ������true����ȊO��false��Ԃ��֐�
//�����FPlayer�AShadow��Position.x_��Position.y_ -1(����)
//�߂�l�F����ł����true����ł��Ȃ����false
bool Stage::No2MultiButton(int x, int y)
{
    //���������{�^��
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //���ɂ���{�^�������������{�^���̉����O�A�������͉�������̃��f����������
        if (map_[x][y] == NO2_MULTI_BUTTON_UP_ + i || map_[x][y] == NO2_MULTI_BUTTON_DOWN_ + i) return true;
    }
    //���ꂽ���̏���
    CollisionExit();
    return false;
}

//�{�^�����痣�ꂽ��Ă΂��֐��A���f����؂�ւ��鏈�����s��
//�����F�Ȃ�
//�߂�l�F�Ȃ�
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
        if (steppingNumber_No1Multi_[i] == 0)
        {
            //�{�^���̃��f����؂�ւ���
            CheckBlock(NO1_MULTI_BUTTON_DOWN_ + i, false);

            //�ǂ��J���t���O��true�ɂ���
            isMultiButton_[0] = false;
        }
    }

    //���������{�^���̂����Е��̃{�^��
    //���ׂẴM�~�b�N�𒲂ׂ�
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        //���������{�^���̂����Е��̃{�^���ɏ���Ă���l����0�l��������
        if (steppingNumber_No2Multi_[i] == 0)
        {
            //�{�^���̃��f����؂�ւ���
            CheckBlock(NO2_MULTI_BUTTON_DOWN_ + i, false);

            //�ǂ��J���t���O��true�ɂ���
            isMultiButton_[1] = false;
        }
    }
}

//�ǂ̃��f���ƃ{�^���̃��f����؂�ւ���֐��B
//�����F�Ȃ�
//�߂�l�F�Ȃ�
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
        if (steppingNumber_No1Multi_[i] != 0)
        {
            //���f���ύX
            CheckBlock(NO1_MULTI_BUTTON_UP_ + i, true);

            //�ǂ��J���t���O��true�ɂ���
            isMultiButton_[0] = true;

            //�����{�^����2�Ƃ�������Ă�����ǂ��J������������֐�
            SimultaneousWallOpen();
        }
    }

    //��L�Ɠ��������Ȃ̂ŃR�����g�͏ȗ�
    for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
    {
        if (steppingNumber_No2Multi_[i] != 0)
        {
            CheckBlock(NO2_MULTI_BUTTON_UP_ + i, true);
            isMultiButton_[1] = true;
            SimultaneousWallOpen();
        }
    }
}

//���������{�^�����ǂ����������Ă�����B�ǂ��J���A����ȊO�̏�����������ǂ����֐�
//�����F�Ȃ�
//�߂�l�F�Ȃ�
void Stage::SimultaneousWallOpen()
{
    //�����{�^���̃M�~�b�N
    //�ǂ�����{�^���������Ă�����ǂ��J��
    if (isMultiButton_[0] && isMultiButton_[1]) CheckBlock(MULTI_BUTTON_WALL_, true);

    //����ȊO�̏����̏ꍇ
    //�ǂ����
    else CheckBlock(MULTI_BUTTON_WALL_ALPHA_, false);
}

//�����̃u���b�N�̃��f���ԍ��������Ŏ󂯎��A�����1�̈ʂ�Ԃ��֐�
//�����FPlayer�AShadow��Position.x_��Position.y_ -1(����)
//�߂�l�F�{�^���̃��f���ԍ���1�̈�
int Stage::CheckFootBlock(int x, int y)
{
    //1�̈ʂ�Ԃ�
    return (map_[x][y] % 10) -1;
}

//�e�̍Đ�����t���O�Ɛ����̏������s���֐�
//�����F�Ȃ�
//�߂�l�F�Ȃ�
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

    //�ۑ����ꂽ�e�����ׂĉ������
    if (Input::IsKeyDown(DIK_3))
    {
        for (int i = 0; i < shadowCount_; i++)
        {
            pShadow_[i]->killMe();
        }

        //�ۑ����ꂽ�e�������Ƃ��Ƀ{�^�������ׂă��Z�b�g
        for (int i = RESET_VALU_; i < ALL_GIMMICKS_; i++)
        {
            steppingNumberMeanTime_[i] = RESET_VALU_;
            steppingNumber_No1Multi_[i] = RESET_VALU_;
            steppingNumber_No2Multi_[i] = RESET_VALU_;
        }

        //������e�̐������Z�b�g
        shadowCount_ = 0;
    }
}

//�{�^���ɏ���Ă���l�����J�E���g�A�b�v����֐�
//�����F����ł���Ԕ�������{�^���̃��f���ԍ���1�̈�
//�߂�l�F�Ȃ�
void Stage::SetMeanTimeStepNumberCountUp(int meanTimeNum)
{
    steppingNumberMeanTime_[meanTimeNum]++;
}

//�{�^���ɏ���Ă���l�����J�E���g�_�E������֐�
//�����F����ł���Ԕ�������{�^���̃��f���ԍ���1�̈�
//�߂�l�F�Ȃ�
void Stage::SetMeanTimeStepNumberCountDown(int meanTimeNum)
{
    steppingNumberMeanTime_[meanTimeNum]--;
}

//���������{�^���̕Е��̃{�^���̏���Ă���l�����J�E���g�A�b�v����֐�
//�����F���������{�^���̃��f���ԍ���1�̈�
//�߂�l�F�Ȃ�
void Stage::SetNo1MultiStepNumberCountUp(int onDoubleNum)
{
    steppingNumber_No1Multi_[onDoubleNum]++;
}

//���������{�^���̕Е��̃{�^���̏���Ă���l�����J�E���g�_�E������֐�
//�����F���������{�^���̃��f���ԍ���1�̈�
//�߂�l�F�Ȃ�
void Stage::SetNo1MultiStepNumberCountDown(int onDoubleNum)
{
    steppingNumber_No1Multi_[onDoubleNum]--;
}

//���������{�^���̂����Е��̃{�^���̏���Ă���l�����J�E���g�A�b�v����֐�
//�����F���������{�^���̃��f���ԍ���1�̈�
//�߂�l�F�Ȃ�
void Stage::SetNo2MultiStepNumberCountUp(int orDunbleNum)
{
    steppingNumber_No2Multi_[orDunbleNum]++;
}

//���������{�^���̂����Е��̃{�^���̏���Ă���l�����J�E���g�_�E������֐�
//�����F���������{�^���̃��f���ԍ���1�̈�
//�߂�l�F�Ȃ�
void Stage::SetNo2MultiStepNumberCountDown(int orDunbleNum)
{
    steppingNumber_No2Multi_[orDunbleNum]--;
}

//���[�v�u���b�N�̃M�~�b�N���܂Ƃ߂��֐��B
//�����FgetX, getY �v���C���[�̈ʒu
//�ߒl�F�Ȃ�
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

//�_�Ńu���b�N�̃M�~�b�N���܂Ƃ߂��֐��B
//�����F�_�ł������u���b�N�̃��f���ԍ�, �_�ŊԊu�B�P�ʂ̓t���[��
//�߂�l�F�Ȃ�
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

//���f����؂�ւ���֐��B
//�����F�ύX���������f���ԍ�, true��+10���ꂽ���f���ɁAfalse��-10���ꂽ���f���ɕύX
//�߂�l�F�Ȃ�
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

//�S�[���𔻒肵�A�V�[����؂�ւ���֐�
//�����FPlayer��Position.x_��Position.y_
//�߂�l�F�Ȃ�
void Stage::GoalCol(int x, int y)
{
    //�����̓S�[��
    if (map_[x][y] == GOAL_BLOCK_)
    {
        Audio::Stop(hSound_[0]);
        //�V�[���ړ�
        //Find�֐���SceneManager�N���X��T����
        //ChangeScene�֐��̈����Ɉړ��������V�[����ID��n��
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_CLEAR);
    }
}

//�Ԃ��������ǂ���
//�����FPlayer��Position.x_��Position.y_
//�߂�l�F�Ԃ�������false�A�����Ȃ����true
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
        map_[x][y] == MULTI_BUTTON_WALL_ALPHA_)
    {
        return false;
    }
    return true;
}

//�����X�|�[���n�_��Ԃ��Q�b�^�[
//�����F�Ȃ�
 //�߂�l�FstertPos_
XMFLOAT3 Stage::GetStartPosition()
{
    return stertPos_;
}

//�J��
void Stage::Release()
{
}

//Load������10�񃋁[�v����֐�
//�����F���f�����i�[�������z��̏����l, �t�@�C���l�[��(fbx�̖��O������OK)
//�߂�l�F�Ȃ�
void Stage::LoopLoad(int modelNum, string modelName)
{
    for (int i = modelNum; i < modelNum + 10; i++)
    {
        hModel_[i] = Model::Load(FILE_PAS_ + modelName);
    }
}


//���f�������[�h���鏈�����܂Ƃ߂��֐�
//�����F�Ȃ�
//�߂�l�F�Ȃ�
void Stage::ModelLoad()
{
    //�T�E���h�f�[�^�̃��[�h
    hSound_[BGM] = Audio::Load("Assets/Sound/GameBGM.wav", 4);
    hSound_[SE_GOAl] = Audio::Load("Assets/Sound/Goal.wav",4);
    hSound_[SE_WARPE] = Audio::Load("Assets/Sound/Warpe.wav",4);

    //�X�e�[�W���\������u���b�N
    hModel_[0] = Model::Load(FILE_PAS_ + "Block_01.fbx");
    hModel_[1] = Model::Load(FILE_PAS_ + "Block_03.fbx");
    hModel_[2] = Model::Load(FILE_PAS_ + "Goal.fbx");
    hModel_[3] = Model::Load(FILE_PAS_ + "GameBG.fbx");
    hModel_[4] = Model::Load(FILE_PAS_ + "Block_01.fbx");
    hModel_[5] = Model::Load(FILE_PAS_ + "Block_01.fbx");
    hModel_[6] = Model::Load(FILE_PAS_ + "Block_01.fbx");
    hModel_[7] = Model::Load(FILE_PAS_ + "Block_01.fbx");
    hModel_[8] = Model::Load(FILE_PAS_ + "Block_01.fbx");
    hModel_[9] = Model::Load(FILE_PAS_ + "Block_01.fbx");

    //�������甭������{�^��
    LoopLoad(10, "PushButton.fbx");

    //��������J���������
    LoopLoad(20, "Wall_01.fbx");

    //�����Ă���Ԃ�����������{�^��(�����O)
    LoopLoad(30, "MeantimeButto_up.fbx");

    //�����Ă���Ԃ�����������{�^��(��������)
    LoopLoad(40, "MeantimeButto_down.fbx");

    //�J����
    LoopLoad(50, "Wall_01.fbx");

    //�J���Ă���Ԃ̉����Ȃ��u���b�N
    LoopLoad(60, "Wall_02.fbx");

    //�_�ł���u���b�N(������O)
    LoopLoad(70, "Wall_01.fbx");

    //�_�ł���u���b�N(��������)
    LoopLoad(80, "Wall_02.fbx");

    //���[�v�u���b�N(����)
    LoopLoad(90, "WarpEntrance.fbx");

    //���[�v�u���b�N(�o��)
    LoopLoad(100, "WarpExit.fbx");

    //���������{�^��(�����O)
    LoopLoad(110, "MultiButton_01_up.fbx");

    //���������{�^��(��������)
    LoopLoad(120, "MultiButton_01_down.fbx");

    //���������{�^��(�����O)
    LoopLoad(130, "MultiButton_02_up.fbx");

    //���������{�^��(��������)
    LoopLoad(140, "MultiButton_02_down.fbx");

    //�����{�^���������ꂽ��J����
    LoopLoad(150, "Wall_01.fbx");

    //�����{�^�������ꂽ������
    LoopLoad(160, "Wall_02.fbx");
}

