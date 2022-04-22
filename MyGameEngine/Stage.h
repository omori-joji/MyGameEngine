#pragma once
#include "Engine/GameObject.h"

//�N���X�̑O���錾
class Player;
class Shadow;


//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_[500];
    int shadowCount_;
    int timeCount_;
    int hSound_;

    bool isOpenWall_;
    bool isBlinking_;
    

    Player* pPlayer_;
    Shadow* pShadow[6];




public:


    int map_[20][12];
    XMFLOAT3 stertPos;



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

    void ModelLoad();

    //�Ԃ��邩�ǂ���
    bool isCrash(int x , int y);

    void DownButton(int x, int y);

    void OpenWall();

    void CheckBlock(int find , bool which);

    void Blinking(int blockNum, int time);

    void WarpBlock(int x, int y);

    void GoalCol(int x, int y);
};

