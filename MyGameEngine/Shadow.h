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



	int hModel_;

	bool isRecording_; //Player�̓������L�^���Ă��邩

	const float sWIDTH;//Player�̕�
	const float sMARGIN;//�����蔻��̗V��


	DWORD frameCounter_;//�t���[����
	std::vector<XMFLOAT3> recordData_;//�v���C���[�̈ʒu���L�^����ϒ��z��

public:


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

