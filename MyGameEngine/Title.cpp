#include "Title.h"

//コンストラクタ
Title::Title(GameObject* parent)
	: GameObject(parent, "Title"), 
    imageNum_(0),
    iskeyDown_(false),
    chengeCount(0),
    hModel_(),
    stageNumModel_(),
    stageNum_(0),
    se_()
{
}

//初期化
void Title::Initialize()
{
    //se_[0] = Audio::Load("Assets/Sound/StegeSelectMove.wav", 2);
    se_[1] = Audio::Load("Assets/Sound/StageSelect.wav", 1);

    //モデルデータのロード
    hModel_[0] = Model::Load("Assets/StageBlock/Title.fbx");
    hModel_[1] = Model::Load("Assets/StageBlock/TitleNowLoading.fbx");
    hModel_[2] = Model::Load("Assets/StageBlock/TitleNumber1.fbx");

    stageNumModel_[0] = Model::Load("Assets/StageBlock/TitleNumber1.fbx");
    stageNumModel_[1] = Model::Load("Assets/StageBlock/TitleNumber2.fbx");
    stageNumModel_[2] = Model::Load("Assets/StageBlock/TitleNumber3.fbx");
    stageNumModel_[3] = Model::Load("Assets/StageBlock/TitleNumber4.fbx");
}

//更新
void Title::Update()
{
    if (Input::IsKeyDown(DIK_UP) && stageNum_ < 3)
    {
        //Audio::Play(se_[0]);
        stageNum_++;
    }
    if (Input::IsKeyDown(DIK_DOWN) && stageNum_ > 0)
    {
        //Audio::Play(se_[0]);
        stageNum_--;
    }

    if (Input::IsKeyDown(DIK_SPACE))
    {
        Audio::Play(se_[1]);
        imageNum_ = 1;
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        switch (stageNum_)
        {
        case 0:pSceneManager->ChangeScene(SCENE_ID_STAGE1); break;
        case 1:pSceneManager->ChangeScene(SCENE_ID_STAGE2); break;
        case 2:pSceneManager->ChangeScene(SCENE_ID_STAGE3); break;
        case 3:pSceneManager->ChangeScene(SCENE_ID_STAGE4); break;
        }
    }
}

//描画
void Title::Draw()
{
    Transform trans;
    trans.position_.x = 28 / 2;
    trans.position_.y = 23 / 2;
    trans.position_.z = -17.8;
    trans.Calclation();

    Model::SetTransform(hModel_[imageNum_], trans);
    Model::Draw(hModel_[imageNum_]);



    Transform stageNum;
    stageNum.position_.x = 17.3;
    stageNum.position_.y = 9.7;
    stageNum.position_.z = -17.9;
    stageNum.scale_.x = 0.6;
    stageNum.scale_.y = 0.6;
    stageNum.Calclation();

    Model::SetTransform(stageNumModel_[stageNum_], stageNum);
    Model::Draw(stageNumModel_[stageNum_]);
}

//開放
void Title::Release()
{
}