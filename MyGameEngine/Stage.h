#pragma once
#include "Engine/GameObject.h"

class Player;
class Shadow;


//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_[99];
    int shadowCount_;
    bool isOpenWall_;
    

    Player* pPlayer_;
    Shadow* pShadow[6];

public:
    bool isButtonCol_;
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

    //�Ԃ��邩�ǂ���
    bool isCrash(int x , int y);

    void DownButton(int x, int y);

    void OpenWall();
};

