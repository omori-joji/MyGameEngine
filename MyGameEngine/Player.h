#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"
#include "Stage.h"
#include "Shadow.h"


//Player���Ǘ�����N���X
class Player : public GameObject
{
    //const�͒萔�錾�Ŏg��
    const float SPEED;//Player�̈ړ����x
    const float WIDTH;//Player�̕�
    const float HEIGHT;//Player�̍���
    const float MARGIN;//�����蔻��̗V��
    const float BLOCK_SIZE;//�u���b�N�̃T�C�Y
    const float MAX_JUMP;//�W�����v�̏��
    bool isJump; //�W�����v���Ă��邩
    bool isRecording_; //Player�̓������L�^���Ă��邩
    float move_; //Y���̈ړ�
    float gravity_; //�d��
    DWORD frameCounter_; //�t���[����
    std::vector<XMFLOAT3>   recordData_;//�v���C���[�̈ʒu���L�^����ϒ��z��


    //Fbx* pFbx;
    int hModel_[2];
    Stage* pStage_;
    //XMFLOAT3 prevPos_; //1�t���[���O�̈ʒu

public:
    XMFLOAT3 stertPos_; //�e���Đ������Ƃ��ɏ����ʒu�ɖ߂邽�߂̕ϐ�


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

    /*bool isCrash(int x, int y);*/
};
