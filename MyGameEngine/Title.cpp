#include "Title.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Title::Title(GameObject* parent)
	: GameObject(parent, "Title"), imageNum_(0), iskeyDown_(false), chengeCount(0),hModel_()
{
}

//������
void Title::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_[0] = Model::Load("Assets/StageBlock/Title.fbx");
    hModel_[1] = Model::Load("Assets/StageBlock/TitleNowLoading.fbx");
}

//�X�V
void Title::Update()
{


    if (Input::IsKeyDown(DIK_1))
    {
        imageNum_ = 1;
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_STAGE1);
    }

    if (Input::IsKeyDown(DIK_2))
    {
        imageNum_ = 1;
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_STAGE2);
    }

    if (Input::IsKeyDown(DIK_3))
    {
        imageNum_ = 1;
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_STAGE3);
    }

    if (Input::IsKeyDown(DIK_4))
    {
        imageNum_ = 1;
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_STAGE4);
    }
}

//�`��
void Title::Draw()
{
    Transform trans,stage;
    trans.position_.x = 28 / 2;
    trans.position_.y = 23 / 2;
    trans.position_.z = -17.8;
    trans.Calclation();

    Model::SetTransform(hModel_[imageNum_], trans);
    Model::Draw(hModel_[imageNum_]);
}

//�J��
void Title::Release()
{
}