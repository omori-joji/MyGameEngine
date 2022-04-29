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
    bool isJump_;            //�W�����v���Ă��邩
    float move_;            //Y���̈ړ�
    float gravity_;         //�d��
   



    int hModel_Left[2];
    int hModel_Right[2];

    Stage* pStage_;


public:
    int plyerRightMoveCount;
    int plyerLeftMoveCount;
    bool isDirection;


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

};
