#include "Title.h"

//�R���X�g���N�^
Title::Title(GameObject* parent)
	: GameObject(parent, "Title"), 
    imageNum_(0),                   //�w�i�̃��f���ԍ�
    stageNum_(0),                   //�ڍs�������X�e�[�W�̃��f���ԍ�
    BACK_GROUND_VERTICAL_(23),      //�w�i��Y���̒l
    BACK_GROUND_BESIDE_(28),        //�w�i��X���̒l
    hModel_(),                      //���f�����i�[����ϐ�
    se_(),                          //SE���i�[����ϐ�
    stageNum_Modele_(),             //�X�e�[�W�ԍ��̃��f�����i�[����ϐ�
    DEPTH_(-17.8f),                 //�w�i�̉��s
    STAGE_NUMBER_VERTICAL_(9.7),    //�X�e�[�W�ԍ�Y���̒l
    STAGE_NUMBER_BESIDE_(17.3),     //�X�e�[�W�ԍ�X���̒l
    SCALE_MAGNIFICATION_(0.6)       //�X�e�[�W�ԍ��̉��s
{
}

//������
void Title::Initialize()
{
    //�T�E���h�t�@�C�������[�h
    se_[SE_NUMBER_2] = Audio::Load("Assets/Sound/StageSelect.wav", 1);

    //���f���f�[�^�̃��[�h
    hModel_[0] = Model::Load("Assets/StageBlock/Title.fbx");
    hModel_[1] = Model::Load("Assets/StageBlock/TitleNowLoading.fbx");

    //Stage�ԍ��̃��f��
    stageNum_Modele_[MODELE_NUMVER_1] = Model::Load("Assets/StageBlock/TitleNumber1.fbx");
    stageNum_Modele_[MODELE_NUMVER_2] = Model::Load("Assets/StageBlock/TitleNumber2.fbx");
    stageNum_Modele_[MODELE_NUMVER_3] = Model::Load("Assets/StageBlock/TitleNumber3.fbx");
    stageNum_Modele_[MODELE_NUMVER_4] = Model::Load("Assets/StageBlock/TitleNumber4.fbx");
}

//�X�V
void Title::Update()
{
    //�\������X�e�[�W�ԍ��̕ϓ�
    //�㉺�L�[�Œl��ς���
    //�Ƃ肠����4�X�e�[�W��
    if (Input::IsKeyDown(DIK_UP) && stageNum_ < 3) stageNum_++;
    if (Input::IsKeyDown(DIK_DOWN) && stageNum_ > 0) stageNum_--;

    //�X�y�[�X�L�[����������
    if (Input::IsKeyDown(DIK_SPACE))
    {
        //����{�^����SE
        Audio::Play(se_[SE_NUMBER_2]);

        //�w�i�̃��f���ԍ���ύX
        imageNum_ = 1;

        //SceneManager�N���X��T��
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        switch (stageNum_)
        {
        //stageNum_�̒l�ɑΉ������X�e�[�W�Ɉڍs
        case MODELE_NUMVER_1: pSceneManager->ChangeScene(SCENE_ID_STAGE1); break;
        case MODELE_NUMVER_2: pSceneManager->ChangeScene(SCENE_ID_STAGE2); break;
        case MODELE_NUMVER_3: pSceneManager->ChangeScene(SCENE_ID_STAGE3); break;
        case MODELE_NUMVER_4: pSceneManager->ChangeScene(SCENE_ID_STAGE4); break;
        }
    }

    //�f�o�b�O�p�̃X�e�[�W�Ɉڍs
    if (Input::IsKeyDown(DIK_1))
    {
        SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_DEBUG);
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
    stageNum.position_.z = DEPTH_ - 0.1;

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