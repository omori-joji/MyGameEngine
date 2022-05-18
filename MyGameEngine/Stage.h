#pragma once
#include "Engine/VisualEffect.h"
#include "Engine/SceneManager.h"
#include "Engine/GameObject.h"
#include "Engine/CsvReader.h"
#include "Engine/Audio.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Fbx.h"
#include "Player.h"
#include "Shadow.h"
//�N���X�̑O���錾
class Player;
class Shadow;
class SceneManager;

//���������Ǘ�����N���X
class Stage : public GameObject
{
    //int hVfxA, hVfxB;
    const int VERTICAL_VALU_;                       //�X�e�[�W�̍���
    const int BESIDE_VALU_;                         //�X�e�[�W�̉���
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
    const int ON_WARP_BLOCK_;                       //�Е��̃��[�v�u���b�N�̃��f���ԍ�
    const int OR_WARP_BLOCK_;                       //�����Е��̃��[�v�u���b�N�̃��f���ԍ�
    const int GOAL_BLOCK_;                          //�S�[���u���b�N�̃��f���ԍ�
    const int ON_DOUBLE_BUTTON_UP_;                 //���������{�^���̕Е��B����ł��Ȃ���Ԃ̃��f���ԍ�
    const int ON_DOUBLE_BUTTON_DOWN_;               //���������{�^���̕Е��B����ł����Ԃ̃��f���ԍ�
    const int OR_DOUBLE_BUTTON_UP_;                 //���������{�^���̂����Е��B����ł��Ȃ���Ԃ̃��f���ԍ�
    const int OR_DOUBLE_BUTTON_DOWN_;               //���������{�^���̕Е��B����ł����Ԃ̃��f���ԍ�
    const int DOUBLE_BUTTON_WALL_;                  //���������{�^���ɑΉ������ǁB�J���ĂȂ���Ԃ̃��f���ԍ�
    const int DOUBLE_BUTTON_WALL_ALPHA_;            //���������{�^���ɑΉ������ǁB�J���Ă����Ԃ̃��f���ԍ�
    int shadowCount_;                               //�e�̐�
    int timeCount_;                                 //�_�Ńu���b�N�̓_�ŊԊu
    bool isBlinking_;                               //�u���b�N�����������ǂ���
    bool isWarp_;                                   //���[�v��������
    XMFLOAT3 stertPos;                              //Player�����Z�b�g�������̃��Z�b�g�ʒu���L������ϐ�
    Player* pPlayer_;                               //Player�N���X���i�[����|�C���^
    SceneManager* pSceneManager_;                   //SceneManager�N���X���i�[����|�C���^
    enum
    {
        MAP_BESIDE_ = 28,
        MAP_VERTICAL = 23,
        MAX_MODEL = 200,
        MAX_SOUND = 4,
        MAX_STEPNUMBER = 10,
        MAX_DOUBLE_FLAG = 2,
        MAX_SHADOW_NUMBER = 6,
    };
    int map_[MAP_BESIDE_][MAP_VERTICAL];            //�X�e�[�W�̃}�X���
    int hModel_[MAX_MODEL];                         //���f���ԍ�
    int hSound_[MAX_SOUND];                         //�T�E���h�t�@�C��
    int steppingNumberMeanTime[MAX_STEPNUMBER];     //���l����ł��邩
    int steppingNumber_OnDouble[MAX_STEPNUMBER];    //���l����ł��邩
    int steppingNumber_OrDouble[MAX_STEPNUMBER];    //���l����ł��邩
    bool isDoubleButton_[MAX_DOUBLE_FLAG];          //�����{�^���̕Е���������
    Shadow* pShadow_[MAX_SHADOW_NUMBER];            //Shadow�N���X���i�[����|�C���^�^�̔z��

public:
    Stage(GameObject* parent);                      //�R���X�g���N�^
    ~Stage();                                       //�f�X�g���N�^
    void Initialize() override;                     //������
    void Update() override;                         //�X�V
    void Draw() override;                           //�`��
    void Release() override;                        //�J��
    void GoalCol(int x, int y);                     //�S�[���𔻒肷��֐��B�����̓v���C���[�̈ʒu
    void WarpBlockCollision(int getX, int getY);    //���[�v�u���b�N�̃M�~�b�N���܂Ƃ߂��֐��B�����̓v���C���[�̈ʒu
    void ChengeButtonAndWall();                     //�ǂ̃��f���ƃ{�^���̃��f����؂�ւ���֐��B
    void SetMeanTimeStepNumberCountUp(int a);       //�{�^���ɏ���Ă���l�����J�E���g�A�b�v����֐�
    void SetMeanTimeStepNumberCountDown(int a);     //�{�^���ɏ���Ă���l�����J�E���g�A�b�v����֐�
    void SetOnDoubleStepNumberCountUp(int b);       //���������{�^���̕Е��̃{�^���̏���Ă���l�����J�E���g�A�b�v����֐�
    void SetOnDoubleStepNumberCountDown(int b);     //���������{�^���̕Е��̃{�^���̏���Ă���l�����J�E���g�_�E������֐�
    void SetOrDoubleStepNumberCountUp(int c);       //���������{�^���̂����Е��̃{�^���̏���Ă���l�����J�E���g�A�b�v����֐�
    void SetOrDoubleStepNumberCountDown(int c);     //���������{�^���̂����Е��̃{�^���̏���Ă���l�����J�E���g�_�E������֐�
    int CheckFootBlock(int x, int y);               //�����̃u���b�N�̃��f���ԍ��������Ŏ󂯎��A�����1�̈ʂ�Ԃ��֐�
    bool isCrash(int x, int y);                     //�Ԃ��邩�ǂ���
    bool MeanTimeButton(int x, int y);              //���ׂẴ{�^�����Ǘ�����֐�
    bool OnDoubleButton(int x, int y);              //���������{�^���̕Е��ɏ������true����ȊO��false��Ԃ��֐�
    bool OrDoubleButton(int x, int y);              //���������{�^���̂����Е��ɏ������true����ȊO��false��Ԃ��֐�
    XMFLOAT3 GetStartPosition();                    //�����X�|�[���n�_��Ԃ��Q�b�^�[
private:
    void ModelLoad();                               //�܂Ƃ߂ă��f�������[�h����֐�
    void CheckBlock(int find , bool which);         //���f����؂�ւ���֐��B������(�؂�ւ��������f���ԍ�, true����������+10false����������-10���ꂽ���f���ԍ��ɐ؂�ւ���)
    void CollisionExit();                           //�����蔻��B�{�^�����痣�ꂽ��Ă΂��
    void Blinking(int blockNum, int time);          //�_�Ńu���b�N�̃M�~�b�N���܂Ƃ߂��֐��B������(���������_�ł��������u���b�N�̃��f���ԍ�, ���������_�ł��鎞�Ԃ̊Ԋu(�P�ʂ̓t���[��))
    void SimultaneousWallOpen();                    //���������{�^�����ǂ����������Ă�����B�ǂ��J���A����ȊO�̏�����������ǂ����֐�
    void ResetShadow();                             //�L�^�����e�̓��������ׂĂ܂�����ȏ�Ԃɂ��鏈�����܂Ƃ߂��֐�
    void PlayRecord();                              //�e�̍Đ����܂Ƃ߂��֐�
    void AllFind();                                 //Find�������܂Ƃ߂��֐�
};