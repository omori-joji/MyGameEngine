#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"


//�N���X�̑O���錾
class Player;
class Stage;


//Shadow���Ǘ�����N���X
class Shadow : public GameObject
{
	int hModel_[2][2];							//�e�̃��f�����i�[���鑽�����z��
	int shadowDirection_;						//�e�̌���
	int shadowModelNumber_;						//�����Ă��郂�f���ԍ�


	DWORD frameCounter_;						//�t���[����


	std::vector<XMFLOAT3> recordData_;			//�v���C���[�̈ʒu���L�^����ϒ��z��
	std::vector<int> recordDirection_;			//Player�̌������L�^���铮�I�z��
	std::vector<int> recordModelNumber_;		//�����Ă��郂�f���ԍ����L�^���铮�I�z��


	Player* pPlayer_;							//Player�̏�񂪓���ϐ�
	Stage* pStage_;								//Stage�̏�񂪓���ϐ�


public:
	bool isRecording_;							//�L�^�����ǂ���

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Shadow(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//Find�������܂Ƃ߂�֐�
	void AllFind();

	//Player�̓������L�^�ƍĐ�����֐�
	void RecordingandPlayBack();


	//�e�̕\����\�����Ǘ�����֐�
	//���̂ق��ɂ��Đ������L�^�����𔻒f���鏈�����s��
	void ShadowDisplayFlag();
};

