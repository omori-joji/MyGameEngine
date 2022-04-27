#include "Title.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Title::Title(GameObject* parent)
	: GameObject(parent, "Title"), imageNum_(0), iskeyDown_(false), chengeCount(0)
{
}

//������
void Title::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_[0] = Model::Load("Assets/Title.fbx");
    hModel_[1] = Model::Load("Assets/TitleNowLoding.fbx");
}

//�X�V
void Title::Update()
{
    if (iskeyDown_)
    {
        chengeCount++;
        if (chengeCount >= 30)
        {
            imageNum_++;
            chengeCount = 0;
            if (imageNum_ >= 4)
            {
                imageNum_ = 1;
            }
        }
    }


    if (Input::IsKeyDown(DIK_1))
    {
        iskeyDown_ = true;
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_STAGE1);
    }

    if (Input::IsKeyDown(DIK_2))
    {
        iskeyDown_ = true;
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_STAGE2);
    }

    if (Input::IsKeyDown(DIK_3))
    {
        iskeyDown_ = true;
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_STAGE3);
    }
}

//�`��
void Title::Draw()
{
    Transform trans;
    trans.position_.x = 28 / 2;
    trans.position_.y = 23 / 2;
    trans.position_.z = -21.4;

    trans.Calclation();

    Model::SetTransform(hModel_[imageNum_], trans);
    Model::Draw(hModel_[imageNum_]);
}

//�J��
void Title::Release()
{
}