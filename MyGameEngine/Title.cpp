#include "Title.h"

//コンストラクタ
Title::Title(GameObject* parent)
	: GameObject(parent, "Title"), 
    imageNum_(0),
    stageNum_(0),
    chengeCount_(0),
    hModel_(),
    se_(),
    stageNum_Modele_(),
    BACK_GROUND_VERTICAL_(23),
    BACK_GROUND_BESIDE_(28),
    DEPTH_(-17.8f),
    STAGE_NUMBER_VERTICAL_(9.7),
    STAGE_NUMBER_BESIDE_(17.3),
    SCALE_MAGNIFICATION_(0.6),
    iskeyDown_(false)
{
}

//初期化
void Title::Initialize()
{
    //se_[0] = Audio::Load("Assets/Sound/StegeSelectMove.wav", 2);
    se_[SE_NUMBER_2] = Audio::Load("Assets/Sound/StageSelect.wav", 1);

    //モデルデータのロード
    hModel_[0] = Model::Load("Assets/StageBlock/Title.fbx");
    hModel_[1] = Model::Load("Assets/StageBlock/TitleNowLoading.fbx");

    stageNum_Modele_[MODELE_NUMVER_1] = Model::Load("Assets/StageBlock/TitleNumber1.fbx");
    stageNum_Modele_[MODELE_NUMVER_2] = Model::Load("Assets/StageBlock/TitleNumber2.fbx");
    stageNum_Modele_[MODELE_NUMVER_3] = Model::Load("Assets/StageBlock/TitleNumber3.fbx");
    stageNum_Modele_[MODELE_NUMVER_4] = Model::Load("Assets/StageBlock/TitleNumber4.fbx");
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
        Audio::Play(se_[SE_NUMBER_2]);
        imageNum_ = 1;
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        switch (stageNum_)
        {
        case MODELE_NUMVER_1: pSceneManager->ChangeScene(SCENE_ID_STAGE1); break;
        case MODELE_NUMVER_2: pSceneManager->ChangeScene(SCENE_ID_STAGE2); break;
        case MODELE_NUMVER_3: pSceneManager->ChangeScene(SCENE_ID_STAGE3); break;
        case MODELE_NUMVER_4: pSceneManager->ChangeScene(SCENE_ID_STAGE4); break;
        }
    }
}

//描画
void Title::Draw()
{
    Transform trans, stageNum;
    trans.position_.x = BACK_GROUND_BESIDE_ / 2;
    trans.position_.y = BACK_GROUND_VERTICAL_ / 2;
    trans.position_.z = DEPTH_;
    trans.Calclation();

    Model::SetTransform(hModel_[imageNum_], trans);
    Model::Draw(hModel_[imageNum_]);


    stageNum.position_.x = STAGE_NUMBER_BESIDE_;
    stageNum.position_.y = STAGE_NUMBER_VERTICAL_;
    stageNum.position_.z = DEPTH_ - 0.1;
    stageNum.scale_.x = SCALE_MAGNIFICATION_;
    stageNum.scale_.y = SCALE_MAGNIFICATION_;
    stageNum.Calclation();

    Model::SetTransform(stageNum_Modele_[stageNum_], stageNum);
    Model::Draw(stageNum_Modele_[stageNum_]);
}

//開放
void Title::Release()
{
}