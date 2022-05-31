#include "Title.h"

//コンストラクタ
Title::Title(GameObject* parent)
	: GameObject(parent, "Title"), 
    imageNum_(0),                   //背景のモデル番号
    stageNum_(0),                   //移行したいステージのモデル番号
    BACK_GROUND_VERTICAL_(22.0f),   //背景のY軸の値
    BACK_GROUND_BESIDE_(28.0f),     //背景のX軸の値
    hModel_(),                      //モデルを格納する変数
    se_(),                          //SEを格納する変数
    stageNum_Modele_(),             //ステージ番号のモデルを格納する変数
    DEPTH_(-17.9f),                 //背景の奥行
    DEPTH_DIFFERRENCE_(0.1f),       //背景との奥行の差
    STAGE_NUMBER_VERTICAL_(9.7f),   //ステージ番号Y軸の値
    STAGE_NUMBER_BESIDE_(17.3f),    //ステージ番号X軸の値
    SCALE_MAGNIFICATION_(0.6f),     //ステージ番号の奥行
    FILE_PAS_("Assets/Title/")      //Titleのモデルデータのファイルパス
{
}

//初期化
void Title::Initialize()
{
    //サウンドファイルをロード
    se_[SE_DECISION] = Audio::Load("Assets/Sound/StageSelect.wav", 1);
    se_[SOUND_BGM] = Audio::Load("Assets/Sound/TitleBGM.wav", 1);

    //モデルデータのロード
    hModel_[BACKGROUND] = Model::Load(FILE_PAS_ + "TitleBG_01.fbx");
    hModel_[BACKGROUND_NOWLOADING] = Model::Load(FILE_PAS_ + "TitleBG_02.fbx");

    //ステージナンバーのモデルをロード
    for (int i = 0; i < STAGE_NUMBER_MAX; i++)
    {
        char fileName[MAX_PATH];
        wsprintf(fileName, "%sStageNumber%d.fbx", FILE_PAS_.c_str(), (i + 1));
        stageNum_Modele_[i] = Model::Load(fileName);
    }
}

//更新
void Title::Update()
{
    Audio::Play(se_[SOUND_BGM]);
    //表示するステージ番号の変動
    //上下キーで値を変える
    //とりあえす4ステージ分
    if (Input::IsKeyDown(DIK_UP) && stageNum_ < 3) stageNum_++;
    if (Input::IsKeyDown(DIK_DOWN) && stageNum_ > 0) stageNum_--;

    //スペースキーを押したら
    if (Input::IsKeyDown(DIK_SPACE))
    {
        //決定ボタンのSE
        Audio::Play(se_[SE_DECISION]);

        //背景のモデル番号を変更
        imageNum_ = 1;

        //SceneManagerクラスを探す
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");

        //現在のステージ番号に対応したステージに移行
        pSceneManager->ChangeScene((SCENE_ID)stageNum_);
    }
}

//描画
void Title::Draw()
{
    //背景の描画
    Transform trans, stageNum;

    //背景の位置決定
    trans.position_.x = BACK_GROUND_BESIDE_ / 2;
    trans.position_.y = BACK_GROUND_VERTICAL_ / 2;
    trans.position_.z = DEPTH_;

    //ワールド行列
    trans.Calclation();

    //描画開始
    Model::SetTransform(hModel_[imageNum_], trans);
    Model::Draw(hModel_[imageNum_]);


    //ステージ番号の位置決定
    stageNum.position_.x = STAGE_NUMBER_BESIDE_;
    stageNum.position_.y = STAGE_NUMBER_VERTICAL_;
    stageNum.position_.z = DEPTH_ - DEPTH_DIFFERRENCE_;

    //サイズも指定
    stageNum.scale_.x = SCALE_MAGNIFICATION_;
    stageNum.scale_.y = SCALE_MAGNIFICATION_;
    //ワールド行列
    stageNum.Calclation();

    //描画開始
    Model::SetTransform(stageNum_Modele_[stageNum_], stageNum);
    Model::Draw(stageNum_Modele_[stageNum_]);
}

//開放
void Title::Release()
{
}