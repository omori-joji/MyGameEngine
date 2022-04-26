#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"



class Player;
class Stage;

//�����V�[�����Ǘ�����N���X
class Shadow : public GameObject
{
	Player* pPlayer_;//Player�̏�񂪓���ϐ�
	Stage* pStage_;//Stage�̏�񂪓���ϐ�



	int hModel_Right_[2]; //�E�������Ă��郂�f��
	int hModel_Left_[2];  //���������Ă��郂�f��
	int leftModel_;       //���̃��f���ԍ�
	int rightModel_;      //�E�̃��f���ԍ�
	int sMemory;

	
	bool isRecordCheck_;  //�v���C���[���E�������Ă��邩���������Ă��邩

	const float sWIDTH;//�e�̕�
	const float sMARGIN;//�����蔻��̗V��


	DWORD frameCounter_;//�t���[����
	std::vector<XMFLOAT3> recordData_;//�v���C���[�̈ʒu���L�^����ϒ��z��
	std::vector<bool> recordCheck_;   //�L�^����Ă���t���[�����̎��v���C���[�͂ǂ����Ɍ����Ă��邩
	std::vector<int> recordRightMove_;//�E�̃��f���ԍ����L�^����
	std::vector<int> recordLeftMove_;//���̃��f���ԍ����L�^����



public:
	bool isRecording_; //Player�̓������L�^���Ă��邩

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

	void Collision();

	void Flag();
};

