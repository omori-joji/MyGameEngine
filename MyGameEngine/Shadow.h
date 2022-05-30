#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Fbx.h"
#include "Actor.h"
#include <string>

//�N���X�̑O���錾
class Player;
class Stage;

//Shadow���Ǘ�����N���X
class Shadow : public Actor
{
	const int MATCH_VALU_;						//�z��̗v�f�������킹�邽�߂̒l
	const char RESET_VALU_;						//�������p
	const float BACK_DRAW_;						//Player�ɏd�Ȃ�Ȃ��悤�ɏ������ɕ`�悷��
	const string filePas_;						//���f�����ۑ�����Ă���t�@�C���p�X
	char shadowDirection_;						//�e�̌���
	char shadowModelNumber_;					//�����Ă��郂�f���ԍ�
	bool isRecording_;							//�L�^�����ǂ���
	DWORD frameCounter_;						//�t���[����
	Player* pPlayer_;							//Player�̏�񂪓���ϐ�
	Stage* pStage_;								//Stage�̏�񂪓���ϐ�

	//�ϒ��z��
	std::vector<int> recordDirection_;			//Player�̌������L�^���铮�I�z��
	std::vector<int> recordModelNumber_;		//�����Ă��郂�f���ԍ����L�^���铮�I�z��
	std::vector<XMFLOAT3> recordData_;			//�v���C���[�̈ʒu���L�^����ϒ��z��

	//�e�̃��f���ԍ�
	enum S_Model
	{
		S_DIR_RIGHT,							//�E����
		S_DIR_LEFT,								//������
		S_DIRMAX,								//�z��̍ő�v�f��

		STANDING_MODEL = 0,						//�����Ă��郂�f���ԍ�
		RUN_MODEL,								//�����Ă��郂�f���ԍ�
	}s_Modele;
	int hModel_[S_DIRMAX][S_DIRMAX];			//�e�̃��f�����i�[���鑽�����z��
public:
	Shadow(GameObject* parent);					//�R���X�g���N�^
	void Initialize() override;					//������
	void Update() override;						//�X�V
	void Draw() override;						//�`��
	void Release() override;					//�J��

	//�e�̕\����\���A�Đ������L�^���������Ǘ�����֐�
	//�����F�Ȃ�
	//�߂�l�F�Ȃ�
	void ShadowIsPlayFlag();
private:
	//Find�������܂Ƃ߂�֐�
	//�����F�Ȃ�
	//�߂�l�F�Ȃ�
	void AllFind();

	//Player�̓������L�^�ƍĐ�����֐�
	//�����F�Ȃ�
	//�߂�l�F�Ȃ�
	void RecordingandPlayBack();
};

