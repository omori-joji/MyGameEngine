#pragma once
#include <DirectXMath.h>

//���O���
using namespace DirectX;

//�ʒu�A�����A�g�嗦�Ȃǂ��Ǘ�����N���X
class Transform
{
	XMMATRIX matTranslate_;		//�ړ��s��
	XMMATRIX matRotate_;		//��]�s��	
	XMMATRIX matScale_;			//�g��s��

public:
	Transform();				//�R���X�g���N�^
	~Transform();				//�f�X�g���N�^
	void Calclation();			//�e�s��̌v�Z

	//����̒l��ς��Ċe�s���������̂�public�ɂ��Ă���
	XMFLOAT3  position_;		//�ʒu
	XMFLOAT3  rotate_;			//����
	XMFLOAT3  scale_;			//�g�嗦

	//�Q�b�^�[
	XMMATRIX GetWorldMatrix();	//���[���h�s���n���Q�b�^�[
	XMMATRIX GetNormalmatrix();	//���K�s���n���Q�b�^�[
};