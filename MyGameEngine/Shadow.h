#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Player.h"
#include "Stage.h"

//�N���X�̑O���錾
class Player;
class Stage;


//Shadow���Ǘ�����N���X
class Shadow : public GameObject
{
	const int RESET_VALU_;						//�������p
	const int ALL_GIMICKS_;						//������ނ̃M�~�b�N���ׂĂ�T�����߂̒l
	const int MEANTIME_BUTTON_DOWN_;			//����ł���Ԕ�������{�^���̃��f���ԍ�
	const int MEANTIME_BLOCK_ALPHA_;			//�J���Ă���ǂ̃��f���ԍ�
	const int MATCH_VALU_;						//�z��̗v�f�������킹�邽�߂̒l
	const int SHADOW_FOOT_;						//�e�̑��������邽�߂̒l
	const float BACK_DRAW_;						//Player�ɏd�Ȃ�Ȃ��悤�ɏ������ɕ`�悷��

	int shadowDirection_;						//�e�̌���
	int shadowModelNumber_;						//�����Ă��郂�f���ԍ�
	DWORD frameCounter_;						//�t���[����

	bool isRecording_;							//�L�^�����ǂ���
	bool isShadowPastButton;					//�{�^���𓥂�ł��邩

	std::vector<int> recordDirection_;			//Player�̌������L�^���铮�I�z��
	std::vector<int> recordModelNumber_;		//�����Ă��郂�f���ԍ����L�^���铮�I�z��
	std::vector<XMFLOAT3> recordData_;			//�v���C���[�̈ʒu���L�^����ϒ��z��

	Player* pPlayer_;							//Player�̏�񂪓���ϐ�
	Stage* pStage_;								//Stage�̏�񂪓���ϐ�

	enum ShadowDirection
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
	bool GetIsRecording();						//isRecording_��Ԃ����߂̃Q�b�^�[

private:
	void AllFind();								//Find�������܂Ƃ߂�֐�
	void RecordingandPlayBack();				//Player�̓������L�^�ƍĐ�����֐�
	void ShadowFootButtonCheck();				//���������ă{�^���𓥂񂾏u�ԁA���ꂽ�u�Ԃ̏���������֐�
};

