#include "Camera.h"

namespace Camera
{
	//�ϐ�
	XMVECTOR position_;		//�J�����̈ʒu�i���_�j
	XMVECTOR target_;		//����ʒu�i�œ_�j
	XMMATRIX viewMatrix_;	//�r���[�s��
	XMMATRIX projMatrix_;	//�v���W�F�N�V�����s��
}

//������
void Camera::Initialize()
{
	//�J�������X�e�[�W�̒����ɏo������
	//��
	//�c
	int x = 28;
	int y = 23;

	//�����l��ݒ�
	//�J�����̈ʒu
	position_ = XMVectorSet((x / 2), (y / 2), -25, 0);

	//�J�����̏œ_
	target_ = XMVectorSet((x/2), (y / 2), 0, 0);

	//�v���W�F�N�V�����s��̏��������s����֐�
	//������(��p, �A�X�y�N�g��, ���̒l���߂����͉̂f��Ȃ�, ���̒l��艓�����͉̂f��Ȃ�)
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)800 / (FLOAT)600, 0.1f, 100.0f);

	//�r���[�s��̍쐬
	//������(�J�����̈ʒu, �œ_, ������̃x�N�g��)
	//�J�����̈ʒu�͕ς�邱�Ƃ��Ȃ��̂�Initialize�ŏ������Ă���
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
}

//�X�V
void Camera::Update()
{
}

//�ʒu��ݒ�
void Camera::SetPosition(XMVECTOR position)
{
	//�����ɓn���ꂽposition�Ɉʒu��ύX����
	position_ = position;
}

void Camera::SetPosition(XMFLOAT3 position)
{
	//�ʒu��n��
	SetPosition(XMLoadFloat3(&position));
}

//void Camera::SetPosition(float x, float y, float z)
//{
//}

XMFLOAT3 Camera::GetPosition()
{
	XMFLOAT3 f;
	XMVECTOR v = XMLoadFloat3(&f);
	return f;
}

//�œ_��ݒ�
void Camera::SetTarget(XMVECTOR target)
{
	target_ = target;
}

//�œ_�̃A�h���X��SetTarget�̈����ɓn��
void Camera::SetTarget(XMFLOAT3 target)
{
	SetTarget(XMLoadFloat3(&target));
}

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix()
{
	return viewMatrix_;
}

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix()
{
	return projMatrix_;
}