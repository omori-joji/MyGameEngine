#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"
#include "Stage.h"
#include "Shadow.h"


class Shadow;

//Player���Ǘ�����N���X
class Player : public GameObject
{
    //const�͒萔�錾�Ŏg��
    const float SPEED;      //Player�̈ړ����x
    const float WIDTH;      //Player�̕�
    const float HEIGHT;     //Player�̍���
    const float MARGIN;     //�����蔻��̗V��
    const float BLOCK_SIZE; //�u���b�N�̃T�C�Y
    const float MAX_JUMP;   //�W�����v�̏��
    const float BACK_POSITION_LEFT_;
    const float BACK_POSITION_RIGHT_;
    const float BACK_POSITION_UP_;
    const float BACK_POSITION_DOWN_;
    const float GRAVITY_;
    const float DROP_DOWN_;
    const int RESET_VALU_;
    const int PLAYER_FOOT_;


    bool isJump_;            //�W�����v���Ă��邩
    float move_;            //Y���̈ړ�
   



    int hModel_Left[2];
    int hModel_Right[2];

    Stage* pStage_;


public:
    bool isPastButton;       //����������ł��邩
    int plyerRightMoveCount;
    int plyerLeftMoveCount;
    bool isDirection;

    enum Direction
    {
        DIR_LEFT,
        DIR_RIGHT
    };


public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //Find���������ׂĂ܂Ƃ߂�֐�
    void AllFind();

    //Player�̑�����܂Ƃ߂�֐�
    void PlayerMove();

    //Playyer�̓����蔻����܂Ƃ߂�֐�
    void PlayerCollision();
};
