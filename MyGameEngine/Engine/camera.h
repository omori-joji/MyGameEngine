#include "Direct3D.h"
#include <DirectXMath.h>

//���O���
using namespace DirectX;

namespace Camera
{
	void Initialize();								//�������i�v���W�F�N�V�����s��쐬�j
	void Update();									//�X�V�i�r���[�s��쐬�j
	void SetPosition(XMVECTOR position);			//���_�i�J�����̈ʒu�j��ݒ�
	void SetPosition(XMFLOAT3 position);			//SetPosition�ɃA�h���X��n���Z�b�^�[
	void SetTarget(XMVECTOR target);				//�œ_�i����ʒu�j��ݒ�
	void SetTarget(XMFLOAT3 target);				//SetTarget�ɃA�h���X��n���Z�b�^�[
	XMFLOAT3 GetPosition();							//�ʒu�Əœ_�̒l��n���Q�b�^�[
	XMMATRIX GetViewMatrix();						//�r���[�s����擾
	XMMATRIX GetProjectionMatrix();					//�v���W�F�N�V�����s����擾
};

