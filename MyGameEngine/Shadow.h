#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Fbx.h"
#include "Basic.h"
#include <string>

//�N���X�̑O���錾
class Player;
class Stage;

//Shadow���Ǘ�����N���X
class Shadow : public Basic
{
	//�萔�錾
	const char RESET_VALU_;						//�������p
	const int MATCH_VALU_;						//�z��̗v�f�������킹�邽�߂̒l
	const float BACK_DRAW_;						//Player�ɏd�Ȃ�Ȃ��悤�ɏ������ɕ`�悷��
	const string filePas_;						//���f�����ۑ�����Ă���t�@�C���p�X

	//�ϐ��錾
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

	enum
	{
		SDIR_RIGHT,								//�E����
		SDIR_LEFT,								//������
		SDIR_MAX,								//�z��̍ő�v�f��

		STANDING_MODEL = 0,						//�����Ă��郂�f���ԍ�
		RUN_MODEL,								//�����Ă��郂�f���ԍ�
	};
	int hModel_[SDIR_MAX][SDIR_MAX];			//�e�̃��f�����i�[���鑽�����z��

public:
	Shadow(GameObject* parent);					//�R���X�g���N�^
	void Initialize() override;					//������
	void Update() override;						//�X�V
	void Draw() override;						//�`��
	void Release() override;					//�J��
	void ShadowIsPlayFlag();					//�e�̕\����\���A�Đ������L�^���������Ǘ�����֐�
private:
	void AllFind();								//Find�������܂Ƃ߂�֐�
	void RecordingandPlayBack();				//Player�̓������L�^�ƍĐ�����֐�
};

