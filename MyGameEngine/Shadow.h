#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"



class Player;

//�����V�[�����Ǘ�����N���X
class Shadow : public GameObject
{
	Player* pPlayer_;

	int hModel_;

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
};

