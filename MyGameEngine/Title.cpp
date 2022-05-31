#include "Title.h"

//�R���X�g���N�^
Title::Title(GameObject* parent)
	: GameObject(parent, "Title"), 
    imageNum_(0),                   //�w�i�̃��f���ԍ�
    stageNum_(0),                   //�ڍs�������X�e�[�W�̃��f���ԍ�
    BACK_GROUND_VERTICAL_(22.0f),   //�w�i��Y���̒l
    BACK_GROUND_BESIDE_(28.0f),     //�w�i��X���̒l
    hModel_(),                      //���f�����i�[����ϐ�
    se_(),                          //SE���i�[����ϐ�
    stageNum_Modele_(),             //�X�e�[�W�ԍ��̃��f�����i�[����ϐ�
    DEPTH_(-17.9f),                 //�w�i�̉��s
    DEPTH_DIFFERRENCE_(0.1f),       //�w�i�Ƃ̉��s�̍�
    STAGE_NUMBER_VERTICAL_(9.7f),   //�X�e�[�W�ԍ�Y���̒l
    STAGE_NUMBER_BESIDE_(17.3f),    //�X�e�[�W�ԍ�X���̒l
    SCALE_MAGNIFICATION_(0.6f),     //�X�e�[�W�ԍ��̉��s
    FILE_PAS_("Assets/Title/")      //Title�̃��f���f�[�^�̃t�@�C���p�X
{
}

//������
void Title::Initialize()
{
    //�T�E���h�t�@�C�������[�h
    se_[SE_DECISION] = Audio::Load("Assets/Sound/StageSelect.wav", 1);
    se_[SOUND_BGM] = Audio::Load("Assets/Sound/TitleBGM.wav", 1);

    //���f���f�[�^�̃��[�h
    hModel_[BACKGROUND] = Model::Load(FILE_PAS_ + "TitleBG_01.fbx");
    hModel_[BACKGROUND_NOWLOADING] = Model::Load(FILE_PAS_ + "TitleBG_02.fbx");

    //�X�e�[�W�i���o�[�̃��f�������[�h
    for (int i = 0; i < STAGE_NUMBER_MAX; i++)
    {
        char fileName[MAX_PATH];
        wsprintf(fileName, "%sStageNumber%d.fbx", FILE_PAS_.c_str(), (i + 1));
        stageNum_Modele_[i] = Model::Load(fileName);
    }
}

//�X�V
void Title::Update()
{
    Audio::Play(se_[SOUND_BGM]);
    //�\������X�e�[�W�ԍ��̕ϓ�
    //�㉺�L�[�Œl��ς���
    //�Ƃ肠����4�X�e�[�W��
    if (Input::IsKeyDown(DIK_UP) && stageNum_ < 3) stageNum_++;
    if (Input::IsKeyDown(DIK_DOWN) && stageNum_ > 0) stageNum_--;

    //�X�y�[�X�L�[����������
    if (Input::IsKeyDown(DIK_SPACE))
    {
        //����{�^����SE
        Audio::Play(se_[SE_DECISION]);

        //�w�i�̃��f���ԍ���ύX
        imageNum_ = 1;

        //SceneManager�N���X��T��
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");

        //���݂̃X�e�[�W�ԍ��ɑΉ������X�e�[�W�Ɉڍs
        pSceneManager->ChangeScene((SCENE_ID)stageNum_);
    }
}

//�`��
void Title::Draw()
{
    //�w�i�̕`��
    Transform trans, stageNum;

    //�w�i�̈ʒu����
    trans.position_.x = BACK_GROUND_BESIDE_ / 2;
    trans.position_.y = BACK_GROUND_VERTICAL_ / 2;
    trans.position_.z = DEPTH_;

    //���[���h�s��
    trans.Calclation();

    //�`��J�n
    Model::SetTransform(hModel_[imageNum_], trans);
    Model::Draw(hModel_[imageNum_]);


    //�X�e�[�W�ԍ��̈ʒu����
    stageNum.position_.x = STAGE_NUMBER_BESIDE_;
    stageNum.position_.y = STAGE_NUMBER_VERTICAL_;
    stageNum.position_.z = DEPTH_ - DEPTH_DIFFERRENCE_;

    //�T�C�Y���w��
    stageNum.scale_.x = SCALE_MAGNIFICATION_;
    stageNum.scale_.y = SCALE_MAGNIFICATION_;
    //���[���h�s��
    stageNum.Calclation();

    //�`��J�n
    Model::SetTransform(stageNum_Modele_[stageNum_], stageNum);
    Model::Draw(stageNum_Modele_[stageNum_]);
}

//�J��
void Title::Release()
{
}