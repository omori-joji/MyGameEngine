#pragma once
#include "Engine/GameObject.h"

class Player;


//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_[7];
    bool isOpenWall_;

    Player* pPlayer_;

public:

    int map_[20][10];

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

