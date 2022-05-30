#pragma once
#include "Engine/VisualEffect.h"
#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"
#include "Engine/Audio.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Fbx.h"

//�N���X�̑O���錾
class Player;
class Shadow;
class SceneManager;

//Stage���Ǘ�����N���X
class Stage : public GameObject
{
    const int BACK_GROUND_;                         //�w�i�̃��f���ԍ�
    const int PLAYER_GENERAT_POS_;                  //Player�̃��X�|�[���n�_
    const int SHADOW_NAMBER_;                       //�e�̐�
    const int ALL_GIMMICKS_;                        //�M�~�b�N�̃��f���ԍ��𒲂ׂ�J��Ԃ����̂��߂̒萔
    const int RESET_VALU_;                          //�������p�̒l
    const int CHENGE_POSITIVE_GIMMICKS_;            //+10�������f���ԍ��ɕς��邽�߂̒萔
    const int BRINKING_BLOCKS_;                     //�_�ł���u���b�N
    const int FRAME_TIME_;                          //�_�ł���Ԋu
    const int MEANTIME_WALL_;                       //�{�^�������܂�Ă��Ȃ��ԕ��Ă���ǂ̃��f���ԍ�
    const int MEANTIME_BUTTON_UP_;                  //����ł���Ԕ�������{�^���̓��ޑO�̃��f���ԍ�
    const int MEANTIME_BUTTON_DOWN_;                //����ł���Ԕ�������{�^���̓��񂾂��Ƃ̃��f���ԍ�
    const int MEANTIME_BLOCK_ALPHA_;                //�{�^�������܂�Ă���ԊJ���Ă���ǂ̃��f���ԍ�
    const int NO1_WARP_BLOCK_;                      //�Е��̃��[�v�u���b�N�̃��f���ԍ�
    const int NO2_WARP_BLOCK_;                      //�����Е��̃��[�v�u���b�N�̃��f���ԍ�
    const int GOAL_BLOCK_;                          //�S�[���u���b�N�̃��f���ԍ�
    const int NO1_DOUBLE_BUTTON_UP_;                //���������{�^���̕Е��B����ł��Ȃ���Ԃ̃��f���ԍ�
    const int NO1_DOUBLE_BUTTON_DOWN_;              //���������{�^���̕Е��B����ł����Ԃ̃��f���ԍ�
    const int NO2_DOUBLE_BUTTON_UP_;                //���������{�^���̂����Е��B����ł��Ȃ���Ԃ̃��f���ԍ�
    const int NO2_DOUBLE_BUTTON_DOWN_;              //���������{�^���̕Е��B����ł����Ԃ̃��f���ԍ�
    const int DOUBLE_BUTTON_WALL_;                  //���������{�^���ɑΉ������ǁB�J���ĂȂ���Ԃ̃��f���ԍ�
    const int DOUBLE_BUTTON_WALL_ALPHA_;            //���������{�^���ɑΉ������ǁB�J���Ă����Ԃ̃��f���ԍ�
    char shadowCount_;                              //������e�̐�
    const string FILE_PAS_;                         //Assets�t�@�C���̃p�X
    int timeCount_;                                 //�_�Ńu���b�N�̓_�ŊԊu
    bool isBlinking_;                               //�u���b�N�����������ǂ���
    bool isWarp_;                                   //���[�v��������
    XMFLOAT3 stertPos_;                             //Player�����Z�b�g�������̃��Z�b�g�ʒu���L������ϐ�
    Player* pPlayer_;                               //Player�N���X���i�[����|�C���^
    SceneManager* pSceneManager_;                   //SceneManager�N���X���i�[����|�C���^
    enum
    {
        MAP_BESIDE_ = 28,                           //�}�b�v��X��
        MAP_VERTICAL = 23,                          //�}�b�v��Y��
        MAX_MODEL = 200,                            //hModel_�̗v�f��
        MAX_SOUND = 4,                              //hSound_�̗v�f��
        MAX_STEPNUMBER = 10,                        //�e�{�^��������ł���l�����L������z��̗v�f��
        MAX_DOUBLE_FLAG = 2,                        //�����{�^���̓���ł���t���O�̗v�f��
        MAX_SHADOW_NUMBER = 5,                      //�e�̍ő吶����
    };
    int map_[MAP_BESIDE_][MAP_VERTICAL];            //�X�e�[�W�̃}�X���
    int hModel_[MAX_MODEL];                         //���f���ԍ�
    int hSound_[MAX_SOUND];                         //�T�E���h�t�@�C��
    char steppingNumberMeanTime_[MAX_STEPNUMBER];    //���l����ł��邩
    char steppingNumber_No1Double_[MAX_STEPNUMBER];  //���l����ł��邩
    char steppingNumber_No2Double_[MAX_STEPNUMBER];  //���l����ł��邩
    bool isDoubleButton_[MAX_DOUBLE_FLAG];          //�����{�^���̕Е���������
    Shadow* pShadow_[MAX_SHADOW_NUMBER];            //Shadow�N���X���i�[����|�C���^�^�̔z��

public:
    Stage(GameObject* parent);                      //�R���X�g���N�^
    ~Stage();                                       //�f�X�g���N�^
    void Initialize() override;                     //������
    void Update() override;                         //�X�V
    void Draw() override;                           //�`��
    void Release() override;                        //�J��

