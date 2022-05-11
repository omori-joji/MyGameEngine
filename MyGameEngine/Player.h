#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"
#include "Stage.h"


class Shadow;

//Player���Ǘ�����N���X
class Player : public GameObject
{

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
    const int RUN_MODEL_;                   //�����Ă��郂�f���̔ԍ�
    const int STANDING_MODEL_;              //�����Ă��郂�f���̔ԍ�

    int direction_;                         //�v���C���[�̌����̔ԍ�
    int modelNumber_;                       //�����Ă��郂�f���̔ԍ�
    float move_;                            //Y���̈ړ�

    bool isJump_;                           //�W�����v���Ă��邩
    bool isPastButton;                      //����������ł��邩

    Stage* pStage_;                         //�X�e�[�W�̏�������|�C���^

    enum ModelNumber                        //Player�̌���
    {
        DIR_RIGHT,                          //�E����
        DIR_LEFT,                           //������
        DIR_MAX,                            //�z��̍ő�v�f��
    };
    int hModel_[DIR_MAX][DIR_MAX];          //Player�̃��f���ԍ����i�[���鑽�����z��

public:    
    Player(GameObject* parent);             //�R���X�g���N�^
    
    ~Player();                              //�f�X�g���N�^
    
    void Initialize() override;             //������
    
    void Update() override;                 //�X�V
    
    void Draw() override;                   //�`��
    
    void Release() override;                //�J��
    
    int GetModelNumber();                   //Player�̑����Ă��郂�f���ԍ���Ԃ��֐�
    
    int GetDirection();                     //Player�����̃��f���ԍ���Ԃ��֐�

    void FootButtonCheck();                 //Player���{�^���𓥂�ł��邩�A�{�^�����痣�ꂽ���𔻒f����֐�

private:    
    void AllFind();                         //Find���������ׂĂ܂Ƃ߂�֐�

    void PlayerRightMove();                 //Player�̑�����܂Ƃ߂�֐�
    void PlayerLeftMove();

    void PlayerCollision();                 //Playyer�̓����蔻����܂Ƃ߂�֐�
};
