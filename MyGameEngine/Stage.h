#pragma once
#include "Engine/Fbx.h"
#include "Engine/GameObject.h"

//�N���X�̑O���錾
class Player;
class Shadow;
class SceneManager;


//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hVfxA, hVfxB;



    int map_[28][23];   //�X�e�[�W�̃}�X���
    int hModel_[500];   //���f���ԍ�
    int shadowCount_;   //�e�̐�
    int timeCount_;     //�_�Ńu���b�N�̓_�ŊԊu
    int hSound_;        //�T�E���h�t�@�C��
    int downNum_;

    const int VERTICAL_VALU_; //�X�e�[�W�̍���
    const int BESIDE_VALU_;   //�X�e�[�W�̉���
    const int BACK_GROUND_;
    const int PLAYER_GENERAT_POS_;  //Player�̃��X�|�[���n�_
    const int SHADOW_NAMBER_; //�e�̐�
    const int ALL_GIMMICKS_; //�M�~�b�N�̃��f���ԍ��𒲂ׂ�J��Ԃ����̂��߂̒萔
    const int RESET_VALU_; //�������p�̒l
    const int CHENGE_POSITIVE_GIMMICKS_; //+10�������f���ԍ��ɕς��邽�߂̒萔
    const int BRINKING_BLOCKS_;
    const int FRAME_TIME_;
    const int DOBLE_BLOCKS_;
    const int TWO_BLOCKS_;
    const int MEANTIME_WALL_;
    const int MEANTIME_BUTTON_UP_;
    const int MEANTIME_BUTTON_DOWN_;
    const int MEANTIME_BLOCK_ALPHA_;
    const int WARP_BLOCK_ENTRANS_;
    const int WARP_BLOCK_EXIT_;
    const int GOAL_BLOCK_;



    bool isBlinking_;      //�u���b�N�����������ǂ���
    bool isWarp_;          //���[�v��������
    bool isdoubleButton1_; //�����{�^���̕Е���������
    bool isdoubleButton2_; //�����{�^���̂����Е���������
    bool isButtonMenberFlg[9];



    Player* pPlayer_;             //Player�N���X���i�[����|�C���^
    SceneManager* pSceneManager_; //SceneManager�N���X���i�[����|�C���^
    Shadow* pShadow_[6];          //Shadow�N���X���i�[����|�C���^�^�̔z��


    XMFLOAT3 stertPos; //Player�����Z�b�g�������̃��Z�b�g�ʒu���L������ϐ�

public:
    int steppingNumber;//���l����ł��邩
    bool isOnButton;


public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�܂Ƃ߂ă��f�������[�h����֐�
    void ModelLoad();

    //�Ԃ��邩�ǂ���
    bool isCrash(int x , int y);

    //���ׂẴ{�^�����Ǘ�����֐�
    bool DownButton(int x, int y);


    //���f����؂�ւ���֐�
    //�������͐؂�ւ��������f���ԍ�
    //��������true����������+10���ꂽ���f���ԍ��ɐ؂�ւ���
    //false����������-10���ꂽ���f���ԍ��ɐ؂�ւ���
    void CheckBlock(int find , bool which);


    //�_�Ńu���b�N�̃M�~�b�N���܂Ƃ߂��֐�
    //���������_�ł��������u���b�N�̃��f���ԍ�
    //���������_�ł��鎞�Ԃ̊Ԋu(�P�ʂ̓t���[��)
    void Blinking(int blockNum, int time);

    //�S�[���𔻒肷��֐�
    //�����̓v���C���[�̈ʒu
    void GoalCol(int x, int y);

    int NawBox(int x, int y);


    //���[�v�u���b�N�̏o���̃M�~�b�N���܂Ƃ߂��֐�
    //�����̓v���C���[�̈ʒu
    void WarpBlockCollision(int getX, int getY);

    XMFLOAT3 GetStartPosition();



    void ChengeButton(int x, int y);

    void StepNumberCountUp();
    void StepNumberCountDown();
};