    //�S�[���𔻒肵�A�V�[����؂�ւ���֐�
    //�����FPlayer��Position.x_��Position.y_
    //�߂�l�F�Ȃ�
    void GoalCol(int x, int y);                     
    
    //���[�v�u���b�N�̃M�~�b�N���܂Ƃ߂��֐��B
    //�����FgetX, getY �v���C���[�̈ʒu
    //�ߒl�F�Ȃ�
    void WarpBlockCollision(int getX, int getY);    


    //�ǂ̃��f���ƃ{�^���̃��f����؂�ւ���֐��B
    //�����F�Ȃ�
    //�߂�l�F�Ȃ�
    void ChengeButtonAndWall();

    //�{�^���ɏ���Ă���l�����J�E���g�A�b�v����֐�
    //�����F����ł���Ԕ�������{�^���̃��f���ԍ���1�̈�
    //�߂�l�F�Ȃ�
    void SetMeanTimeStepNumberCountUp(int a);

    //�{�^���ɏ���Ă���l�����J�E���g�_�E������֐�
    //�����F����ł���Ԕ�������{�^���̃��f���ԍ���1�̈�
    //�߂�l�F�Ȃ�
    void SetMeanTimeStepNumberCountDown(int a);

    //���������{�^���̕Е��̃{�^���̏���Ă���l�����J�E���g�A�b�v����֐�
    //�����F���������{�^���̃��f���ԍ���1�̈�
    //�߂�l�F�Ȃ�
    void SetNo1DoubleStepNumberCountUp(int b);

    //���������{�^���̕Е��̃{�^���̏���Ă���l�����J�E���g�_�E������֐�
    //�����F���������{�^���̃��f���ԍ���1�̈�
    //�߂�l�F�Ȃ�
    void SetNo1DoubleStepNumberCountDown(int b);

    //���������{�^���̂����Е��̃{�^���̏���Ă���l�����J�E���g�A�b�v����֐�
    //�����F���������{�^���̃��f���ԍ���1�̈�
    //�߂�l�F�Ȃ�
    void SetNo2DoubleStepNumberCountUp(int c);

    //���������{�^���̂����Е��̃{�^���̏���Ă���l�����J�E���g�_�E������֐�
    //�����F���������{�^���̃��f���ԍ���1�̈�
    //�߂�l�F�Ȃ�
    void SetNo2DoubleStepNumberCountDown(int c);

    //�����̃u���b�N�̃��f���ԍ��������Ŏ󂯎��A�����1�̈ʂ�Ԃ��֐�
    //�����FPlayer�AShadow��Position.x_��Position.y_ -1(����)
    //�߂�l�F�{�^���̃��f���ԍ���1�̈�
    int CheckFootBlock(int x, int y);

    //�Ԃ��������ǂ���
    //�����FPlayer��Position.x_��Position.y_
    //�߂�l�F�Ԃ�������false�A�����Ȃ����true
    bool isCrash(int x, int y);

    //����ł���Ԕ�������{�^�������邩�ǂ����̏��������s����
    //�����FPlayer�AShadow��Position.x_��Position.y_ -1(����)
    //�߂�l�F����ł����true����ł��Ȃ����false
    bool MeanTimeButton(int x, int y);

    //���������{�^���̕Е��ɏ������true����ȊO��false��Ԃ��֐�
    //�����FPlayer�AShadow��Position.x_��Position.y_ -1(����)
    //�߂�l�F����ł����true����ł��Ȃ����false
    bool No1DoubleButton(int x, int y);

    //���������{�^���̂����Е��ɏ������true����ȊO��false��Ԃ��֐�
    //�����FPlayer�AShadow��Position.x_��Position.y_ -1(����)
    //�߂�l�F����ł����true����ł��Ȃ����false
    bool No2DoubleButton(int x, int y);


    //�����X�|�[���n�_��Ԃ��Q�b�^�[
    //�����F�Ȃ�
    //�߂�l�FstertPos_
    XMFLOAT3 GetStartPosition();
private:
    //���f�������[�h���鏈�����܂Ƃ߂��֐�
    //�����F�Ȃ�
    //�߂�l�F�Ȃ�
    void ModelLoad();

    //���f����؂�ւ���֐��B
    //�����F�ύX���������f���ԍ�, true��+10���ꂽ���f���ɁAfalse��-10���ꂽ���f���ɕύX
    //�߂�l�F�Ȃ�
    void CheckBlock(int find , bool which);

    //�{�^�����痣�ꂽ��Ă΂��֐��A���f����؂�ւ��鏈�����s��
    //�����F�Ȃ�
    //�߂�l�F�Ȃ�
    void CollisionExit();


    //�_�Ńu���b�N�̃M�~�b�N���܂Ƃ߂��֐��B
    //�����F�_�ł������u���b�N�̃��f���ԍ�, �_�ŊԊu�B�P�ʂ̓t���[��
    //�߂�l�F�Ȃ�
    void Blinking(int blockNum, int time);

    //���������{�^�����ǂ����������Ă�����B�ǂ��J���A����ȊO�̏�����������ǂ����֐�
    //�����F�Ȃ�
    //�߂�l�F�Ȃ�
    void SimultaneousWallOpen();

    //�e�̍Đ�����t���O�Ɛ����̏������s���֐�
    //�����F�Ȃ�
    //�߂�l�F�Ȃ�
    void PlayRecord();
};