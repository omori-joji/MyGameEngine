#pragma once
#include "Engine/GameObject.h"
#include "Actor.h"

//�N���X�̑O���錾
class Stage;

//Player�������s���N���X
class Player :  public Actor
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
    const char RESET_VALU_;                 //�������p�̒萔
    const char PLAYER_FOOT_;                //Player�̑��������邽�߂�Y����-1����萔
    const string MODEL_FILE_PAS_;           //���f�����ۑ�����Ă���t�@�C���p�X
    const string SE_FILE_PAS_;              //���f�����ۑ�����Ă���t�@�C���p�X
    char Model_Number_;                     //�����Ă��郂�f���̔ԍ�
    float yMove_;                           //Y���̈ړ�
    bool isJump_;                           //�W�����v���Ă��邩
    Stage* pStage_;                         //�X�e�[�W�̏�������|�C���^

    //Player�̃��f���ԍ�
    enum Direction
    {
        STANDING_MODEL,                     //�����Ă��郂�f���ԍ�
        RUN_MODEL,                          //�����Ă��郂�f���ԍ�

        DIR_RIGHT = 0,                      //�E�����̃��f���ԍ�
        DIR_LEFT,                           //�������̃��f���ԍ�
        DIR_MAX                             //hModel_�̗v�f��
    }direction_;                            //�v���C���[�̌����̔ԍ�
    int hModel_[DIR_MAX][DIR_MAX];          //Player�̃��f���ԍ����i�[���鑽�����z��

    //�T�E���h�t�@�C���ԍ�
    enum Se
    {
        JUMP,                               //�W�����v��SE
        RESET,                              //���Z�b�g��SE
        MAX_SE,                             //�z��̗v�f��
    }se_;
    int hSe_[MAX_SE];                       //�T�E���h�t�@�C�����i�[����z��

public:    
    Player(GameObject* parent);             //�R���X�g���N�^
    ~Player();                              //�f�X�g���N�^    
    void Initialize() override;             //������
    void Update() override;                 //�X�V
    void Draw() override;                   //�`��  
    void Release() override;                //�J��

    //Player�̑����Ă��郂�f���ԍ���Ԃ��֐�
    //�����F�Ȃ�
    //�߂�l�FmodelNumber_
    int GetModelNumber();

    //Player�����̃��f���ԍ���Ԃ��֐�
    //�����F�Ȃ�
    //�߂�l�Fdirection_
    int GetDirection();
private:
    //Find���������ׂĂ܂Ƃ߂�֐�
    //�����F�Ȃ�
    //�߂�l�F�Ȃ�
    void AllFind();

    //Player�̉E������܂Ƃ߂�֐�
    //�����F�Ȃ�
    //�߂�l�F�Ȃ�
    void PlayerRightMove();

    //Player�̍�������܂Ƃ߂�֐�
    //�����F�Ȃ�
    //�߂�l�F�Ȃ�
    void PlayerLeftMove();

    //Playyer�̓����蔻����܂Ƃ߂�֐�
    //�����F�Ȃ�
    //�߂�l�F�Ȃ�
    void Collision();

    //�����ʒu�ɖ߂鏈�����܂Ƃ߂��֐�
    //�����F�Ȃ�
    //�߂�l�F�Ȃ�
    void Reset();

    //�W�����v�̏������܂Ƃ߂��֐�
    //�����F�Ȃ�
    //�߂�l�F�Ȃ�
    void Jump();
};
