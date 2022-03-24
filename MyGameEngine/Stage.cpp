#include "Stage.h"
#include "Engine/Model.h"
#include "Player.h"
#include "Engine/CsvReader.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")//, hModel_(-1)
{
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    hModel_[0] = Model::Load("Assets/BlueBlock.fbx");
    hModel_[1] = Model::Load("Assets/YellowBlock.fbx");
    hModel_[2] = Model::Load("Assets/GreenBlock.fbx");
    hModel_[3] = Model::Load("Assets/PushButton.fbx");
    hModel_[4] = Model::Load("Assets/PushButton2.fbx");


    //Csv�t�@�C���̓ǂݍ���
    CsvReader csv;
    csv.Load("Assets/Stage1.csv");


    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            map_[x][y] = csv.GetValue(x, 9 - y); //�G�N�Z������y�̒l���t�Ȃ̂�-9�����Ă�����

            if (map_[x][y] == 99)
            {
                Player* pPlayer = (Player*)Instantiate<Player>(this->pParent_);
                pPlayer->transform_.position_.x = x;
                pPlayer->transform_.position_.y = y;
            }
        }
    }
}

//�X�V
void Stage::Update()
{

}

//�`��
void Stage::Draw()
{
    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            if (map_[x][y] == 0 || map_[x][y] == 99)
            {
                continue;
            }

            int type = map_[x][y] - 1;
            Transform trans;
            trans.position_.x = x;
            trans.position_.y = y;
            trans.Calclation();



            Model::SetTransform(hModel_[type], trans);
            Model::Draw(hModel_[type]);
        }
    }
}

//�J��
void Stage::Release()
{
}

//���̃}�X�ɏ�Q�������邩�ǂ���
//�߂�l�A��������true,�����Ȃ�false
bool Stage::isCrash(int x, int y)
{
    //�z���1�������Ă���Βʂ�Ȃ�
    if (map_[x][y] == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Stage::Button(int x, int y)
{
    //�����O�̃{�^����Ԃ�
    if(map_[x][y] == 4)
    {
        map_[x][y] = 5;
    }
}

void Stage::Down(int x, int y)
{
    
}
