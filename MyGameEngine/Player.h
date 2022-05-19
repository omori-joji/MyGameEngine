#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"
#include "Engine/Fbx.h"
#include <string>

//�N���X�̑O���錾
class Stage;

//Player�������s���N���X
class Player : public GameObject
{
    //�萔�錾
    const float SPEED_;                     //Player�̈ړ����x
    const float WIDTH_;                     //Player�̕�
    const float HEIGHT_;                    //Player�̍���
    const float MARGIN_;                    //�����蔻��̗V��
    const float BLOCK_SIZE_;                //�u���b�N�̃T�C�Y
    const float MAX_JUMP_;                  //�W�����v�̏��
    const float BACK_POSITION_LEFT_;        //�G��Ă�����ʒu��߂��l
    const float BACK_POSITION_RIGHT_;       //�G��Ă�����ʒu��߂��l
    const float BACK_POSITION_UP_;          //�G��Ă�����ʒu��߂��l
    const float BACK_POSITION_DOWN_;        //�G��Ă�����ʒu��߂��l
    const float GRAVITY_;                   //�d�͂̒l
    const float DROP_DOWN_;                 //Player�̉��ɉ����Ȃ���Ή��ɗ����邽�߂̒萔
    const int RESET_VALU_;                  //�������p�̒萔
    const int PLAYER_FOOT_;                 //Player�̑��������邽�߂�Y����-1����萔
    const string filePas_;                  //���f�����ۑ�����Ă���t�@�C���p�X

    //�ϐ��錾
    int direction_;                         //�v���C���[�̌����̔ԍ�
    int modelNumber_;                       //�����Ă��郂�f���̔ԍ�
    int meanTimeGimmickNumber_;             //���񂾃{�^���̃��f���ԍ����i�[����ϐ�
    int onGimmickNumber_;                   //���񂾃{�^���̃��f���ԍ����i�[����ϐ�
    int orGimmickNumber_;                   //���񂾃{�^���̃��f���ԍ����i�[����ϐ�
    float yMove_;                           //Y���̈ړ�
    bool isJump_;                           //�W�����v���Ă��邩
    bool isPastMeanTimeButton_;             //����������ł��邩
    Stage* pStage_;                         //�X�e�[�W�̏�������|�C���^

    enum Direction                         //Player�̌���
    {
        DIR_RIGHT,                          //�E����
        DIR_LEFT,                           //������
        DIR_MAX,                            //�z��̍ő�v�f��

        STANDING_MODEL = 0,                 //�����Ă��郂�f���ԍ�
        RUN_MODEL,                          //�����Ă��郂�f���ԍ�

        ON_DOUBLE_BUTTON = 0,               //�Е��̓��������{�^���̃t���O�ԍ�
        OR_DOUBLE_BUTTON,                   //�����Е��̓��������{�^���̃t���O�ԍ�
        MAX_DOUBLE_BUTTON,              //isPastDoubleButton_�̍ő�v�f��
    };
    int hModel_[DIR_MAX][DIR_MAX];          //Player�̃��f���ԍ����i�[���鑽�����z��
    bool isPastDoubleButton_[MAX_DOUBLE_BUTTON];//�����{�^���̃t���O
    int hSe_[10];

public:    
    Player(GameObject* parent);             //�R���X�g���N�^
    ~Player();                              //�f�X�g���N�^    
    void Initialize() override;             //������
    void Update() override;                 //�X�V
    void Draw() override;                   //�`��  
    void Release() override;                //�J��
    void MeanTimeButtonCheck();             //Player���{�^���𓥂�ł��邩�A�{�^�����痣�ꂽ���𔻒f����֐�
    void OnDoubleButtonCheck();             //�Е��̓��������{�^�����������u�ԂƗ��ꂽ�u�Ԃ̏������s���֐�
    void OrDoubleButtonCheck();             //�����Е��̓��������{�^�����������u�ԂƗ��ꂽ�u�Ԃ̏������s���֐�
    int GetModelNumber();                   //Player�̑����Ă��郂�f���ԍ���Ԃ��֐�
    int GetDirection();                     //Player�����̃��f���ԍ���Ԃ��֐�
private:    
    void AllFind();                         //Find���������ׂĂ܂Ƃ߂�֐�
    void PlayerRightMove();                 //Player�̉E������܂Ƃ߂�֐�
    void PlayerLeftMove();                  //Player�̍�������܂Ƃ߂�֐�
    void Collision();                       //Playyer�̓����蔻����܂Ƃ߂�֐�
    void Jamp();                            //�W�����v�̏������܂Ƃ߂��֐�
    void Reset();                           //�����ʒu�ɖ߂鏈�����܂Ƃ߂��֐�
};
